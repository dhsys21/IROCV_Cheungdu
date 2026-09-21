#ifndef SiteConfigH
#define SiteConfigH

// 사이트 변경 시작점: 실제 트레이 행/열. PLC 주소와 할당 길이는 Modplc.h에서 별도로 확인한다.
const int CELL_ROW_COUNT = 20;
const int CELL_COLUMN_COUNT = 20;
typedef char CheckTrayDimensions[(CELL_ROW_COUNT > 0 && CELL_COLUMN_COUNT > 0) ? 1 : -1];
const int MAXCHANNEL = CELL_ROW_COUNT * CELL_COLUMN_COUNT;
const int LINECOUNT = CELL_COLUMN_COUNT; // 기존 화면 코드 호환용: 한 줄의 셀 개수.
const int CELL_DATA_WORD_COUNT = (MAXCHANNEL + 15) / 16;

// Config에 새 키가 없는 기존 설비는 닫힘 재측정 1~49개 정책을 유지한다.
// 실제 적용값은 Config의 closedProbeRemeasureMaxNgCount(이하, 0=끔).
const int DEFAULT_CLOSED_PROBE_REMEASURE_MAX_NG_COUNT = 49;
// 재개폐/OP 요청의 전체·불량셀 선택 기준은 별도 사이트 정책이다.
// Config의 닫힘 재측정 최대 개수와 무관: 50개 초과=전체, 이하=불량셀.
const int PROBE_REMEASURE_ALL_CELL_NG_THRESHOLD = 50;
const unsigned long RESULT_COMPLETE_DELAY_MS = 1000;
const unsigned long RESULT_SERIAL_TIMEOUT_MS = 10000;

// 최종 판정 코드. 수치가 우선순위가 아니며 접촉 > IR > OCV 순서로 판정한다.
enum TCellResult { CELL_OK = 0, CELL_IR_NG = 2, CELL_OCV_NG = 3, CELL_CONTACT_NG = 4 };

// 결과 마감 상태: 파일 실패는 재시도 1회 후 진행, 시리얼 오류만 작업자 선택 대기.
enum TResultSaveStep {
    RESULT_IDLE, RESULT_WAIT_SERIAL, RESULT_WAIT_OPERATOR,
    RESULT_WRITE_FILE, RESULT_WAIT_PLC_SEND, RESULT_COMPLETE, RESULT_CANCELLED, RESULT_ERROR
};
#endif
