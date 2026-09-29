// [자동 검사 연결] Timer_AutoInspection, PLC 입력/출력, 단계 표시, 오류창 선택 처리.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"


namespace
{
// 자동측정 처리 함수가 중복 실행되지 않도록 잠근다.
// ProcessAutoInspection 한 번의 처리 동안만 유지하며, 함수 종료/예외 시 자동 해제한다.
class TAutoInspectionRunLock
{
public:
    // 처리 시작: 호출자의 재진입 방지 플래그를 켠다.
    explicit TAutoInspectionRunLock(bool &isProcessing) : isProcessing_(isProcessing) { isProcessing_ = true; }
    // 처리 종료: 예외가 나더라도 재진입 방지 플래그를 끈다.
    ~TAutoInspectionRunLock() { isProcessing_ = false; }
private:
    bool &isProcessing_; // TTotalForm::isAutoInspectionProcessing 참조
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
    setting.probeRemeasureCount = config.probeRemeasureCount < 0 ? 0 : config.probeRemeasureCount;
    setting.closedProbeRemeasureMaxNgCount = config.closedProbeRemeasureMaxNgCount;
    setting.startDelayCount = delay < 0 ? 0 : delay;
    setting.cellSerialTimeoutCount = 50;
    return setting;
}

//---------------------------------------------------------------------------
// 단계가 바뀔 때 이전/다음 단계와 전환 이유를 PLC 로그에 기록한다.
void __fastcall TTotalForm::WriteAutoStepLog(TAutoInspectionStep previous, AnsiString reason)
{
    if(previous == autoInspection.GetStep()) return;
    WritePlcLog("AutoInspection",
        AnsiString(TAutoInspectionSequence::GetStepName(previous)) + " -> " +
        TAutoInspectionSequence::GetStepName(autoInspection.GetStep()) + " : " + reason);
}

//---------------------------------------------------------------------------
// 자동측정 단계와 NG 개수를 초기화한다. PLC 출력과 트레이 데이터 초기화는 InitializeInspection에서 한다.
void __fastcall TTotalForm::ResetAutoInspection()
{
    TAutoInspectionStep previous = autoInspection.GetStep();
    autoInspection.Initialize(GetAutoInspectionSetting());
    measurementNgCount = 0;
    WriteAutoStepLog(previous, "Reset");
}

// 자동 타이머가 꺼져 있어도 상태 타이머에서 PLC 운전 모드를 감시한다.
// PLC 수동/통신 해제 전환 시 한 번만 초기화하며, 자동 복귀는 TRAY IN 대기부터 시작한다.
void __fastcall TTotalForm::UpdateAutoInspectionMode()
{
    const unsigned long version = Mod_PLC->plcAutoMode.GetResetVersion();
    if(!(stage.arl == nAuto && !bLocal))
    {
        // PC manual/local tests retain independent measurement and result-save behavior.
        Timer_AutoInspection->Enabled = false;
        lastPlcAutoResetVersion = version;
        autoInspectionBlockedByPlc = true;
        return;
    }

    const bool plcAuto = Mod_PLC->IsPlcAutoMode();
    const bool wasBlocked = autoInspectionBlockedByPlc;
    if(version != lastPlcAutoResetVersion || (!plcAuto && !wasBlocked))
    {
        Timer_AutoInspection->Enabled = false;
        ResetAutoInspectionForPlcMode();
    }
    lastPlcAutoResetVersion = version;
    autoInspectionBlockedByPlc = !plcAuto;
    Timer_AutoInspection->Enabled = plcAuto;

    if(!plcAuto)
        DisplayError("PLC manual or mode data unavailable. Automatic inspection is disabled.", true);
    else if(wasBlocked)
        DisplayError("");
}
//---------------------------------------------------------------------------
bool __fastcall TTotalForm::IsAutoInspectionBlocked()
{
    UpdateAutoInspectionMode();
    return (stage.arl == nAuto && !bLocal) && autoInspectionBlockedByPlc;
}
//---------------------------------------------------------------------------
// 소프트웨어 시퀀스 초기화이며 물리적인 충전/측정 정지 명령은 보내지 않는다.
// 기존 측정 표시값은 유지하되, 이전 검사에서 대기하던 결과 저장/COMPLETE는 취소한다.
void __fastcall TTotalForm::ResetAutoInspectionForPlcMode()
{
    CancelResultSave();
    ResetAutoInspection();
    InitializePlcData();
    autoInspectionTrayId = "";
    tray.ams = false;
    tray.amf = false;
    // Discard commands and remeasure state belonging to the cancelled automatic cycle.
    send.tx_mode = 0;
    send.time_out = 0;
    while(!q_cmd.empty()) q_cmd.pop();
    while(!q_param.empty()) q_param.pop();
    memset(&retest, 0, sizeof(retest));
    retest.waitingChannel = -1;
    // Only a new tray/manual measurement may set RESULT_IDLE and allow saving again.
    WritePlcLog("PLC MODE", "Automatic cycle reset; next AUTO starts at WAIT_TRAY_IN");
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// 자동측정 타이머 처리: 오류 확인 → 단계 판단 → 명령 실행 → 화면 갱신.
// 호출 위치: FormTotal.cpp의 Timer_AutoInspectionTimer.
void __fastcall TTotalForm::ProcessAutoInspection(TObject *Sender)
{
    UpdateAutoInspectionMode();
    if(!Timer_AutoInspection->Enabled) return;
    // PRECHARGER와 공통 계약: 입력 수집 → 순수 상태 판단 → CMD 실행 → 표시.
    // IR/OCV 차이: 재개폐 재측정 정책을 전달하며 결과 마감은 Timer_ResultSave가 독립 처리한다.
    // 1. 처리 중이면 중복 실행을 막는다.
    if(isAutoInspectionProcessing) return;

    // 실행 중=true, 함수 종료 시 자동으로 false.
    TAutoInspectionRunLock runLock(isAutoInspectionProcessing);
    try
    {
        // 2. 예외로 정지된 상태: 재시작 전까지 진행하지 않는다.
        if(autoInspection.GetStep() == STEP_ERROR_STOP)
        {
            DisplayError("Auto inspection stopped. Check the log and restart.", true);
            return;
        }

        // 3. 측정장비/PLC 연결, PLC 오류 및 수동 운전 차단 조건 확인.
        if(CheckAutoInspectionError()) return;

        // 4. 재측정 설정 전달. 트레이 투입 대기 중에만 반영.
        //    첫 번째: 닫힘 상태 재측정 최대 NG 개수(이하, 0=생략).
        //    두 번째: 프로브 재개폐 추가 측정 횟수(0=생략).
        autoInspection.SetNextTrayRemeasureSettings(
            config.closedProbeRemeasureMaxNgCount, config.probeRemeasureCount);

        // 5. PC→PLC AUTO READY 출력. Auto=1, Local(수동)=0.
        SetAutoReadySignalToPLC();

        // 6. 트레이 유무, 프로브 열림/닫힘, 모드, 셀/NG 개수 확인.
        //    트레이 ID와 CELL SERIAL 완료 여부는 해당 단계에서만 확인.
        TAutoInspectionData data = ReadAutoInspectionData();

        // 변경 전 단계 보관: 단계 로그와 PROBE OPEN 요청 해제에 사용.
        TAutoInspectionStep previous = autoInspection.GetStep();

        // 다음 단계와 실행할 명령을 최대 한 개 결정한다. CMD_NONE은 정상 신호/완료 대기다.
        // RunAutoStep 내부는 PLC/UI를 조작하지 않고 STEP과 대기 횟수만 갱신한다.
        TAutoInspectionCommand command = autoInspection.RunAutoStep(data);

        // 단계가 바뀐 경우에만 로그 기록.
        WriteAutoStepLog(previous, "Timer");

        // 7. 프로브 열림 대기를 마치면 PC→PLC PROBE OPEN 요청 해제.
        //    실제 프로브를 닫는 명령은 아니다.
        if(previous == STEP_WAIT_PROBE_OPEN && command != CMD_NONE)
            ClearProbeOpenSignalToPLC();

        // 명령 실행: PLC 출력, 측정 시작, 시리얼 처리, 오류창 등.
        // 상태 판단 후 실행하므로 새 입력(시리얼 개수/프로브 응답)은 다음 유효 주기에 반영된다.
        RunAutoInspectionCommand(command, data);

        // 8. 현재 단계에 맞춰 진행 화면 갱신.
        DisplayAutoInspectionStep();
    }
    catch(const Exception &error)
    {
        // 예외 내용 기록 후 자동 진행 정지. 설비 비상정지 명령은 아니다.
        StopAutoInspectionOnError(error.Message);
    }
    catch(...)
    {
        // 그 외 예외도 자동 진행 정지.
        StopAutoInspectionOnError("Unknown auto inspection exception");
    }
}

//---------------------------------------------------------------------------

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
    WritePlcLog("IROCV STAGE AUTO/MANUAL", "IROCV STAGE AUTO READY = " + IntToStr(requested));
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
    data.cellSerialContinuousRead = cellSerialContinuousReadForTray;
    data.cellCount = tray.cell_count;
    data.ngCount = measurementNgCount;
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
    WritePlcLog("AutoInspection", "Start reading CELL SERIAL data.");
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
            InitializePlcData();
            InitializeTrayData();
            measurementNgCount = 0;
            DisplayStatus(nREADY);
            break;
        case CMD_READ_TRAY_ID:
            m_dateTime = Now();
            tray.trayid = autoInspectionTrayId;
            pTrayid->Caption = tray.trayid;
            editTrayId->Text = tray.trayid;
            WritePlcLog("AutoInspection", "TRAY ID = " + tray.trayid);
            break;
        case CMD_READ_CELL_DATA:
            ReadAutoCellData();
            break;
        case CMD_PROBE_CLOSE:
        case CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL:
            Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
            WritePlcLog("AutoInspection", "PC_D_IROCV_PROB_CLOSE = 1");
            // 미체크만 투입 시 전체 수신/개수 검사. 상시 모드는 결과 저장 때 검사한다.
            if(command == CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL) StartAutoCellSerialRead();
            break;
        case CMD_SAVE_CELL_SERIAL:
            SaveTrayInfo(tray.trayid);
            WritePlcLog("AutoInspection", "CELL SERIAL complete. Serial = " +
                IntToStr(data.serialCount) + ", CellData = " + IntToStr(data.cellCount));
            break;
        case CMD_CELL_SERIAL_COUNT_ERROR:
        case CMD_CELL_SERIAL_TIMEOUT:
            // 단계는 이미 오류 대기 상태. 창 표시 여부와 무관하게 PLC 오류를 출력한다.
            Mod_PLC->SetValue(PC_D_IROCV_ERROR, 1);
            Form_CellIdError->ChangeMessage("CELL SERIAL - BEFORE MEASUREMENT",
                "Check CELL DATA count and complete CELL SERIAL data.",
                "SAVE: accept data / CANCEL: read again");
            if(command == CMD_CELL_SERIAL_TIMEOUT)
                WritePlcLog("AutoInspection", "CELL SERIAL Read Timeout.");
            else
                WritePlcLog("AutoInspection", "CELL SERIAL Count Error. Serial = " +
                    IntToStr(data.serialCount) + ", CellData = " + IntToStr(data.cellCount));
            Form_CellIdError->DisplayErrorMessage(this->Tag);
            break;
        case CMD_REQUEST_PROBE_REMEASURE:
            // 프로브 열림을 실제 확인한 뒤 요청한다. 기존 전체/불량셀 선택 기준 유지.
            CancelResultSave();
            resultSaveStep = RESULT_IDLE;
            Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
            Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
            // 재개폐 횟수와 닫힘 재측정 NG 제한은 별개. 전체/선택 전환은 사이트 정책 유지.
            if(data.ngCount > PROBE_REMEASURE_ALL_CELL_NG_THRESHOLD)
            {
                ResetMeasurementData(); // 시리얼/파일명/트레이 누계는 보존한다.
                memset(&retest, 0, sizeof(retest));
                retest.waitingChannel = -1;
                tray.rem_mode = 0;
            }
            else
            {
                PrepareRemeasureItems();
                retest.re_excute = true;
                tray.rem_mode = 1;
            }
            resultSaveStep = RESULT_IDLE;
            Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
            WritePlcLog("PROBE REMEASURE", "Request " +
                IntToStr(autoInspection.GetProbeRemeasureDoneCount() + 1) + "/" +
                IntToStr(autoInspection.GetSetting().probeRemeasureCount));
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
                ExecuteRemeasure();
            else
                CmdStartMeasurement();
            break;
        case CMD_NG_ERROR:
            // Already in STEP_WAIT_NG_ERROR before showing a modeless dialog.
            Mod_PLC->SetValue(PC_D_IROCV_ERROR, 1);
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
            WritePlcLog("AutoInspection", command == CMD_BYPASS_TRAY_OUT ?
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
    if(resultSaveStep == RESULT_WAIT_PLC_SEND)
    {
        Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
        DisplayProcess(sFinish, "RESULT SAVE", " Waiting for PLC results / COMPLETE delay ... ");
        return;
    }
    if(IsWaitingForResultSave())
    {
        Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
        DisplayProcess(sBarcode, "CELL SERIAL", " Reading CELL SERIAL before result save ... ");
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
    CancelResultSave();
    TAutoInspectionStep previous = autoInspection.GetStep();
    autoInspection.StopWithError();
    resultSaveStep = RESULT_ERROR;
    // This stops PC sequence progression; it is NOT a PLC emergency stop.
    // Do not issue new probe/tray movements on an exception.
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 1);
    Mod_PLC->SetValue(PC_D_IROCV_MEASURING, 0);
    DisplayStatus(nEND);
    DisplayError(message, true);
    WritePlcLog("AutoInspection ERROR", AnsiString(TAutoInspectionSequence::GetStepName(previous)) + ": " + message);
}


//---------------------------------------------------------------------------
// 시리얼 오류창 SAVE: 현재 데이터를 저장하고 프로브 닫힘 확인 단계로 진행한다.
void __fastcall TTotalForm::AcceptCellSerialData()
{
    // 미체크 모드의 투입 후 오류만 작업자 선택으로 재개한다.
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
    // 미체크 모드의 투입 후 오류만 다시 읽는다.
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
void __fastcall TTotalForm::SetAutoMeasurementComplete()
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
        WritePlcLog("AutoInspection", "Remeasure ignored in " +
            AnsiString(TAutoInspectionSequence::GetStepName(previous)));
        return false;
    }
    WriteAutoStepLog(previous, "Operator remeasure");
    CancelResultSave();
    resultSaveStep = RESULT_IDLE;
    tray.ams = false;
    tray.amf = false;
    measurementNgCount = 0;
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 0);
    Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
    return true;
}

//---------------------------------------------------------------------------
// 자동 배출 판단: Auto/프로브 열림/결과 완료를 확인하고 NG 조건에 따라 오류 대기 또는 배출한다.
void __fastcall TTotalForm::ProcessAutoTrayOut()
{
    if(IsAutoInspectionBlocked()) return;
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
    CancelResultSave(); // [CELL SERIAL 공통] 배출 이후 지연된 결과 저장 방지.
    try
    {
        TAutoInspectionStep previous = autoInspection.GetStep();
        TAutoInspectionCommand command = autoInspection.ForceTrayOut();
        // 작업자가 승인한 배출에서 오류를 해제한다. 오류창 타이머에서는 해제하지 않는다.
        Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
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
        InitializeInspection();
        WritePlcLog("AutoInspection", "Operator restart from TRAY IN");
    }
    catch(const Exception &error) { StopAutoInspectionOnError(error.Message); }
}

//---------------------------------------------------------------------------
// 자동 검사 전체 초기화: PLC 출력 → 트레이 데이터 → 단계 순서로 초기화한다.
void __fastcall TTotalForm::InitializeInspection()
{
    InitializePlcData();
    InitializeTrayData();
    ResetAutoInspection();
    DisplayProcess(sReady, "AutoInspection", " IR/OCV is ready... ");
}

//---------------------------------------------------------------------------
// 메인 화면 수동 배출: 재측정 목록 정리, 강제 배출, PROBE CLOSE=0 / OPEN=1 / COMPLETE=1.
void __fastcall TTotalForm::ProcessManualTrayOut()
{
		for(int i = 0; i < MAXCHANNEL; i++) retest.cell[i] = 0;
		this->ForceTrayOut();

        Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
        Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 1);
        Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);

}
