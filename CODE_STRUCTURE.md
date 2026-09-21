# IROCV 코드 구조와 수정 위치

목표는 “어디를 고쳐야 하는지, 어떤 단계에서 멈췄는지 바로 찾을 수 있는 구조”입니다.
생산 판정과 PLC 주소를 바꾸기 위한 정리가 아닙니다. PRECHARGER와 별도 저장소로 관리합니다.

## 먼저 볼 파일

| 파일 | 담당 역할 | 처음 찾아볼 함수 |
|---|---|---|
| `FormTotal.cpp` | 폼 생성·시작·종료, 버튼/입력 이벤트 | `FormShow`, 각 버튼 이벤트 |
| `FormTotal.h` | 폼 구성요소와 공용 데이터, 역할별 함수 선언 | private/public의 구현 파일별 구역 |
| `AutoInspectionSequence.h/.cpp` | 자동 단계와 다음 명령 판단 | `TAutoInspectionSequence::RunAutoStep` |
| `Stage_AutoInspection.cpp` | 자동 타이머와 PLC/UI 연결 | `Timer_AutoInspectionTimer`, `RunAutoInspectionCommand` |
| `Stage_Measurement.cpp` | IR/OCV 수신값 처리·재측정·결과 마감 | `ProcessIr/Ocv`, `SetRemeasureList`, `CmdForceStop` |
| `Stage_PlcData.cpp` | PC→PLC 초기값·측정값·NG·결과 코드 작성 | `PLCInitialization`, `BadInfomation`, `WriteResultCode` |
| `Stage_TrayData.cpp` | 트레이 데이터 초기화·시리얼 복사·임시 파일 | `InitTrayStruct`, `ReadCellSerial`, `SaveTrayInfo` |
| `Stage_CellDisplay.cpp` | 400채널 생성·번호/측정값·색상 표시 | `InitCellDisplay`, `SetProcessColor`, `InitMeasureForm` |
| `Stage_comm.cpp` | 측정장비 소켓·송수신·프레임·응답 분기 | `ClientRead`, `OnReceiveStage`, `SendData` |
| `Stage_Form.cpp` | 상태/오류/연결 이미지·PLC 표시등·화면 전환 | `DisplayStatus`, `RefreshStageStatusImage`, `DisplayError` |
| `Stage_log.cpp` | 설정·채널 매핑·결과 파일·로그 | `ReadSystemInfo`, `ReadchannelMapping`, `WriteResultFile` |
| `Modplc.h/.cpp` | PLC 주소와 실제 PLC 통신 | 주소 상수, `StartCellSerialRead` |
| `FormPLCInterface.cpp/.dfm` | PLC 데이터 모니터 및 테스트 패널 | `chkShowAllClick`, `GetDisplayChannelStep`, `Timer_UpdateTimer` |

폼의 컨트롤이나 기존 DFM 이벤트를 사용하는 함수는 `TTotalForm::` 형태를 유지합니다.
구현 파일만 역할별로 나눠 DFM 연결과 기존 폼 접근 방식을 유지했습니다.
PLC/화면을 사용하지 않는 자동 단계 판단만 `TAutoInspectionSequence`로 독립되어 있습니다.

## 자동측정을 읽는 순서

1. `Timer_AutoInspectionTimer`: 진행 가능한지 확인하고 이번 명령을 구합니다.
2. `RunAutoStep`: 현재 `STEP_...`의 진행 조건을 확인하고 다음 단계/명령을 결정합니다.
3. `RunAutoInspectionCommand`: 반환된 `CMD_...`에 해당하는 PLC 출력이나 측정 명령을 **한 번** 실행합니다.
4. `OnReceiveStage`: 장비의 AMS/AMF/IR/OCV 응답을 해당 처리 함수에 전달합니다.
5. `CmdForceStop`: 기존 순서로 결과를 마감한 뒤 `SetAutoMeasureComplete`로 완료를 알립니다.
6. `RunAutoStep`: 프로브 열림 확인 후 정상 배출 또는 NG 오류 선택 대기로 진행합니다.

`SetStep`은 “진행 단계 변경 + 해당 단계 대기 횟수 초기화”입니다.
`SetAutoReadySignalToPLC`는 “운전 모드에 따라 AUTO READY를 자동=1, 수동=0으로 설정”입니다.
이 함수 하나가 전체 측정 준비 조건을 확인하는 것은 아닙니다.

## 증상별 확인 위치

| 증상 | 확인 순서 |
|---|---|
| 자동측정이 시작되지 않음 | `CheckAutoInspectionError` → 마지막 단계 로그 → `RunAutoStep`의 해당 STEP 조건 |
| 시리얼 개수 불일치/타임아웃 | `STEP_WAIT_CELL_SERIAL` → `ReadCellSerial` → `Modplc::StartCellSerialRead` 및 수신 완료 처리 |
| NG 오류창이 안 뜨거나 정상 배출됨 | `BadInfomation`의 `NgCount` → `IsNgCountError` → `CMD_NG_ERROR`; 수동/BYPASS는 의도적으로 NG를 무시 |
| NG 창에서 배출/재시작 문제 | `FormError.cpp`의 버튼 → `ForceTrayOut` / `RestartAutoInspection` |
| IR/OCV 값·보정·재측정 문제 | `ProcessIr/Ocv` → `InsertIr/OcvValue` → `SetRemeasureList` / `RemeasureExcute` |
| 트레이 투입 후 번호/이전 값이 보임 | `CMD_TRAY_IN`의 `showStartupChannelNumbers=false` → `InitCellDisplay` → `SetProcessColor`의 개별 수신 플래그 |
| PLC 결과값/NG 비트가 이상함 | `Stage_PlcData.cpp`의 해당 작성 함수 → `Modplc.h` 주소/배율 |
| 연결 끊김이 Vacancy로 보임 | `RefreshStageStatusImage`와 장비 `Client... ` 이벤트 |
| 트레이 ID/시리얼 파일 문제 | `Stage_TrayData.cpp`의 `Load/Save/DeleteTrayInfo` |
| 설정/채널 매핑/로그 문제 | `Stage_log.cpp` |

기존 PLC 로그의 `AutoInspection` 항목에는 “이전 단계 → 다음 단계 : 이유”가 기록됩니다.
`AutoInspection ERROR`는 예외 발생 단계와 메시지입니다.
오류 정지는 PC 시퀀스 진행 정지이며 PLC 비상정지/이미 실행된 이동의 취소가 아닙니다.

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
- 구형 장비 명령: `CmdForceStop_Original`, `CmdTrayOut_Original`, `CmdVersion`, `CmdEmergencyStop`, `CmdGetSensorInfo`, `CmdRestart`, `StageClearAlarm`, `CmdDeviceInfo`
- 중복/미연결 UI 함수: `btnPLCConnectClick`, `btnPLCDisconnectClick`, `ShowAlarm`, `VisibleSpec`

선언만 남아 있던 `WriteResultFile_MES`, `WriteResultFile_MES2`, `StageReady`도 제거했습니다.
실제로 쓰는 평균 옵션, 재측정 판정, 기존 결과 파일 형식은 변경하지 않았습니다.

읽히지 않던 멤버 13개를 제거했습니다:
`Old_batch`, `clSelect`, `clNo`, `clYes`, `remeasure_info`, `precharger_okng`,
`m_bAuto`, `mAuto`, `q_txMode`, `ErrorCheckStatus`, `OldIROCVStage`, `IROCVStage`, `bconfig`.
`bconfig`는 항상 false였으므로 해당 불가능 분기를 정리했습니다.
사용하지 않는 지역 변수와 `SetProcessColor`의 무사용 인자/계산도 정리했습니다.
`ReadSystemInfo`와 `ReadCellInfo`는 반환값을 사용하지 않는 동작 함수여서 `void`로 맞췄습니다.

DFM 연결이 있는 빈/시험용 이벤트는 보존했습니다. 저장소에 남은 프로젝트 미등록 구형 파일은 자동 삭제하지 않았습니다.
삭제한 이전 구현은 기준 커밋 `dd69ce9`에서 확인할 수 있습니다.

## PLC 결과 규격과 작성 순서

운영자 확인 규격은 **OK=0, NG=1**입니다. 내부 재측정 사유 코드와 PLC 결과 코드는 다릅니다.
`CmdForceStop`은 `BadInfomation()`으로 최종 OK/NG 비트를 만든 다음 `WriteResultCode()`를 호출합니다.
`WriteResultCode()`는 해당 비트를 셀마다 읽어 400개 결과 코드에도 같은 0/1을 기록합니다.
기존 4/5/6 출력과 정상 셀의 미초기화 문제를 제거했고, NG 다음 OK 셀에도 반드시 0을 씁니다.
기존 빈 셀의 NG 비트 처리 및 PLC용 `ngCount`/오류창용 `NgCount` 집계 기준은 변경하지 않았습니다.

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

1. `CmdForceStop`에서 기존 STP/프로브 열림을 요청하고 `StartResultCellSerialRead`로 새 수신을 시작합니다.
2. `Timer_ResultCellSerialTimer`가 자동/수동 모두에서 완료를 기다립니다. 일반적인 추가 대기는 PLC 응답 속도에 따라 약 2초이며 제한은 10초입니다.
3. 완료 후 `ReadCellSerial`로 현재 트레이에 복사하고 CELL DATA 개수와 비교합니다.
4. 정상 수신이면 `SaveMeasurementResult`에서 IR/OCV와 함께 저장하고 COMPLETE를 출력합니다. 이전 .Tray 파일을 다시 읽어 덮어쓰지 않습니다.
5. 시간 초과/개수 불일치는 FormCellIdError 대기로 전환합니다. 파일 저장/COMPLETE/자동 배출을 하지 않습니다.
6. CANCEL은 시리얼만 재수신합니다. SAVE는 전체 수신 완료 데이터에 한해 개수 불일치를 운영자 승인으로 저장합니다. 미완료 데이터는 SAVE해도 저장하지 않습니다.
7. 초기화/강제 배출/예외 정지는 지연 저장을 취소합니다. 기존 NG 판정과 수동/BYPASS 배출 정책은 유지합니다.

관련 주석은 `[CELL SERIAL 공통]`으로 검색할 수 있습니다.
통신은 `Modplc.cpp`, 설정은 `Stage_log.cpp`, 최종 수신 대기는 `Stage_TrayData.cpp`,
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
