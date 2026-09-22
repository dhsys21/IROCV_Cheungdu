# 실제 오류창 이벤트를 추출해 선택 전달/지연 닫기를 검사한다. PLC/화면은 실행하지 않는다.
param([string]$Compiler = 'C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference = 'Stop'
$encoding = [Text.Encoding]::GetEncoding(949)
$methods = ''
$targets = @(
    @('FormError.cpp','TForm_Error',@('Button_OKClick','btnTrayOutClick','btnRestartClick','timerErrorOffTimer')),
    @('FormNgCountError.cpp','TForm_NgCountError',@('btnTrayOutClick','btnOKClick','timerErrorOffTimer')),
    @('FormCellIdError.cpp','TForm_CellIdError',@('btnSAVEClick','btnCANCELClick','timerErrorOffTimer'))
)
foreach ($target in $targets) {
    $source = [IO.File]::ReadAllText((Join-Path $PSScriptRoot $target[0]),$encoding)
    foreach ($name in $target[2]) {
        $pattern = '(?ms)^void __fastcall ' + $target[1] + '::' + $name + '\([^\n]*\).*?^\}'
        $match = [regex]::Match($source,$pattern)
        if (-not $match.Success) { throw "Missing event: $name" }
        $methods += [regex]::Replace($match.Value,'//[^\r\n]*','') + "`r`n"
    }
}
$template = [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'ErrorDialogTests.cpp.in'),[Text.Encoding]::UTF8)
$output = Join-Path ([IO.Path]::GetTempPath()) ('irocv-dialog-tests-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $output | Out-Null
[IO.File]::WriteAllText((Join-Path $output 'ErrorDialogTests.cpp'),$template.Replace('@@METHODS@@',$methods),$encoding)
Push-Location $output
try {
    & $Compiler '-tWC' '-eErrorDialogTests.exe' 'ErrorDialogTests.cpp'
    if ($LASTEXITCODE -ne 0) { throw 'Error-dialog test compile failed' }
    & .\ErrorDialogTests.exe
    if ($LASTEXITCODE -ne 0) { throw 'Error-dialog tests failed' }
} finally { Pop-Location }
