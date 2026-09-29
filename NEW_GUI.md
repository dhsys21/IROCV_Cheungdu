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

## 표시와 제어의 경계

`Stage_OperationView.cpp`의 `TOperationView`가 왼쪽 화면을 동적으로 만듭니다.
따라서 새 영역은 실행 시 보이며, 기존 FormTotal DFM의 채널 맵은 호환용으로 남아 있습니다.

- 화면은 별도 200ms 타이머로 갱신합니다. 자동 검사 타이머가 꺼진 수동/오류 대기 중에도 갱신됩니다.
- 생산 명령 실행 후 알림, 실제 파일 저장 결과, 현재 PLC 입력/PC 출력 설정, 기존 로그를 관찰합니다.
- 화면/로그 오류가 검사 단계나 PLC 출력을 바꾸지 않도록 관찰 호출은 예외를 차단합니다.
- 자동 단계, PLC 주소, 송신 길이, 시리얼 검증 방식, 재측정, 파일 저장 실패 시 기존 계속 진행 정책은 변경하지 않습니다.
- 구형 이미지 대신 현재 작업 영역에서 통신 끊김, PLC 수동, 시리얼 오류, NG 선택 대기 및 설비 알람을 확인합니다.

## PROCESS INFO 14개

READY / TRAY IN / TRAY ID / CELL DATA / CLOSE REQ / CLOSE OK / MEASURE

SAVE FILE / RESULT TX / COMPLETE / OPEN REQ / OPEN OK / OUT REQ / OUT OK

- REQ의 SET은 **PC 출력 버퍼 설정**입니다. 실제 전송 또는 PLC 동작 완료와 다릅니다.
- CLOSE OK, OPEN OK는 해당 요청 이후 유효한 PLC 입력 조건으로 표시합니다.
- OUT OK는 기존 시퀀스와 동일하게 **TRAY IN = 0** 조건입니다. 별도 배출 완료 주소를 만들지 않습니다.
- RESULT TX는 기존 `WasResultTransmitted()`로 확인합니다. PLC 내부 적용 ACK를 뜻하지 않습니다.
- 프로브 열기는 실제 코드상 결과 파일/PLC 결과 처리가 끝나기 전에 요청될 수 있습니다.
  따라서 앞쪽 판넬을 무조건 모두 완료로 칠하지 않고, 각 사건을 독립적으로 표시합니다.
- BYPASS는 측정 관련 판넬에 SKIP을 표시합니다. 재측정은 해당 구간의 이전 완료 표시를 지웁니다.
- 시리얼은 설정에 따라 측정 전 또는 저장 시점에 처리되므로 별도 고정 순서 판넬 대신 현재 작업/진행 블록 수로 표시합니다.
- 파일 저장 실패는 SAVE FILE의 WARNING과 로그로 표시하며, 성공으로 표시하지 않습니다.
- 상세 신호명/현재값/기대값과 경과 시간은 CURRENT OPERATION에서 확인합니다.

## 로그

- 기존 PLC/장비 파일 로그를 보존하면서, 운영에 필요한 이벤트만 화면에 전달합니다.
- IR/OCV 개별 수신과 반복 폴링 원문은 기존 파일에만 남깁니다. 화면에는 주요 AMS/AMF/STP 및 단계/오류를 표시합니다.
- 현재 대기는 상태 제목이 바뀔 때만 기록합니다. 경과 시간·진행률 갱신마다 로그를 쌓지 않습니다.
- PLC RX/PC SET 변경 행은 마지막 정상 수신 버퍼/출력 버퍼의 **화면 갱신 시점 관찰값**입니다.
  200ms 사이의 모든 신호 전이를 보장하는 패킷 추적기가 아닙니다. 정밀 통신 분석은 기존 통신 로그/PLC 인터페이스를 사용합니다.
- 입력 데이터가 유효하지 않으면 이전 값을 새 완료 신호로 해석하지 않습니다. 재연결 첫 값은 기준값으로 취급합니다.
- 표시 버퍼는 약 500줄로 제한합니다. Follow latest 해제 시 스크롤을 유지하며 COPY는 선택 문자열 또는 전체 표시 로그를 복사합니다.

## 수정 위치와 확인 방법

| 파일 | 역할 |
|---|---|
| `RVMO_main.dfm/.cpp/.h` | 상단 버튼 배치, 두 연결 표시, PLC 연결 판넬 클릭 |
| `Stage_OperationView.cpp`, `OperationView.h` | 왼쪽 동적 배치, 현재 작업, 화면 로그, 표시 타이머 |
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
6. 로그 Follow latest 해제/복사와 장시간 누적 시 응답성 확인.

이 변경은 실제 장비를 자동 실행해 검증하지 않습니다. 빌드·오프라인 회귀와 별도로 현장 시운전이 필요합니다.
