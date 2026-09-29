# 실제 패널 생성 메서드를 VCL 없는 테스트로 실행한다. 장비/프로그램 창을 열지 않는다.
param([string]$Compiler = 'C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference = 'Stop'
function Read-Source([string]$name) {
    $bytes=[IO.File]::ReadAllBytes((Join-Path $PSScriptRoot $name))
    # IDE가 UTF-8 BOM을 붙여 저장해도 CP949 테스트 소스 앞에 '?'가 생기지 않도록 제거한다.
    try {return [Text.UTF8Encoding]::new($false,$true).GetString($bytes).TrimStart([char]0xFEFF)}
    catch {return [Text.Encoding]::GetEncoding(949).GetString($bytes)}
}
function Get-Methods([string]$name,[string]$className,[string[]]$methods) {
    $text=Read-Source $name
    foreach($method in $methods){
        $m=[regex]::Match($text,'(?ms)void __fastcall '+$className+'::'+$method+'\([^\n]*\)\r?\n\{.*?^\}')
        if(-not $m.Success){throw "Missing $className::$method"}
        # 배치 테스트에서는 VCL 이벤트 연결만 제외한다. 이벤트 형식은 전체 빌드에서 확인한다.
        [regex]::Replace($m.Value,'(?m)^.*->OnMouse(?:Enter|Leave).*\r?\n','')
    }
}
$isIROCV=Test-Path (Join-Path $PSScriptRoot 'IROCV.cbproj')
$methods=@(Get-Methods 'Stage_CellDisplay.cpp' 'TTotalForm' @('MakePanel'))
$methods+=@(Get-Methods 'FormMeasureInfo.cpp' 'TMeasureInfoForm' @('MakePanel','MakeUIPanel'))
$methods+=@(Get-Methods 'FormRemeasure.cpp' 'TRemeasureForm' @('MakePanel','MakeUIPanel'))
if($isIROCV){$methods+=@(Get-Methods 'FormCalibration.cpp' 'TCaliForm' @('MakePanel'))}
$template=Read-Source 'ChannelLayoutTests.cpp.in'
$source=$template.Replace('@@METHODS@@',($methods -join "`r`n"))
$site=Read-Source 'SiteConfig.h'
$testOutput=Join-Path ([IO.Path]::GetTempPath()) ('channel-layout-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $testOutput | Out-Null
$encoding=[Text.Encoding]::GetEncoding(949)
[IO.File]::WriteAllText((Join-Path $testOutput 'ChannelLayout.h'),(Read-Source 'ChannelLayout.h'),$encoding)
[IO.File]::WriteAllText((Join-Path $testOutput 'ChannelLayoutTests.cpp'),$source,$encoding)
$corners=@('CHANNEL_BOTTOM_RIGHT','CHANNEL_TOP_RIGHT','CHANNEL_BOTTOM_LEFT','CHANNEL_TOP_LEFT')
$directions=@('CHANNEL_HORIZONTAL','CHANNEL_VERTICAL')
Push-Location $testOutput
try {
    foreach($corner in $corners){foreach($direction in $directions){
        $config=$site -replace 'CHANNEL_START_CORNER = \w+;',("CHANNEL_START_CORNER = "+$corner+";")
        $config=$config -replace 'CHANNEL_FILL_DIRECTION = \w+;',("CHANNEL_FILL_DIRECTION = "+$direction+";")
        [IO.File]::WriteAllText((Join-Path $testOutput 'SiteConfig.h'),$config,$encoding)
        $compilerArgs=@('-tWC','-eChannelLayoutTests.exe')
        if($isIROCV){$compilerArgs+='-DTEST_IROCV'}
        $compilerArgs+='ChannelLayoutTests.cpp'
        $output=& $Compiler @compilerArgs 2>&1
        if($LASTEXITCODE -ne 0){$output;throw 'Panel test build failed'}
        & .\ChannelLayoutTests.exe
        if($LASTEXITCODE -ne 0){throw 'Panel layout tests failed'}
    }}
    Write-Output "Test artifacts: $testOutput"
}
finally {Pop-Location}
