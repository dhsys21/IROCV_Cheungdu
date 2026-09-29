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
#endif
