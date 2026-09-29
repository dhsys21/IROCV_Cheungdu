#include "OperationViewState.h"
#include "PlcAutoMode.h"
#include <stdio.h>
#include <stdlib.h>

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
    Check(V::ActiveTile(STEP_WAIT_CELL_SERIAL) == V::CellData, "serial read preparation active");
    Check(V::ActiveTile(STEP_WAIT_PROBE_CLOSE) == V::CloseConfirmed, "probe down confirmation active");
    Check(V::ActiveTile(STEP_WAIT_REMEASURE_PROBE_CLOSE) == V::CloseConfirmed, "remeasure probe down active");
    Check(V::ActiveTile(STEP_WAIT_MEASURE_COMPLETE) == V::Measure, "measurement active");
    Check(V::ActiveTile(STEP_WAIT_PROBE_OPEN) == V::OpenConfirmed, "probe open confirmation active");
    Check(V::ActiveTile(STEP_WAIT_TRAY_OUT) == V::OutConfirmed, "tray out confirmation active");
    Check(V::ActiveTile(STEP_ERROR_STOP) == -1 && V::ActiveTile(STEP_WAIT_NG_ERROR) == -1,
        "operator/error waits have no active measurement tile");
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
