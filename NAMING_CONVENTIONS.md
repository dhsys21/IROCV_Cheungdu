# 함수·변수 명명 규칙

PRECHARGER와 IR/OCV의 **현재 프로젝트에 등록된 운영 코드**에 적용한다. 이번 정리는 이름만 바꾸며, 함수 파일 위치·실행 순서·인수·반환값·검사 조건은 유지한다.

## 역할별 규칙

| 역할 | 규칙 | 예 |
|---|---|---|
| 초기화 | Initialize + 대상 | InitializeInspection, InitializeTrayData |
| 재설정/취소 | Reset / Cancel + 대상 | ResetMeasurementData, CancelResultSave |
| 반복 처리·수신 처리 | Process + 대상 | ProcessAutoInspection, ProcessEquipmentMessage |
| 오류 판단·조건 확인 | Check / Is / Has | CheckManualInspectionError, IsEquipmentSettingReady |
| 데이터 읽기·쓰기 | Read / Write + 대상 | ReadChannelMapping, WritePlcSpecifications |
| 로그 기록 | Write + 대상 + Log | WriteErrorLog, WritePlcLog |
| 표시·갱신 | Display / Update + 대상 | DisplayStageError, UpdateRemeasureAlarm |
| 장비 명령 | Cmd + 동작 + 대상 | CmdSetManualMode, CmdSetSpeed |
| 접속·해제 | Connect / Disconnect | TMod_PLC::Disconnect |
| 결과 마감 | …ResultSave | StartResultSave, ProcessResultSave, CancelResultSave |

- 일반 함수는 PascalCase를 사용한다. Plc/Id처럼 단어 단위로 적되, PLC 주소 상수·프로토콜 명령·외부 API의 이름은 변경하지 않는다.
- 서로 같은 역할이면 같은 이름을 사용하되 장비별 인수와 실제 처리 내용은 유지한다. 결과 마감의 ResultSave는 파일 저장뿐 아니라 기존 시리얼/PLC 송신 대기도 포함한다.
- 측정 NG 수는 양쪽 모두 measurementNgCount로 맞췄다. 그 외 기존 구조체/변수 전체를 일괄 재작성하지 않고 명확한 오타와 대응 항목만 정리했다.
- DFM 이벤트 이름 변경 시 선언·정의·DFM 연결을 함께 수정한다. 수동 시작은 btnStartManualInspectionClick으로 구분하며, FormTotal의 btnAutoClick은 자동모드 전환이므로 유지한다. 컴포넌트 이름과 다른 이벤트는 유지한다.
- 통신 프레임 문자열, INI 키, CSV 헤더, 로그 메시지 문자열은 유지한다. 기존 로그 문자열에 옛 함수명이 남아 있을 수 있다.
- 프로젝트 미등록 레거시 통신 모듈과 VISA/외부 SDK 헤더는 이번 운영 코드 통일 범위에서 제외한다. 등록된 클래스의 이름 변경에 영향을 받는 참조는 별도로 확인한다.
- 자동/수동 오류 검사 호출 위치는 그대로다. 자동은 ProcessAutoInspection에서 진행을 보류하고, 수동은 ProcessStageStatus에서 표시만 갱신한다.

## 변경 목록

| 이전 이름 | 현재 이름 |
|---|---|
| `BadInformation` | `UpdatePlcResults` |
| `CmdManualMod` | `CmdSetManualMode` |
| `CmdSpeedSet` | `CmdSetSpeed` |
| `DataCheck` | `ParseEquipmentMessage` |
| `DisConnect` | `Disconnect` |
| `ErrorLog` | `WriteErrorLog` |
| `ErrorMsg` | `DisplayStageError` |
| `InitCellDisplay` | `InitializeCellDisplay` |
| `InitMeasureForm` | `InitializeMeasureForm` |
| `InitStruct` | `InitializeDisplayData` |
| `InitTrayStruct` | `InitializeTrayData` |
| `Initialization` | `InitializeInspection` |
| `OnInit` | `ResetMeasurementData` |
| `OnReceiveStage` | `ProcessEquipmentMessage` |
| `PC_Initialization` | `InitializePcCommunication` |
| `PLCInitialization` | `InitializePlcData` |
| `PLC_Initialization` | `InitializePlcCommunication` |
| `PLC_Recv_Interface` | `ReadPlcInterfaceData` |
| `PLC_Recv_Interface_CellSerial` | `ReadPlcCellSerialChunk` |
| `ReadCaliboffset` | `ReadCalibrationOffsets` |
| `ReadchannelMapping` | `ReadChannelMapping` |
| `RemeasureAlarm` | `UpdateRemeasureAlarm` |
| `RemeasureExcute` | `ExecuteRemeasure` |
| `ResponseAutoTestFinish` | `ProcessMeasurementCompleteResponse` |
| `SensorInputProcess` | `ProcessSensorInput` |
| `SensorOutputProcess` | `ProcessSensorOutput` |
| `SetAutoMeasureComplete` | `SetAutoMeasurementComplete` |
| `ShowPLCSignal` | `DisplayPlcSignal` |
| `VisibleBox` | `ShowPanelGroup` |
| `WriteCaliboffset` | `WriteCalibrationOffsets` |
| `WriteIRMINMAX` | `WritePlcSpecifications` |
| `WritePLCLog` | `WritePlcLog` |
| `initChart` | `InitializeChart` |
| `measNgCount` | `measurementNgCount` |
| `orginal_value` | `original_value` |

## 자동·수동 내부 역할 명확화

공통 처리에는 Auto/Manual을 붙이지 않고, 모드 전용 처리에만 붙인다. Cmd는 실제 장비 명령에 사용한다. 호출 위치·순서·프로토콜 문자열은 바꾸지 않는다.

| 이전 이름 | 현재 이름 |
|---|---|
| `CmdAutoTest` | `CmdStartMeasurement` |
| `ProcessAutoTestComplete` | `ProcessMeasurementCompleteResponse` |
| `CmdTrayOut` | `ProcessAutoTrayOut` |
| `ManualTrayOut` | `ProcessManualTrayOut` |
| `StageLocalRemeasure` | `ProcessOpBoxRemeasureRequest` |
| `SaveMeasurementResult` | `WriteMeasurementResults` |
| `TMeasureInfoForm::btnAutoClick` | `btnStartManualInspectionClick` |

- `WriteMeasurementResults`: 확보한 데이터로 판정/누계·PLC 결과값·CSV를 기록하고 PLC 송신 완료 대기로 전환하는 실행 단계. 순수 파일 기록은 기존 `WriteResultFile`이 담당한다. PRECHARGER에도 같은 역할 이름을 적용한다.
- `ProcessMeasurementCompleteResponse`는 완료 응답의 진입점이며 결과를 마감하는 `FinishMeasurement`와 구분한다.
- `ProcessAutoTrayOut`은 자동 조건을 확인하고, `ProcessManualTrayOut`은 수동 배출을 요청한다. 기존 `ForceTrayOut`은 별도 강제 배출 처리로 유지한다.
- `ProcessOpBoxRemeasureRequest`는 OP BOX 요청을 처리한다. `StartFullRemeasure` / `StartSelectedRemeasure`와 요청 출처 및 동작이 달라 별도로 유지한다.
- `bLocal`과 `stage.arl`은 다른 상태이므로 통합하거나 이름만 보고 치환하지 않는다. 자동·수동 오류 검사 호출 위치도 유지한다.

## 검증

`TestNamingConventions.ps1`은 등록 소스와 대응 헤더의 코드 토큰에서 이전 이름의 잔존 여부를 확인한다. 문자열·주석·프로토콜 데이터는 검사에서 제외한다. 기존 회귀검사 및 별도 경로 Debug/Win32 전체 빌드와 함께 실행한다.
