# newGui: IR/OCV 운영 화면

이 브랜치는 IR/OCV 전용입니다. PRECHARGER 및 원격 Malaysia 저장소는 변경하지 않습니다.

## 화면 배치

- 오른쪽 `FormMeasureInfo`의 채널·측정값·수동 측정 화면은 그대로 유지합니다.
- 왼쪽 폭 620 안에 기존 운전 버튼 → TRAY ID → PROCESS INFO → 현재 작업 → 작업 로그를 배치합니다.
- 중복 채널 맵/범례, 큰 STAGE/LOCAL 이미지, 별도 STATUS 행, 왼쪽 연결 문구는 숨깁니다.
- 기존 채널 패널/색상/상태 함수는 다른 코드에서 참조하므로 삭제하지 않습니다.
- MSA/CALIBRATION은 수동 모드일 때 왼쪽 아래에 표시합니다. 암호, 설정, 오류/재측정 창과 알람 집계는 유지합니다.
- 기존에 숨겨진 TEST MODE/BYPASS 설정은 자동으로 노출하지 않습니다.
- 상단 오른쪽 순서: INIT → LOG/DATA 세로 묶음 → PLC/IR·OCV 연결 세로 묶음.
- 별도 PLC 버튼은 제거했습니다. PLC 연결 판넬 클릭은 기존 `advPLCInterfaceShowClick`에 연결됩니다.
- 연결 판넬은 각각 80×26입니다. 실제 소켓 연결 여부를 ON/OFF 문구와 색으로 표시합니다.
- PC/PLC 운전 모드는 왼쪽 두 판넬로 표시합니다. AUTO=Lime, MANUAL/UNKNOWN=Red입니다.
- RESET / TRAY OUT / NG INFO는 각각 CONFIG / MANUAL / AUTO 바로 아래에 정렬합니다.

## 표시와 제어의 경계

왼쪽 화면은 `FormTotal.dfm`의 실제 컴포넌트입니다. C++Builder에서 FormTotal의 Design 탭을 열면
PROCESS INFO / CURRENT OPERATION / OPERATION LOG와 운전 버튼 배치를 확인·수정할 수 있습니다.
`Stage_OperationView.cpp`의 `TOperationView`는 DFM 컴포넌트에 연결되어 값·색상·로그만 갱신합니다.
위치·크기를 실행 중 다시 지정하지 않으므로 디자이너에서 수정한 새 영역의 배치가 유지됩니다.

기존 채널 맵·범례·대형 상태 이미지는 참조 호환용 `pnlLegacyDisplay`에 보관합니다.
이 판넬은 화면 밖(Left=1950)에 있고 실행 중 숨김 상태입니다. 필요할 때 Structure/Object Tree에서
선택할 수 있습니다. 기존 오류/설정 창과 오른쪽 `FormMeasureInfo`는 그대로 유지합니다.

- 화면은 별도 200ms 타이머로 갱신합니다. 자동 검사 타이머가 꺼진 수동/오류 대기 중에도 갱신됩니다.
- 생산 명령 실행 후 알림, 실제 파일 저장 결과, 현재 PLC 입력/PC 출력 설정, 기존 로그를 관찰합니다.
- 화면/로그 오류가 검사 단계나 PLC 출력을 바꾸지 않도록 관찰 호출은 예외를 차단합니다.
- 자동 단계, PLC 주소, 송신 길이, 시리얼 검증 방식, 재측정, 파일 저장 실패 시 기존 계속 진행 정책은 변경하지 않습니다.
- 구형 이미지 대신 현재 작업 영역에서 통신 끊김, PLC 수동, 시리얼 오류, NG 선택 대기 및 설비 알람을 확인합니다.

## PROCESS INFO 14개

READY / TRAY IN / TRAY ID / CELL DATA / DOWN REQ / DOWN OK / MEASURE

SAVE FILE / RESULT TX / COMPLETE / OPEN REQ / OPEN OK / OUT REQ / OUT OK

- 현재 진행/대기 단계 하나만 Lime, 나머지는 완료 여부와 관계없이 Silver로 표시합니다.
- WAIT / DONE / SET / SKIP 등 별도 상태 문자열은 판넬에 표시하지 않습니다. 이전 사건은 로그에서 확인합니다.
- REQ는 **PC 출력 버퍼 설정**을 뜻하며, 실제 전송 또는 PLC 동작 완료와 다릅니다.
- 닫힘/열림/배출 완료를 기다리는 동안에는 DOWN REQ / OPEN REQ / OUT REQ를 강조합니다.
- DOWN OK는 유효한 PLC 닫힘=1 및 TRAY IN=1, OPEN OK는 유효한 열림=1을 확인한 경우에만 표시합니다.
  다음 검사 단계로 넘어가면 그 단계를 강조합니다. 완료 표시를 위해 검사 진행을 지연하지 않습니다.
- OUT OK는 기존 시퀀스와 동일하게 **TRAY IN = 0** 조건입니다. 별도 배출 완료 주소를 만들지 않습니다.
- RESULT TX는 기존 `WasResultTransmitted()`로 확인합니다. PLC 내부 적용 ACK를 뜻하지 않습니다.
- 프로브 열기는 실제 코드상 결과 파일/PLC 결과 처리가 끝나기 전에 요청될 수 있습니다.
  따라서 완료 이력을 녹색으로 누적하지 않으며, 결과 처리 중에는 해당 단계가 표시됩니다.
- BYPASS는 측정 관련 단계를 건너뛰며 현재 배출 대기만 강조합니다.
- 시리얼은 설정에 따라 측정 전 또는 저장 시점에 처리되므로 별도 고정 순서 판넬 대신 현재 작업/진행 블록 수로 표시합니다.
- 파일 저장 실패는 경고 로그에 남기며, 성공으로 기록하지 않습니다.
- CURRENT OPERATION은 변수 접두어 대신 TRAY IN / PROBE DOWN 등 운전용 이름과 현재값/기대값을 표시합니다.
- Elapsed는 첫 TRAY IN 명령(또는 BYPASS 투입)부터 배출 완료까지의 총시간입니다. 단계 변경·재측정으로 다시 시작하지 않습니다.
  배출 완료 시 총시간은 CYCLE 로그로 남기고 표시값은 0으로 돌아갑니다. READY/초기화 상태에서는 0으로 고정됩니다.

## 로그

- 기존 PLC/장비 파일 로그를 보존하면서, 운영에 필요한 이벤트만 화면에 전달합니다.
- IR/OCV 개별 수신과 반복 폴링 원문은 기존 파일에만 남깁니다. 화면에는 주요 AMS/AMF/STP 및 단계/오류를 표시합니다.
- 현재 대기는 상태 제목이 바뀔 때만 기록합니다. 경과 시간·진행률 갱신마다 로그를 쌓지 않습니다.
- PLC RX/PC SET 변경 행은 마지막 정상 수신 버퍼/출력 버퍼의 **화면 갱신 시점 관찰값**입니다.
  200ms 사이의 모든 신호 전이를 보장하는 패킷 추적기가 아닙니다. 정밀 통신 분석은 기존 통신 로그/PLC 인터페이스를 사용합니다.
- 입력 데이터가 유효하지 않으면 이전 값을 새 완료 신호로 해석하지 않습니다. 재연결 첫 값은 기준값으로 취급합니다.
- 표시 버퍼는 약 500줄로 제한합니다. Follow latest 해제 시 스크롤을 유지합니다.
- 같은 내용을 `Log\\yyyymmdd\\STAGE001_OPERATION_yymmdd-hh.log`에 UTF-8로 누적 저장합니다(스테이지 번호별).
  기존 PLC/통신 로그는 그대로 유지합니다. 매 행 저장 후 파일을 닫으며, 일자/시간 변경 시 새 파일로 전환합니다.
- LOG FILE은 현재 운영 로그를 Notepad++ 읽기 전용으로 엽니다. 설치 등록 정보, 기본 설치 폴더 또는 실행 파일 옆의 휴대용 버전을 찾습니다.
- 파일 저장 실패는 버튼에 LOG ERROR로 표시하고, 편집기 미설치/실행 실패는 안내창으로 알립니다. 검사 제어는 변경하지 않습니다.

## 수정 위치와 확인 방법

| 파일 | 역할 |
|---|---|
| `RVMO_main.dfm/.cpp/.h` | 상단 버튼 배치, 두 연결 표시, PLC 연결 판넬 클릭 |
| `FormTotal.dfm/.h` | 디자이너에서 편집 가능한 왼쪽 배치와 컴포넌트 선언 |
| `Stage_OperationView.cpp`, `OperationView.h` | DFM 표시 컴포넌트 연결, 현재 작업, 화면 로그, 표시 타이머 |
| `OperationViewState.h` | 화면용 요청/완료/생략/경고 이력. PLC/VCL 없이 테스트 가능 |
| `FormTotal.cpp/.h` | 표시 객체 생성/소유. 새 타이머는 폼과 함께 해제 |
| `Stage_AutoInspection.cpp` | 명령 실행 후 관찰 알림 및 초기화 알림 |
| `Stage_Measurement.cpp` | 측정 시작과 실제 파일 저장 성공/실패 알림 |
| `Stage_log.cpp` | 기존 파일 로그의 화면 전달 |
| `Stage_Form.cpp` | 큰 MAIN/LOCAL 이미지만 다시 나타나지 않도록 처리 |

오프라인 검사: `TestNewGui.ps1`, `TestSourceStructure.ps1`, 기존 `Test*.ps1`.
전체 빌드: C++Builder Debug/Win32. 빌드 산출물은 커밋하지 않습니다.

설비 연결 전/시운전 확인:

1. 첫 실행의 연결 OFF/UNKNOWN, PLC 연결 판넬 클릭, INIT/LOG/DATA 및 기존 버튼 확인.
2. 정상 투입 → 측정 → 저장 → 열림 → 배출 시 요청/완료 표시와 로그 확인.
3. 두 시리얼 모드, 분할 수신 중 표시, 개수 불일치 SAVE/CANCEL 확인.
4. 재측정, BYPASS, 수동 측정, MSA/CALIBRATION, NG 오류창 확인.
5. PLC 수동 전환/연결 끊김 시 이전 완료값을 새 완료로 표시하지 않는지 확인.
6. 로그 Follow latest 해제/LOG FILE, 시간대별 파일 전환, 저장 실패 안내 및 장시간 누적 시 응답성 확인.
7. TRAY IN부터 재측정·배출까지 Elapsed 연속 증가, 배출 완료/READY에서 0 및 CYCLE 로그 확인.

이 변경은 실제 장비를 자동 실행해 검증하지 않습니다. 빌드·오프라인 회귀와 별도로 현장 시운전이 필요합니다.
