# 실제 MSA 타이머/버튼/정지 함수를 추출한다. 창이나 장비 연결은 실행하지 않는다.
param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference='Stop'
$enc=[Text.Encoding]::GetEncoding(949)
# 수동 진입을 흉내 내는 테스트와 실제 버튼의 모드 계약이 일치하는지도 확인한다.
$form=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'FormTotal.cpp'),$enc)
$manual=[regex]::Match($form,'(?ms)^void __fastcall TTotalForm::btnManualClick\([^\n]*\).*?^\}').Value
foreach($rule in @('stage.arl = nLocal','bLocal = true','CmdSetManualMode(true)')) {
    if(!$manual.Contains($rule)){throw "MSA manual-mode entry changed: $rule"}
}
$methods=''
foreach($entry in @(
    @('FormMeasureInfo.cpp','TMeasureInfoForm','msaTimerTimer'),
    @('FormMeasureInfo.cpp','TMeasureInfoForm','advMSAStartClick'),
    @('FormMeasureInfo.cpp','TMeasureInfoForm','advMSAStopClick'),
    @('Stage_Measurement.cpp','TTotalForm','StopMsaMeasurement'))) {
    $source=[IO.File]::ReadAllText((Join-Path $PSScriptRoot $entry[0]),$enc)
    $match=[regex]::Match($source,'(?ms)^void __fastcall '+$entry[1]+'::'+$entry[2]+'\([^\n]*\).*?^\}')
    if(!$match.Success){throw "Missing MSA method: $entry"}
    $methods += [regex]::Replace($match.Value,'//[^\r\n]*','')+"`r`n"
}
$dir=Join-Path ([IO.Path]::GetTempPath()) ('irocv-msa-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
$template=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'MsaTests.cpp.in'),[Text.Encoding]::UTF8)
[IO.File]::WriteAllText((Join-Path $dir 'MsaTests.cpp'),$template.Replace('@@METHODS@@',$methods),$enc)
Push-Location $dir
try {
    & $Compiler '-tWC' '-eMsaTests.exe' 'MsaTests.cpp'
    if($LASTEXITCODE -ne 0){throw 'MSA tests compile failed'}
    & .\MsaTests.exe
    if($LASTEXITCODE -ne 0){throw 'MSA tests failed'}
} finally {Pop-Location}
