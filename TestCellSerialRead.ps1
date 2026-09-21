# CELL SERIAL 두 모드 회귀 검사. 생산 메서드를 추출해 가짜 PLC/UI로 실행한다.
# 생성 파일/실행 파일은 임시 폴더에만 두며 실제 PLC/측정장비에 연결하지 않는다.
param([string]$Compiler = 'C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference = 'Stop'
$encoding = [Text.Encoding]::GetEncoding(949)
function Read-TestMethods([string]$file, [string]$className, [string[]]$names) {
    $text = [IO.File]::ReadAllText((Join-Path $PSScriptRoot $file), $encoding)
    $result = @()
    foreach($name in $names) {
        $pattern = '(?ms)^(?:void|bool|int) __fastcall ' + $className + '::' + $name + '\([^\n]*\).*?^\}'
        $match = [regex]::Match($text, $pattern)
        if(-not $match.Success) { throw "Missing production method: $className::$name" }
        $result += [regex]::Replace($match.Value, '//[^\r\n]*', '')
    }
    return $result -join "`r`n"
}
$plcMethods = Read-TestMethods 'Modplc.cpp' 'TMod_PLC' @(
    'ResetCellSerialRead','StartCellSerialRead','SetCellSerialContinuousRead',
    'BeginCellSerialRead','PrepareCellSerialRead','CompleteCellSerialChunk',
    'IsCellSerialReadComplete','IsCellSerialReadActive','GetCellSerialReadWords',
    'PLC_Recv_Interface_CellSerial','ClientSocket_PLCRead')
$formMethods = Read-TestMethods 'Stage_TrayData.cpp' 'TTotalForm' @(
    'ApplyCellSerialReadMode')
$formMethods += "`r`n" + (Read-TestMethods 'FormTotal.cpp' 'TTotalForm' @('Timer_ResultSaveTimer'))
$formMethods += "`r`n" + (Read-TestMethods 'Stage_Measurement.cpp' 'TTotalForm' @('StartResultCellSerialRead','ShowResultCellSerialError','CompleteResultCellSerialRead','ProcessResultSave','CancelResultSave','FinishMeasurement','SaveMeasurementResult','JudgeCellResult','SetRemeasureList','SetRemeasureListAfter','PrepareRemeasureItems','RemeasureExcute'))
$formMethods += "`r`n" + (Read-TestMethods 'Stage_PlcData.cpp' 'TTotalForm' @('BadInformation','WriteResultCode'))
$formMethods += "`r`n" + (Read-TestMethods 'Stage_CellDisplay.cpp' 'TTotalForm' @('UpdateCellDisplay'))
$template = [IO.File]::ReadAllText((Join-Path $PSScriptRoot 'CellSerialReadTests.cpp.in'),[Text.Encoding]::UTF8)
$testSource = $template.Replace('@@PLC_METHODS@@',$plcMethods).Replace('@@FORM_METHODS@@',$formMethods)
$testOutput = Join-Path ([IO.Path]::GetTempPath()) ('irocv-serial-tests-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testOutput | Out-Null
# 현재 생산 메서드로 만든 일회용 검사 소스(빌드 산출물).
[IO.File]::WriteAllText((Join-Path $testOutput 'CellSerialReadTests.cpp'),$testSource,$encoding)
Push-Location $testOutput
try {
    & $Compiler '-tWC' "-I$PSScriptRoot" '-eCellSerialReadTests.exe' 'CellSerialReadTests.cpp'
    if($LASTEXITCODE -ne 0) { throw "CELL SERIAL test compile failed: $LASTEXITCODE" }
    & .\CellSerialReadTests.exe
    if($LASTEXITCODE -ne 0) { throw "CELL SERIAL tests failed: $LASTEXITCODE" }
    Write-Output "Test artifacts: $testOutput"
}
finally { Pop-Location }
