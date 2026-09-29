# Offline display-state and layout contract tests. Never launches the application.
param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe')
$ErrorActionPreference='Stop'
function Read-Source([string]$name){
 $bytes=[IO.File]::ReadAllBytes((Join-Path $PSScriptRoot $name))
 try{return [Text.UTF8Encoding]::new($false,$true).GetString($bytes).TrimStart([char]0xFEFF)}catch{return [Text.Encoding]::GetEncoding(949).GetString($bytes)}
}
$dfm=Read-Source 'RVMO_main.dfm'
function Dfm-Block([string]$name){
 $m=[regex]::Match($dfm,'(?ms)^  object '+$name+':.*?^  end')
 if(!$m.Success){throw "Missing DFM component: $name"};return $m.Value
}
function Bounds([string]$block){
 $values=@{};foreach($prop in @('Left','Top','Width','Height')){
  $values[$prop]=[int][regex]::Match($block,'(?m)^    '+$prop+' = (\d+)').Groups[1].Value
 };return $values
}
if($dfm -match 'object advPLCInterfaceShow:'){throw 'Standalone PLC button remains'}
$init=Bounds (Dfm-Block 'btnInit');$log=Bounds (Dfm-Block 'btnViewLog');$data=Bounds (Dfm-Block 'btnViewData')
$plc=Bounds (Dfm-Block 'AdvSmoothPanel_PLC');$equipment=Bounds (Dfm-Block 'AdvSmoothPanel_IROCV')
if($init.Left+$init.Width -ge $log.Left -or $log.Left -ne $data.Left -or $log.Top+$log.Height -gt $data.Top){throw 'INIT / LOG / DATA layout'}
if($plc.Left -ne $equipment.Left -or $plc.Top+$plc.Height -gt $equipment.Top){throw 'Connection panels must be vertically stacked'}
if((Dfm-Block 'AdvSmoothPanel_PLC') -notmatch 'OnClick = advPLCInterfaceShowClick'){throw 'PLC panel must use the original PLC interface handler'}
$view=Read-Source 'Stage_OperationView.cpp'
if($view -match '(?:SetValue|SendText|RunAutoStep|WriteIROCVValue|InitializePlcData)\s*\('){throw 'Display module may not control production'}
foreach($token in @('owner->pBase->Visible = false','owner->flowChart->Visible = false','owner->StatusImage->Visible = false','while(logMemo->Lines->Count >= 500)','if(i < 6 && !valid) continue')){
 if(!$view.Contains($token)){throw "Missing display contract: $token"}
}
$form=Read-Source 'FormTotal.cpp'
if(!$form.Contains('operationView = NULL;') -or !$form.Contains('CreateOperationView();')){throw 'Stage view lifetime wiring'}
if(!(Read-Source 'Stage_Form.cpp').Contains('if(operationView && grp->Visible) grp->BringToFront();')){throw 'Alarm groups must remain above the dynamic log area'}
[xml]$project=Read-Source 'IROCV.cbproj'
if(@($project.Project.ItemGroup.CppCompile.Include | Where-Object {$_ -eq 'Stage_OperationView.cpp'}).Count -ne 1){throw 'Display module project registration'}
$dir=Join-Path ([IO.Path]::GetTempPath()) ('irocv-newgui-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
Push-Location $dir
try{
 & $Compiler '-tWC' "-I$PSScriptRoot" '-eOperationViewStateTests.exe' (Join-Path $PSScriptRoot 'OperationViewStateTests.cpp')
 if($LASTEXITCODE -ne 0){throw 'newGui test compile failed'}
 & .\OperationViewStateTests.exe
 if($LASTEXITCODE -ne 0){throw 'newGui state tests failed'}
 'PASS: header order, stacked connections, original PLC click, bounded logs, no production-control calls'
 "Test artifacts: $dir"
}finally{Pop-Location}
