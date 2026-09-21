// [트레이 데이터] 검사 데이터 초기화, CELL SERIAL 복사, .Tray 임시 파일 저장/복원/삭제.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

//---------------------------------------------------------------------------
// 새 트레이 검사 데이터 초기화: 문자열/숫자/배열과 수신 표시를 지운다. 투입 이후 화면은 공란이다.
void __fastcall TTotalForm::InitTrayStruct()
{
    // [CELL SERIAL 공통] 이전 결과 저장 대기를 취소하고 이번 트레이의 수신 방식을 확정한다.
    CancelResultCellSerialRead();
    ApplyCellSerialReadMode();
    // 문자열은 대입으로, 숫자/배열은 명시적으로 초기화한다.
    // 구형 BCC32의 TRAY_INFO() 임시 객체 초기화에 의존하지 않는다.
    tray.ams = false;
    tray.amf = false;
    tray.trayid = "start";
    tray.cell_type = "";
    tray.lotid = "";
    tray.arrive = "";
    tray.finish = "";
    tray.cell_model = "";
    tray.lot_number = "";
    tray.cell_count = 0;
    tray.rem_mode = 0;
    tray.first = true;
    tray.ir_range = tray.ir_sigma = tray.ir_avg = tray.ir_avgAll = 0;
    tray.ocv_range = tray.ocv_sigma = tray.ocv_avg = tray.ocv_avgAll = 0;
    tray.ir_avgAll_count = tray.ocv_avgAll_count = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        tray.cell[i] = 1;
        tray.cell_serial[i] = "";
        tray.precharger[i] = "";
        tray.precharge_volt[i] = "";
        tray.orginal_value[i] = 0;
        tray.after_value[i] = 0;
        tray.ocv_value[i] = 0;
        tray.Cali_value[i] = 0;
        tray.measure_result[i] = 0;
        tray.ir_flag[i] = false;
        tray.ocv_flag[i] = false;
    }
    memset(&retest, 0, sizeof(retest)); // REMEASURE는 숫자/bool 배열만 포함한다.
    NgCount = 0;
    InitCellDisplay();
	this->WriteRemeasureInfo();

	pWork->Visible = false;
	pWork->BringToFront();
}

//---------------------------------------------------------------------------
// 수신 버퍼의 400셀 시리얼을 복사하고 비어 있지 않은 개수를 반환한다. 완료 판정은 호출부에서 한다.
int __fastcall TTotalForm::ReadCellSerial()
{
    int count = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        tray.cell_serial[i] = Mod_PLC->GetCellSrial(
            PLC_D_IROCV_CELL_SERIAL, i, PLC_D_CELL_SERIAL_WORDS_PER_CHANNEL);
        if(!tray.cell_serial[i].IsEmpty()) ++count;
    }
    return count;
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] false=TRAY IN 보관, true=상시 수신 + 결과 직전 새 수신.
// 현재 트레이에 적용한 값은 INI 설정과 분리하여 운전 도중 변경하지 않는다.
void __fastcall TTotalForm::ApplyCellSerialReadMode()
{
    cellSerialContinuousReadForTray = config.cell_serial_continuous_read;
    Mod_PLC->SetCellSerialContinuousRead(cellSerialContinuousReadForTray);
    WritePLCLog("CELL SERIAL MODE", cellSerialContinuousReadForTray
        ? "Continuous read / refresh before result save" : "TRAY IN capture / use saved serial");
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 요청 이후에 시작한 4,010워드 전체 수신까지 결과 저장을 보류한다.
// UI/소켓 처리를 막지 않으며 수동 모드에서도 전용 타이머가 동작한다.
void __fastcall TTotalForm::StartResultCellSerialRead()
{
    resultCellSerialPending = true;
    resultCellSerialError = false;
    resultCellSerialStartTime = GetTickCount();
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->StartCellSerialRead();
    Timer_ResultCellSerial->Enabled = true;
    Panel_State->Caption = " Reading CELL SERIAL before result save ... ";
    WritePLCLog("CELL SERIAL", "Continuous mode: request final complete read before result save");
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 시간 초과/개수 불일치는 결과 저장과 자동 배출을 보류한다.
// SAVE=완료 데이터 운영자 승인 저장, CANCEL=새 전체 수신 재시도.
void __fastcall TTotalForm::ShowResultCellSerialError(AnsiString reason)
{
    Timer_ResultCellSerial->Enabled = false;
    resultCellSerialError = true;
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
    DisplayStatus(nEND);
    Panel_State->Caption = " CELL SERIAL error - result save waiting ... ";
    WritePLCLog("CELL SERIAL ERROR", reason);
    Form_CellIdError->ChangeMessage("CELL SERIAL - RESULT SAVE", reason,
        "SAVE: use completed data / CANCEL: read again");
    Form_CellIdError->DisplayErrorMessage(this->Tag);
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 완료본을 트레이에 복사한다. 상시 모드는 이전 .Tray 파일로 덮어쓰지 않는다.
// SAVE 승인도 전체 수신 전에는 허용하지 않아 이전 트레이/조각 데이터를 결과에 넣지 않는다.
void __fastcall TTotalForm::CompleteResultCellSerialRead(bool operatorOverride)
{
    if(!resultCellSerialPending) return;
    if(!Mod_PLC->IsCellSerialReadComplete())
    {
        ShowResultCellSerialError("No complete CELL SERIAL data. Select CANCEL to read again.");
        return;
    }
    const int serialCount = ReadCellSerial();
    // 수동 전체 측정도 같은 기준을 쓴다. 수동 초기화에서는 cell_count 캐시가 0일 수 있다.
    int cellCount = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
        if(tray.cell[i] == 1) ++cellCount;
    if(!operatorOverride && serialCount != cellCount)
    {
        ShowResultCellSerialError("Serial count " + IntToStr(serialCount)
            + " / Cell count " + IntToStr(cellCount));
        return;
    }
    Timer_ResultCellSerial->Enabled = false;
    WritePLCLog("CELL SERIAL", (operatorOverride ? AnsiString("Operator SAVE: ") : AnsiString("Final read OK: "))
        + IntToStr(serialCount) + " / " + IntToStr(cellCount));
    SaveTrayInfo(tray.trayid);
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
    SaveMeasurementResult();
    resultCellSerialPending = false;
    resultCellSerialError = false;
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 완료를 먼저 확인하고 미완료면 요청 후 10초에 오류로 전환한다.
// unsigned 경과시간 계산은 GetTickCount의 약 49일 주기 순환도 처리한다.
void __fastcall TTotalForm::Timer_ResultCellSerialTimer(TObject *Sender)
{
    Timer_ResultCellSerial->Enabled = false;
    if(!resultCellSerialPending || resultCellSerialError) return;
    try
    {
        if(Mod_PLC->IsCellSerialReadComplete())
            CompleteResultCellSerialRead(false);
        else if(static_cast<DWORD>(GetTickCount() - resultCellSerialStartTime) >= 10000)
            ShowResultCellSerialError("CELL SERIAL final read timeout (10 seconds).");
    }
    catch(const Exception &error)
    {
        StopAutoInspectionOnError(error.Message);
    }
    catch(...)
    {
        StopAutoInspectionOnError("Unknown CELL SERIAL result save error");
    }
    Timer_ResultCellSerial->Enabled = resultCellSerialPending && !resultCellSerialError;
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 초기화/재시작/강제 배출 후 늦게 도착한 응답이 결과를 저장하지 못하게 한다.
void __fastcall TTotalForm::CancelResultCellSerialRead()
{
    Timer_ResultCellSerial->Enabled = false;
    if(resultCellSerialPending && resultCellSerialError && Form_CellIdError->stage == this->Tag)
    {
        Form_CellIdError->Timer_BringToFront->Enabled = false;
        Form_CellIdError->timerErrorOff->Enabled = false;
        Form_CellIdError->Close();
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
    }
    resultCellSerialPending = false;
    resultCellSerialError = false;
}

//---------------------------------------------------------------------------
// 트레이 ID의 .Tray 파일에서 셀 시리얼을 복원한다. 파일이 없으면 false.
bool __fastcall TTotalForm::LoadTrayInfo(AnsiString trayID)
{
	AnsiString filename;

	ForceDirectories((UnicodeString)TRAY_PATH);
	filename = (UnicodeString)TRAY_PATH + trayID + ".Tray";

	if(FileExists(filename)){
		TIniFile *ini;
		ini = new TIniFile(filename);

		//tray.cell_model = ini->ReadString("TRAY INFO", "CELL MODEL", "");
		//tray.lot_number = ini->ReadString("TRAY INFO", "LOT NUMBER", "");
		for(int i = 0; i < 400; i++)
		{
			tray.cell_serial[i] = ini->ReadString(i, "CELL_SERIAL", "");
		}

		delete ini;
	}
	else return false;

	return true;
}

//---------------------------------------------------------------------------
// 현재 트레이의 400셀 시리얼을 .Tray 파일에 저장한다.
void __fastcall TTotalForm::SaveTrayInfo(AnsiString trayID)
{
	ForceDirectories((UnicodeString)TRAY_PATH);
	TIniFile *ini = new TIniFile((UnicodeString)TRAY_PATH + trayID + ".Tray");

//	ini->WriteString("TRAY INFO", "CELL MODEL", m_sCellModel);
//	ini->WriteString("TRAY INFO", "LOT NUMBER", m_sLOTNumber);
	for(int i = 0; i < 400; i++)
	{
		ini->WriteString(i, "CELL_SERIAL", tray.cell_serial[i]);
	}
	delete ini;
}

//---------------------------------------------------------------------------
// 배출 완료한 트레이의 임시 .Tray 파일을 삭제한다.
void __fastcall TTotalForm::DeleteTrayInfo(AnsiString trayID)
{
    DeleteFile((AnsiString)TRAY_PATH + trayID + ".Tray");
}

