#ifndef OperationViewStateH
#define OperationViewStateH

#include "AutoInspectionSequence.h"

// Display-only history. No PLC writes, timing decisions or production interlocks.
// Completion is recorded from executed commands / confirmed inputs, not from tile order.
class TOperationViewState
{
public:
    enum { Count = 14 };
    enum TState { Pending, Waiting, Done, Skipped, Warning };
    enum TTile { Ready, TrayIn, TrayId, CellData, CloseRequest, CloseConfirmed,
        Measure, FileSave, ResultTransmit, Complete, OpenRequest, OpenConfirmed,
        OutRequest, OutConfirmed };
    TState state[Count];

    TOperationViewState() { Reset(); }
    // Current step only: completed history must not leave multiple green tiles.
    static int ActiveTile(TAutoInspectionStep step, bool valid = false,
        bool closed = false, bool opened = false, bool trayPresent = true)
    {
        switch(step)
        {
            case STEP_WAIT_TRAY_IN: return Ready;
            case STEP_READ_TRAY_ID: return TrayId;
            case STEP_READ_CELL_DATA:
            case STEP_WAIT_START_DELAY:
            case STEP_WAIT_CELL_SERIAL: return CellData;
            case STEP_WAIT_PROBE_CLOSE:
            case STEP_WAIT_REMEASURE_PROBE_CLOSE:
                // WAIT is the request phase, not proof of PLC completion.
                return valid && closed && trayPresent ? CloseConfirmed : CloseRequest;
            case STEP_WAIT_MEASURE_COMPLETE: return Measure;
            case STEP_WAIT_PROBE_OPEN: return valid && opened ? OpenConfirmed : OpenRequest;
            case STEP_WAIT_TRAY_OUT: return valid && !trayPresent ? OutConfirmed : OutRequest;
            default: return -1; // Error/operator-decision state: no running tile.
        }
    }
    void Reset()
    {
        for(int i = 0; i < Count; ++i) state[i] = Pending;
        state[Ready] = Waiting;
    }
    void ResetMeasurement()
    {
        for(int i = CloseRequest; i < Count; ++i) state[i] = Pending;
    }
    void MeasurementStarted()
    {
        for(int i = Measure; i < Count; ++i) state[i] = Pending;
        state[Measure] = Waiting;
    }
    void Command(TAutoInspectionCommand command)
    {
        switch(command)
        {
            case CMD_TRAY_IN:
                Reset(); state[Ready] = state[TrayIn] = Done;
                state[TrayId] = Waiting; break;
            case CMD_READ_TRAY_ID:
                state[TrayId] = Done; state[CellData] = Waiting; break;
            case CMD_READ_CELL_DATA: state[CellData] = Done; break;
            case CMD_PROBE_CLOSE:
            case CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL:
                state[CloseRequest] = Done; state[CloseConfirmed] = Waiting; break;
            case CMD_REQUEST_PROBE_REMEASURE:
                ResetMeasurement(); state[CloseRequest] = Done;
                state[CloseConfirmed] = Waiting; break;
            case CMD_MEASURE_START:
            case CMD_REMEASURE_START:
                // The sequence has already checked both TRAY IN and PROBE CLOSED.
                state[CloseConfirmed] = Done; state[Measure] = Waiting; break;
            case CMD_BYPASS_TRAY_OUT:
                Reset(); state[Ready] = state[TrayIn] = Done;
                for(int i = TrayId; i < OutRequest; ++i) state[i] = Skipped;
                state[OutRequest] = Done; state[OutConfirmed] = Waiting; break;
            case CMD_TRAY_OUT:
                state[OutRequest] = Done; state[OutConfirmed] = Waiting; break;
            case CMD_TRAY_OUT_COMPLETE:
                // In this PLC contract completion means TRAY IN became zero.
                state[OutConfirmed] = Done; state[Ready] = Waiting; break;
            default: break;
        }
    }
    void Output(int tile, bool on)
    {
        if(!on) return;
        state[tile] = Done;
        if(tile == CloseRequest && state[CloseConfirmed] == Pending) state[CloseConfirmed] = Waiting;
        if(tile == OpenRequest && state[OpenConfirmed] == Pending) state[OpenConfirmed] = Waiting;
        if(tile == OutRequest && state[OutConfirmed] == Pending) state[OutConfirmed] = Waiting;
    }
    void Inputs(bool valid, bool closed, bool opened, bool trayPresent)
    {
        if(!valid) return; // Never turn a stale/disconnected zero into completion.
        if(state[CloseRequest] == Done && closed) state[CloseConfirmed] = Done;
        if(state[OpenRequest] == Done && opened) state[OpenConfirmed] = Done;
        if(state[OutRequest] == Done && !trayPresent) state[OutConfirmed] = Done;
    }
    void FileSaved(bool saved)
    {
        state[Measure] = Done;
        state[FileSave] = saved ? Done : Warning;
        state[ResultTransmit] = Waiting;
    }
    void ResultSent() { state[ResultTransmit] = Done; }
};

// Display clock only; unsigned 32-bit subtraction also handles GetTickCount wrap.
// Start is idempotent, so retry/remeasure cannot restart the tray's total time.
class TOperationCycleClock
{
    bool running;
    unsigned long started;
public:
    TOperationCycleClock() : running(false), started(0) {}
    void Reset() { running = false; started = 0; }
    void Start(unsigned long now) { if(!running) { running = true; started = now; } }
    bool IsRunning() const { return running; }
    unsigned long Elapsed(unsigned long now) const { return running ? now - started : 0; }
    unsigned long Finish(unsigned long now)
    {
        unsigned long elapsed = Elapsed(now);
        Reset();
        return elapsed;
    }
};
#endif
