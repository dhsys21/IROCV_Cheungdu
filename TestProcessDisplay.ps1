# Offline regression for the retired eight-panel process display.
param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference='Stop'
function Read-Source([string]$name) {
    $bytes=[IO.File]::ReadAllBytes((Join-Path $PSScriptRoot $name))
    try { return [Text.UTF8Encoding]::new($false,$true).GetString($bytes) }
    catch { return [Text.Encoding]::GetEncoding(949).GetString($bytes) }
}
$names=@('FormTotal.cpp','FormTotal.h','FormTotal.dfm','Stage_Form.cpp','Stage_AutoInspection.cpp',
    'Stage_Measurement.cpp','Stage_log.cpp','FormLanguage.cpp','DEFINE.h')
$retired='\b(?:pProcess|flowChart|lblProcessInfo|lblRemeasureAlarmCheck|pReadyClick|pReady|pTrayIn|pBarcode|pMeasure|pFinish|pProbeOpen|pTrayOut|pProbeDown|sReady|sTrayIn|sBarcode|sProbeDown|sMeasure|sFinish|sProbeOpen|sTrayOut)\b'
foreach($name in $names) {
    if((Read-Source $name) -cmatch $retired) { throw "Retired process reference remains: $name" }
}
$view=Read-Source 'Stage_OperationView.cpp'
if(!$view.Contains('f->Panel_State->Caption') -or !$view.Contains('stageForm->Panel_State->Color')) {
    throw 'Current operation message/error backing state was removed'
}
$alarm=Read-Source 'Stage_log.cpp'
foreach($text in @('PC_D_IROCV_NG_ALARM, 1','PC_D_IROCV_NG_ALARM, 0','btnRemeasureInfo->Color = clRed','btnRemeasureInfo->Color = clWhite')) {
    if(!$alarm.Contains($text)) { throw "Live remeasure alarm behavior missing: $text" }
}
$source=Read-Source 'Stage_Form.cpp'
$methods=''
foreach($name in @('DisplayProcess','DisplayError')) {
    $match=[regex]::Match($source,'(?ms)^void __fastcall TTotalForm::'+$name+'\([^\n]*\).*?^\}')
    if(!$match.Success) { throw "Missing display method: $name" }
    $methods+=$match.Value+"`r`n"
}
$temp=Join-Path ([IO.Path]::GetTempPath()) ('irocv-process-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $temp | Out-Null
$template=Read-Source 'ProcessDisplayTests.cpp.in'
[IO.File]::WriteAllText((Join-Path $temp 'ProcessDisplayTests.cpp'),$template.Replace('@@METHODS@@',$methods),[Text.Encoding]::GetEncoding(949))
Push-Location $temp
try {
    & $Compiler '-tWC' '-eProcessDisplayTests.exe' 'ProcessDisplayTests.cpp'
    if($LASTEXITCODE -ne 0) { throw 'Process display regression compile failed' }
    & .\ProcessDisplayTests.exe
    if($LASTEXITCODE -ne 0) { throw 'Process display regression failed' }
    'PASS: retired symbols absent; PLC alarm and new operation view preserved'
} finally { Pop-Location }
