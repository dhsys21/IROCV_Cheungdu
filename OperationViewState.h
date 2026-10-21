#ifndef OperationViewStateH
#define OperationViewStateH

#include "AutoInspectionSequence.h"
#include <string.h>

// 표시용 이력. PLC 출력·시간 판정·인터록에 관여하지 않는다.
// 완료는 타일 순서가 아닌 실행 명령과 확인된 입력으로 기록한다.
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
    // 시퀀스는 현재 명령 실행 전에 다음 단계를 설정한다.
    // 이 내부 추적은 운영 이력이 아닌 기존 PLC 로그에 남긴다.
    static bool IsInternalStepTrace(const char *source, const char *message)
    {
        return strcmp(source, "AutoInspection") == 0 &&
            strncmp(message, "STEP_", 5) == 0 && strstr(message, " -> STEP_") != 0;
    }
    static const char *TileName(int tile)
    {
        static const char *names[Count] = { "READY", "TRAY IN", "TRAY ID", "CELL DATA",
            "DOWN REQ", "DOWN OK", "MEASURE", "SAVE FILE", "RESULT TX", "COMPLETE",
            "OPEN REQ", "OPEN OK", "OUT REQ", "OUT OK" };
        return tile >= 0 && tile < Count ? names[tile] : names[Ready];
    }
    static int CommandTile(TAutoInspectionCommand command)
    {
        switch(command)
        {
            case CMD_TRAY_IN: return TrayIn;
            case CMD_READ_TRAY_ID: return TrayId;
            case CMD_READ_CELL_DATA: return CellData;
            case CMD_SAVE_CELL_SERIAL:
            case CMD_CELL_SERIAL_COUNT_ERROR:
            case CMD_CELL_SERIAL_TIMEOUT: return CloseRequest;
            case CMD_PROBE_CLOSE:
            case CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL:
            case CMD_REQUEST_PROBE_REMEASURE: return CloseRequest;
            case CMD_MEASURE_START:
            case CMD_REMEASURE_START: return Measure;
            case CMD_NG_ERROR: return OpenConfirmed;
            case CMD_BYPASS_TRAY_OUT:
            case CMD_TRAY_OUT: return OutRequest;
            case CMD_TRAY_OUT_COMPLETE: return OutConfirmed;
            default: return -1;
        }
    }
    // 입력 수신보다 화면이 앞서갈 수 있으므로 핸드셰이크 초기화는
    // 후속 측정·준비 단계가 아닌 실제 이벤트로 구분한다.
    int SignalTile(int index, bool on, bool valid, bool closed, bool opened,
        bool trayPresent, int current) const
    {
        if(index < 6 && !valid) return current;
        if(index == 1 && on) return TrayIn;
        if((index == 1 || index == 9) && !on && valid && !trayPresent && state[OutRequest] == Done)
            return OutConfirmed;
        if(index == 7 && on) return CloseRequest;
        if(((index == 2 && on) || (index == 7 && !on)) && valid && closed && trayPresent && state[CloseRequest] == Done)
            return CloseConfirmed;
        if(index == 8 && on) return OpenRequest;
        if(index == 3 && on && valid && opened && state[OpenRequest] == Done) return OpenConfirmed;
        if(index == 9 && on) return OutRequest;
        if((index == 4 || index == 10) && on) return Complete;
        if(index == 6 && on) return Ready;
        return current;
    }
    // 현재 단계만 표시한다. 완료 이력으로 여러 타일을 켜지 않는다.
    static int ActiveTile(TAutoInspectionStep step, bool valid = false,
        bool closed = false, bool opened = false, bool trayPresent = true)
    {
        switch(step)
        {
            case STEP_WAIT_TRAY_IN: return Ready;
            case STEP_READ_TRAY_ID: return TrayId;
            case STEP_READ_CELL_DATA:
            case STEP_WAIT_START_DELAY: return CellData;
            case STEP_WAIT_CELL_SERIAL:
            case STEP_WAIT_CELL_SERIAL_ERROR: return CloseRequest;
            case STEP_WAIT_PROBE_CLOSE:
            case STEP_WAIT_REMEASURE_PROBE_CLOSE:
                // WAIT는 요청 단계이며 PLC 완료를 뜻하지 않는다.
                return valid && closed && trayPresent ? CloseConfirmed : CloseRequest;
            case STEP_WAIT_MEASURE_COMPLETE: return Measure;
            case STEP_WAIT_PROBE_OPEN: return valid && opened ? OpenConfirmed : OpenRequest;
            case STEP_WAIT_TRAY_OUT: return valid && !trayPresent ? OutConfirmed : OutRequest;
            default: return -1; // 오류·운영자 선택 대기 중에는 진행 타일을 끈다.
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
                // 시퀀스가 TRAY IN과 PROBE CLOSED를 모두 확인한 상태다.
                state[CloseConfirmed] = Done; state[Measure] = Waiting; break;
            case CMD_BYPASS_TRAY_OUT:
                Reset(); state[Ready] = state[TrayIn] = Done;
                for(int i = TrayId; i < OutRequest; ++i) state[i] = Skipped;
                state[OutRequest] = Done; state[OutConfirmed] = Waiting; break;
            case CMD_TRAY_OUT:
                state[OutRequest] = Done; state[OutConfirmed] = Waiting; break;
            case CMD_TRAY_OUT_COMPLETE:
                // 현재 PLC 규약에서 완료는 TRAY IN=0이다.
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
        if(!valid) return; // 오래되거나 단절된 입력의 0을 완료로 처리하지 않는다.
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

// 패널과 운영 로그는 같은 대표 단계를 사용한다.
// 시퀀스·결과·명령 진행만 단계를 바꾸며 신호 이름은 영향을 주지 않는다.
// 새 트레이·재측정·초기화·주기 종료 때만 이전 단계로 돌아간다.
class TOperationTimeline
{
    int phase;
    unsigned int cycle, attempt;
public:
    TOperationTimeline() : phase(TOperationViewState::Ready), cycle(0), attempt(0) {}
    int Phase() const { return phase; }
    unsigned int Cycle() const { return cycle; }
    unsigned int Attempt() const { return attempt; }
    void Reset() { phase = TOperationViewState::Ready; attempt = 0; }
    void BeginTray() { ++cycle; attempt = 1; phase = TOperationViewState::TrayIn; }
    void BeginManual() { ++cycle; attempt = 1; phase = TOperationViewState::Measure; }
    void BeginRemeasure() { ++attempt; phase = TOperationViewState::CloseRequest; }
    void FinishTray() { phase = TOperationViewState::Ready; attempt = 0; }
    int Advance(int candidate)
    {
        if(candidate > phase && candidate < TOperationViewState::Count) phase = candidate;
        return phase;
    }
};

// 표시용 시간. 부호 없는 32비트 차이로 시간값 순환을 처리한다.
// 중복 시작을 무시하여 재시도에도 트레이 총시간을 유지한다.
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
