// Standalone regression tests. No VCL, sockets, PLC or production app startup.
#include "AutoInspectionSequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int checks = 0;
#define CHECK(expr) do { ++checks; if(!(expr)) { \
    printf("FAIL line %d: %s\n", __LINE__, #expr); exit(1); } } while(0)

struct Fixture
{
    TAutoInspectionSequence seq;
    TAutoInspectionData data;
    TAutoInspectionSetting setting;
    Fixture()
    {
        setting.startDelayCount = 2;
        setting.cellSerialTimeoutCount = 3;
        seq.Initialize(setting);
        data.autoMode = true;
        data.cellCount = 400;
        data.serialCount = 400;
    }
    void ToSerial()
    {
        CHECK(seq.RunAutoStep(data) == CMD_NONE);
        data.trayIn = true;
        CHECK(seq.RunAutoStep(data) == CMD_TRAY_IN);
        CHECK(seq.GetStep() == STEP_READ_TRAY_ID);
        CHECK(seq.RunAutoStep(data) == CMD_NONE);
        data.trayIdReady = true;
        CHECK(seq.RunAutoStep(data) == CMD_READ_TRAY_ID);
        CHECK(seq.RunAutoStep(data) == CMD_READ_CELL_DATA);
        CHECK(seq.RunAutoStep(data) == CMD_NONE);
        CHECK(seq.RunAutoStep(data) == CMD_NONE);
        CHECK(seq.RunAutoStep(data) == CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL);
        CHECK(seq.GetStep() == STEP_WAIT_CELL_SERIAL);
    }
    void ToResults()
    {
        ToSerial();
        data.serialComplete = true;
        CHECK(seq.RunAutoStep(data) == CMD_SAVE_CELL_SERIAL);
        CHECK(seq.GetStep() == STEP_WAIT_PROBE_CLOSE);
        CHECK(seq.RunAutoStep(data) == CMD_NONE);
        data.probeClosed = true;
        CHECK(seq.RunAutoStep(data) == CMD_MEASURE_START);
        CHECK(seq.GetStep() == STEP_WAIT_MEASURE_COMPLETE);
    }
    void ToProbeOpen()
    {
        ToResults();
        CHECK(seq.SetMeasureComplete());
        CHECK(seq.GetStep() == STEP_WAIT_PROBE_OPEN);
    }
    void ToNg()
    {
        ToProbeOpen();
        data.probeOpen = true;
        data.ngCount = data.ngLimit + 1;
        CHECK(seq.RunAutoStep(data) == CMD_NG_ERROR);
        CHECK(seq.GetStep() == STEP_WAIT_NG_ERROR);
    }
};

// 정상 연속 측정과 결과 처리 전 배출 방지를 검증한다.
static void NormalCycle()
{
    Fixture f;
    f.ToResults();
    // A stale/early PROBE OPEN must never bypass result publication.
    f.data.probeOpen = true;
    for(int i = 0; i < 100; ++i) CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    CHECK(f.seq.SetMeasureComplete());
    CHECK(!f.seq.SetMeasureComplete());
    CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_OUT);
    CHECK(f.seq.GetStep() == STEP_WAIT_TRAY_OUT);
    for(int i = 0; i < 10; ++i) CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    f.data.trayIn = false;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_OUT_COMPLETE);
    CHECK(f.seq.GetStep() == STEP_WAIT_TRAY_IN);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    f.data.trayIn = true;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_IN);
}

// 시리얼 개수·부분 수신·시간 경계·SAVE/CANCEL을 검증한다.
static void SerialCountAndTimeout()
{
    Fixture mismatch;
    mismatch.ToSerial();
    mismatch.data.serialComplete = true;
    mismatch.data.serialCount = 399;
    CHECK(mismatch.seq.RunAutoStep(mismatch.data) == CMD_CELL_SERIAL_COUNT_ERROR);
    for(int i = 0; i < 100; ++i) CHECK(mismatch.seq.RunAutoStep(mismatch.data) == CMD_NONE);
    CHECK(mismatch.seq.RetryCellSerialRead());
    CHECK(!mismatch.seq.RetryCellSerialRead());
    CHECK(mismatch.seq.GetWaitCount() == 0);
    mismatch.data.serialCount = 400;
    CHECK(mismatch.seq.RunAutoStep(mismatch.data) == CMD_SAVE_CELL_SERIAL);

    Fixture timeout;
    timeout.ToSerial();
    // A partial buffer with a matching count is NOT complete.
    for(int i = 0; i < 3; ++i) CHECK(timeout.seq.RunAutoStep(timeout.data) == CMD_NONE);
    CHECK(timeout.seq.RunAutoStep(timeout.data) == CMD_CELL_SERIAL_TIMEOUT);
    CHECK(timeout.seq.GetStep() == STEP_WAIT_CELL_SERIAL_ERROR);
    CHECK(timeout.seq.SaveCellSerialAfterError());
    CHECK(!timeout.seq.SaveCellSerialAfterError());
    CHECK(timeout.seq.GetStep() == STEP_WAIT_PROBE_CLOSE);

    Fixture boundary;
    boundary.ToSerial();
    for(int i = 0; i < 3; ++i) CHECK(boundary.seq.RunAutoStep(boundary.data) == CMD_NONE);
    boundary.data.serialComplete = true;
    CHECK(boundary.seq.RunAutoStep(boundary.data) == CMD_SAVE_CELL_SERIAL);

    Fixture overrideMismatch;
    overrideMismatch.ToSerial();
    overrideMismatch.data.serialComplete = true;
    overrideMismatch.data.serialCount = 401;
    CHECK(overrideMismatch.seq.RunAutoStep(overrideMismatch.data) == CMD_CELL_SERIAL_COUNT_ERROR);
    CHECK(overrideMismatch.seq.SaveCellSerialAfterError());
}

// NG 기준과 오류창 배출/재시작을 검증한다.
static void NgChoices()
{
    CHECK(!TAutoInspectionSequence::IsNgCountError(10, 400, 10));
    CHECK(TAutoInspectionSequence::IsNgCountError(11, 400, 10));
    CHECK(TAutoInspectionSequence::IsNgCountError(4, 4, 10));
    CHECK(!TAutoInspectionSequence::IsNgCountError(0, 0, 10));
    CHECK(!TAutoInspectionSequence::IsNgCountError(0, 400, 0));
    CHECK(TAutoInspectionSequence::IsNgCountError(1, 400, 0));
    CHECK(!TAutoInspectionSequence::IsNgCountError(0, 400, 10));

    Fixture trayOut;
    trayOut.ToNg();
    for(int i = 0; i < 100; ++i) CHECK(trayOut.seq.RunAutoStep(trayOut.data) == CMD_NONE);
    CHECK(trayOut.seq.AutomaticTrayOut(50, 400, 10) == CMD_NONE);
    CHECK(trayOut.seq.ForceTrayOut() == CMD_TRAY_OUT);
    CHECK(trayOut.seq.GetStep() == STEP_WAIT_TRAY_OUT);
    CHECK(trayOut.seq.ForceTrayOut() == CMD_NONE);

    Fixture restart;
    restart.ToNg();
    restart.seq.Initialize(restart.setting);
    CHECK(restart.seq.GetStep() == STEP_WAIT_TRAY_IN);
    CHECK(restart.seq.RunAutoStep(restart.data) == CMD_TRAY_IN);
    CHECK(restart.seq.GetStep() == STEP_READ_TRAY_ID);

    Fixture equal;
    equal.ToProbeOpen();
    equal.data.probeOpen = true;
    equal.data.ngCount = equal.data.ngLimit;
    CHECK(equal.seq.RunAutoStep(equal.data) == CMD_TRAY_OUT);

    Fixture allNg;
    allNg.ToProbeOpen();
    allNg.data.probeOpen = true;
    allNg.data.cellCount = 4;
    allNg.data.ngCount = 4;
    CHECK(allNg.seq.RunAutoStep(allNg.data) == CMD_NG_ERROR);
}

// 수동/BYPASS 배출 및 Auto 모드 조건을 검증한다.
static void BypassAndManual()
{
    Fixture bypass;
    bypass.data.trayIn = true;
    bypass.data.bypass = true;
    bypass.data.ngCount = 400;
    CHECK(bypass.seq.RunAutoStep(bypass.data) == CMD_BYPASS_TRAY_OUT);
    CHECK(bypass.seq.GetStep() == STEP_WAIT_TRAY_OUT);

    Fixture manual;
    manual.ToResults();
    CHECK(manual.seq.ForceTrayOut() == CMD_TRAY_OUT);
    CHECK(!manual.seq.SetMeasureComplete()); // Late callback cannot undo tray-out.
    CHECK(manual.seq.GetStep() == STEP_WAIT_TRAY_OUT);

    Fixture noAuto;
    noAuto.ToProbeOpen();
    noAuto.data.probeOpen = true;
    noAuto.data.autoMode = false;
    CHECK(noAuto.seq.RunAutoStep(noAuto.data) == CMD_NONE);
    noAuto.data.autoMode = true;
    CHECK(noAuto.seq.RunAutoStep(noAuto.data) == CMD_TRAY_OUT);
}

// 중복 시작/완료, 재측정, 오류 정지를 검증한다.
static void GuardsAndRemeasure()
{
    Fixture f;
    CHECK(!f.seq.SetMeasureComplete());
    CHECK(!f.seq.RetryCellSerialRead());
    CHECK(!f.seq.SaveCellSerialAfterError());
    CHECK(f.seq.AutomaticTrayOut(0, 400, 10) == CMD_NONE);
    f.ToResults();
    CHECK(!f.seq.StartRemeasure());
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE); // No duplicate AMS on a high close bit.
    CHECK(f.seq.SetMeasureComplete());
    CHECK(f.seq.StartRemeasure());
    CHECK(f.seq.GetStep() == STEP_WAIT_REMEASURE_PROBE_CLOSE);
    f.data.trayIn = false;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    f.data.trayIn = true;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_REMEASURE_START);
    CHECK(f.seq.GetStep() == STEP_WAIT_MEASURE_COMPLETE);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    CHECK(f.seq.SetMeasureComplete());

    Fixture ngRemeasure;
    ngRemeasure.ToNg();
    CHECK(ngRemeasure.seq.StartRemeasure());
    CHECK(!ngRemeasure.seq.StartRemeasure());

    Fixture fault;
    fault.ToResults();
    fault.seq.StopWithError();
    CHECK(fault.seq.GetStep() == STEP_ERROR_STOP);
    CHECK(!fault.seq.SetMeasureComplete());
    CHECK(!fault.seq.StartRemeasure());
    CHECK(fault.seq.RunAutoStep(fault.data) == CMD_NONE);
    fault.seq.Initialize(fault.setting);
    CHECK(fault.seq.GetStep() == STEP_WAIT_TRAY_IN);
}

// 시작 지연, 셀 없음, 오류 중 대기 횟수 보존을 검증한다.
static void DelayAndPause()
{
    Fixture f;
    f.data.trayIn = true;
    f.data.trayIdReady = true;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_IN);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_READ_TRAY_ID);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_READ_CELL_DATA);
    f.data.cellCount = 0;
    for(int i = 0; i < 10; ++i) CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    CHECK(f.seq.GetStep() == STEP_WAIT_START_DELAY);
    f.data.cycleMode = true;
    CHECK(f.seq.RunAutoStep(f.data) == CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    unsigned int before = f.seq.GetWaitCount();
    // Adapter does not call RunAutoStep while CheckAutoInspectionError blocks (same as production).
    for(int i = 0; i < 100; ++i) CHECK(f.seq.GetStep() == STEP_WAIT_CELL_SERIAL);
    CHECK(f.seq.GetWaitCount() == before);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
    CHECK(f.seq.RunAutoStep(f.data) == CMD_CELL_SERIAL_TIMEOUT);

    for(int s = STEP_WAIT_TRAY_IN; s <= STEP_ERROR_STOP; ++s)
        CHECK(strcmp(TAutoInspectionSequence::GetStepName((TAutoInspectionStep)s), "InvalidState") != 0);
}

// 프로브 재개폐 추가 횟수(0/1/2), 성공 조기 종료, 중복 닫힘, 다음 트레이 초기화.
static void ProbeRemeasureCounts()
{
    for(int limit = 0; limit <= 2; ++limit)
    {
        Fixture f;
        f.setting.probeRemeasureCount = limit;
        f.seq.Initialize(f.setting);
        f.ToProbeOpen();
        f.data.probeOpen = true;
        f.data.ngCount = 1; // NG 알람 한도 미만도 재개폐 대상이다.
        for(int round = 0; round < limit; ++round)
        {
            CHECK(f.seq.RunAutoStep(f.data) == CMD_REQUEST_PROBE_REMEASURE);
            CHECK(f.seq.GetProbeRemeasureDoneCount() == round);
            f.data.probeClosed = false;
            CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
            f.data.probeClosed = true;
            CHECK(f.seq.RunAutoStep(f.data) == CMD_REMEASURE_START);
            CHECK(f.seq.GetProbeRemeasureDoneCount() == round + 1);
            CHECK(f.seq.RunAutoStep(f.data) == CMD_NONE);
            CHECK(f.seq.SetMeasureComplete());
        }
        CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_OUT);
        f.data.trayIn = false;
        CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_OUT_COMPLETE);
        f.data.trayIn = true;
        CHECK(f.seq.RunAutoStep(f.data) == CMD_TRAY_IN);
        CHECK(f.seq.GetProbeRemeasureDoneCount() == 0);
    }
    Fixture good;
    good.setting.probeRemeasureCount = 2;
    good.seq.Initialize(good.setting);
    good.ToProbeOpen();
    good.data.probeOpen = true;
    good.data.ngCount = 1;
    CHECK(good.seq.RunAutoStep(good.data) == CMD_REQUEST_PROBE_REMEASURE);
    CHECK(good.seq.RunAutoStep(good.data) == CMD_REMEASURE_START);
    CHECK(good.seq.SetMeasureComplete());
    good.data.ngCount = 0;
    CHECK(good.seq.RunAutoStep(good.data) == CMD_TRAY_OUT);
    CHECK(good.seq.GetProbeRemeasureDoneCount() == 1);

    Fixture exhausted;
    exhausted.setting.probeRemeasureCount = 1;
    exhausted.seq.Initialize(exhausted.setting);
    exhausted.ToProbeOpen();
    exhausted.data.probeOpen = true;
    exhausted.data.ngCount = 400;
    CHECK(exhausted.seq.RunAutoStep(exhausted.data) == CMD_REQUEST_PROBE_REMEASURE);
    CHECK(exhausted.seq.RunAutoStep(exhausted.data) == CMD_REMEASURE_START);
    CHECK(exhausted.seq.SetMeasureComplete());
    CHECK(exhausted.seq.RunAutoStep(exhausted.data) == CMD_NG_ERROR);
    CHECK(exhausted.seq.ForceTrayOut() == CMD_TRAY_OUT);
    CHECK(exhausted.seq.RunAutoStep(exhausted.data) == CMD_NONE);
}

int main()
{
    // The two settings are independent and are frozen after TRAY IN.
    Fixture settings;
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == 49);
    settings.seq.SetNextTrayRemeasureSettings(50, 2);
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == 50);
    CHECK(settings.seq.GetSetting().probeRemeasureCount == 2);
    settings.ToResults();
    settings.seq.SetNextTrayRemeasureSettings(0, 0);
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == 50);
    CHECK(settings.seq.GetSetting().probeRemeasureCount == 2);
    settings.seq.Initialize(settings.setting);
    settings.seq.SetNextTrayRemeasureSettings(-1, -1);
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == 0);
    CHECK(settings.seq.GetSetting().probeRemeasureCount == 0);
    settings.seq.SetNextTrayRemeasureSettings(MAXCHANNEL + 1, 0);
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == MAXCHANNEL);
    settings.seq.SetNextTrayRemeasureSettings(0, 3);
    CHECK(settings.seq.GetSetting().closedProbeRemeasureMaxNgCount == 0);
    CHECK(settings.seq.GetSetting().probeRemeasureCount == 3);
    ProbeRemeasureCounts();
    NormalCycle();
    SerialCountAndTimeout();
    NgChoices();
    BypassAndManual();
    GuardsAndRemeasure();
    DelayAndPause();
    printf("PASS: %d checks across 8 scenario groups\n", checks);
    return 0;
}
