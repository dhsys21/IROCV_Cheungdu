# IROCV 코드 구조와 수정 위치

목표는 “어디를 고쳐야 하는지, 어떤 단계에서 멈췄는지 바로 찾을 수 있는 구조”입니다.
생산 판정과 PLC 주소를 바꾸기 위한 정리가 아닙니다. PRECHARGER와 별도 저장소로 관리합니다.

## 먼저 볼 파일

| 파일 | 담당 역할 | 처음 찾아볼 함수 |
|---|---|---|
| `FormTotal.cpp` | 폼 생성·시작·종료, 버튼/입력 이벤트 | `FormShow`, 각 버튼 이벤트 |
| `FormTotal.h` | 폼 구성요소와 공용 데이터, 역할별 함수 선언 | private/public의 구현 파일별 구역 |
| `AutoInspectionSequence.h/.cpp` | 자동 단계와 다음 명령 판단 | `TAutoInspectionSequence::RunAutoStep` |
| `Stage_AutoInspection.cpp` | 자동 타이머 처리와 PLC/UI 연결 | `ProcessAutoInspection`, `RunAutoInspectionCommand` |
| `Stage_Measurement.cpp` | IR/OCV 수신값 처리·재측정·결과 마감 | `ProcessIr/Ocv`, `SetRemeasureList`, `FinishMeasurement` |
| `Stage_PlcData.cpp` | PC→PLC 초기값·측정값·NG·결과 코드 작성 | `PLCInitialization`, `BadInformation` |
| `CellJudgment.h` | 화면/통신 없는 공통 규격 판정 | `JudgeCellValues` |
| `Stage_TrayData.cpp` | 트레이 데이터 초기화·시리얼 복사·임시 파일 | `InitTrayStruct`, `ReadCellSerial`, `SaveTrayInfo` |
| `Stage_CellDisplay.cpp` | 400채널 생성·번호/측정값·색상 표시 | `InitCellDisplay`, `UpdateCellDisplay`, `InitMeasureForm` |
| `Stage_comm.cpp` | 측정장비 소켓·송수신·프레임·응답 분기 | `ProcessEquipmentSocketRead`, `OnReceiveStage`, `SendData` |
| `Stage_Form.cpp` | 상태/오류/연결 이미지·PLC 표시등·화면 전환 | `DisplayStatus`, `RefreshStageStatusImage`, `DisplayError` |
| `Stage_log.cpp` | 설정·채널 매핑·결과 파일·로그 | `ReadSystemInfo`, `ReadchannelMapping`, `WriteResultFile` |
| `Modplc.h/.cpp` | PLC 주소와 실제 PLC 통신 | 주소 상수, `StartCellSerialRead` |
| `FormPLCInterface.cpp/.dfm` | PLC 데이터 모니터 및 테스트 패널 | `chkShowAllClick`, `GetDisplayChannelStep`, `Timer_UpdateTimer` |

폼의 컨트롤이나 기존 DFM 이벤트를 사용하는 함수는 `TTotalForm::` 형태를 유지합니다.
DFM에 연결된 이벤트 함수 정의는 반드시 대응하는 폼 .cpp에 둡니다.
FormTotal의 버튼뿐 아니라 타이머·소켓 이벤트도 FormTotal.cpp에 두고,
실제 처리만 Stage_*.cpp의 Process... 함수로 전달합니다. 디자이너에서 코드를 찾을 때의 진입점입니다.
FormTotal.cpp의 각 함수 끝에는 C++Builder 기본 구분선(//와 하이픈)을 유지합니다.
TestSourceStructure.ps1은 전체 프로젝트의 이벤트 중복/폼 파일 위치 및 FormTotal 구분선을 검사합니다.
FormTotal.h의 __published(IDE 관리) 영역은 컴포넌트 선언을 먼저 끝내고 이벤트 함수를 선언합니다.
이벤트 함수 뒤에 컴포넌트 선언을 끼워 넣지 않습니다. 일반 처리 함수는 private/public에 둡니다.
컴파일 성공만으로 디자이너 호환성을 판단하지 않으며, 검사 스크립트도 이 선언 순서를 확인합니다.
IDE에서 기존 파일을 열어 둔 경우 외부 변경을 다시 읽거나 프로젝트를 다시 연 후
Design의 버튼 더블클릭 및 Object Inspector > Events의 값 더블클릭으로 이동을 확인합니다.
타이머 간격·DFM 이벤트 이름·PLC 신호·측정 순서는 변경하지 않습니다.
PLC/화면을 사용하지 않는 자동 단계 판단만 `TAutoInspectionSequence`로 독립되어 있습니다.

## 자동측정을 읽는 순서

1. `FormTotal.cpp::Timer_AutoInspectionTimer` → `Stage_AutoInspection.cpp::ProcessAutoInspection`: 진행 가능한지 확인하고 이번 명령을 구합니다.
2. `RunAutoStep`: 현재 `STEP_...`의 진행 조건을 확인하고 다음 단계/명령을 결정합니다.
3. `RunAutoInspectionCommand`: 반환된 `CMD_...`에 해당하는 PLC 출력이나 측정 명령을 **한 번** 실행합니다.
4. `OnReceiveStage`: 장비의 AMS/AMF/IR/OCV 응답을 해당 처리 함수에 전달합니다.
5. `FinishMeasurement`: 기존 순서로 결과를 마감한 뒤 `SetAutoMeasureComplete`로 완료를 알립니다.
6. `RunAutoStep`: 프로브 열림 확인 후 설정 횟수가 남고 NG가 있으면 재개폐 재측정, 아니면 배출/NG 오류 선택 대기로 진행합니다.

`SetStep`은 “진행 단계 변경 + 해당 단계 대기 횟수 초기화”입니다.
`SetAutoReadySignalToPLC`는 “운전 모드에 따라 AUTO READY를 자동=1, 수동=0으로 설정”입니다.
이 함수 하나가 전체 측정 준비 조건을 확인하는 것은 아닙니다.

## 증상별 확인 위치

| 증상 | 확인 순서 |
|---|---|
| 자동측정이 시작되지 않음 | `CheckAutoInspectionError` → 마지막 단계 로그 → `RunAutoStep`의 해당 STEP 조건 |
| 시리얼 개수 불일치/타임아웃 | `STEP_WAIT_CELL_SERIAL` → `ReadCellSerial` → `Modplc::StartCellSerialRead` 및 수신 완료 처리 |
| NG 오류창이 안 뜨거나 정상 배출됨 | `BadInformation`의 `measNgCount` → `IsNgCountError` → `CMD_NG_ERROR`; 수동/BYPASS는 의도적으로 NG를 무시 |
| NG 창에서 배출/재시작 문제 | `FormError.cpp`의 버튼 → `ForceTrayOut` / `RestartAutoInspection` |
| IR/OCV 값·보정·재측정 문제 | `ProcessIr/Ocv` → `InsertIr/OcvValue` → `SetRemeasureList` / `RemeasureExcute` |
| 트레이 투입 후 번호/이전 값이 보임 | `CMD_TRAY_IN`의 `showStartupChannelNumbers=false` → `InitCellDisplay` → `UpdateCellDisplay`의 개별 수신 플래그 |
| PLC 결과값/NG 비트가 이상함 | `BadInformation`에서 비트/코드/수량 동시 작성 → `Modplc.h` 주소/배율 |
| 연결 끊김이 Vacancy로 보임 | `RefreshStageStatusImage`와 장비 `Client... ` 이벤트 |
| 트레이 ID/시리얼 파일 문제 | `Stage_TrayData.cpp`의 `Load/Save/DeleteTrayInfo` |
| 설정/채널 매핑/로그 문제 | `Stage_log.cpp` |

기존 PLC 로그의 `AutoInspection` 항목에는 “이전 단계 → 다음 단계 : 이유”가 기록됩니다.
`AutoInspection ERROR`는 예외 발생 단계와 메시지입니다.
오류 정지는 PC 시퀀스 진행 정지이며 PLC 비상정지/이미 실행된 이동의 취소가 아닙니다.

## 공통 판정 / 오류창 / 결과 작성

- `CellJudgment.h::JudgeCellValues`: 접촉 > IR > OCV 우선순위를 한 곳에서 계산합니다.
  항목별 불량은 화면 색상 표시용이며, 미수신 공란은 기존 수신 플래그로 구분합니다.
- 불량셀 재측정은 원인에 관계없이 IR 다음 OCV를 모두 요청합니다.
  `pendingItems`의 1/2는 응답 대기와 송신 순서 관리용입니다. 정상/빈 셀은 제외합니다.
- `BadInformation`은 같은 `plcNg` 값으로 PLC 비트와 결과 코드를 동시에 작성합니다.
  OK=0/NG=1, 빈 채널도 PLC에는 NG, 작업자 알람 개수는 실제 셀 불량만 집계하는 정책을 유지합니다.
  별도 두 번째 순회인 `WriteResultCode`는 제거했습니다.
- 오류창은 표시와 작업자 선택 전달만 담당합니다. 창 표시/닫기 타이머는 PLC를 제어하지 않습니다.
  미체크 모드의 측정 전 시리얼/NG 오류는 `RunAutoInspectionCommand`에서 ERROR=1을 출력합니다.
  상시 읽기 모드의 결과 시리얼 불일치/타임아웃은 로그만 남기고 저장을 진행합니다.
  해제는 배출/재시작/시리얼 승인·재시도를 처리하는 검사 함수에서 수행합니다.
- 규격 기본값은 `SiteConfig.h`에 모았습니다. 기존 초기 로딩 값인 IR 10~40,
  OCV 500~3000을 사용하며, 저장된 현장 규격값은 바꾸지 않습니다.
  입력을 한 번 해석한 `config`를 파일 저장과 PLC 규격 작성에서 함께 사용합니다.
- 결과 마감 함수 `SaveMeasurementResult` 이름과 파일 저장/완료 지연 정책은 유지합니다.

검증: `TestAutoInspection.ps1`, `TestCellSerialRead.ps1`, `TestResultFile.ps1`,
`TestErrorDialogs.ps1`, `TestErrorDialogLayout.ps1`, `TestSourceStructure.ps1`.
오류창 시험은 실제 이벤트 본문을 사용하며 설비에는 연결하지 않습니다.

### CELL SERIAL 읽기 모드

- Continuous read 미체크: TRAY IN 후 전체 시리얼을 수신/검사하고, 불일치/타임아웃은
  오류창에서 SAVE 또는 CANCEL을 기다립니다. 결과에는 투입 시 보관한 시리얼을 사용합니다.
- Continuous read 체크: 상시 PLC 읽기는 유지하지만 TRAY IN 시 개수 검사/수신 대기는 건너뜁니다.
  프로브 닫힘과 트레이 존재 확인 후 측정하고, 결과 저장 직전 새 전체 시리얼을 요청합니다.
- 결과 수신 완료본의 개수가 다르면 WARNING 로그와 함께 완료본으로 저장합니다.
  10초 안에 전체 수신이 없으면 ID를 공란으로 저장합니다. 이전 .Tray/부분 수신값은 사용하지 않습니다.
  이 두 경우에는 시리얼 오류창/PLC ERROR/작업자 대기를 만들지 않습니다.
  기존 NG 판정, PLC 전송 확인과 1초 완료 지연, 수동측정 ID 없는 저장 정책은 유지합니다.
- 오류창 3종은 760×420, 제목 32px/본문 22px 및 고정 폭 줄바꿈을 사용합니다.
  위치/크기를 표시 함수에서 다시 덮어쓰지 않고 DFM에서 관리합니다.

## 사이트별 수정 원칙

PLC Interface의 `Show all`은 기본 해제입니다. 해제하면 1·21·41…381번, 체크하면 1~400번의
시리얼/결과 코드/IR/OCV를 표시합니다. 셀 유무와 OK/NG의 25워드는 기존처럼 모두 표시합니다.
목록 생성과 값 갱신은 같은 `GetDisplayChannelStep()`을 사용하며 PLC 통신 범위는 바꾸지 않습니다.
체크 상태는 창을 닫았다 열어도 해당 실행 세션에서 유지하고, 제목 클릭의 테스트 패널 표시와는 독립적입니다.

- 대기 설정: `GetAutoInspectionSetting`. 기존 단위는 200ms 자동 타이머의 유효 호출 횟수입니다.
- 진행 조건/단계 추가: `RunAutoStep`과 enum을 수정하고 단계 테스트를 추가합니다.
- PLC 신호/주소 차이: `ReadAutoInspectionData`, `RunAutoInspectionCommand`, `Stage_PlcData`, `Modplc.h`를 확인합니다.
- 셀 판정/재측정 차이: `Stage_Measurement.cpp`를 별도로 검토합니다.
- 화면 문구/색상 차이: 자동 단계 문구는 `DisplayAutoInspectionStep`, 채널 화면은 `Stage_CellDisplay.cpp`.
- 다른 폼에서 단계 값을 직접 쓰지 말고 배출/재시작/시리얼 재시도 함수를 호출합니다.
- 주석에는 “무엇을 확인하는지, 무엇을 바꾸는지, 어느 조건에서 호출하는지”를 적습니다.

## 미사용 코드 정리 범위

현재 C++ 호출, 함수 포인터/메시지 연결, DFM의 `On...` 이벤트 이름을 확인했습니다.
호출과 이벤트 연결이 모두 없는 `TTotalForm` 구현 23개를 제거했습니다.

- 이전 경로: `InitMeasureFormRemeasure`, `CmdTestMode`, `SetRemeasureList2`, `AddRemeasureList`, `GetSigma`
- 미사용 트레이/기록 경로: `SetTrayID`, `plc_Barcode`, `ResultReportToPLC`, `WriteTrayInfo`, `WriteOKNG`, `ReadPreChargerOKNG`
- 구형 장비 명령: `FinishMeasurement_Original`, `CmdTrayOut_Original`, `CmdVersion`, `CmdEmergencyStop`, `CmdGetSensorInfo`, `CmdRestart`, `StageClearAlarm`, `CmdDeviceInfo`
- 중복/미연결 UI 함수: `btnPLCConnectClick`, `btnPLCDisconnectClick`, `ShowAlarm`, `VisibleSpec`

선언만 남아 있던 `WriteResultFile_MES`, `WriteResultFile_MES2`, `StageReady`도 제거했습니다.
실제로 쓰는 평균 옵션, 재측정 판정, 기존 결과 파일 형식은 변경하지 않았습니다.

읽히지 않던 멤버 13개를 제거했습니다:
`Old_batch`, `clSelect`, `clNo`, `clYes`, `remeasure_info`, `precharger_okng`,
`m_bAuto`, `mAuto`, `q_txMode`, `ErrorCheckStatus`, `OldIROCVStage`, `IROCVStage`, `bconfig`.
`bconfig`는 항상 false였으므로 해당 불가능 분기를 정리했습니다.
사용하지 않는 지역 변수와 `UpdateCellDisplay`의 무사용 인자/계산도 정리했습니다.
`ReadSystemInfo`와 `ReadCellInfo`는 반환값을 사용하지 않는 동작 함수여서 `void`로 맞췄습니다.

DFM 연결이 있는 빈/시험용 이벤트는 보존했습니다. 저장소에 남은 프로젝트 미등록 구형 파일은 자동 삭제하지 않았습니다.
삭제한 이전 구현은 기준 커밋 `dd69ce9`에서 확인할 수 있습니다.

## PLC 결과 규격과 작성 순서

운영자 확인 규격은 **OK=0, NG=1**입니다. 내부 재측정 사유 코드와 PLC 결과 코드는 다릅니다.
`FinishMeasurement`은 `BadInformation()`으로 최종 OK/NG 비트를 만든 다음 `WriteResultCode()`를 호출합니다.
`WriteResultCode()`는 해당 비트를 셀마다 읽어 400개 결과 코드에도 같은 0/1을 기록합니다.
기존 4/5/6 출력과 정상 셀의 미초기화 문제를 제거했고, NG 다음 OK 셀에도 반드시 0을 씁니다.
기존 빈 셀의 NG 비트 처리 및 PLC용 `ngCount`/오류창용 `measNgCount` 집계 기준은 변경하지 않았습니다.

## 검증 방법

### CELL SERIAL 수신 방식 설정

Configuration 아래의 `Continuous read (PLC keeps data until TRAY OUT)`를 선택하고 SAVE합니다.

| 체크 | PLC 데이터 유지 방식 | 결과파일에 사용할 시리얼 |
|---|---|---|
| 해제 (기본값) | TRAY IN 때만 제공하고 이후 지움 | 기존 TRAY IN 검사 단계에서 수신·확인·보관한 .Tray 데이터 |
| 체크 | 트레이 투입부터 배출까지 유지 | 일반 PLC 데이터와 번갈아 상시 읽고, 결과 저장 직전에 요청한 새 전체 수신본 |

- 설정: `SystemInfo_<stage>.inf / [CELL_SERIAL] CONTINUOUS_READ`. 기존 INI는 false입니다.
- 검사 중 저장한 설정은 현재 트레이를 바꾸지 않고 다음 트레이/검사 초기화에 적용합니다.
- 두 방식 모두 측정 전 CELL DATA/시리얼 개수 비교와 기존 오류창 SAVE/CANCEL을 유지합니다.
- CELL SERIAL START/COMPLETE 핸드셰이크는 추가하지 않습니다.
- Chengdu의 주소/400채널/4,010워드(820×4+730)를 유지합니다. 576채널 주소·크기를 복사하지 않았습니다.
- 임시 수신 버퍼와 완료 버퍼를 분리해 5조각 전체 수신 시 한 번에 교체합니다.
- TCP 부분 응답은 끝까지 기다리고 다음 요청을 보내지 않습니다.

상시 수신의 결과 저장 흐름:

1. `FinishMeasurement`에서 기존 STP/프로브 열림을 요청하고 `StartResultCellSerialRead`로 새 수신을 시작합니다.
2. 자동측정만 `Timer_ResultSaveTimer`에서 최종 시리얼 수신을 기다립니다. 일반적인 추가 대기는 PLC 응답 속도에 따라 약 2초이며 제한은 10초입니다.
   수동측정(bLocal 또는 stage.arl == nLocal)은 시리얼 수신/개수 검사/타임아웃 오류창 없이 저장합니다.
   `SaveMeasurementResult(true)`는 이전 .Tray/PLC 시리얼 복원을 생략하고 CSV CELL_ID를 공란으로 만듭니다.
   파일 저장 재시도 1회와 이후 PLC 결과 송신/완료 대기는 기존대로 유지합니다.
3. 완료 후 `ReadCellSerial`로 현재 트레이에 복사하고 CELL DATA 개수와 비교합니다.
4. 정상 수신이면 `SaveMeasurementResult`에서 IR/OCV와 함께 저장한 뒤 PLC 결과 송신과 최소 1초 경과를 확인하고 COMPLETE를 출력합니다. 이전 .Tray 파일을 다시 읽어 덮어쓰지 않습니다.
5. 개수 불일치는 WARNING 로그를 남기고 완료 수신본으로 저장합니다. 오류창/작업자 대기는 없습니다.
6. 10초 동안 전체 수신이 없으면 WARNING 로그를 남기고 CELL_ID를 공란으로 저장합니다. 이전 .Tray/부분 데이터를 사용하지 않습니다.
7. 초기화/강제 배출/예외 정지는 지연 저장을 취소합니다. 기존 NG 판정과 수동/BYPASS 배출 정책은 유지합니다.

관련 주석은 `[CELL SERIAL 공통]`으로 검색할 수 있습니다.
통신은 `Modplc.cpp`, 설정은 `Stage_log.cpp`, 최종 수신 대기는 `Stage_Measurement.cpp`,
결과 저장은 `Stage_Measurement.cpp`를 확인합니다.
PLC가 배출 전에 시리얼을 지우는 현장은 반드시 체크를 해제해야 합니다.

### 오프라인 검사

```powershell
.\TestAutoInspection.ps1
.\TestSourceStructure.ps1
.\TestCellSerialRead.ps1
```

첫 번째는 PLC/VCL 없는 자동 단계 회귀 테스트입니다.
두 번째는 현재 프로젝트의 DFM 이벤트가 실제 구현에 연결되는지, 분리한 소스가 한 번씩 등록됐는지 확인합니다.
세 번째 검사는 실제 수신/저장 제어 메서드를 추출해 가짜 PLC/UI로 실행합니다.
한 번/상시 수신, 부분 TCP 응답, 5조각 교체, 재접속, 수신 중 새 요청,
최종 저장, 개수 불일치, 시간 초과, 운영자 승인/재시도, 지연 저장 취소를 검사합니다.
검사 모두 생산 프로그램을 실행하거나 장비에 접속하지 않습니다.

명령행 전체 빌드에서는 프로젝트 아이콘/버전 리소스도 먼저 생성합니다.
이 프로젝트는 `Rebuild`에서 `IROCV.res`를 삭제한 뒤 자동 재생성이 누락될 수 있으므로,
RAD Studio 명령 프롬프트에서 아래 순서로 실행합니다.

```bat
MSBuild.exe IROCV.cbproj /t:_ResolveIcons;BuildVersionResource;Build /p:Config=Debug /p:Platform=Win32 /p:SkipResGeneration=false /p:ForceRebuild=true /m /verbosity:minimal
```

`IROCV.res`, `Win32/` 등의 생성 산출물은 소스 커밋에 넣지 않습니다.

전체 C++Builder Debug/Win32 빌드 후에도 실제 에뮬레이터/설비 확인은 별도입니다.
최소한 정상 연속 측정, 개별 재측정, NG Tray Out/Restart, SERIAL 재시도, 수동/BYPASS, 연결 복구를 확인해야 합니다.
자세한 기존 동작과 테스트 항목은 `AUTO_INSPECTION.md`를 참고하세요.

## 유지보수 정리 (2026-09-21)

### 사이트 변경 위치
- `SiteConfig.h`: 실제 행/열(20×20=400, 16×16=256), 재측정 개수 기준, 완료 신호 지연(ms).
- `Modplc.h`: PLC 주소/예약 채널 수/전송 길이. 실제 256채널이어도 PLC 공간 400채널을 유지할 수 있으므로 자동 축소하지 않는다.
- 배열·채널 반복·MSA 결과 배열은 MAXCHANNEL을 사용한다. 화면의 사이트별 방향/장식 좌표와 매핑 파일은 별도로 확인한다.
- PLC 결과는 OK=0 / NG=1. 측정 NG 수량은 존재 셀만, PLC NG 수량은 기존 정책대로 빈 채널 포함.

### 재측정 두 종류
1. 닫힌 프로브 유지: 전체 측정 뒤 NG가 Config의 최대 개수 **이하**이면 불량 항목을 한 번 확인. 0이면 생략하며, 기본값 49로 기존 정책을 유지한다. Config 재개폐 횟수와 무관.
2. 프로브 재개폐: 열림 확인 뒤 NG가 남으면 추가 재측정. Config REMEASURE=0이면 끔, N이면 최대 N회. 중간에 NG가 없어지면 종료.
   기존 선택 기준은 50개 초과 전체 / 50개 이하 불량셀. 횟수는 닫힘 확인 후 실제 시작 때 증가하고 새 트레이에서 초기화한다.
- 이전 AUTO_CHECK=false 설정은 처음 읽을 때 0회로 이관하며, 설정 저장 후에는 횟수 하나만 사용한다.
- 재측정 중 설정 변경은 다음 트레이부터 적용한다.
- 두 설정 저장/읽기: Stage_log.cpp의 WriteSystemInfo / ReadSystemInfo.
- 닫힘 최대 개수: config.closedProbeRemeasureMaxNgCount → MAIN/CLOSED_PROBE_REMEASURE_MAX_NG_COUNT(0~MAXCHANNEL, 기본 49). Stage_Measurement.cpp::SetRemeasureList에서 NG > 0 && NG <= 설정값으로 판단한다.
- 재개폐 횟수: config.probeRemeasureCount → 기존 MAIN/REMEASURE. 순수 시퀀스에서 NG가 남은 동안 최대 N회 요청한다.
- 두 값은 SetNextTrayRemeasureSettings에서 TRAY IN 대기 중에만 갱신한다. 재개폐 전체/선택 기준(50개 초과 전체)은 SiteConfig.h::PROBE_REMEASURE_ALL_CELL_NG_THRESHOLD로 분리한다.
- `retest.cell`은 최종 판정, `pendingItems / waitingChannel / waitingItem`은 재측정 요청 진행이다.
- 판정 우선순위는 접촉(4) > IR(2) > OCV(3). 이전 불량·화면 색상을 판정 근거로 사용하지 않는다.

### 결과 마감과 화면
- `FinishMeasurement` → 최종 시리얼(상시 모드만) → `SaveMeasurementResult` → `Timer_ResultSaveTimer`.
- `resultSaveStep`: 대기 / 시리얼 대기 / 파일 작성 / PLC 전송 대기 / 완료 / 취소 / 오류.
- 참고용 CSV는 최초 시도 + 재시도 1회. 두 번 실패해도 로그 후 생산 진행. 시리얼 작업자 선택은 미체크 모드의 투입 시 검사에만 사용합니다.
- 파일명은 분 단위 유지. 같은 트레이 전체/선택 재측정은 파일명을 보존해 최종값으로 덮어쓴다.
- 임시 파일을 완전히 쓴 후 교체하므로 실패할 때 이전 결과를 먼저 삭제하지 않는다.
- 생산 트레이 수는 한 번 집계하고 재측정에 따른 최종 IR/접촉 NG 누계 차이만 보정한다.
- COMPLETE는 새 판정/IR/OCV 블록 송신 + 최소 1000ms 후 출력. UI 스레드 Sleep은 사용하지 않는다.
- 이 확인은 TCP 송신 확인이며 PLC 내부 반영 ACK는 아니다. PLC 신호는 추가하지 않는다.
- 초기화/강제 배출은 지연 완료를 취소한다. 수동/BYPASS 배출은 기존 NG 무시 정책 유지.
- `UpdateCellDisplay`는 현재 수신 여부/값으로 색상을 다시 만든다. 이전 색상이나 응답 순서에 의존하지 않는다.
- 평균 기준 판정 설정과 미계산 평균/시그마 CSV 항목은 제거했다. 기존 파일 소비자가 있으면 헤더 호환성을 확인한다.
- `SetString / GetPlcData / GetCellSerial*`은 확장용 PLC API로 유지한다.

### 추가 회귀 검사
`TestAutoInspection.ps1`: 설정 0/1/2회, NG 소멸 조기 종료, 횟수 소진, 강제 배출.
`TestCellSerialRead.ps1`: 실제 메서드 추출로 시리얼·판정 우선순위·화면·재측정 요청·중복 집계·저장 재시도·완료 지연 검증.
`TestResultFile.ps1`: 실제 임시 파일로 CSV 생성 실패/부분 쓰기/덮어쓰기/파일 잠금을 검사한다.
검사는 생산 실행 파일을 실행하거나 PLC/측정장비에 접속하지 않는다.
