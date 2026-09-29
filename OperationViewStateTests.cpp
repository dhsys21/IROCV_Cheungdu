#include "OperationViewState.h"
#include "PlcAutoMode.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int checks = 0;
static void Check(bool condition, const char *message)
{
    ++checks;
    if(!condition) { printf("FAIL: %s\n", message); exit(1); }
}
int main()
{
    typedef TOperationViewState V;
    V view;
    Check(view.state[V::Ready] == V::Waiting, "initial ready wait");
    view.Inputs(true, true, true, false);
    Check(view.state[V::CloseConfirmed] == V::Pending, "no unrequested close completion");
    Check(view.state[V::OpenConfirmed] == V::Pending, "no unrequested open completion");
    Check(view.state[V::OutConfirmed] == V::Pending, "no unrequested tray-out completion");
    view.Command(CMD_TRAY_IN);
    Check(view.state[V::TrayIn] == V::Done && view.state[V::TrayId] == V::Waiting, "tray received");
    view.Command(CMD_READ_TRAY_ID);
    view.Command(CMD_READ_CELL_DATA);
    Check(view.state[V::CellData] == V::Done, "cell data read");
    Check(view.state[V::CloseRequest] == V::Pending, "delay is not a close request");
    view.Command(CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL);
    Check(view.state[V::CloseRequest] == V::Done && view.state[V::CloseConfirmed] == V::Waiting, "separate request and confirmation");
    view.Inputs(false, true, true, false);
    Check(view.state[V::CloseConfirmed] == V::Waiting, "invalid PLC data cannot confirm close");
    view.Inputs(true, true, false, true);
    Check(view.state[V::CloseConfirmed] == V::Done, "valid PLC closed input");
    view.Command(CMD_SAVE_CELL_SERIAL);
    Check(view.state[V::Measure] == V::Pending, "serial save does not start measurement");
    view.MeasurementStarted();
    view.Command(CMD_MEASURE_START);
    Check(view.state[V::Measure] == V::Waiting, "measurement wait");
    view.Output(V::OpenRequest, true);
    view.Inputs(true, false, true, true);
    Check(view.state[V::OpenConfirmed] == V::Done, "open may complete before file/result transmission");
    Check(view.state[V::FileSave] == V::Pending, "open does not imply file save");
    view.FileSaved(false);
    Check(view.state[V::FileSave] == V::Warning, "file failure is not shown as saved");
    Check(view.state[V::ResultTransmit] == V::Waiting, "existing continue policy can still transmit");
    view.ResultSent();
    Check(view.state[V::Complete] == V::Pending, "transmission is not complete output / PLC ACK");
    view.Output(V::Complete, true);
    view.Command(CMD_REQUEST_PROBE_REMEASURE);
    Check(view.state[V::CloseRequest] == V::Done && view.state[V::CloseConfirmed] == V::Waiting, "remeasure close request");
    for(int i = V::Measure; i < V::Count; ++i) Check(view.state[i] == V::Pending, "remeasure clears old downstream progress");
    Check(view.state[V::CellData] == V::Done, "remeasure preserves tray data progress");
    view.Command(CMD_REMEASURE_START);
    view.FileSaved(true);
    Check(view.state[V::FileSave] == V::Done, "file success");
    view.Command(CMD_TRAY_OUT);
    view.Inputs(false, false, false, false);
    Check(view.state[V::OutConfirmed] == V::Waiting, "disconnect cannot complete tray out");
    view.Inputs(true, false, true, true);
    Check(view.state[V::OutConfirmed] == V::Waiting, "tray still present");
    view.Inputs(true, false, true, false);
    Check(view.state[V::OutConfirmed] == V::Done, "TRAY IN zero confirms tray out");
    view.Command(CMD_TRAY_OUT_COMPLETE);
    Check(view.state[V::Ready] == V::Waiting && view.state[V::OutConfirmed] == V::Done, "retain completed cycle while idle");
    view.Reset();
    for(int i = 1; i < V::Count; ++i) Check(view.state[i] == V::Pending, "mode reset clears progress");
    view.Command(CMD_BYPASS_TRAY_OUT);
    for(int i = V::TrayId; i < V::OutRequest; ++i) Check(view.state[i] == V::Skipped, "bypass is skipped, not completed");
    Check(view.state[V::OutConfirmed] == V::Waiting, "bypass still waits for tray absence");
    view.Reset();
    view.MeasurementStarted();
    Check(view.state[V::Measure] == V::Waiting && view.state[V::CloseConfirmed] == V::Pending, "manual measurement does not fabricate PLC confirmation");
    TPlcAutoModeState plc;
    Check(!plc.IsValid(), "initial PLC validity");
    plc.Observe(false);
    Check(plc.IsValid() && !plc.IsAutomatic(), "manual is known, not disconnected");
    plc.Invalidate();
    Check(!plc.IsValid(), "invalidated data is unknown");
    Check(V::ActiveTile(STEP_WAIT_TRAY_IN) == V::Ready, "ready only is active while idle");
    Check(V::ActiveTile(STEP_READ_TRAY_ID) == V::TrayId, "tray ID active");
    Check(V::ActiveTile(STEP_WAIT_CELL_SERIAL) == V::CloseRequest, "serial read after close request stays DOWN REQ");
    Check(V::ActiveTile(STEP_WAIT_PROBE_CLOSE) == V::CloseRequest, "probe down wait is request, not OK");
    Check(V::ActiveTile(STEP_WAIT_REMEASURE_PROBE_CLOSE) == V::CloseRequest, "remeasure probe down wait is request");
    Check(V::ActiveTile(STEP_WAIT_MEASURE_COMPLETE) == V::Measure, "measurement active");
    Check(V::ActiveTile(STEP_WAIT_PROBE_OPEN) == V::OpenRequest, "probe open wait is request");
    Check(V::ActiveTile(STEP_WAIT_TRAY_OUT) == V::OutRequest, "tray out wait is request");
    for(int valid = 0; valid < 2; ++valid)
    for(int closed = 0; closed < 2; ++closed)
    for(int opened = 0; opened < 2; ++opened)
    for(int trayPresent = 0; trayPresent < 2; ++trayPresent)
    {
        int down = valid && closed && trayPresent ? V::CloseConfirmed : V::CloseRequest;
        Check(V::ActiveTile(STEP_WAIT_PROBE_CLOSE, valid, closed, opened, trayPresent) == down,
            "DOWN OK requires valid PLC closed and tray present");
        Check(V::ActiveTile(STEP_WAIT_REMEASURE_PROBE_CLOSE, valid, closed, opened, trayPresent) == down,
            "remeasure uses the same confirmation conditions");
        Check(V::ActiveTile(STEP_WAIT_PROBE_OPEN, valid, closed, opened, trayPresent) ==
            (valid && opened ? V::OpenConfirmed : V::OpenRequest), "OPEN OK requires valid PLC open");
        Check(V::ActiveTile(STEP_WAIT_TRAY_OUT, valid, closed, opened, trayPresent) ==
            (valid && !trayPresent ? V::OutConfirmed : V::OutRequest), "OUT OK requires valid tray absence");
    }
    Check(V::ActiveTile(STEP_WAIT_MEASURE_COMPLETE, true, true, false, true) == V::Measure,
        "after confirmation advance to measurement, do not hold stale DOWN OK");
    Check(V::ActiveTile(STEP_ERROR_STOP) == -1 && V::ActiveTile(STEP_WAIT_NG_ERROR) == -1,
        "operator/error waits have no active measurement tile");
    Check(strcmp(V::TileName(V::Ready), "READY") == 0, "log READY matches process label");
    Check(V::IsInternalStepTrace("AutoInspection", "STEP_WAIT_TRAY_IN -> STEP_READ_TRAY_ID : Timer"),
        "early next-step trace is excluded from operator timeline");
    Check(V::IsInternalStepTrace("AutoInspection", "STEP_READ_TRAY_ID -> STEP_READ_CELL_DATA : Timer"),
        "cell-data next-step trace is excluded before tray-id command logs");
    Check(!V::IsInternalStepTrace("AutoInspection", "TRAY ID = TEST01"), "actual tray ID event stays visible");
    Check(!V::IsInternalStepTrace("AutoInspection ERROR", "STEP_WAIT_TRAY_IN: PLC error"),
        "failure diagnostics are not filtered as step traces");
    Check(!V::IsInternalStepTrace("PC_SET", "PROBE_CLOSE (D5): 1 -> 0"), "signal transitions remain visible");
    // Reported startup regression: future-step traces must not split actual commands.
    const char *sources[] = {"PC", "STATE", "AutoInspection", "PLCInitialization",
        "PLC_RX", "STATE", "AutoInspection", "AutoInspection", "STATE"};
    const char *messages[] = {"reset", "Waiting for TRAY IN",
        "STEP_WAIT_TRAY_IN -> STEP_READ_TRAY_ID : Timer", "outputs reset", "TRAY IN confirmed",
        "Reading TRAY ID", "STEP_READ_TRAY_ID -> STEP_READ_CELL_DATA : Timer", "TRAY ID = TEST01", "Reading CELL DATA"};
    const int phases[] = {V::Ready, V::Ready, V::TrayId, V::TrayIn, V::TrayIn, V::TrayId, V::CellData, V::TrayId, V::CellData};
    int previousPhase = V::Ready;
    for(int event = 0; event < 9; ++event)
    {
        if(V::IsInternalStepTrace(sources[event], messages[event])) continue;
        Check(phases[event] >= previousPhase, "normal startup operator timeline does not move backward");
        previousPhase = phases[event];
    }
    Check(strcmp(V::TileName(V::CloseConfirmed), "DOWN OK") == 0, "log DOWN OK matches process label");
    Check(V::CommandTile(CMD_TRAY_IN) == V::TrayIn, "tray-in command logs before next TRAY ID step");
    Check(V::CommandTile(CMD_READ_TRAY_ID) == V::TrayId, "tray ID command retains its phase");
    Check(V::CommandTile(CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL) == V::CloseRequest, "close command phase despite parallel serial read");
    Check(V::CommandTile(CMD_TRAY_OUT_COMPLETE) == V::OutConfirmed, "completion logs OUT OK, not following READY");
    view.Reset();
    Check(view.SignalTile(2, true, true, true, false, true, V::Ready) == V::Ready,
        "unrequested close input does not fabricate DOWN OK phase");
    view.Command(CMD_PROBE_CLOSE);
    Check(view.SignalTile(7, true, true, false, false, true, V::CellData) == V::CloseRequest,
        "PC close assertion logs DOWN REQ");
    Check(view.SignalTile(2, true, true, true, false, true, V::Measure) == V::CloseConfirmed,
        "PLC closed logs DOWN OK even after sequence advances");
    Check(view.SignalTile(7, false, true, true, false, true, V::Measure) == V::CloseConfirmed,
        "PC close request reset after confirmation logs DOWN OK");
    Check(view.SignalTile(7, false, false, true, false, true, V::Measure) == V::Measure,
        "invalid PLC buffer cannot label reset as confirmed");
    Check(view.SignalTile(7, false, true, false, false, true, V::CloseRequest) == V::CloseRequest,
        "cancel without confirmation must not be DOWN OK");
    view.Output(V::OpenRequest, true);
    Check(view.SignalTile(8, true, true, false, false, true, V::FileSave) == V::OpenRequest,
        "open output has its own phase during file save");
    Check(view.SignalTile(3, true, true, false, true, true, V::ResultTransmit) == V::OpenConfirmed,
        "open input has its own phase during result transmission");
    Check(view.SignalTile(2, false, true, false, true, true, V::OpenConfirmed) == V::OpenConfirmed,
        "falling closed input uses current phase, not DOWN OK");
    view.Command(CMD_TRAY_OUT);
    Check(view.SignalTile(1, false, true, false, true, false, V::Ready) == V::OutConfirmed,
        "tray absence logs OUT OK after READY transition");
    Check(view.SignalTile(9, false, true, false, true, false, V::Ready) == V::OutConfirmed,
        "tray out request reset logs OUT OK");
    Check(view.SignalTile(10, true, true, false, true, true, V::ResultTransmit) == V::Complete,
        "COMPLETE output retains event phase");
    // Whole-cycle representative timeline, including both serial modes and all
    // late event phases. Only explicit boundaries may lower the phase index.
    TOperationTimeline timeline;
    Check(timeline.Phase() == V::Ready, "timeline starts READY");
    timeline.BeginTray();
    Check(timeline.Phase() == V::TrayIn && timeline.Attempt() == 1, "new tray boundary");
    timeline.Advance(V::TrayId);timeline.Advance(V::CellData);timeline.Advance(V::CloseRequest);
    const int serialCandidates[] = {
        V::ActiveTile(STEP_WAIT_CELL_SERIAL), V::CommandTile(CMD_SAVE_CELL_SERIAL),
        V::CommandTile(CMD_CELL_SERIAL_COUNT_ERROR), V::ActiveTile(STEP_WAIT_CELL_SERIAL_ERROR),
        V::ActiveTile(STEP_WAIT_PROBE_CLOSE)};
    for(unsigned int i = 0; i < sizeof(serialCandidates)/sizeof(serialCandidates[0]); ++i)
        Check(timeline.Advance(serialCandidates[i]) == V::CloseRequest, "reported DOWN REQ / serial trace never returns to CELL DATA");
    for(int phase = V::CloseConfirmed; phase < V::Count; ++phase)
    {
        Check(timeline.Advance(phase) == phase, "advance whole normal cycle in process order");
        for(int late = V::Ready; late <= phase; ++late)
            Check(timeline.Advance(late) == phase, "late snapshots cannot regress representative phase");
        Check(timeline.Advance(-1) == phase, "error/unknown keeps failing phase");
    }
    timeline.FinishTray();
    Check(timeline.Phase() == V::Ready, "explicit cycle end returns READY");
    unsigned int cycle = timeline.Cycle();
    timeline.BeginTray();
    Check(timeline.Cycle() == cycle+1, "next tray gets a new cycle number");
    timeline.Advance(V::Measure);
    // An early PROBE OPEN event is only body text; the authoritative phase is
    // still MEASURE, then FILE SAVE (including result-time serial), RESULT TX.
    const int resultCandidates[] = {V::Measure,V::FileSave,V::FileSave,V::ResultTransmit,V::ResultTransmit,V::Complete,V::OpenRequest,V::OpenConfirmed};
    int previousResult = V::Measure;
    for(unsigned int i = 0; i < sizeof(resultCandidates)/sizeof(resultCandidates[0]); ++i)
    {
        int phase = timeline.Advance(resultCandidates[i]);
        Check(phase >= previousResult, "parallel probe open and result processing are monotonic");
        previousResult = phase;
    }
    timeline.BeginRemeasure();
    Check(timeline.Phase() == V::CloseRequest && timeline.Attempt() == 2, "explicit remeasure boundary restarts attempt at DOWN REQ");
    timeline.Advance(V::Measure);timeline.Advance(V::FileSave);
    Check(timeline.Advance(V::Measure) == V::FileSave, "late AMF does not regress remeasure attempt");
    timeline.Reset();
    Check(timeline.Phase() == V::Ready && timeline.Attempt() == 0, "explicit reset boundary");
    timeline.BeginTray();timeline.Advance(V::OutRequest);timeline.Advance(V::OutConfirmed);
    Check(timeline.Phase() == V::OutConfirmed, "bypass/forced out skips phases without fake measurement");
    timeline.FinishTray();timeline.BeginManual();
    Check(timeline.Phase() == V::Measure, "manual cycle does not fabricate tray input");
    timeline.Advance(V::FileSave);
    Check(timeline.Advance(V::Ready) == V::FileSave, "manual idle snapshot cannot interleave READY during save");
    timeline.Advance(V::ResultTransmit);timeline.Advance(V::Complete);
    Check(timeline.Advance(V::Ready) == V::Complete, "manual result completion stays COMPLETE until an explicit boundary");
    timeline.BeginManual();
    Check(timeline.Phase() == V::Measure && timeline.Attempt() == 1, "next manual measurement explicitly restarts at MEASURE");
    Check(timeline.Advance(V::Count) == V::Measure, "out of range candidate cannot corrupt timeline");
    TOperationCycleClock clock;
    Check(clock.Elapsed(9999) == 0, "READY never accumulates elapsed time");
    clock.Start(1000);
    Check(clock.Elapsed(2500) == 1500, "elapsed begins at tray in");
    clock.Start(2000);
    Check(clock.Elapsed(3000) == 2000, "repeated start does not reset tray time");
    Check(clock.Finish(4000) == 3000, "tray out returns total time for log");
    Check(clock.Elapsed(10000) == 0 && !clock.IsRunning(), "ready is zero after tray out");
    clock.Start(12000);clock.Reset();
    Check(clock.Elapsed(15000) == 0, "manual/reset cancels displayed tray timing");
    clock.Start(0xFFFFFFF0UL);
    Check(clock.Elapsed(0x20UL) == 48, "32-bit timer rollover");
    printf("PASS: %d newGui progress / current-step / tray-clock / validity checks\n", checks);
    return 0;
}
