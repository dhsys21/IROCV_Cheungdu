# Offline production-method tests. No application startup or equipment connection.
param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference='Stop'
function Read-Source([string]$name){
    $b=[IO.File]::ReadAllBytes((Join-Path $PSScriptRoot $name))
    try{return [Text.UTF8Encoding]::new($false,$true).GetString($b).TrimStart([char]0xFEFF)}
    catch{return [Text.Encoding]::GetEncoding(949).GetString($b)}
}
function Method([string]$file,[string]$class,[string]$name){
    $s=Read-Source $file
    $m=[regex]::Match($s,'(?ms)^(?:void|bool) __fastcall '+$class+'::'+$name+'\([^;{]*\)\s*\{.*?^\}')
    if(!$m.Success){throw "Missing production method: $class::$name"}
    return $m.Value
}
$isIROCV=Test-Path (Join-Path $PSScriptRoot 'IROCV.cbproj')
$methods=@(Method 'ModPLC.cpp' 'TMod_PLC' 'IsPlcAutoMode')
foreach($name in @('UpdateAutoInspectionMode','IsAutoInspectionBlocked','ResetAutoInspectionForPlcMode')){
    $methods+=Method 'Stage_AutoInspection.cpp' 'TTotalForm' $name
}
$status=Method 'Stage_Form.cpp' 'TTotalForm' 'ProcessStageStatus'
if($status -notmatch 'UpdateAutoInspectionMode\(\)'){throw 'Status timer must monitor PLC mode'}
$auto=Method 'Stage_AutoInspection.cpp' 'TTotalForm' 'ProcessAutoInspection'
if($auto.IndexOf('UpdateAutoInspectionMode()') -gt $auto.IndexOf('RunAutoStep(') -or
   $auto -notmatch 'UpdateAutoInspectionMode\(\);\s*if\(!Timer_AutoInspection->Enabled\) return;'){
    throw 'Auto sequence entry must enforce PLC mode before advancing'
}
$mode=Method 'Stage_comm.cpp' 'TTotalForm' 'CmdSetManualMode'
if($mode -match 'Timer_AutoInspection->Enabled = true' -or $mode -notmatch 'UpdateAutoInspectionMode\(\)'){
    throw 'PC AUTO selection must not bypass PLC interlock'
}
foreach($name in @('ProcessResultSave',$(if($isIROCV){'FinishMeasurement'}else{'SaveChargingResult'}))){
    if((Method 'Stage_Measurement.cpp' 'TTotalForm' $name) -notmatch 'if\(IsAutoInspectionBlocked\(\)\) return;'){
        throw "Result callback bypasses mode interlock: $name"
    }
}
if((Read-Source 'FormTotal.dfm') -notmatch 'object Timer_AutoInspection: TTimer\s+Enabled = False'){
    throw 'Automatic timer must be disabled at startup'
}
$receive=Method 'ModPLC.cpp' 'TMod_PLC' 'ClientSocket_PLCRead'
if($receive -notmatch 'ReadPlcInterfaceData\([^)]*\);\s*plcAutoMode.Observe\(GetPlcValue\(PLC_D_(?:IROCV_)?AUTO_MANUAL\) == PLC_AUTO_MODE_VALUE\)'){
    throw 'Only a complete standard response may publish PLC mode'
}
foreach($name in @('Disconnect','InitializePlcCommunication','ClientSocket_PCDisconnect','ClientSocket_PLCDisconnect','ClientSocket_PCError','ClientSocket_PLCError')){
    if((Method 'ModPLC.cpp' 'TMod_PLC' $name) -notmatch 'plcAutoMode.Invalidate\(\)'){
        throw "Stale PLC mode is not invalidated: $name"
    }
}
$source=(Read-Source 'PlcAutoModeTests.cpp.in').Replace('@@METHODS@@',($methods -join [Environment]::NewLine))
$dir=Join-Path ([IO.Path]::GetTempPath()) ('plc-mode-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
[IO.File]::WriteAllText((Join-Path $dir 'PlcAutoModeTests.cpp'),$source,[Text.Encoding]::GetEncoding(949))
Push-Location $dir
try{
    $args=@('-tWC',"-I$PSScriptRoot",'-ePlcAutoModeTests.exe')
    if($isIROCV){$args+='-DTEST_IROCV'}
    $args+='PlcAutoModeTests.cpp'
    & $Compiler @args
    if($LASTEXITCODE -ne 0){throw 'PLC mode test build failed'}
    & .\PlcAutoModeTests.exe
    if($LASTEXITCODE -ne 0){throw 'PLC mode tests failed'}
    'PASS: startup, status/auto/result callbacks, PC mode selection and receive/disconnect wiring'
    "Test artifacts: $dir"
}finally{Pop-Location}

