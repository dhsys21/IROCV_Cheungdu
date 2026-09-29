# 등록된 운영 코드의 이전 식별자 잔존 검사. 실제 프로그램/장비를 실행하지 않는다.
param([string]$SourceRoot = $PSScriptRoot)
$ErrorActionPreference = 'Stop'
function Read-Source([string]$name) {
    $bytes=[IO.File]::ReadAllBytes((Join-Path $SourceRoot $name))
    try {return [Text.UTF8Encoding]::new($false,$true).GetString($bytes).TrimStart([char]0xFEFF)}
    catch {return [Text.Encoding]::GetEncoding(949).GetString($bytes)}
}
[xml]$project=Read-Source 'IROCV.cbproj'
$sources=@($project.Project.ItemGroup.CppCompile.Include | Where-Object {$_})
$files=@($sources)+@($sources | ForEach-Object {[IO.Path]::ChangeExtension($_,'.h')})+@('DEFINE.h','SiteConfig.h')
$files=@($files|Sort-Object -Unique|Where-Object {Test-Path -LiteralPath (Join-Path $SourceRoot $_)})
$renames=@{
    'CmdAutoTest' = 'CmdStartMeasurement'
    'ProcessAutoTestComplete' = 'ProcessMeasurementCompleteResponse'
    'CmdTrayOut' = 'ProcessAutoTrayOut'
    'ManualTrayOut' = 'ProcessManualTrayOut'
    'StageLocalRemeasure' = 'ProcessOpBoxRemeasureRequest'
    'SaveMeasurementResult' = 'WriteMeasurementResults'
    'BadInformation' = 'UpdatePlcResults'
    'CmdManualMod' = 'CmdSetManualMode'
    'CmdSpeedSet' = 'CmdSetSpeed'
    'DataCheck' = 'ParseEquipmentMessage'
    'DisConnect' = 'Disconnect'
    'ErrorLog' = 'WriteErrorLog'
    'ErrorMsg' = 'DisplayStageError'
    'InitCellDisplay' = 'InitializeCellDisplay'
    'InitMeasureForm' = 'InitializeMeasureForm'
    'InitStruct' = 'InitializeDisplayData'
    'InitTrayStruct' = 'InitializeTrayData'
    'Initialization' = 'InitializeInspection'
    'OnInit' = 'ResetMeasurementData'
    'OnReceiveStage' = 'ProcessEquipmentMessage'
    'PC_Initialization' = 'InitializePcCommunication'
    'PLCInitialization' = 'InitializePlcData'
    'PLC_Initialization' = 'InitializePlcCommunication'
    'PLC_Recv_Interface' = 'ReadPlcInterfaceData'
    'PLC_Recv_Interface_CellSerial' = 'ReadPlcCellSerialChunk'
    'ReadCaliboffset' = 'ReadCalibrationOffsets'
    'ReadchannelMapping' = 'ReadChannelMapping'
    'RemeasureAlarm' = 'UpdateRemeasureAlarm'
    'RemeasureExcute' = 'ExecuteRemeasure'
    'ResponseAutoTestFinish' = 'ProcessMeasurementCompleteResponse'
    'SensorInputProcess' = 'ProcessSensorInput'
    'SensorOutputProcess' = 'ProcessSensorOutput'
    'SetAutoMeasureComplete' = 'SetAutoMeasurementComplete'
    'ShowPLCSignal' = 'DisplayPlcSignal'
    'VisibleBox' = 'ShowPanelGroup'
    'WriteCaliboffset' = 'WriteCalibrationOffsets'
    'WriteIRMINMAX' = 'WritePlcSpecifications'
    'WritePLCLog' = 'WritePlcLog'
    'initChart' = 'InitializeChart'
    'measNgCount' = 'measurementNgCount'
    'orginal_value' = 'original_value'
}
# 문자열 안의 //, /* 및 이스케이프된 따옴표를 코드/주석으로 오인하지 않는다.
$nonCode='(?s)"(?:\\.|[^"\\])*"|''(?:\\.|[^''\\])*''|/\*.*?\*/|//[^\r\n]*'
$all=''
foreach($file in $files){
    $code=[regex]::Replace((Read-Source $file),$nonCode,' ')
    foreach($old in $renames.Keys){
        if($code -cmatch ('\b'+[regex]::Escape($old)+'\b')){
            throw "Obsolete identifier in ${file}: $old -> $($renames[$old])"
        }
    }
    $all+=$code+"`n"
}
foreach($new in $renames.Values){
    if($all -cnotmatch ('\b'+[regex]::Escape($new)+'\b')){throw "Renamed identifier missing: $new"}
}
"PASS: $($renames.Count) naming mappings across $($files.Count) registered source/header files"

# 수동 시작 이벤트만 변경한다. FormTotal의 자동모드 전환 이벤트는 별개다.
foreach($file in @('FormMeasureInfo.cpp','FormMeasureInfo.h','FormMeasureInfo.dfm')){
    $text=Read-Source $file
    if($text -cmatch '\bbtnAutoClick\b' -or $text -cnotmatch '\bbtnStartManualInspectionClick\b'){
        throw "Manual start event naming mismatch: $file"
    }
}
if((Read-Source 'FormMeasureInfo.dfm') -cnotmatch 'OnClick\s*=\s*btnStartManualInspectionClick\b'){
    throw 'Manual start DFM event is not connected'
}
foreach($file in @('FormTotal.cpp','FormTotal.h','FormTotal.dfm')){
    if((Read-Source $file) -cnotmatch '\bbtnAutoClick\b'){throw "Auto-mode event must remain intact: $file"}
}
'PASS: manual-start event declaration/definition/DFM naming and separate auto-mode event verified'
