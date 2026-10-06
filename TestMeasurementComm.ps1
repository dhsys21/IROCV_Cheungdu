param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference='Stop'
$dir=Join-Path ([IO.Path]::GetTempPath()) ('irocv-measurement-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
Copy-Item -LiteralPath (Join-Path $PSScriptRoot 'MeasurementCommTests.cpp.in') -Destination (Join-Path $dir 'MeasurementCommTests.cpp')
Push-Location $dir
try {
 & $Compiler '-tWC' "-I$PSScriptRoot" '-eMeasurementCommTests.exe' 'MeasurementCommTests.cpp'
 if($LASTEXITCODE -ne 0){throw 'Measurement communication test compile failed'}
 & .\MeasurementCommTests.exe
 if($LASTEXITCODE -ne 0){throw 'Measurement communication test failed'}
 $comm=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'Stage_comm.cpp'))
 if($comm -notmatch 'measurementClock.Start\(receivedTick\)' -or $comm -notmatch 'measurementClock.Stop\(receivedTick\)' -or $comm -notmatch 'ParseEquipmentMessage\(AnsiString\(frame.c_str\(\)\), parameter\)' -or $comm -notmatch 'AppendEquipmentFrames\(remainMsg,'){throw 'BCC-validated socket receipt hooks missing'}
 $view=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'Stage_OperationView.cpp'))
 if($view.Contains('Inspection warning / error')){throw 'Retired warning display remains'}
 'PASS: actual AMS/AMF receive hooks and display-only clock integration'
} finally {Pop-Location}
