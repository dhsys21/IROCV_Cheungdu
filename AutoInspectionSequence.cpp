// [자동 검사 단계 판단] PLC/VCL에 의존하지 않는 단계·명령 결정 코드.
// 실제 출력: Stage_AutoInspection.cpp / RunAutoInspectionCommand

#include "AutoInspectionSequence.h"
#include <limits.h>

// PLC 신호와 검사 수량의 기본값을 초기화한다.
TAutoInspectionData::TAutoInspectionData()
    : trayIn(false), bypass(false), trayIdReady(false), cycleMode(false),
      cellSerialContinuousRead(false), serialComplete(false), probeClosed(false), probeOpen(false),
      autoMode(false), cellCount(0), serialCount(0), ngCount(0), ngLimit(10)
{
}

// 자동 검사 시작 단계를 TRAY IN 대기로 설정한다.
TAutoInspectionSequence::TAutoInspectionSequence() : probeRemeasureDoneCount(0), automaticProbeRemeasure(false), currentStep(STEP_WAIT_TRAY_IN), waitCount(0) {}

// 다음 단계로 변경하고 해당 단계의 대기 횟수를 0으로 초기화한다.
void TAutoInspectionSequence::SetStep(TAutoInspectionStep step)
{
    currentStep = step;
    waitCount = 0;
}

// 대기 설정을 적용하고 TRAY IN부터 시작한다. PLC 출력은 호출부에서 초기화한다.
void TAutoInspectionSequence::Initialize(const TAutoInspectionSetting &setting)
{
    sequenceSetting = setting;
    probeRemeasureDoneCount = 0;
    automaticProbeRemeasure = false;
    SetStep(STEP_WAIT_TRAY_IN);
}

// 현재 단계의 조건을 검사하여 실행할 명령 하나를 반환한다. PLC/UI를 직접 조작하지 않는다.
TAutoInspectionCommand TAutoInspectionSequence::RunAutoStep(const TAutoInspectionData &data)
{
    switch(currentStep)
    {
        case STEP_WAIT_TRAY_IN:
            if(!data.trayIn) return CMD_NONE;
            if(data.bypass)
            {
                SetStep(STEP_WAIT_TRAY_OUT);
                return CMD_BYPASS_TRAY_OUT;
            }
            probeRemeasureDoneCount = 0;
            automaticProbeRemeasure = false;
            SetStep(STEP_READ_TRAY_ID);
            return CMD_TRAY_IN;

        case STEP_READ_TRAY_ID:
            if(!data.trayIdReady) return CMD_NONE;
            SetStep(STEP_READ_CELL_DATA);
            return CMD_READ_TRAY_ID;

        case STEP_READ_CELL_DATA:
            SetStep(STEP_WAIT_START_DELAY);
            return CMD_READ_CELL_DATA;

        case STEP_WAIT_START_DELAY:
            if(waitCount < UINT_MAX) ++waitCount;
            if(data.cellCount <= 0 && !data.cycleMode) return CMD_NONE;
            if(waitCount <= sequenceSetting.startDelayCount) return CMD_NONE;
            // 상시 읽기는 투입 시 시리얼을 기다리거나 비교하지 않는다.
            if(data.cellSerialContinuousRead)
            {
                SetStep(STEP_WAIT_PROBE_CLOSE);
                return CMD_PROBE_CLOSE;
            }
            SetStep(STEP_WAIT_CELL_SERIAL);
            return CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL;

        case STEP_WAIT_CELL_SERIAL:
            // Complete on the boundary wins over timeout; never compare a chunk.
            if(data.serialComplete)
            {
                if(data.serialCount == data.cellCount)
                {
                    SetStep(STEP_WAIT_PROBE_CLOSE);
                    return CMD_SAVE_CELL_SERIAL;
                }
                SetStep(STEP_WAIT_CELL_SERIAL_ERROR);
                return CMD_CELL_SERIAL_COUNT_ERROR;
            }
            if(waitCount < UINT_MAX) ++waitCount;
            if(waitCount <= sequenceSetting.cellSerialTimeoutCount) return CMD_NONE;
            SetStep(STEP_WAIT_CELL_SERIAL_ERROR);
            return CMD_CELL_SERIAL_TIMEOUT;

        case STEP_WAIT_PROBE_CLOSE:
        case STEP_WAIT_REMEASURE_PROBE_CLOSE:
            if(!data.probeClosed || !data.trayIn) return CMD_NONE;
            {
                const bool remeasure = currentStep == STEP_WAIT_REMEASURE_PROBE_CLOSE;
                if(remeasure && automaticProbeRemeasure) ++probeRemeasureDoneCount;
                automaticProbeRemeasure = false;
                SetStep(STEP_WAIT_MEASURE_COMPLETE); // Set before sending; duplicate ticks cannot start twice.
                return remeasure ? CMD_REMEASURE_START : CMD_MEASURE_START;
            }

        case STEP_WAIT_PROBE_OPEN:
            if(!data.autoMode || !data.probeOpen) return CMD_NONE;
            return AutomaticTrayOut(data.ngCount, data.cellCount, data.ngLimit);

        case STEP_WAIT_TRAY_OUT:
            if(data.trayIn) return CMD_NONE;
            SetStep(STEP_WAIT_TRAY_IN);
            return CMD_TRAY_OUT_COMPLETE;

        // These are explicit waits, not undefined numeric steps (e.g. 99).
        case STEP_WAIT_CELL_SERIAL_ERROR:
        case STEP_WAIT_MEASURE_COMPLETE:
        case STEP_WAIT_NG_ERROR:
        case STEP_ERROR_STOP:
            return CMD_NONE;
    }
    StopWithError();
    return CMD_NONE;
}

// 사용자 SAVE 승인에 따라 프로브 닫힘 대기로 진행한다. 실제 시리얼 저장은 폼에서 처리한다.
bool TAutoInspectionSequence::SaveCellSerialAfterError()
{
    if(currentStep != STEP_WAIT_CELL_SERIAL_ERROR) return false;
    SetStep(STEP_WAIT_PROBE_CLOSE);
    return true;
}

// 시리얼 오류 상태에서 수신 대기로 되돌아간다. 실제 수신 요청은 폼에서 실행한다.
bool TAutoInspectionSequence::RetryCellSerialRead()
{
    if(currentStep != STEP_WAIT_CELL_SERIAL_ERROR) return false;
    SetStep(STEP_WAIT_CELL_SERIAL);
    return true;
}

// 재측정 가능한 단계에서 프로브 닫힘 대기로 변경한다. 진행 중 중복 요청은 거절한다.
bool TAutoInspectionSequence::StartRemeasure()
{
    // Existing remeasure buttons are also usable from the idle/manual UI.
    if(currentStep != STEP_WAIT_TRAY_IN && currentStep != STEP_WAIT_NG_ERROR && currentStep != STEP_WAIT_PROBE_OPEN)
        return false;
    automaticProbeRemeasure = false; // 작업자가 직접 누른 재측정은 자동 횟수와 구분.
    SetStep(STEP_WAIT_REMEASURE_PROBE_CLOSE);
    return true;
}

// 측정 결과 처리 완료를 받아 프로브 열림 대기로 변경한다. 중복/다른 단계의 완료는 무시한다.
bool TAutoInspectionSequence::SetMeasureComplete()
{
    if(currentStep != STEP_WAIT_MEASURE_COMPLETE) return false;
    SetStep(STEP_WAIT_PROBE_OPEN);
    return true;
}

// 존재하는 셀의 NG가 설정값 초과 또는 전량 NG인지 검사한다. 설정값과 같으면 허용한다.
bool TAutoInspectionSequence::IsNgCountError(int ngCount, int cellCount, int ngLimit)
{
    // NgCount is occupied-cell IR/OCV NG, NOT the PLC's lowercase ngCount.
    // Equality at the configured limit is allowed; all occupied cells NG is not.
    return (cellCount > 0 && ngCount == cellCount) || ngCount > ngLimit;
}

// 정상 자동 배출 판단: NG 오류 대기 또는 트레이 배출 명령을 반환한다.
TAutoInspectionCommand TAutoInspectionSequence::AutomaticTrayOut(int ngCount, int cellCount, int ngLimit)
{
    if(currentStep != STEP_WAIT_PROBE_OPEN) return CMD_NONE;
    // 2번 재측정은 NG 알람 기준과 별개: 불량이 남고 설정 횟수가 남으면 먼저 재개폐.
    if(ngCount > 0 && probeRemeasureDoneCount < sequenceSetting.probeRemeasureCount)
    {
        automaticProbeRemeasure = true;
        SetStep(STEP_WAIT_REMEASURE_PROBE_CLOSE);
        return CMD_REQUEST_PROBE_REMEASURE;
    }
    if(IsNgCountError(ngCount, cellCount, ngLimit))
    {
        SetStep(STEP_WAIT_NG_ERROR);
        return CMD_NG_ERROR;
    }
    SetStep(STEP_WAIT_TRAY_OUT);
    return CMD_TRAY_OUT;
}

// 운영자가 요청한 강제 배출 단계로 변경한다. NG 판정은 생략하고 중복 배출 요청은 무시한다.
TAutoInspectionCommand TAutoInspectionSequence::ForceTrayOut()
{
    if(currentStep == STEP_WAIT_TRAY_OUT) return CMD_NONE;
    automaticProbeRemeasure = false;
    SetStep(STEP_WAIT_TRAY_OUT);
    return CMD_TRAY_OUT;
}

// 자동 단계 진행을 오류 정지로 고정한다. PLC 비상정지나 이동 명령을 출력하지 않는다.
void TAutoInspectionSequence::StopWithError() { SetStep(STEP_ERROR_STOP); }

// 현재 단계가 측정 준비/측정 완료/프로브 대기 구간인지 반환한다.
bool TAutoInspectionSequence::IsMeasureStep() const
{
    return currentStep == STEP_WAIT_PROBE_CLOSE || currentStep == STEP_WAIT_REMEASURE_PROBE_CLOSE ||
           currentStep == STEP_WAIT_MEASURE_COMPLETE || currentStep == STEP_WAIT_PROBE_OPEN;
}

// 단계 이름을 로그용 문자열로 반환한다.
const char *TAutoInspectionSequence::GetStepName(TAutoInspectionStep step)
{
    switch(step)
    {
        case STEP_WAIT_TRAY_IN: return "STEP_WAIT_TRAY_IN";
        case STEP_READ_TRAY_ID: return "STEP_READ_TRAY_ID";
        case STEP_READ_CELL_DATA: return "STEP_READ_CELL_DATA";
        case STEP_WAIT_START_DELAY: return "STEP_WAIT_START_DELAY";
        case STEP_WAIT_CELL_SERIAL: return "STEP_WAIT_CELL_SERIAL";
        case STEP_WAIT_CELL_SERIAL_ERROR: return "STEP_WAIT_CELL_SERIAL_ERROR";
        case STEP_WAIT_PROBE_CLOSE: return "STEP_WAIT_PROBE_CLOSE";
        case STEP_WAIT_REMEASURE_PROBE_CLOSE: return "STEP_WAIT_REMEASURE_PROBE_CLOSE";
        case STEP_WAIT_MEASURE_COMPLETE: return "STEP_WAIT_MEASURE_COMPLETE";
        case STEP_WAIT_PROBE_OPEN: return "STEP_WAIT_PROBE_OPEN";
        case STEP_WAIT_NG_ERROR: return "STEP_WAIT_NG_ERROR";
        case STEP_WAIT_TRAY_OUT: return "STEP_WAIT_TRAY_OUT";
        case STEP_ERROR_STOP: return "STEP_ERROR_STOP";
    }
    return "InvalidState";
}
