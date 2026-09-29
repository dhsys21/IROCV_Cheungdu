// newGui: display-only layout, current wait and bounded operator event history.
// Right-hand FormMeasureInfo and all production decisions remain unchanged.
#include <vcl.h>
#pragma hdrstop
#include "OperationView.h"
#include "FormTotal.h"
#include "RVMO_main.h"
#include <Clipbrd.hpp>

namespace
{
const char *TileNames[TOperationViewState::Count] = {
    "READY", "TRAY IN", "TRAY ID", "CELL DATA", "CLOSE REQ", "CLOSE OK", "MEASURE",
    "SAVE FILE", "RESULT TX", "COMPLETE", "OPEN REQ", "OPEN OK", "OUT REQ", "OUT OK"
};
const int InputAddresses[] = { PLC_D_IROCV_AUTO_MANUAL, PLC_D_IROCV_TRAY_IN,
    PLC_D_IROCV_PROB_CLOSE, PLC_D_IROCV_PROB_OPEN, PLC_D_IROCV_COMPLETE, PLC_D_IROCV_ERROR };
const char *InputNames[] = { "AUTO_MANUAL", "TRAY_IN", "PROB_CLOSE", "PROB_OPEN", "COMPLETE", "ERROR" };
const int OutputAddresses[] = { PC_D_IROCV_STAGE_AUTO_READY, PC_D_IROCV_PROB_CLOSE,
    PC_D_IROCV_PROB_OPEN, PC_D_IROCV_TRAY_OUT, PC_D_IROCV_COMPLETE, PC_D_IROCV_ERROR };
const char *OutputNames[] = { "AUTO_READY", "PROB_CLOSE", "PROB_OPEN", "TRAY_OUT", "COMPLETE", "ERROR" };

bool Connected(TClientSocket *client)
{
    return client && client->Active && client->Socket && client->Socket->Connected;
}
}

__fastcall TOperationView::TOperationView(TTotalForm *owner)
    : TComponent(owner), stageForm(owner), refreshTimer(NULL), logMemo(NULL),
      waitStarted(GetTickCount()), signalsKnown(false), plcWasValid(false), previousCloseRequest(0)
{
    // Layout belongs to FormTotal.dfm. Never override designer bounds at runtime.
    // The form owns visual controls; this observer owns only its refresh timer.
    modeLabel = owner->lblOperationMode;
    serialLabel = owner->lblOperationSerial;
    currentTitle = owner->lblOperationTitle;
    currentDetail = owner->lblOperationDetail;
    elapsedLabel = owner->lblOperationElapsed;
    logMemo = owner->memoOperationLog;
    followLog = owner->chkOperationFollow;
    followLog->OnClick = FollowLogClick;
    owner->btnOperationCopy->OnClick = CopyLog;
    tiles[0] = owner->pOpReady;
    tileLabels[0] = owner->lblOpReady;
    tiles[1] = owner->pOpTrayIn;
    tileLabels[1] = owner->lblOpTrayIn;
    tiles[2] = owner->pOpTrayId;
    tileLabels[2] = owner->lblOpTrayId;
    tiles[3] = owner->pOpCellData;
    tileLabels[3] = owner->lblOpCellData;
    tiles[4] = owner->pOpCloseRequest;
    tileLabels[4] = owner->lblOpCloseRequest;
    tiles[5] = owner->pOpCloseConfirmed;
    tileLabels[5] = owner->lblOpCloseConfirmed;
    tiles[6] = owner->pOpMeasure;
    tileLabels[6] = owner->lblOpMeasure;
    tiles[7] = owner->pOpFileSave;
    tileLabels[7] = owner->lblOpFileSave;
    tiles[8] = owner->pOpResultTransmit;
    tileLabels[8] = owner->lblOpResultTransmit;
    tiles[9] = owner->pOpComplete;
    tileLabels[9] = owner->lblOpComplete;
    tiles[10] = owner->pOpOpenRequest;
    tileLabels[10] = owner->lblOpOpenRequest;
    tiles[11] = owner->pOpOpenConfirmed;
    tileLabels[11] = owner->lblOpOpenConfirmed;
    tiles[12] = owner->pOpOutRequest;
    tileLabels[12] = owner->lblOpOutRequest;
    tiles[13] = owner->pOpOutConfirmed;
    tileLabels[13] = owner->lblOpOutConfirmed;
    if(owner->CurrentGrp && owner->CurrentGrp->Visible)
        owner->CurrentGrp->BringToFront();

    DrawTiles();
    Append("UI", "newGui ready. Right-hand measurement screen is unchanged.");
    refreshTimer = new TTimer(this);
    refreshTimer->Enabled = false;
    refreshTimer->Interval = 200;
    refreshTimer->OnTimer = TimerTick;
    refreshTimer->Enabled = true;
}

void __fastcall TOperationView::CopyLog(TObject *)
{
    Clipboard()->AsText = logMemo->SelLength > 0 ? logMemo->SelText : logMemo->Lines->Text;
}
void __fastcall TOperationView::FollowLogClick(TObject *)
{
    if(followLog->Checked)
    {
        logMemo->SelStart = logMemo->Text.Length();
        logMemo->Perform(EM_SCROLLCARET, 0, 0);
    }
}
void TOperationView::Append(AnsiString source, AnsiString message)
{
    if(!logMemo || message.IsEmpty()) return;
    message = StringReplace(message, "\r", " ", TReplaceFlags() << rfReplaceAll);
    message = StringReplace(message, "\n", " ", TReplaceFlags() << rfReplaceAll);
    if(message.Length() > 1200) message = message.SubString(1, 1200) + " ...";
    // Existing DisplayProcess writes the same text into both files. One UI row is enough.
    AnsiString key = source + ": " + message.Trim();
    if(key == lastLog) return;
    lastLog = key;
    int firstLine = logMemo->Perform(EM_GETFIRSTVISIBLELINE, 0, 0);
    int selection = logMemo->SelStart, length = logMemo->SelLength;
    logMemo->Lines->BeginUpdate();
    try
    {
        // Bounded memory even during a long production run; original file logs remain intact.
        while(logMemo->Lines->Count >= 500)
        {
            selection -= logMemo->Lines->Strings[0].Length() + 2;
            if(selection < 0) selection = 0;
            logMemo->Lines->Delete(0);
            if(firstLine > 0) --firstLine;
        }
        logMemo->Lines->Add(Now().FormatString("hh:nn:ss.zzz ") + "[" + source + "] " + message.Trim());
    }
    __finally { logMemo->Lines->EndUpdate(); }
    if(followLog->Checked) FollowLogClick(NULL);
    else
    {
        logMemo->SelStart = selection;
        logMemo->SelLength = length;
        int visible = logMemo->Perform(EM_GETFIRSTVISIBLELINE, 0, 0);
        logMemo->Perform(EM_LINESCROLL, 0, firstLine - visible);
    }
}
void TOperationView::Reset()
{
    progress.Reset();
    previousCloseRequest = 0;
    lastWaitKey = "";
    Append("PC", "Inspection reset; waiting for a new tray.");
    DrawTiles();
}
void TOperationView::Command(TAutoInspectionCommand command)
{
    progress.Command(command);
    if(command == CMD_TRAY_IN) Append("PLC RX", "TRAY IN confirmed; new cycle.");
    if(command == CMD_READ_CELL_DATA) Append("PC", "CELL DATA read: " + IntToStr(stageForm->tray.cell_count) + " cells.");
    if(command == CMD_MEASURE_START || command == CMD_REMEASURE_START)
        Append("PLC RX", "PROBE CLOSED and TRAY IN confirmed; measurement requested.");
    if(command == CMD_TRAY_OUT_COMPLETE) Append("PLC RX", "TRAY IN = 0; tray-out complete.");
    DrawTiles();
}
void TOperationView::FileSaved(bool saved)
{
    progress.FileSaved(saved);
    Append(saved ? "PC" : "WARNING", saved ? "Result file saved." : "Result file save failed after retry; existing continue policy retained.");
    DrawTiles();
}
void TOperationView::MeasurementStarted()
{
    if(stageForm->bLocal || stageForm->stage.arl == nLocal) progress.Reset();
    progress.MeasurementStarted();
    Append("PC", "Measurement command queued (AMS); waiting for device responses.");
    DrawTiles();
}
void TOperationView::DrawTiles()
{
    for(int i = 0; i < TOperationViewState::Count; ++i)
    {
        const TOperationViewState::TState state = progress.state[i];
        const char *status = state == TOperationViewState::Done ? "DONE" :
            state == TOperationViewState::Waiting ? "WAIT" :
            state == TOperationViewState::Skipped ? "SKIP" :
            state == TOperationViewState::Warning ? "WARNING" : "-";
        if(state == TOperationViewState::Done &&
            (i == TOperationViewState::CloseRequest || i == TOperationViewState::OpenRequest ||
             i == TOperationViewState::OutRequest || i == TOperationViewState::Complete)) status = "SET";
        tileLabels[i]->Caption = AnsiString(TileNames[i]) + "\r\n" + status;
        tiles[i]->Color = state == TOperationViewState::Done ? (TColor)RGB(220, 242, 226) :
            state == TOperationViewState::Waiting ? (TColor)RGB(255, 236, 186) :
            state == TOperationViewState::Warning ? (TColor)RGB(255, 212, 212) : (TColor)RGB(234, 239, 245);
    }
}
void TOperationView::ObserveSignals(bool valid)
{
    // Input values are display samples of the last complete PLC response.
    // Output values are buffer settings, never labelled PLC ACK or device completion.
    for(int i = 0; i < 12; ++i)
    {
        if(i < 6 && !valid) continue;
        int address = i < 6 ? InputAddresses[i] : OutputAddresses[i - 6];
        int value = (int)(i < 6 ? Mod_PLC->GetPlcValue(address) : Mod_PLC->GetValue(address));
        AnsiString text = IntToStr(value);
        if(!signalsKnown || (i < 6 && !plcWasValid))
            lastSignals[i] = text; // Baseline is not a fabricated 0 -> 1 transition.
        else if(text != lastSignals[i])
        {
            AnsiString name = i < 6 ? InputNames[i] : OutputNames[i - 6];
            Append(i < 6 ? "PLC RX" : "PC SET", name + " (D" + IntToStr(address) + "): " + lastSignals[i] + " -> " + text);
            lastSignals[i] = text;
        }
    }
    signalsKnown = true;
    plcWasValid = valid;
    int closeRequest = (int)Mod_PLC->GetValue(PC_D_IROCV_PROB_CLOSE);
    if(closeRequest == 1 && previousCloseRequest == 0 &&
        progress.state[TOperationViewState::Measure] != TOperationViewState::Pending)
        progress.ResetMeasurement();
    previousCloseRequest = closeRequest;
    progress.Output(TOperationViewState::CloseRequest, closeRequest == 1);
    progress.Output(TOperationViewState::OpenRequest, Mod_PLC->GetValue(PC_D_IROCV_PROB_OPEN) == 1);
    progress.Output(TOperationViewState::OutRequest, Mod_PLC->GetValue(PC_D_IROCV_TRAY_OUT) == 1);
    progress.Output(TOperationViewState::Complete, Mod_PLC->GetValue(PC_D_IROCV_COMPLETE) == 1);
    progress.Inputs(valid, Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE) == 1,
        Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN) == 1, Mod_PLC->GetPlcValue(PLC_D_IROCV_TRAY_IN) == 1);
}
void TOperationView::SetCurrent(AnsiString title, AnsiString detail, bool error)
{
    AnsiString key = title;
    if(key != lastWaitKey)
    {
        lastWaitKey = key;
        waitStarted = GetTickCount();
        Append(error ? "ATTENTION" : "STATE", title);
    }
    currentTitle->Caption = title;
    currentTitle->Font->Color = error ? clRed : (TColor)RGB(18, 77, 124);
    currentDetail->Caption = detail;
    elapsedLabel->Caption = "Elapsed " + FormatFloat("0.0", (DWORD)(GetTickCount() - waitStarted) / 1000.0) + " s";
}
void TOperationView::Refresh()
{
    TTotalForm *f = stageForm;
    const bool plcConnected = Connected(Mod_PLC->ClientSocket_PC) && Connected(Mod_PLC->ClientSocket_PLC);
    const bool valid = plcConnected && Mod_PLC->plcAutoMode.IsValid();
    const bool local = f->bLocal || f->stage.arl == nLocal;
    ObserveSignals(valid);
    modeLabel->Caption = AnsiString("PC: ") + (local ? "MANUAL" : "AUTO") + "   PLC: " +
        (!valid ? "UNKNOWN" : Mod_PLC->IsPlcAutoMode() ? "AUTO" : "MANUAL");
    f->localTest->Visible = local;
    f->localCali->Visible = local;
    const TAutoInspectionStep step = f->autoInspection.GetStep();
    const bool serialWaiting = step == STEP_WAIT_CELL_SERIAL || f->resultSaveStep == RESULT_WAIT_SERIAL;
    int chunks = Mod_PLC->CellSerialReadRequested ? 0 :
        Mod_PLC->IsCellSerialReadComplete() ? PLC_D_CELL_SERIAL_READCOUNT : Mod_PLC->CellSerialIndex;
    AnsiString serialText = AnsiString("CELL SERIAL: ") + (f->cellSerialContinuousReadForTray ? "AT RESULT SAVE" : "BEFORE MEASURE");
    if(serialWaiting) serialText += "   RECEIVED " + IntToStr(chunks) + "/" + IntToStr(PLC_D_CELL_SERIAL_READCOUNT) + " BLOCKS";
    serialLabel->Caption = serialText;
    AnsiString title, detail;
    bool error = false;
    if(!Connected(f->Client)) { title = "IR/OCV disconnected"; detail = "Waiting for the measurement equipment connection."; error = true; }
    else if(f->stage.alarm_status == nEmergency) { title = "Equipment emergency"; detail = "Equipment reports EMERGENCY. Check the equipment before restarting."; error = true; }
    else if(f->stage.alarm_status == nOpbox) { title = "Equipment OP BOX alarm"; detail = "Check the equipment operation box and alarm status."; error = true; }
    else if(!valid) { title = "PLC data unavailable"; detail = "Waiting for both PLC connections and a complete interface response.\r\nInput values must not be treated as current until reception completes."; error = true; }
    else if(!local && !Mod_PLC->IsPlcAutoMode()) { title = "PLC MANUAL - automatic cycle reset"; detail = "Automatic inspection is disabled. Next PLC AUTO starts from TRAY IN."; }
    else if(step == STEP_ERROR_STOP || f->resultSaveStep == RESULT_ERROR) { title = "Inspection stopped"; detail = f->Panel_State->Caption; error = true; }
    else if(Mod_PLC->GetPlcValue(PLC_D_IROCV_ERROR) != 0) { title = "PLC error"; detail = "PLC_D_IROCV_ERROR is nonzero. Check the PLC interface and equipment."; error = true; }
    else if(step == STEP_WAIT_CELL_SERIAL_ERROR) { title = "CELL SERIAL verification error"; detail = "Waiting for SAVE (accept) / CANCEL (read again) in CELL ID ERROR.\r\nCELL DATA: " + IntToStr(f->tray.cell_count) + " cells."; error = true; }
    else if(step == STEP_WAIT_NG_ERROR) { title = "NG - operator decision required"; detail = "Waiting for TRAY OUT / RESTART in the NG error window."; error = true; }
    else if(f->Panel_State->Color == clRed && !f->Panel_State->Caption.IsEmpty()) { title = "Inspection warning / error"; detail = f->Panel_State->Caption; error = true; }
    else if(f->resultSaveStep == RESULT_WAIT_SERIAL) { title = "Reading CELL SERIAL for result save"; detail = "Waiting for all serial blocks. No partial/previous read is used.\r\nProgress: " + IntToStr(chunks) + "/" + IntToStr(PLC_D_CELL_SERIAL_READCOUNT) + " blocks."; }
    else if(f->resultSaveStep == RESULT_WAIT_PLC_SEND)
    {
        bool sent = Mod_PLC->WasResultTransmitted();
        if(sent) progress.ResultSent();
        title = sent ? "Waiting for COMPLETE delay" : "Sending PLC result data";
        detail = sent ? "Result blocks transmitted; waiting for the configured COMPLETE delay.\r\nTransmission completion is not a PLC application ACK." : "Waiting for result-code, IR and OCV blocks to be transmitted.\r\nPC COMPLETE remains zero until the existing completion conditions pass.";
    }
    else if(local && step == STEP_WAIT_TRAY_IN)
    {
        title = f->tray.ams && !f->tray.amf ? "Manual measurement in progress" : "Manual mode";
        detail = "Manual measurement controls remain in the right-hand measurement screen.\r\nAutomatic inspection is disabled.";
    }
    else
    {
        switch(step)
        {
            case STEP_WAIT_TRAY_IN: title = "Waiting for TRAY IN"; detail = "PLC_D_IROCV_TRAY_IN: " + IntToStr((int)Mod_PLC->GetPlcValue(PLC_D_IROCV_TRAY_IN)) + " -> expected 1"; break;
            case STEP_READ_TRAY_ID: title = "Reading TRAY ID"; detail = "Waiting for a valid tray ID in the PLC interface data."; break;
            case STEP_READ_CELL_DATA: title = "Reading CELL DATA"; detail = "Reading channel occupancy from PLC CELL DATA."; break;
            case STEP_WAIT_START_DELAY: title = f->tray.cell_count > 0 ? "Measurement start delay" : "Waiting for CELL DATA"; detail = "CELL DATA: " + IntToStr(f->tray.cell_count) + " cells.\r\nStart delay: " + IntToStr((int)f->autoInspection.GetWaitCount()) + "/" + IntToStr((int)f->autoInspection.GetSetting().startDelayCount) + " timer ticks."; break;
            case STEP_WAIT_CELL_SERIAL: title = "Reading and verifying CELL SERIAL"; detail = "Waiting for all serial blocks, then comparing serial count with CELL DATA.\r\nProgress: " + IntToStr(chunks) + "/" + IntToStr(PLC_D_CELL_SERIAL_READCOUNT) + " blocks. CELL DATA: " + IntToStr(f->tray.cell_count); break;
            case STEP_WAIT_PROBE_CLOSE:
            case STEP_WAIT_REMEASURE_PROBE_CLOSE:
                title = "Waiting for PROBE CLOSED";
                detail = "PC_D_IROCV_PROB_CLOSE = " + IntToStr((int)Mod_PLC->GetValue(PC_D_IROCV_PROB_CLOSE)) + " (output setting)\r\nPLC_D_IROCV_PROB_CLOSE: " + IntToStr((int)Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE)) + " -> expected 1\r\nTRAY IN must also remain 1."; break;
            case STEP_WAIT_MEASURE_COMPLETE:
                title = f->tray.rem_mode ? "Remeasurement in progress" : "Measurement in progress";
                detail = "Waiting for measurement responses / result processing."; break;
            case STEP_WAIT_PROBE_OPEN:
                title = "Waiting for PROBE OPEN";
                detail = "PC_D_IROCV_PROB_OPEN = " + IntToStr((int)Mod_PLC->GetValue(PC_D_IROCV_PROB_OPEN)) + " (output setting)\r\nPLC_D_IROCV_PROB_OPEN: " + IntToStr((int)Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN)) + " -> expected 1"; break;
            case STEP_WAIT_TRAY_OUT:
                title = "Waiting for TRAY OUT completion";
                detail = "PC_D_IROCV_TRAY_OUT = " + IntToStr((int)Mod_PLC->GetValue(PC_D_IROCV_TRAY_OUT)) + " (output setting)\r\nPLC_D_IROCV_TRAY_IN: " + IntToStr((int)Mod_PLC->GetPlcValue(PLC_D_IROCV_TRAY_IN)) + " -> expected 0"; break;
            default: title = "Waiting"; detail = f->Panel_State->Caption; break;
        }
    }
    if(f->resultSaveStep == RESULT_COMPLETE)
    {
        progress.ResultSent();
        progress.Output(TOperationViewState::Complete, true);
    }
    if(step == STEP_WAIT_MEASURE_COMPLETE || (local && f->tray.ams && !f->tray.amf))
    {
        int ir = 0, ocv = 0;
        for(int i = 0; i < MAXCHANNEL; ++i) { if(f->irValueReceived[i]) ++ir; if(f->ocvValueReceived[i]) ++ocv; }
        detail += "\r\nReceived IR: " + IntToStr(ir) + " / OCV: " + IntToStr(ocv) + " (" + IntToStr(MAXCHANNEL) + " channels)";
    }
    SetCurrent(title, detail, error);
    DrawTiles();
}
void __fastcall TOperationView::TimerTick(TObject *)
{
    // A display failure must never change an inspection state, PLC output or timer.
    try { Refresh(); } catch(...) { currentTitle->Caption = "Display refresh error - check logs"; }
}

void __fastcall TTotalForm::CreateOperationView()
{
    if(!operationView) operationView = new TOperationView(this);
}
void __fastcall TTotalForm::ResetOperationView()
{
    try { if(operationView) operationView->Reset(); } catch(...) {}
}
void __fastcall TTotalForm::RecordOperationCommand(TAutoInspectionCommand command)
{
    try { if(operationView) operationView->Command(command); } catch(...) {}
}
void __fastcall TTotalForm::RecordOperationFileSave(bool saved)
{
    try { if(operationView) operationView->FileSaved(saved); } catch(...) {}
}
void __fastcall TTotalForm::RecordOperationMeasurementStart()
{
    try { if(operationView) operationView->MeasurementStarted(); } catch(...) {}
}
void __fastcall TTotalForm::AppendOperationLog(AnsiString type, AnsiString message)
{
    try
    {
        if(!operationView) return;
        // Raw IR/OCV samples and polling traffic stay in the original communication file.
        if(type == "RX" || type == "TX")
        {
            if(message.Pos("AMS") == 0 && message.Pos("AMF") == 0 && message.Pos("STP") == 0) return;
            type = type == "RX" ? "DEVICE RX" : "DEVICE TX REQUEST";
        }
        if(type == "AutoInspection" && message.Pos("...") != 0) return;
        operationView->Append(type, message);
    }
    catch(...) {} // UI logging is not part of the production-control contract.
}
