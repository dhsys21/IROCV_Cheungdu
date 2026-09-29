#ifndef SiteConfigH
#define SiteConfigH

// PLC AUTO/MANUAL input: confirmed for Chengdu, 0=manual / 1=automatic.
const int PLC_AUTO_MODE_VALUE = 1;

// 사이트 변경 시작점: 실제 트레이 행/열. PLC 주소와 할당 길이는 Modplc.h에서 별도로 확인한다.
const int CELL_ROW_COUNT = 20;
const int CELL_COLUMN_COUNT = 20;
typedef char CheckTrayDimensions[(CELL_ROW_COUNT > 0 && CELL_COLUMN_COUNT > 0) ? 1 : -1];
const int MAXCHANNEL = CELL_ROW_COUNT * CELL_COLUMN_COUNT;
const int LINECOUNT = CELL_COLUMN_COUNT; // 기존 화면 코드 호환용: 한 줄의 셀 개수.
const int CELL_DATA_WORD_COUNT = (MAXCHANNEL + 15) / 16;

// 채널 화면 배치: 1번 시작 모서리 × 번호 증가 방향 = 8가지.
// HORIZONTAL: 한 행에서 좌우로 진행 후 다음 행, VERTICAL: 한 열에서 상하로 진행 후 다음 열.
// 매 행/열은 같은 방향으로 진행하며 지그재그(왕복) 배치는 아니다.
// 기존 라인 5와 동일한 기본값: 오른쪽 아래 1번 → 위쪽 증가 → 다음 열은 왼쪽.
// 화면 좌표만 바꾼다. PLC 채널/배열 인덱스/보정·판정 데이터 순서는 변경하지 않는다.
enum TChannelStartCorner {
    CHANNEL_BOTTOM_RIGHT, // 오른쪽 아래
    CHANNEL_TOP_RIGHT,    // 오른쪽 위
    CHANNEL_BOTTOM_LEFT,  // 왼쪽 아래
    CHANNEL_TOP_LEFT      // 왼쪽 위
};
enum TChannelFillDirection {
    CHANNEL_HORIZONTAL,  // 좌우 우선: 한 행을 채우고 다음 행으로
    CHANNEL_VERTICAL     // 상하 우선: 한 열을 채우고 다음 열로
};
const TChannelStartCorner CHANNEL_START_CORNER = CHANNEL_TOP_RIGHT;
const TChannelFillDirection CHANNEL_FILL_DIRECTION = CHANNEL_HORIZONTAL;
typedef char CheckChannelLayout[
    (CHANNEL_START_CORNER >= CHANNEL_BOTTOM_RIGHT && CHANNEL_START_CORNER <= CHANNEL_TOP_LEFT &&
     (CHANNEL_FILL_DIRECTION == CHANNEL_HORIZONTAL || CHANNEL_FILL_DIRECTION == CHANNEL_VERTICAL)) ? 1 : -1];

// 규격 기본값은 기존 설정파일 읽기 값을 유지한다. 저장/읽기/입력 실패에 같은 값을 사용.
// 정상적으로 저장된 사이트별 규격값은 변경하지 않는다.
const int DEFAULT_IR_MIN = 10;
const int DEFAULT_IR_MAX = 40;
const int DEFAULT_OCV_MIN = 500;
const int DEFAULT_OCV_MAX = 3000;

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

// 결과 마감 상태: 파일 실패는 재시도 1회 후 진행. 상시 시리얼 오류는 로그만 기록.
enum TResultSaveStep {
    RESULT_IDLE, RESULT_WAIT_SERIAL,
    RESULT_WRITE_FILE, RESULT_WAIT_PLC_SEND, RESULT_COMPLETE, RESULT_CANCELLED, RESULT_ERROR
};
#endif
