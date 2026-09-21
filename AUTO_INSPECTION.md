# IROCV 자동측정 시퀀스 구조

기준: `dd69ce9` (`2026 09 18 001`). IROCV 전용 변경이며 PRECHARGER와 독립적으로 관리합니다.

전체 파일 구성, 증상별 수정 위치, 미사용 코드 정리 내역은 [CODE_STRUCTURE.md](CODE_STRUCTURE.md)를 먼저 참고하세요.

CELL SERIAL 현장별 수신 방식은 Configuration의 `Continuous read`로 선택합니다.
해제=기존 TRAY IN 수신 보관, 체크=상시 수신 후 결과 저장 직전 새 전체 수신본을 반영합니다.
공통 주석은 `[CELL SERIAL 공통]`이며 자세한 설정/저장/오류 복귀는 CODE_STRUCTURE.md에 정리했습니다.

## 코드 용어

추상적인 이름 대신 설비 동작과 진행 단계를 구분하는 이름을 사용합니다.

| 기존 이름 | 현재 이름 | 의미 |
|---|---|---|
| `Sequence::Tick` | `TAutoInspectionSequence::RunAutoStep` | 현재 자동측정 단계의 조건 검사 |
| `Enter` | `SetStep` | 다음 단계로 변경하고 대기 횟수 초기화 |
| `Inputs` | `TAutoInspectionData` | PLC 신호·운전 옵션·검사 수량 |
| `State` | `TAutoInspectionStep` | 진행 단계: `STEP_WAIT_TRAY_IN` 등 |
| `Action` | `TAutoInspectionCommand` | 실행할 명령: `CMD_TRAY_IN`, `CMD_READ_TRAY_ID` 등 |
| `Policy` | `TAutoInspectionSetting` | 대기 시간 등의 설정 |

별도 namespace 없이 파일 이름과 같은 `TAutoInspectionSequence` 클래스에 구현합니다.
실제 PLC/UI 처리는 기존 폼 형식의 `TTotalForm::RunAutoInspectionCommand`에서 실행합니다.

```cpp
TAutoInspectionData data = ReadAutoInspectionData();
TAutoInspectionCommand command = autoInspection.RunAutoStep(data);
RunAutoInspectionCommand(command, data);
DisplayAutoInspectionStep();
```

## 측정 전/후 표시

- 프로그램 시작 안내: IR은 `1 ... 400`, OCV는 `1-1 ... 1-20, 2-1 ... 20-20`.
- 트레이 투입부터 `showStartupChannelNumbers=false`로 유지하여 미수신 IR/OCV는 공란으로 표시합니다.
- 각 채널의 IR/OCV를 독립적으로 관리합니다. IR만 받으면 IR만 측정값으로 바꾸고 OCV는 공란을 유지합니다.
- `irValueReceived` / `ocvValueReceived`는 표시용 수신 상태입니다. 기존 평균 계산용 `ir_flag` / `ocv_flag`와 다릅니다.
- 수신한 실제 0도 측정값으로 표시합니다. 미수신 여부를 값이 0인지로 판단하지 않습니다.
- 트레이 투입 후 초기화와 새 전체/수동 측정은 공란으로 돌아갑니다. 측정정보 창을 다시 열어도 수신값과 미수신 공란을 유지합니다.
- 채널/위치 번호는 그래프의 측정값으로 사용하지 않습니다. 차트 인덱스는 0부터 시작합니다.
- 빈 셀의 측정 응답에는 기존 `NO / CELL` 표시를 유지합니다.

## 어디를 수정하면 되는가

| 파일 / 함수 | 책임 | 현장별 변경 예 |
|---|---|---|
| `AutoInspectionSequence.h` | 상태·입력·동작·정책 정의 | 새 공정의 상태/입력 추가 |
| `AutoInspectionSequence.cpp` / `TAutoInspectionSequence::RunAutoStep` | 다음 상태와 한 번 실행할 동작 결정 | 공정 순서, 진행 조건 |
| `Stage_AutoInspection.cpp` / `GetAutoInspectionSetting` | 현장 기본값과 기존 설정 연결 | 시작 대기, SERIAL 제한 시간 |
| `ReadAutoInspectionData`, `ReadAutoCellData` | PLC/UI 값을 시퀀스 입력으로 변환 | CELL DATA 읽기, 입력 신호 연결 |
| `RunAutoInspectionCommand` | 단계 진입 시 PLC 출력·측정 명령·오류창 실행 | 출력 순서, 추가 인터페이스 |
| `DisplayAutoInspectionStep` | 현재 상태의 화면 문구·MEASURING 표시 | 문구와 화면 표현 |
| `AutoInspectionSequenceTests.cpp` | PLC 없는 결정 로직 회귀 테스트 | 새로운 현장 조건 검증 |
| `Modplc.*`, `Stage_comm.cpp` | PLC/장비 저수준 통신과 응답 분기 | 주소·통신 프로토콜 |
| `Stage_Measurement.cpp`, `Stage_PlcData.cpp` | 측정값·재측정·PLC 결과 작성 | 보정·판정·전송 배율 |
| `Stage_TrayData.cpp`, `Stage_CellDisplay.cpp` | 트레이/시리얼 데이터, 채널 화면 | 초기화·시리얼 저장·표시 |

여러 폼에서 `nSection`/`nStep`을 직접 쓰던 구조는 제거했습니다. 외부에서는 `ForceTrayOut`, `RestartAutoInspection`, `AcceptCellSerialData`, `RetryCellSerialRead` 같은 의미 있는 함수만 호출합니다. 상태 자체는 `TTotalForm`의 private 멤버입니다.

## 상태 흐름과 기존 코드 대응

| 새 상태 | 대기/실행 조건 | 이전 위치 |
|---|---|---|
| `STEP_WAIT_TRAY_IN` | TRAY IN 확인, BYPASS 분기 | WAIT / 0 |
| `STEP_READ_TRAY_ID` | 비어 있지 않은 TRAY ID | WAIT / 1 |
| `STEP_READ_CELL_DATA` | 25워드 × 16비트 CELL DATA 읽기 | WAIT / 2 |
| `STEP_WAIT_START_DELAY` | CELL 존재 및 설정 대기 완료 | WAIT / 3 |
| `STEP_WAIT_CELL_SERIAL` | 4,010워드 전체 수신 후 개수 비교 | WAIT / 4 |
| `STEP_WAIT_CELL_SERIAL_ERROR` | 불일치/타임아웃 후 SAVE 또는 CANCEL | WAIT / 5 |
| `STEP_WAIT_PROBE_CLOSE` | TRAY IN + PROBE CLOSED 후 AMS 한 번 시작 | MEASURE / 0 |
| `STEP_WAIT_REMEASURE_PROBE_CLOSE` | 전체/선택 재측정의 PROBE CLOSED 대기 | MEASURE / 2 |
| `STEP_WAIT_MEASURE_COMPLETE` | AMF → 기존 개별 재측정 → 결과 처리 함수 종료 | 기존 MEASURE / 3의 앞부분 |
| `STEP_WAIT_PROBE_OPEN` | 결과 처리 후 Auto 모드 + PROBE OPEN | 기존 MEASURE / 3의 배출 판단 |
| `STEP_WAIT_NG_ERROR` | NG 경보 후 Tray Out 또는 Restart | MEASURE / 99 |
| `STEP_WAIT_TRAY_OUT` | TRAY IN 해제 후 배출 출력 정리 | FINISH / 0 |
| `STEP_ERROR_STOP` | 타이머/연결된 조작 함수의 예외 발생 시 진행 중지 | 신규 |

기존 MEASURE / 1은 진입하는 코드가 없어 연결되지 않은 `ViewRemeasureList`와 함께 제거했습니다. 실제 생산에서 사용하던 `ResponseAutoTestFinish` → `SetRemeasureList` → `RemeasureExcute` 경로는 유지합니다.

## 유지한 생산 규칙

- `NgCount`는 **존재하는 셀 중 IR/OCV/접촉 불량**만 집계합니다. PLC 전송용 `ngCount`와 통합하지 않습니다. `BadInfomation`의 집계식은 변경하지 않았습니다.
- 자동 배출은 `NgCount > 설정값` 또는 존재하는 셀 전부 NG일 때 대기합니다. 설정값과 같은 개수는 허용하며, 셀이 0개인 상황을 전량 NG로 오판하지 않습니다.
- NG 대기 진입 시 TRAY OUT을 내보내지 않고 `nFinish`도 표시하지 않습니다. Tray Out 버튼은 NG 재검사 없이 배출, Restart는 TRAY IN부터 다시 시작합니다.
- 수동 배출과 BYPASS는 NG 조건을 적용하지 않습니다. 수동 배출 버튼별 기존 PROBE OPEN/COMPLETE 출력은 유지합니다.
- CELL SERIAL START/COMPLETE 핸드셰이크는 사용하지 않습니다. 기존 Modplc의 820워드 × 4 + 730워드 수신 완료를 확인한 뒤 개수를 비교합니다.
- SERIAL 오류창의 SAVE는 불일치/타임아웃 데이터를 사용자가 명시적으로 승인하는 기존 동작입니다. CANCEL은 분할 수신을 처음부터 재시도합니다.
  단, 새 상시 모드의 **결과 저장 전** 오류에서는 SAVE도 전체 수신 완료본에만 허용합니다. 미완료이면 CANCEL로 다시 수신해야 합니다.
- 지연 설정 단위는 기존 **자동 타이머의 유효 호출 횟수**입니다. 타이머는 200ms, 제한값 50은 51회째 만료(정상 주기에서 약 10.2초)입니다. 통신/PLC 오류 중에는 호출 횟수를 진행하지 않고 복구 후 같은 상태에서 재개합니다. 실제 벽시계 기준 타임아웃으로 바꾸지 않았습니다.
  새 상시 모드의 결과 저장 전 수신 대기는 별도 `Timer_ResultCellSerial`에서 실제 경과 10초를 제한으로 사용합니다.
- TRAY ID, PROBE CLOSED, 측정 응답, PROBE OPEN, TRAY OUT에 새로운 제한 시간이나 자동 강제배출 정책을 임의로 추가하지 않았습니다. 현장별 제한 시간이 필요하면 정책과 테스트를 함께 추가해야 합니다.
- PLC 주소, IR/OCV 계산·판정·스케일, 결과 파일 형식, 자동 개별 재측정 조건은 유지합니다.

## 함께 보완한 부분

1. 상태 전환을 한 곳에서 결정하고, 명령을 실행하기 전에 새 상태를 설정하여 AMS 중복 시작과 상태 덮어쓰기를 방지합니다.
2. PROBE OPEN이 먼저 올라와도 결과 처리 함수가 끝나기 전에는 자동 배출하지 않습니다. `SaveMeasurementResult` 마지막의 `SetAutoMeasureComplete()`가 완료 지점입니다. 상시 모드는 최종 시리얼 수신을 기다린 후 이 함수를 실행합니다.
3. 전체 재측정의 CELL DATA 읽기도 자동측정과 같은 비트맵 함수를 사용합니다. 기존 TRAY ID를 유지합니다.
4. `AnsiString`을 포함하는 TRAY 구조체를 `memset`하지 않습니다. 문자열은 대입으로, 숫자·배열은 명시적으로 초기화하여 구형 BCC32의 임시 객체 초기화에 의존하지 않습니다.
5. 같은 측정의 중복 AMF는 처리하지 않고, 개별 재측정 종료 후 재측정 모드를 해제합니다.
6. 타이머 재진입을 막고 예외 발생 시 `STEP_ERROR_STOP`로 진행을 중지합니다. 이는 PC 시퀀스 정지이며 **PLC 비상정지 명령이 아닙니다**. 이미 출력한 명령의 취소나 설비의 물리적 정지를 보장하지 않습니다.
7. 상태 전환 로그에 이전/다음 상태 이름과 이유를 기록합니다. NG 대기 화면을 매 주기 일반 측정 문구로 덮지 않습니다.
8. 오류창 선택 후 즉시 닫고 기존 지연 닫기 타이머를 끕니다. 이전 오류창의 타이머가 새 오류 신호를 지우는 상황을 줄입니다.
9. PLC 소켓도 `Active`뿐 아니라 실제 `Connected`를 확인합니다.

## 사이트별 확장 순서

1. 해당 사이트에서 달라질 **입력, 출력, 대기 조건**을 먼저 명시합니다.
2. 값만 다르면 `GetAutoInspectionSetting()`나 기존 설정 연결을 수정합니다. PLC 매핑은 어댑터/`Modplc.h`에서 관리하고 순수 시퀀스에 주소를 넣지 않습니다.
3. 단계가 추가되면 상태/동작 enum → `RunAutoStep` 전환 → `RunAutoInspectionCommand` → `DisplayAutoInspectionStep` 순서로 연결합니다.
4. 명령은 `RunAutoInspectionCommand`에서 한 번 실행합니다. 반복 UI 함수에 프로브/배출 명령을 넣지 않습니다.
5. 정상뿐 아니라 불일치, 중복 입력, 타임아웃, 재시도, 수동 배출, 재시작 테스트를 같이 추가합니다.
6. 별도 현장 조건 없이 추상적인 사이트 플러그인/설정 체계까지 도입하지 않았습니다. 실제 차이가 확인되면 이 경계에 맞춰 확장합니다.

## 검증과 적용 전 확인

저장소에서 PowerShell로 실행:

```powershell
.\TestAutoInspection.ps1
.\TestSourceStructure.ps1
```

필요하면 `-Compiler`로 BCC32 경로를 지정합니다. 테스트 산출물은 임시 폴더에만 생성되며 PLC/IR/OCV 연결이나 생산 프로그램 실행은 하지 않습니다.

- 순수 시퀀스 테스트: 정상 배출, NG 기준 경계·전량 NG, 수동/BYPASS, SERIAL 개수 불일치·시간 경계·부분 수신·SAVE/CANCEL, 중복 시작/완료, 재측정, 오류 중 대기 유지, STEP_ERROR_STOP/초기화.
- IROCV Debug/Win32 전체 컴파일·링크 및 현재 프로젝트 DFM 이벤트 연결 검증.
- **실제 에뮬레이터 및 생산 설비의 통신·I/O 테스트는 별도입니다.** 순수 로직 테스트는 VCL 화면/통신 스케줄러/PLC 반응을 대신하지 않습니다.

현장 적용 전 최소 확인:

1. 정상 트레이 1회 및 연속 2회, IR/OCV 자동 개별 재측정이 있는 트레이.
2. NG 설정값과 동일/1개 초과/전량 NG: 대기 중 TRAY OUT=0, Finish 미표시.
3. NG Tray Out 및 Restart: 강제 배출과 TRAY ID/CELL DATA/SERIAL부터 재시작.
4. SERIAL 4,010워드 분할 수신, 일부 지연/누락, 개수 불일치, SAVE 승인 및 CANCEL 재수신.
5. 측정/개별 재측정 완료 전 PROBE OPEN이 올라와도 자동 배출하지 않는지.
6. 수동 배출, BYPASS, 전체/선택 재측정과 TRAY ID 유지.
7. 장비/PLC 연결 끊김 후 No Answer 표시 및 기존 상태 재개, PLC 오류 중 명령 재발행 여부.
8. 설정/파일 예외 시 자동 진행 중지와 운영자 초기화 절차.

`SetAutoMeasureComplete`는 기존 결과 처리 함수의 반환을 확인하는 경계입니다. PLC가 실제로 데이터를 수신했다는 ACK나 디스크 저장 성공까지 새로 검증하는 것은 아닙니다. 기존 통신 재전송·프레임 해석·파일 I/O의 오류 검증은 별도 범위입니다. 운영 버전 교체 전 이 점과 현장 안전 인터록을 확인해야 합니다.
