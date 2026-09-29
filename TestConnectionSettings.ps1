# 실제 메서드를 가짜 소켓/UI로 검증한다. 장비 접속/프로그램 실행 없음.
param([string]$Compiler = 'C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference = 'Stop'
function Read-Source([string]$name) {
    $b=[IO.File]::ReadAllBytes((Join-Path $PSScriptRoot $name))
    try { return [Text.UTF8Encoding]::new($false,$true).GetString($b).TrimStart([char]0xFEFF) }
    catch { return [Text.Encoding]::GetEncoding(949).GetString($b) }
}
function Methods([string]$file,[string]$class,[string[]]$names) {
    $s=Read-Source $file
    foreach($name in $names) {
        $m=[regex]::Match($s,'(?ms)^(?:void|bool) __fastcall '+$class+'::'+$name+'\([^;{]*\)\s*\{.*?^\}')
        if(-not $m.Success){throw "Missing method $class::$name"}
        $m.Value
    }
}
# 두 운전 모드의 오류 검사 정의가 같은 파일에 하나씩 있어야 한다.
$autoDefinition=@(Methods 'Stage_Form.cpp' 'TTotalForm' @('CheckAutoInspectionError'))
if((Read-Source 'Stage_AutoInspection.cpp') -match 'bool __fastcall TTotalForm::CheckAutoInspectionError'){
    throw 'Auto error check must be defined in Stage_Form.cpp'
}
if((Read-Source 'Stage_Form.cpp') -match 'ErrorCheck_Manual'){throw 'Obsolete manual error-check name'}
$isIROCV=Test-Path (Join-Path $PSScriptRoot 'IROCV.cbproj')
$eq=if($isIROCV){'IROCV'}else{'PRECHARGER'}
$disconnect=if($isIROCV){'btnDisConnectIROCVClick'}else{'btnDisconnPRECHARGERClick'}
$methods=@(Methods 'Stage_Form.cpp' 'TTotalForm' @('CheckManualInspectionError'))
$methods+=@(Methods 'Stage_comm.cpp' 'TTotalForm' @('ValidateConnectionSettings','ApplyConnectionSettings','ProcessEquipmentReconnect'))
$methods+=@(Methods 'FormTotal.cpp' 'TTotalForm' @("btnConnect${eq}Click",$disconnect,'btnConnectPLCClick','Timer_PLCConnectTimer'))
$methods+=@(Methods 'ModPLC.cpp' 'TMod_PLC' @('Connect','Disconnect','ClientSocket_PCDisconnect','ClientSocket_PLCDisconnect','Timer_PC_AutoConnectTimer','Timer_PLC_AutoConnectTimer'))
# 호출 위치도 검사: 수동 표시는 상시 상태 타이머에서, 접속 적용은 저장 이후에 실행한다.
$status=(Methods 'Stage_Form.cpp' 'TTotalForm' @('ProcessStageStatus')) -join ""
if($status -notmatch '!Timer_AutoInspection->Enabled' -or $status -notmatch 'CheckManualInspectionError\(\)'){throw 'Manual status timer not wired'}
$save=(Methods 'FormTotal.cpp' 'TTotalForm' @('btnSaveConfigClick')) -join ""
if($save.IndexOf('ValidateConnectionSettings') -gt $save.IndexOf('WriteSystemInfo()') -or
   $save -notmatch 'ReadSystemInfo\(\);\s*ApplyConnectionSettings\(true, true\)'){throw 'Save/reconnect ordering changed'}
$read=(Methods 'Stage_log.cpp' 'TTotalForm' @('ReadSystemInfo')) -join ""
if($read -match 'Client->(?:Host|Port|Active)\s*='){throw 'ReadSystemInfo must not mutate a live equipment socket'}
$source=(Read-Source 'ConnectionSettingsTests.cpp.in').Replace('@@METHODS@@',($methods -join "`r`n"))
$dir=Join-Path ([IO.Path]::GetTempPath()) ('connection-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
[IO.File]::WriteAllText((Join-Path $dir 'ConnectionSettingsTests.cpp'),$source,[Text.Encoding]::GetEncoding(949))
Push-Location $dir
try {
    $args=@('-tWC',"-I$PSScriptRoot",'-eConnectionSettingsTests.exe')
    if($isIROCV){$args+='-DTEST_IROCV'}
    $args+='ConnectionSettingsTests.cpp'
    & $Compiler @args
    if($LASTEXITCODE -ne 0){throw 'Connection test build failed'}
    & .\ConnectionSettingsTests.exe
    if($LASTEXITCODE -ne 0){throw 'Connection tests failed'}
    "Test artifacts: $dir"
} finally { Pop-Location }
