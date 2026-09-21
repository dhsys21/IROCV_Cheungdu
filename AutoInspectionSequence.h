#ifndef AutoInspectionSequenceH
#define AutoInspectionSequenceH

#include "SiteConfig.h"

// 자동측정 단계 정의. PLC 통신과 화면 처리는 Stage_AutoInspection.cpp에 있다.
// RunAutoStep: 현재 단계를 확인하고 이번에 실행할 명령 한 개를 결정한다.
// SetStep: 다음 단계로 변경하고 해당 단계의 대기 횟수를 0으로 초기화한다.
enum TAutoInspectionStep
{
    STEP_WAIT_TRAY_IN,                 // 트레이 도착 대기
    STEP_READ_TRAY_ID,                 // 트레이 ID 읽기
    STEP_READ_CELL_DATA,               // 셀 유무 읽기
    STEP_WAIT_START_DELAY,             // 측정 시작 전 설정 시간 대기
    STEP_WAIT_CELL_SERIAL,             // 셀 시리얼 전체 수신 대기
    STEP_WAIT_CELL_SERIAL_ERROR,       // 시리얼 오류: SAVE / CANCEL 선택 대기
    STEP_WAIT_PROBE_CLOSE,             // 프로브 닫힘 대기
    STEP_WAIT_REMEASURE_PROBE_CLOSE,   // 재측정용 프로브 닫힘 대기
    STEP_WAIT_MEASURE_COMPLETE,        // 측정 및 결과 처리 완료 대기
    STEP_WAIT_PROBE_OPEN,              // 프로브 열림 대기
    STEP_WAIT_NG_ERROR,                // NG 오류: 배출 / 재시작 선택 대기
    STEP_WAIT_TRAY_OUT,                // 트레이 배출 완료 대기
    STEP_ERROR_STOP                    // 예외 발생으로 자동 진행 정지
};

enum TAutoInspectionCommand
{
    CMD_NONE,                             // 실행할 명령 없음
    CMD_TRAY_IN,                          // 트레이 도착 후 검사 정보 초기화
    CMD_BYPASS_TRAY_OUT,                   // BYPASS 배출
    CMD_READ_TRAY_ID,                      // 읽은 트레이 ID 적용
    CMD_READ_CELL_DATA,                    // 셀 유무 읽기
    CMD_PROBE_CLOSE_AND_READ_CELL_SERIAL,  // 프로브 닫기 요청 + 시리얼 수신 시작
    CMD_SAVE_CELL_SERIAL,                 // 정상 수신한 시리얼 저장
    CMD_CELL_SERIAL_COUNT_ERROR,          // 시리얼 개수 불일치 표시
    CMD_CELL_SERIAL_TIMEOUT,              // 시리얼 수신 시간 초과 표시
    CMD_MEASURE_START,                    // 전체 측정 시작
    CMD_REQUEST_PROBE_REMEASURE,          // 프로브 열림 확인 후 다시 닫기 요청
    CMD_REMEASURE_START,                  // 전체/선택 재측정 시작
    CMD_NG_ERROR,                         // NG 개수 오류 표시
    CMD_TRAY_OUT,                         // 트레이 배출 요청
    CMD_TRAY_OUT_COMPLETE                 // 배출 완료 후 출력 정리
};

struct TAutoInspectionSetting
{
    // Config 재측정 두 항목. NG 개수와 재개폐 횟수는 별개이며 이번 트레이 동안 고정한다.
    int closedProbeRemeasureMaxNgCount; // 닫힘 유지: NG가 1~설정값 이하일 때 1회, 0=끔.
    int probeRemeasureCount; // 추가 재개폐 횟수. 0=사용 안 함, 최초 측정 제외.
    // 아래 대기 설정만 200ms 타이머의 유효 호출 횟수 단위다.
    // 대기 설정값 50이면 기존 코드와 동일하게 51번째 호출에서 완료/시간 초과.
    unsigned int startDelayCount; // 측정 시작 전 대기 횟수
    unsigned int cellSerialTimeoutCount; // 시리얼 수신 제한 횟수
    // 생산 버전의 기본 대기 횟수로 초기화한다.
    TAutoInspectionSetting() :
        closedProbeRemeasureMaxNgCount(DEFAULT_CLOSED_PROBE_REMEASURE_MAX_NG_COUNT),
        probeRemeasureCount(0), startDelayCount(50), cellSerialTimeoutCount(50) {}
};

struct TAutoInspectionData
{
    // 현재 PLC 신호, 운전 옵션, 검사 수량. 진행 단계(Step)와는 다른 정보다.
    bool trayIn; // PLC 트레이 도착 신호
    bool bypass; // BYPASS 사용 여부
    bool trayIdReady; // 트레이 ID 읽기 성공 여부
    bool cycleMode; // 전 채널을 사용하는 Cycle 시험 모드
    bool serialComplete; // 분할 수신 전체 완료 여부(PLC 핸드셰이크 비트가 아님)
    bool probeClosed; // PLC 프로브 닫힘 확인
    bool probeOpen; // PLC 프로브 열림 확인
    bool autoMode; // 현재 운전 모드가 Auto인지
    int cellCount; // CELL DATA의 존재 셀 개수
    int serialCount; // 수신한 유효 CELL SERIAL 개수
    int ngCount; // 존재 셀 중 IR/OCV/접촉 불량 개수
    int ngLimit; // NG 오류 설정값(초과 시 오류)
    // PLC 신호와 검사 수량의 기본값을 초기화한다.
    TAutoInspectionData();
};

class TAutoInspectionSequence
{
public:
    // 자동 검사 시작 단계를 TRAY IN 대기로 설정한다.
    TAutoInspectionSequence();
    // 현재 단계 조회. 다른 폼에서 단계 값을 직접 변경하지 않는다.
    TAutoInspectionStep GetStep() const { return currentStep; }
    // 현재 단계의 대기 횟수 조회(화면 진행 표시용).
    unsigned int GetWaitCount() const { return waitCount; }
    // 적용 중인 대기 설정 조회.
    const TAutoInspectionSetting &GetSetting() const { return sequenceSetting; }
    // 대기 설정을 적용하고 TRAY IN부터 시작한다. PLC 출력은 호출부에서 초기화한다.
    void Initialize(const TAutoInspectionSetting &setting);
    // Timer_AutoInspection에서 한 번 호출할 때 현재 단계의 조건을 검사한다.
    // 현재 단계의 조건을 검사하여 실행할 명령 하나를 반환한다. PLC/UI를 직접 조작하지 않는다.
    TAutoInspectionCommand RunAutoStep(const TAutoInspectionData &data);

    // 운영자 선택/측정 완료 통지: 맞지 않는 단계 또는 중복 요청은 false/CMD_NONE으로 무시.
    // 사용자 SAVE 승인에 따라 프로브 닫힘 대기로 진행한다. 실제 시리얼 저장은 폼에서 처리한다.
    bool SaveCellSerialAfterError();
    // 시리얼 오류 상태에서 수신 대기로 되돌아간다. 실제 수신 요청은 폼에서 실행한다.
    bool RetryCellSerialRead();
    // 재측정 가능한 단계에서 프로브 닫힘 대기로 변경한다. 진행 중 중복 요청은 거절한다.
    bool StartRemeasure();
    // 실제 재개폐 재측정 시작 횟수. 새 트레이에서만 0으로 초기화한다.
    int GetProbeRemeasureDoneCount() const { return probeRemeasureDoneCount; }
    // 두 재측정 설정을 TRAY IN 대기에서만 반영한다. 검사 도중 SAVE해도 현재 트레이는 유지.
    // maxNgCount는 셀 개수(이하), probeCount는 추가 재개폐 횟수이며 서로 다른 단위다.
    void SetNextTrayRemeasureSettings(int maxNgCount, int probeCount) {
        if(currentStep != STEP_WAIT_TRAY_IN) return;
        sequenceSetting.closedProbeRemeasureMaxNgCount =
            maxNgCount < 0 ? 0 : (maxNgCount > MAXCHANNEL ? MAXCHANNEL : maxNgCount);
        sequenceSetting.probeRemeasureCount = probeCount < 0 ? 0 : probeCount;
    }
    // 측정 결과 처리 완료를 받아 프로브 열림 대기로 변경한다. 중복/다른 단계의 완료는 무시한다.
    bool SetMeasureComplete();
    // 정상 자동 배출 판단: NG 오류 대기 또는 트레이 배출 명령을 반환한다.
    TAutoInspectionCommand AutomaticTrayOut(int ngCount, int cellCount, int ngLimit);
    // 운영자가 요청한 강제 배출 단계로 변경한다. NG 판정은 생략하고 중복 배출 요청은 무시한다.
    TAutoInspectionCommand ForceTrayOut();
    // 자동 단계 진행을 오류 정지로 고정한다. PLC 비상정지나 이동 명령을 출력하지 않는다.
    void StopWithError();

    // 현재 단계가 측정 준비/측정 완료/프로브 대기 구간인지 반환한다.
    bool IsMeasureStep() const;
    // 존재하는 셀의 NG가 설정값 초과 또는 전량 NG인지 검사한다. 설정값과 같으면 허용한다.
    static bool IsNgCountError(int ngCount, int cellCount, int ngLimit);
    // 단계 이름을 로그에서 검색 가능한 문자열로 반환한다.
    static const char *GetStepName(TAutoInspectionStep step);

private:
    int probeRemeasureDoneCount;
    bool automaticProbeRemeasure; // 자동 요청의 닫힘 확인 때만 횟수를 증가시킨다.
    TAutoInspectionStep currentStep; // 현재 자동 검사 단계
    unsigned int waitCount; // 현재 단계에서 경과한 유효 타이머 호출 횟수
    TAutoInspectionSetting sequenceSetting; // 초기화 때 적용한 대기 설정
    // 다음 단계로 변경하고 해당 단계의 대기 횟수를 0으로 초기화한다.
    void SetStep(TAutoInspectionStep step);
};
#endif
