// [측정·재측정] AMS/AMF 및 IR/OCV 처리, 재측정 목록, 결과 마감. 통신 프레임은 Stage_comm.cpp.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

//---------------------------------------------------------------------------
// 수동 측정 초기화: 내부 값은 0으로 지우고 화면은 수신 전까지 공란으로 표시한다.
void __fastcall TTotalForm::OnInit()
{
    CancelResultSave(); // [CELL SERIAL 공통] 운영자 초기화 이후 지연 저장 방지.
    resultSaveStep = RESULT_IDLE;
    showStartupChannelNumbers = false;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        tray.ocv_value[i] = 0;
        tray.after_value[i] = 0;
        tray.orginal_value[i] = 0;
    }
    InitCellDisplay();
}

//---------------------------------------------------------------------------
// 전체 측정 시작: 표시·수신 플래그를 초기화하고 AMS 명령을 예약한다.
void __fastcall TTotalForm::CmdAutoTest()
{
    if(IsWaitingForResultSave()) return;
    resultSaveStep = RESULT_IDLE; // 새 측정에만 마감 중복 방지를 해제한다.
    showStartupChannelNumbers = false;
    InitCellDisplay();
    tray.ams = false;
    tray.amf = false;
    MakeData(3, "AMS");
}

//---------------------------------------------------------------------------
// AMF 수신 후 처리: 운전 모드에 따라 결과 마감 또는 기존 자동 개별 재측정을 수행한다.
void __fastcall TTotalForm::ResponseAutoTestFinish()
{
    if(resultSaveStep != RESULT_IDLE || tray.rem_mode == 1) return; // 중복 AMF로 재측정을 다시 시작하지 않는다.
	if(bLocal == true){
		FinishMeasurement();
        DisplayProcess(sFinish, "AutoInspection_Measure", " AMF - Measure finished ... ");
		WriteCommLog("IR/OCV STOP", "AMF - ResponseautoTestfinish()");
	}
	else
	{
		SendData("SEN");

        SetRemeasureList();
	}
}

//---------------------------------------------------------------------------
// IR 응답 문자열을 값/채널로 해석하고 일반 측정 또는 교정 화면에 전달한다.
void __fastcall TTotalForm::ProcessIr(AnsiString param)
{
	AnsiString result;
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Pos(",") - pos - 2).ToInt();

	if(count > 10) value = 0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 0 || value > 900)result = "CE";
	else result = "GO";

    int index = channel - 1;

	if(CaliForm->stage != this->Tag)
	{
		InsertIrValue(channel, value, result); //일반계측
	}
	else
	{
		if(result == "GO")
		{
			CaliForm->pmeasure[index]->Caption = FormatFloat("0.000", value);
			CaliForm->poffset[index]->Caption = FormatFloat("0.00", StrToFloat(CaliForm->pstandard[index]->Text) -  value);
		}
	}

	if(tray.rem_mode == 1 && retest.waitingChannel == channel - 1 &&
       retest.waitingItem == 1){
        retest.waitingChannel = -1;
        retest.waitingItem = 0;
        send.tx_mode = 200;
        RemeasureExcute();
    }

}

//---------------------------------------------------------------------------
// 채널 IR 수신 처리: 보정·판정·수신 표시를 갱신한다. 화면은 수신 여부와 현재 측정값으로 갱신한다.
void __fastcall TTotalForm::InsertIrValue(int pos, float value, AnsiString result)
{
	int index = pos-1;
    if(index < 0 || index >= MAXCHANNEL) return;
    irValueReceived[index] = true;

	bool cell = false;

	if(tray.cell[index] == 1)cell = true;
	tray.measure_result[index] = GetResult(result);


	if(cell)   // 셀이 있을때
	{
        tray.orginal_value[index] = value;
		tray.after_value[index] = tray.orginal_value[index] + BaseForm->DefaultOffset[this->Tag];
		tray.after_value[index] = tray.after_value[index] + stage.ir_offset[index];    //개별보정

		if(tray.measure_result[index] == GO)
		{
			if(tray.after_value[index] >= config.ir_min && tray.after_value[index] <= config.ir_max)
			{
				UpdateCellDisplay(index);

			}
			else
			{
				UpdateCellDisplay(index);
            }
		}
		else
		{
			tray.orginal_value[index] = 999;
			tray.after_value[index] = 999;
			UpdateCellDisplay(index);
		}

	}
	else{     // 셀이 없을때
		if(tray.measure_result[index] == GO)
		{
			WriteCommLog("ETC", "OUTFLOW");
			UpdateCellDisplay(index);
		}

		tray.orginal_value[index] = 0;
		tray.after_value[index] = 0;
	}
}

//---------------------------------------------------------------------------
// 장비의 GO/HI/LO/CE 등 판정 문자를 기존 내부 결과 코드로 변환한다.
int __fastcall TTotalForm::GetResult(AnsiString result)
{
	if(result == "GO") return GO;
	if(result == "HI") return HI;
	if(result == "LO") return LO;
	if(result == "OV") return OV;
	if(result == "UN") return UN;
	if(result == "CE") return CE;
	if(result == "NA") return NA;
	if(result == "NO") return NO;
	else return 100;
}

//---------------------------------------------------------------------------
// OCV 응답 문자열을 값/채널로 해석하고 채널 판정 및 필요 시 다음 재측정을 진행한다.
void __fastcall TTotalForm::ProcessOcv(AnsiString param)
{
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Length()).ToInt();

	if(count > 10) value = 0.0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 10 || value > 7000) value = 0.0;

	InsertOcvValue(channel, value);
//	}else{
//    }

	if(tray.rem_mode == 1 && retest.waitingChannel == channel - 1 &&
       retest.waitingItem == 2){
        retest.waitingChannel = -1;
        retest.waitingItem = 0;
        send.tx_mode = 200;
        RemeasureExcute();
    }
}

//---------------------------------------------------------------------------
// 채널 OCV 수신 처리: 규격 판정·화면을 갱신한다.
void __fastcall TTotalForm::InsertOcvValue(int pos, float value)
{
    const int index = pos - 1;
    if(index < 0 || index >= MAXCHANNEL) return;
    ocvValueReceived[index] = true;
    tray.ocv_value[index] = value;
    if(tray.cell[index] != 1 && value > 1500) WriteCommLog("ETC", "OUTFLOW");
    UpdateCellDisplay(index);
}

//---------------------------------------------------------------------------
// 전체 측정 후 재측정 대상 집계. SiteConfig.h의 개수 조건에 따라 개별 재측정 또는 결과 마감한다.
void __fastcall TTotalForm::SetRemeasureList()
{
    SetRemeasureListAfter();
    // 1번: 프로브를 닫은 상태에서 불량 항목을 한 차례 재측정한다.
    // 설정은 이번 트레이 시작 때 고정. 0=생략, N=NG 1~N개(설정값 포함)만 실행.
    // 초과 시 여기서는 전체 재측정하지 않고 결과 마감으로 이동한다.
    const int maxNgCount = autoInspection.GetSetting().closedProbeRemeasureMaxNgCount;
    if(stage.arl == nAuto && retest.cnt_error > 0 &&
       retest.cnt_error <= maxNgCount)
    {
        // 2번 재개폐 횟수가 0이어도 이 재측정은 독립적으로 실행한다.
        PrepareRemeasureItems();
        tray.rem_mode = 1;
        RemeasureExcute();
    }
    else FinishMeasurement();
}

//---------------------------------------------------------------------------
// 개별 재측정 후 최종 불량 목록을 다시 집계한다. 측정 명령은 보내지 않는다.
int __fastcall TTotalForm::JudgeCellResult(int index)
{
    if(tray.cell[index] != 1) return CELL_OK;
    if(tray.after_value[index] == 999) return CELL_CONTACT_NG;
    if(tray.after_value[index] < config.ir_min || tray.after_value[index] > config.ir_max)
        return CELL_IR_NG;
    if(tray.ocv_value[index] < config.ocv_min || tray.ocv_value[index] > config.ocv_max)
        return CELL_OCV_NG;
    return CELL_OK;
}

// 현재 값으로 최종 판정을 재계산한다. 접촉 > IR > OCV. 이전 판정값을 유지하지 않는다.
// 생산 누적 채널 사용/재측정 수는 첫 전체 측정에서만 증가한다.
void __fastcall TTotalForm::SetRemeasureListAfter()
{
    retest.cnt_error = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        retest.cell[i] = JudgeCellResult(i);
        if(tray.cell[i] == 1)
        {
            if(tray.first) ++acc_totaluse[i];
            if(retest.cell[i] != CELL_OK)
            {
                ++retest.cnt_error;
                if(tray.first) ++acc_remeasure[i];
            }
        }
        UpdateCellDisplay(i); // 최종 표시도 측정값/수신 상태에서 다시 만든다.
    }
    measNgCount = retest.cnt_error;
    tray.first = false;
}

// 불량 셀의 IR/OCV 요청 목록. 판정 배열(retest.cell)은 진행 표식으로 사용하지 않는다.
void __fastcall TTotalForm::PrepareRemeasureItems()
{
    retest.re_index = 0;
    retest.waitingChannel = -1;
    retest.waitingItem = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
    {
        retest.pendingItems[i] = 0;
        if(tray.cell[i] != 1) continue;
        if(tray.after_value[i] == 999 || tray.after_value[i] < config.ir_min ||
           tray.after_value[i] > config.ir_max) retest.pendingItems[i] |= 1;
        if(tray.ocv_value[i] < config.ocv_min || tray.ocv_value[i] > config.ocv_max)
            retest.pendingItems[i] |= 2;
    }
}

//---------------------------------------------------------------------------
// 재측정 목록의 다음 IR/OCV를 요청한다. 더 없으면 최종 판정과 결과 마감을 수행한다.
void __fastcall TTotalForm::RemeasureExcute()
{
    if(retest.waitingChannel >= 0) return; // 요청한 채널/항목 응답 전 중복 명령 금지.
    for(int i = retest.re_index; i < MAXCHANNEL; ++i)
    {
        retest.re_index = i;
        int item = (retest.pendingItems[i] & 1) ? 1 : ((retest.pendingItems[i] & 2) ? 2 : 0);
        if(item == 0) continue;
        retest.pendingItems[i] &= ~item;
        retest.waitingChannel = i;
        retest.waitingItem = item;
        if(item == 1) irValueReceived[i] = false;
        else ocvValueReceived[i] = false;
        UpdateCellDisplay(i);
        MakeData(3, item == 1 ? AnsiString("IR*") : AnsiString("OCV"),
            FormatFloat("000", chReverseMap[i + 1]));
        return;
    }
    retest.re_excute = false;
    tray.rem_mode = 0;
    SetRemeasureListAfter();
    FinishMeasurement();
}

//---------------------------------------------------------------------------
// 결과 마감: STP/프로브 열림 요청 → NG·결과 코드·값·파일 작성 → COMPLETE → 자동 단계 완료 통지.
void __fastcall TTotalForm::FinishMeasurement()
{
    // 같은 AMF/정지 통지가 반복되어도 저장/집계를 다시 실행하지 않는다.
    if(resultSaveStep != RESULT_IDLE) return;
    SetRemeasureListAfter();
    MakeData(1, "STP");
    Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 1);
    WritePLCLog("FinishMeasurement", "IROCV PROBE OPEN = 1");
    // 수동측정은 CELL SERIAL 없이 저장한다. 수동 화면(bLocal) 및 설비 Local 모드를 포함.
    // 자동측정의 시리얼 오류를 감추지 않도록 검사 시작/완료 경로 자체를 여기서 분리한다.
    const bool saveWithoutCellSerial = bLocal || stage.arl == nLocal;
    if(!saveWithoutCellSerial && cellSerialContinuousReadForTray)
        StartResultCellSerialRead();
    else
    {
        resultSaveStep = RESULT_WRITE_FILE;
        SaveMeasurementResult(saveWithoutCellSerial);
    }
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 자동=시리얼 확인 후 저장, 수동=시리얼 없이 저장. PLC 완료 처리는 공통 유지.
void __fastcall TTotalForm::SaveMeasurementResult(bool saveWithoutCellSerial)
{
    if(resultSaveStep != RESULT_WRITE_FILE) return;
    BadInformation();
    WriteResultCode();
    ReadCellInfo();
    WriteIROCVValue();
    if(saveWithoutCellSerial)
    {
        // 수동 결과에 이전 트레이 시리얼을 넣지 않는다. .Tray 복원/PLC 시리얼 읽기도 생략.
        for(int i = 0; i < MAXCHANNEL; ++i) tray.cell_serial[i] = "";
    }
    else if(!cellSerialContinuousReadForTray && !LoadTrayInfo(tray.trayid))
        ReadCellSerial();
    // 참고용 CSV: 최초 1회 + 재시도 1회. 재시도에서 판정/생산 누계를 다시 처리하지 않는다.
    if(!WriteResultFile() && !WriteResultFile())
        WritePLCLog("RESULT FILE WARNING", "Save failed twice; continue production: " + resultFileName);
    // 새 결과 전송을 확인할 PC 내부 표식. PLC 신호/프로그램은 추가하지 않는다.
    Mod_PLC->BeginResultTransmission();
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    resultSaveStartTime = GetTickCount();
    resultSaveStep = RESULT_WAIT_PLC_SEND;
    Timer_ResultSave->Enabled = true;
    Panel_State->Caption = " Waiting to send final PLC results ... ";
}

//---------------------------------------------------------------------------
// 전체 재측정 요청: 트레이 ID를 유지하고 데이터 초기화·CELL DATA 재읽기 후 프로브 닫힘을 기다린다.
void __fastcall TTotalForm::StartFullRemeasure()
{
    if(!PrepareAutoRemeasure()) return;
    // 같은 트레이: 시리얼, 파일명, 생산 누계와 재개폐 횟수는 지우지 않는다.
    OnInit();
    memset(&retest, 0, sizeof(retest));
    retest.waitingChannel = -1;
    retest.re_excute = false;
    tray.rem_mode = 0;
    Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
    WritePLCLog("StartFullRemeasure", "IROCV PROBE CLOSE = 1 (all cells)");
    VisibleBox(GrpMain);
}

//---------------------------------------------------------------------------
// 선택 재측정 요청: 기존 불량 목록을 사용하고 프로브 닫힘 확인 후 채널별 재측정을 시작한다.
void __fastcall TTotalForm::StartSelectedRemeasure()
{
    if(!PrepareAutoRemeasure()) return;
    PrepareRemeasureItems();
    tray.rem_mode = 1;
    retest.re_excute = true;
    Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
    WritePLCLog("StartSelectedRemeasure", "IROCV PROBE CLOSE = 1 (NG cells)");
    VisibleBox(GrpMain);
}

//===========================================================================
// 결과 마감 대기: 시리얼 확인 → 파일 작성 → PLC 송신/1초 지연 → 완료.
//===========================================================================
//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 요청 이후에 시작한 4,010워드 전체 수신까지 결과 저장을 보류한다.
// 자동측정 전용 시리얼 대기. 수동측정은 FinishMeasurement에서 이 경로를 건너뛴다.
void __fastcall TTotalForm::StartResultCellSerialRead()
{
    resultSaveStep = RESULT_WAIT_SERIAL;
    resultSaveStartTime = GetTickCount();
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->StartCellSerialRead();
    Timer_ResultSave->Enabled = true;
    Panel_State->Caption = " Reading CELL SERIAL before result save ... ";
    WritePLCLog("CELL SERIAL", "Request fresh complete serial data for result save");
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 시간 초과/개수 불일치는 결과 저장과 자동 배출을 보류한다.
// SAVE=완료 데이터 운영자 승인 저장, CANCEL=새 전체 수신 재시도.
void __fastcall TTotalForm::ShowResultCellSerialError(AnsiString reason)
{
    Timer_ResultSave->Enabled = false;
    resultSaveStep = RESULT_WAIT_OPERATOR;
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
    if(resultSaveStep != RESULT_WAIT_SERIAL && resultSaveStep != RESULT_WAIT_OPERATOR) return;
    if(!Mod_PLC->IsCellSerialReadComplete())
    {
        ShowResultCellSerialError("No complete CELL SERIAL data. Select CANCEL to read again.");
        return;
    }
    const int serialCount = ReadCellSerial();
    // 자동 결과 저장은 캐시가 아닌 현재 CELL DATA의 실제 셀 개수와 비교한다.
    int cellCount = 0;
    for(int i = 0; i < MAXCHANNEL; ++i)
        if(tray.cell[i] == 1) ++cellCount;
    if(!operatorOverride && serialCount != cellCount)
    {
        ShowResultCellSerialError("Serial count " + IntToStr(serialCount)
            + " / Cell count " + IntToStr(cellCount));
        return;
    }
    Timer_ResultSave->Enabled = false;
    WritePLCLog("CELL SERIAL", (operatorOverride ? AnsiString("Operator SAVE: ") : AnsiString("Final read OK: "))
        + IntToStr(serialCount) + " / " + IntToStr(cellCount));
    SaveTrayInfo(tray.trayid);
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
    resultSaveStep = RESULT_WRITE_FILE;
    SaveMeasurementResult();
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 완료를 먼저 확인하고 미완료면 요청 후 10초에 오류로 전환한다.
// unsigned 경과시간 계산은 GetTickCount의 약 49일 주기 순환도 처리한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 Timer_ResultSaveTimer. 시리얼 수신·결과 저장·PLC 완료 대기는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessResultSave(TObject *Sender)
{
    Timer_ResultSave->Enabled = false;
    try
    {
        if(resultSaveStep == RESULT_WAIT_SERIAL)
        {
            if(Mod_PLC->IsCellSerialReadComplete()) CompleteResultCellSerialRead(false);
            else if(static_cast<DWORD>(GetTickCount() - resultSaveStartTime) >= RESULT_SERIAL_TIMEOUT_MS)
                ShowResultCellSerialError("CELL SERIAL final read timeout (10 seconds).");
        }
        else if(resultSaveStep == RESULT_WAIT_PLC_SEND)
        {
            // Sleep 금지: 같은 UI 스레드의 PLC 송신 타이머가 계속 실행되어야 한다.
            // 1초 + 새 결과 각 블록 송신 확인. PLC 응답 신호를 새로 추가하지 않는다.
            if(!Mod_PLC->IsResultConnectionReady())
                resultSaveStartTime = GetTickCount(); // 재접속 직후 즉시 COMPLETE를 출력하지 않는다.
            else if(Mod_PLC->WasResultTransmitted() &&
                    static_cast<DWORD>(GetTickCount() - resultSaveStartTime) >= RESULT_COMPLETE_DELAY_MS)
            {
                resultSaveStep = RESULT_COMPLETE; // 중복 타이머/AMF보다 먼저 완료 상태 확정.
                Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);
                WritePLCLog("FinishMeasurement", "PLC results sent; COMPLETE = 1");
                SetAutoMeasureComplete();
            }
        }
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
    catch(...) { StopAutoInspectionOnError("Unknown result save error"); }
    Timer_ResultSave->Enabled = resultSaveStep == RESULT_WAIT_SERIAL ||
                                resultSaveStep == RESULT_WAIT_PLC_SEND;
}

//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 초기화/재시작/강제 배출 후 늦게 도착한 응답이 결과를 저장하지 못하게 한다.
void __fastcall TTotalForm::CancelResultSave()
{
    Timer_ResultSave->Enabled = false;
    if(resultSaveStep == RESULT_WAIT_OPERATOR && Form_CellIdError->stage == this->Tag)
    {
        Form_CellIdError->Timer_BringToFront->Enabled = false;
        Form_CellIdError->timerErrorOff->Enabled = false;
        Form_CellIdError->Close();
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
    }
    // 초기화/강제 배출 후 늦은 시리얼 응답이나 1초 타이머가 완료를 출력하지 못하게 한다.
    resultSaveStep = RESULT_CANCELLED;
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
}
