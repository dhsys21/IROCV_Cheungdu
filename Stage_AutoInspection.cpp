// [자동 검사 연결] Timer_AutoInspection, PLC 입력/출력, 단계 표시, 오류창 선택 처리.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"


namespace
{
// 자동 타이머가 처리 중일 때 다시 호출되는 것을 막는다.
// 함수 종료/예외 발생 시 busy 플래그를 자동으로 해제한다.
class TAutoTimerGuard
{
public:
    // 처리 시작: 호출자의 재진입 방지 플래그를 켠다.
    explicit TAutoTimerGuard(bool &busy) : busy_(busy) { busy_ = true; }
    // 처리 종료: 예외가 나더라도 재진입 방지 플래그를 끈다.
    ~TAutoTimerGuard() { busy_ = false; }
private:
    bool &busy_; // TTotalForm::autoInspectionBusy 참조
};
}

// Site-specific defaults and conversion from existing configuration live here.
// Keep editMaxDelayTime in its original unit; no configuration migration needed.
//---------------------------------------------------------------------------
// 자동측정 대기 설정 읽기: 기존 200ms 타이머 호출 횟수 단위를 유지한다.
TAutoInspectionSetting __fastcall TTotalForm::GetAutoInspectionSetting()
{
    TAutoInspectionSetting setting;
    int delay = editMaxDelayTime->Text.ToIntDef(50);
    setting.startDelayCount = delay < 0 ? 0 : delay;
    setting.cellSerialTimeoutCount = 50;
    return setting;
}

//---------------------------------------------------------------------------
// 단계가 바뀔 때 이전/다음 단계와 전환 이유를 PLC 로그에 기록한다.
void __fastcall TTotalForm::WriteAutoStepLog(TAutoInspectionStep previous, AnsiString reason)
{
    if(previous == autoInspection.GetStep()) return;
    WritePLCLog("AutoInspection",
        AnsiString(TAutoInspectionSequence::GetStepName(previous)) + " -> " +
        TAutoInspectionSequence::GetStepName(autoInspection.GetStep()) + " : " + reason);
}

//---------------------------------------------------------------------------
// 자동측정 단계와 NG 개수를 초기화한다. PLC 출력과 트레이 데이터 초기화는 Initialization에서 한다.
void __fastcall TTotalForm::ResetAutoInspection()
{
    TAutoInspectionStep previous = autoInspection.GetStep();
    autoInspection.Initialize(GetAutoInspectionSetting());
    NgCount = 0;
    WriteAutoStepLog(previous, "Reset");
}

//---------------------------------------------------------------------------
// 자동모드 타이머: 오류 확인 → PLC 상태 읽기 → 단계 판단 → 명령 1회 실행 → 화면 갱신.
void __fastcall TTotalForm::Timer_AutoInspectionTimer(TObject *Sender)
{
    if(autoInspectionBusy) return;
    TAutoTimerGuard guard(autoInspectionBusy);
    try
    {
        if(autoInspection.GetStep() == STEP_ERROR_STOP)
        {
            DisplayError("Auto inspection stopped. Check the log and restart.", true);
            return;
        }
        // Preserve the production pause/resume setting. Waiting ticks do not
        // advance during a connection failure, PLC error or local-mode block.
        if(CheckAutoInspectionError()) return;

        SetAutoReadySignalToPLC();
        TAutoInspectionData data = ReadAutoInspectionData();
        TAutoInspectionStep previous = autoInspection.GetStep();
        TAutoInspectionCommand command = autoInspection.RunAutoStep(data);
        WriteAutoStepLog(previous, "Timer");
        if(previous == STEP_WAIT_PROBE_OPEN && command != CMD_NONE)
            ClearProbeOpenSignalToPLC();
        RunAutoInspectionCommand(command, data);
        DisplayAutoInspectionStep();
    }
    catch(const Exception &error)
    {
        StopAutoInspectionOnError(error.Message);
    }
    catch(...)
    {
        StopAutoInspectionOnError("Unknown auto inspection exception");
    }
}

//---------------------------------------------------------------------------
// 자동 진행을 막는 통신/PLC/운전 모드 오류를 확인한다. true이면 현재 단계를 유지하고 대기한다.
bool __fastcall TTotalForm::CheckAutoInspectionError()
{
    DisplayError("");
    if(!Client->Active || !Client->Socket->Connected)
    {
        RefreshStageStatusImage();
        DisplayError("IR/OCV Connection Fail.");
        return true;
    }

    AnsiString error;
    if(!Mod_PLC->ClientSocket_PC->Active || !Mod_PLC->ClientSocket_PC->Socket->Connected ||
       !Mod_PLC->ClientSocket_PLC->Active || !Mod_PLC->ClientSocket_PLC->Socket->Connected)
        error = "PLC - PC Connection Fail.";
    else if(Mod_PLC->GetPlcValue(PLC_D_IROCV_ERROR))
        error = "PLC - Error!!";
    else if(bLocal && Mod_PLC->GetValue(PC_D_IROCV_STAGE_AUTO_READY) == 0)
        error = "IR/OCV is not in AutoMode";

    if(error.IsEmpty())
    {
        OldErrorCheckStatus = "";
        return false;
    }
    DisplayError(error, true);
    if(OldErrorCheckStatus != error)
    {
        OldErrorCheckStatus = error;
        WritePLCLog("CheckAutoInspectionError", error);
    }
    return true;
}

//---------------------------------------------------------------------------
// 운전 모드에 따라 PLC AUTO READY 신호 설정: 자동=1, 수동=0. 값이 바뀔 때만 기록한다.
void __fastcall TTotalForm::SetAutoReadySignalToPLC()
{
    int current = Mod_PLC->GetValue(PC_D_IROCV_STAGE_AUTO_READY);
    int requested = current;
    if(stage.arl == nAuto) requested = 1;
    else if(stage.arl == nLocal) requested = 0;
    if(requested == current) return;
    Mod_PLC->SetValue(PC_D_IROCV_STAGE_AUTO_READY, requested);
    WritePLCLog("IROCV STAGE AUTO/MANUAL", "IROCV STAGE AUTO READY = " + IntToStr(requested));
}

//---------------------------------------------------------------------------
// PLC 신호·운전 옵션·검사 수량을 읽는다. 시리얼은 전체 수신 완료 후 버퍼에서 읽는다.
TAutoInspectionData __fastcall TTotalForm::ReadAutoInspectionData()
{
    TAutoInspectionData data;
    data.trayIn = Mod_PLC->GetPlcValue(PLC_D_IROCV_TRAY_IN) == 1;
    data.probeClosed = Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE) == 1;
    data.probeOpen = Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN) == 1;
    data.autoMode = stage.arl == nAuto;
    data.bypass = chkBypass->Checked;
    data.cycleMode = chkCycle->Checked;
    data.cellCount = tray.cell_count;
    data.ngCount = NgCount;
    data.ngLimit = editNgAlarmCount->Text.ToIntDef(10);
    if(autoInspection.GetStep() == STEP_READ_TRAY_ID)
    {
        autoInspectionTrayId = Mod_PLC->GetString(
            Mod_PLC->plc_Interface_Data, PLC_D_IROCV_TRAY_ID, 10);
        data.trayIdReady = !autoInspectionTrayId.IsEmpty();
    }
    if(autoInspection.GetStep() == STEP_WAIT_CELL_SERIAL)
    {
        data.serialComplete = Mod_PLC->IsCellSerialReadComplete();
        if(data.serialComplete) data.serialCount = ReadCellSerial();
    }
    return data;
}

//---------------------------------------------------------------------------
// PLC CELL DATA 25워드의 비트맵으로 400셀 유무와 개수를 읽는다. Cycle 모드는 전 채널 사용.
void __fastcall TTotalForm::ReadAutoCellData()
{
    tray.cell_count = 0;
    for(int channel = 0; channel < MAXCHANNEL; ++channel)
    {
        tray.cell[channel] = chkCycle->Checked ? 1 :
            Mod_PLC->GetData(Mod_PLC->plc_Interface_Data,
                PLC_D_IROCV_TRAY_CELL_DATA + channel / 16, channel % 16);
        tray.cell_count += tray.cell[channel];
    }
    DisplayTrayInfo();
}

//---------------------------------------------------------------------------
// CELL SERIAL 4,010워드 분할 수신 시작. 별도 START/COMPLETE 핸드셰이크는 사용하지 않는다.
void __fastcall TTotalForm::StartAutoCellSerialRead()
{
    // Uses Modplc's existing 4,010-word chunk reader, WITHOUT START/COMPLETE bits.
    Mod_PLC->StartCellSerialRead();
    WritePLCLog("AutoInspection", "Start reading CELL SERIAL data.");
}

//---------------------------------------------------------------------------
// PLC 프로브 열림 확인 후 PC의 PROBE OPEN 요청을 0으로 해제한다.
void __fastcall TTotalForm::ClearProbeOpenSignalToPLC()
{
    Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
    WriteCommLog("AutoInspection", "PLC - PROBE IS OPEN. Results published.");
}

//---------------------------------------------------------------------------
// 단계 판단에서 반환한 명령을 한 번 실행한다. 실제 PLC 출력·측정 시작·오류창은 이곳에서 처리한다.
void __fastcall TTotalForm::RunAutoInspectionCommand(TAutoInspectionCommand command, const TAutoInspectionData &data)
{
    switch(command)
    {
        case CMD_NONE:
            return;
        case CMD_TRAY_IN:
            // 트레이 투입부터는 안내 번호를 숨긴다. 미수신 측정값은 공란으로 표시한다.
            showStartupChannelNumbers = false;
            PLCInitialization();
            InitTrayStruct();
            NgCount = 0;
            Mod_PLC->PLC_Write_Result = false;
            DisplayStatus(nREADY);
            break;
        case CMD_READ_TRAY_ID:
            m_dateTime = Now();
            tray.trayid = autoInspectionTrayId;
            pTrayid->Caption = tray.trayid;
            editTrayId->Text = tray.trayid;
            WritePLCLog("AutoInspection", "TRAY ID = " + tray.trayid);
            break;
        case CMD_READ_CELL_DATA:
            ReadAutoCellData();
            break;
        case CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL:
            Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
            WritePLCLog("AutoInspection", "PC_D_IROCV_PROB_CLOSE = 1");
            StartAutoCellSerialRead();
            break;
        case CMD_SAVE_CELL_SERIAL:
            SaveTrayInfo(tray.trayid);
            WritePLCLog("AutoInspection", "CELL SERIAL complete. Serial = " +
                IntToStr(data.serialCount) + ", CellData = " + IntToStr(data.cellCount));
            break;
        case CMD_CELL_SERIAL_COUNT_ERROR:
        case CMD_CELL_SERIAL_TIMEOUT:
            Form_CellIdError->ChangeMessage("CELL SERIAL - BEFORE MEASUREMENT",
                "Check CELL DATA count and complete CELL SERIAL data.",
                "SAVE: accept data / CANCEL: read again");
            if(command == CMD_CELL_SERIAL_TIMEOUT)
                WritePLCLog("AutoInspection", "CELL SERIAL Read Timeout.");
            else
                WritePLCLog("AutoInspection", "CELL SERIAL Count Error. Serial = " +
                    IntToStr(data.serialCount) + ", CellData = " + IntToStr(data.cellCount));
            Form_CellIdError->DisplayErrorMessage(this->Tag);
            break;
        case CMD_MEASURE_START:
        case CMD_REMEASURE_START:
            DisplayStatus(nRUN);
            Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
            tray.ams = false;
            tray.amf = false;
            if(command == CMD_MEASURE_START)
                Mod_PLC->SetValue(PC_D_IROCV_REMEASURE, 0);
            WriteCommLog("AutoInspection", command == CMD_MEASURE_START ?
                "IR/OCV Measure Start" : "IR/OCV Re-Measure Start");
            if(command == CMD_REMEASURE_START && retest.re_excute)
                RemeasureExcute();
            else
                CmdAutoTest();
            break;
        case CMD_NG_ERROR:
            // Already in STEP_WAIT_NG_ERROR before showing a modeless dialog.
            Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
            Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 0);
            DisplayStatus(nEND);
            Form_Error->Tag = this->Tag;
            Form_Error->DisplayErrorMessage("IR/OCV NG ERROR",
                "There is too many ng cells. Please check it.",
                "Select [Tray Out] or [Restart]");
            break;
        case CMD_BYPASS_TRAY_OUT:
        case CMD_TRAY_OUT:
            // Intentionally no NG recheck: automatic decision is made by the
            // sequence; bypass/manual/operator-approved requests are explicit.
            Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
            Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 1);
            DisplayStatus(nFinish);
            WritePLCLog("AutoInspection", command == CMD_BYPASS_TRAY_OUT ?
                "BYPASS TRAY OUT = 1" : "IROCV TRAY OUT = 1");
            break;
        case CMD_TRAY_OUT_COMPLETE:
            DeleteTrayInfo(tray.trayid);
            Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 0);
            Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
            Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
            WriteCommLog("AutoInspection", "TRAY OUT complete");
            pTrayid->Caption = "";
            editTrayId->Text = "";
            break;
    }
}

//---------------------------------------------------------------------------
// 현재 단계의 화면 문구와 MEASURING 신호를 갱신한다. 프로브/배출 동작을 새로 시작하지 않는다.
void __fastcall TTotalForm::DisplayAutoInspectionStep()
{
    // [CELL SERIAL 공통] 최종 수신 대기/오류 문구를 기존 측정 대기 문구로 덮어쓰지 않는다.
    if(resultCellSerialPending)
    {
        Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
        DisplayProcess(sBarcode, "CELL SERIAL", resultCellSerialError
            ? AnsiString(" CELL SERIAL error - waiting for SAVE / CANCEL ... ")
            : AnsiString(" Reading CELL SERIAL before result save ... "), resultCellSerialError);
        return;
    }
    TAutoInspectionStep step = autoInspection.GetStep();
    const bool measuring = step == STEP_WAIT_MEASURE_COMPLETE && tray.ams && !tray.amf;
    Mod_PLC->SetValue(PC_D_IROCV_MEASURING, measuring ? 1 : 0);
    switch(step)
    {
        case STEP_WAIT_TRAY_IN:
            DisplayStatus(nVacancy);
            DisplayProcess(sReady, "AutoInspection", " IR/OCV is ready... ");
            break;
        case STEP_READ_TRAY_ID:
            DisplayProcess(sBarcode, "AutoInspection", " Waiting for TRAY ID ... ");
            break;
        case STEP_READ_CELL_DATA:
            DisplayProcess(sBarcode, "AutoInspection", " Reading CELL DATA ... ");
            break;
        case STEP_WAIT_START_DELAY:
            DisplayProcess(sProbeDown, "AutoInspection", tray.cell_count > 0 ?
                AnsiString(" Start delay: ") + IntToStr((int)autoInspection.GetWaitCount()) +
                    " / " + IntToStr((int)autoInspection.GetSetting().startDelayCount) :
                AnsiString(" NO CELL ... "), tray.cell_count <= 0);
            break;
        case STEP_WAIT_CELL_SERIAL:
            DisplayProcess(sBarcode, "AutoInspection", " Reading CELL SERIAL ... ");
            break;
        case STEP_WAIT_CELL_SERIAL_ERROR:
            DisplayProcess(sBarcode, "AutoInspection", " CELL SERIAL error - waiting for SAVE / CANCEL ... ", true);
            break;
        case STEP_WAIT_PROBE_CLOSE:
        case STEP_WAIT_REMEASURE_PROBE_CLOSE:
            DisplayProcess(sProbeDown, "AutoInspection", " Waiting for PLC PROBE CLOSED ... ");
            break;
        case STEP_WAIT_MEASURE_COMPLETE:
            DisplayProcess(sMeasure, "AutoInspection", " Measuring / remeasuring - waiting for results ... ");
            break;
        case STEP_WAIT_PROBE_OPEN:
            DisplayProcess(sProbeOpen, "AutoInspection", " Results complete - waiting for PLC PROBE OPEN ... ");
            break;
        case STEP_WAIT_NG_ERROR:
            DisplayStatus(nEND);
            DisplayProcess(sFinish, "AutoInspection", " NG alarm - waiting for Tray Out / Restart ... ", true);
            break;
        case STEP_WAIT_TRAY_OUT:
            DisplayStatus(nFinish);
            DisplayProcess(sTrayOut, "AutoInspection", " IROCV Tray Out ... ");
            break;
        case STEP_ERROR_STOP:
            DisplayStatus(nEND);
            break;
    }
}

//---------------------------------------------------------------------------
// 예외 발생 단계와 원인을 기록하고 PC 자동 진행을 정지한다. 설비 비상정지 명령은 아니다.
void __fastcall TTotalForm::StopAutoInspectionOnError(AnsiString message)
{
    CancelResultCellSerialRead();
    TAutoInspectionStep previous = autoInspection.GetStep();
    autoInspection.StopWithError();
    // This stops PC sequence progression; it is NOT a PLC emergency stop.
    // Do not issue new probe/tray movements on an exception.
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 1);
    Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
    DisplayStatus(nEND);
    DisplayError(message, true);
    WritePLCLog("AutoInspection ERROR", AnsiString(TAutoInspectionSequence::GetStepName(previous)) + ": " + message);
}


//---------------------------------------------------------------------------
// 시리얼 오류창 SAVE: 현재 데이터를 저장하고 프로브 닫힘 확인 단계로 진행한다.
void __fastcall TTotalForm::AcceptCellSerialData()
{
    // [CELL SERIAL 공통] 결과 저장 전 오류와 측정 시작 전 오류의 복귀 위치를 구분한다.
    if(resultCellSerialPending && resultCellSerialError)
    {
        try { CompleteResultCellSerialRead(true); }
        catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
        return;
    }
    if(autoInspection.GetStep() != STEP_WAIT_CELL_SERIAL_ERROR) return;
    try
    {
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
        // Preserve the existing explicit SAVE override, including timeout data.
        ReadCellSerial();
        SaveTrayInfo(tray.trayid);
        TAutoInspectionStep previous = autoInspection.GetStep();
        autoInspection.SaveCellSerialAfterError();
        WriteAutoStepLog(previous, "Operator SAVE: CELL SERIAL override");
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
}

//---------------------------------------------------------------------------
// 시리얼 오류창 CANCEL: 대기 횟수를 초기화하고 4,010워드를 처음부터 다시 수신한다.
void __fastcall TTotalForm::RetryCellSerialRead()
{
    // [CELL SERIAL 공통] 결과 저장 전 재시도는 측정 대신 시리얼만 다시 읽는다.
    if(resultCellSerialPending && resultCellSerialError)
    {
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
        StartResultCellSerialRead();
        return;
    }
    if(autoInspection.GetStep() != STEP_WAIT_CELL_SERIAL_ERROR) return;
    try
    {
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
        TAutoInspectionStep previous = autoInspection.GetStep();
        autoInspection.RetryCellSerialRead();
        WriteAutoStepLog(previous, "Operator CANCEL: retry CELL SERIAL");
        StartAutoCellSerialRead();
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
}

//---------------------------------------------------------------------------
// 결과 처리 함수 종료를 시퀀스에 알린다. 이후 PLC 프로브 열림을 확인해야 자동 배출한다.
void __fastcall TTotalForm::SetAutoMeasureComplete()
{
    TAutoInspectionStep previous = autoInspection.GetStep();
    if(autoInspection.SetMeasureComplete())
        WriteAutoStepLog(previous, "Result processing returned; PLC result buffer ready");
}

//---------------------------------------------------------------------------
// 재측정 가능 단계인지 확인하고 이전 측정 완료/프로브 열림 요청을 초기화한다.
bool __fastcall TTotalForm::PrepareAutoRemeasure()
{
    TAutoInspectionStep previous = autoInspection.GetStep();
    if(!autoInspection.StartRemeasure())
    {
        WritePLCLog("AutoInspection", "Remeasure ignored in " +
            AnsiString(TAutoInspectionSequence::GetStepName(previous)));
        return false;
    }
    WriteAutoStepLog(previous, "Operator remeasure");
    tray.ams = false;
    tray.amf = false;
    NgCount = 0;
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
    return true;
}

//---------------------------------------------------------------------------
// 자동 배출 판단: Auto/프로브 열림/결과 완료를 확인하고 NG 조건에 따라 오류 대기 또는 배출한다.
void __fastcall TTotalForm::CmdTrayOut()
{
    // Automatic/diagnostic entry: cannot skip result publication or NG waiting.
    TAutoInspectionStep previous = autoInspection.GetStep();
    TAutoInspectionData data = ReadAutoInspectionData();
    if(!data.autoMode || !data.probeOpen) return;
    TAutoInspectionCommand command = autoInspection.AutomaticTrayOut(data.ngCount, data.cellCount, data.ngLimit);
    if(command == CMD_NONE) return;
    WriteAutoStepLog(previous, "Automatic tray-out decision");
    ClearProbeOpenSignalToPLC();
    RunAutoInspectionCommand(command, data);
    DisplayAutoInspectionStep();
}

//---------------------------------------------------------------------------
// 수동 또는 운영자가 승인한 배출: NG를 다시 검사하지 않고 TRAY OUT을 요청한다.
void __fastcall TTotalForm::ForceTrayOut()
{
    CancelResultCellSerialRead(); // [CELL SERIAL 공통] 배출 이후 지연된 결과 저장 방지.
    try
    {
        TAutoInspectionStep previous = autoInspection.GetStep();
        TAutoInspectionCommand command = autoInspection.ForceTrayOut();
        WriteAutoStepLog(previous, "Manual / operator-approved tray out (NG bypass)");
        RunAutoInspectionCommand(command, TAutoInspectionData());
        DisplayAutoInspectionStep();
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
}

//---------------------------------------------------------------------------
// NG 오류창 Restart: PLC·트레이·자동 단계를 초기화하고 TRAY IN부터 다시 검사한다.
void __fastcall TTotalForm::RestartAutoInspection()
{
    try
    {
        Initialization();
        WritePLCLog("AutoInspection", "Operator restart from TRAY IN");
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
}

//---------------------------------------------------------------------------
// 자동 검사 전체 초기화: PLC 출력 → 트레이 데이터 → 단계 순서로 초기화한다.
void __fastcall TTotalForm::Initialization()
{
    PLCInitialization();
    InitTrayStruct();
    ResetAutoInspection();
    DisplayProcess(sReady, "AutoInspection", " IR/OCV is ready... ");
}

//---------------------------------------------------------------------------
// 메인 화면 수동 배출: 재측정 목록 정리, 강제 배출, PROBE CLOSE=0 / OPEN=1 / COMPLETE=1.
void __fastcall TTotalForm::ManualTrayOut()
{
		for(int i = 0; i < MAXCHANNEL; i++) retest.cell[i] = 0;
		this->ForceTrayOut();

        Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
        Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 1);
        Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);

}
