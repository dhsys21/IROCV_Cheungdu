param(
    [string]$Compiler = 'C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe'
)

$ErrorActionPreference = 'Stop'
if (-not (Test-Path -LiteralPath $Compiler)) {
    throw "C++Builder compiler not found: $Compiler"
}
$testOutput = Join-Path ([IO.Path]::GetTempPath()) ('irocv-sequence-tests-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testOutput | Out-Null
$executable = Join-Path $testOutput 'AutoInspectionSequenceTests.exe'
$compilerArgs = @(
    '-tWC', "-I$PSScriptRoot", '-eAutoInspectionSequenceTests.exe',
    (Join-Path $PSScriptRoot 'AutoInspectionSequence.cpp'),
    (Join-Path $PSScriptRoot 'AutoInspectionSequenceTests.cpp')
)

Push-Location $testOutput
try {
    & $Compiler @compilerArgs
    if ($LASTEXITCODE -ne 0) { throw "Test compile/link failed: $LASTEXITCODE" }
    & $executable
    if ($LASTEXITCODE -ne 0) { throw "Sequence tests failed: $LASTEXITCODE" }
    Write-Output "Test artifacts (temporary directory only): $testOutput"
}
finally {
    Pop-Location
}
