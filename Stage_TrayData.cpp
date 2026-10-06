// [트레이 데이터] 검사 데이터 초기화, CELL SERIAL 복사, .Tray 임시 파일 저장/복원/삭제.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

//---------------------------------------------------------------------------
// 새 트레이 검사 데이터 초기화: 문자열/숫자/배열과 수신 표시를 지운다. 투입 이후 화면은 공란이다.
void __fastcall TTotalForm::InitializeTrayData()
{
    measurementClock.Reset();
    // [CELL SERIAL 공통] 이전 결과 저장 대기를 취소하고 이번 트레이의 수신 방식을 확정한다.
    CancelResultSave();
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
    resultSaveStep = RESULT_IDLE;
    resultFileName = "";
    trayResultCounted = false;
    countedFinalIrNg = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        tray.cell[i] = 1;
        tray.cell_serial[i] = "";
        tray.precharger[i] = "";
        tray.precharge_volt[i] = "";
        tray.original_value[i] = 0;
        tray.after_value[i] = 0;
        tray.ocv_value[i] = 0;
        tray.Cali_value[i] = 0;
        tray.measure_result[i] = 0;
    }
    memset(&retest, 0, sizeof(retest)); // REMEASURE는 숫자/bool 배열만 포함한다.
    retest.waitingChannel = -1;
    measurementNgCount = 0;
    InitializeCellDisplay();
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
        tray.cell_serial[i] = Mod_PLC->GetCellSerial(
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
    WritePlcLog("CELL SERIAL MODE", cellSerialContinuousReadForTray
        ? "Continuous read / refresh before result save" : "TRAY IN capture / use saved serial");
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
		for(int i = 0; i < MAXCHANNEL; i++)
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
	for(int i = 0; i < MAXCHANNEL; i++)
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
