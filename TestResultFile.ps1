# 실제 결과파일 작성/부분 쓰기/재시도/교체 실패 검증. 생산 경로 대신 새 임시 폴더만 사용.
param([string]$Bds = 'C:\Program Files (x86)\Embarcadero\Studio\18.0')
$ErrorActionPreference = 'Stop'
$source = [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'Stage_log.cpp'),[Text.Encoding]::GetEncoding(949))
$method = [regex]::Match($source,'(?ms)^bool __fastcall TTotalForm::WriteResultFile\(\).*?^\}').Value
if(-not $method) { throw 'WriteResultFile production method not found' }
$method = [regex]::Replace($method,'//[^\r\n]*','')
$template = [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'ResultFileTests.cpp.in'),[Text.Encoding]::UTF8)
$output = Join-Path ([IO.Path]::GetTempPath()) ('irocv-file-tests-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $output | Out-Null
[IO.File]::WriteAllText((Join-Path $output 'ResultFileTests.cpp'),$template.Replace('@@WRITE_RESULT_FILE@@',$method),[Text.Encoding]::GetEncoding(949))
Push-Location $output
try {
    & "$Bds\bin\bcc32.exe" '-tWC' "-I$PSScriptRoot;$Bds\include;$Bds\include\windows\rtl" "-L$Bds\lib\win32\release" 'ResultFileTests.cpp' 'rtl.lib'
    if($LASTEXITCODE -ne 0) { throw 'Result file test compile failed' }
    & .\ResultFileTests.exe
    if($LASTEXITCODE -ne 0) { throw 'Result file tests failed' }
    Write-Output "Test artifacts: $output"
} finally { Pop-Location }
