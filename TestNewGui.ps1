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
foreach($token in @('while(logMemo->Lines->Count >= 500)','if(i < 6 && !valid) continue')){
 if(!$view.Contains($token)){throw "Missing display contract: $token"}
}
if($view -match 'new T(?:Label|Panel|GroupBox|Memo|CheckBox|Button)\s*\(' -or $view -match '->SetBounds\s*\('){throw 'Operation controls/bounds must come from DFM, not runtime construction'}
$totalDfm=Read-Source 'FormTotal.dfm'
$header=Read-Source 'FormTotal.h'
function Read-DfmNodes([string]$text){
 $nodes=@{};$stack=[Collections.Generic.List[object]]::new()
 foreach($line in ($text -split '\r?\n')){
  if($line -match '^( *)object (\w+): (\w+)'){
   $depth=$Matches[1].Length;$name=$Matches[2];$type=$Matches[3]
   while($stack.Count -gt 0 -and $stack[$stack.Count-1].Depth -ge $depth){$stack.RemoveAt($stack.Count-1)}
   if($nodes.ContainsKey($name)){throw "Duplicate DFM component $name"}
   $parent=if($stack.Count){$stack[$stack.Count-1].Name}else{''}
   $node=@{Name=$name;Type=$type;Depth=$depth;Parent=$parent;Props=@{}}
   $nodes[$name]=$node;$stack.Add($node)
  }elseif($line -match '^( *)([\w.]+) = (.*)$' -and $stack.Count){
   $node=$stack[$stack.Count-1]
   if($Matches[1].Length -eq $node.Depth+2){$node.Props[$Matches[2]]=$Matches[3]}
  }
 }
 return $nodes
}
$nodes=Read-DfmNodes $totalDfm
$originalText=(& git show '592f738:FormTotal.dfm') -join "`n"
$original=Read-DfmNodes $originalText
function Image-Payloads([string]$text){
 return @([regex]::Matches($text,'(?s)\w+\.Data = \{([^}]+)\}') | ForEach-Object {$_.Groups[1].Value -replace '\s',''} | Sort-Object)
}
if(Compare-Object (Image-Payloads $originalText) (Image-Payloads $totalDfm)){throw 'Legacy image data changed during DFM migration'}
foreach($name in $original.Keys){
 if(!$nodes.ContainsKey($name) -or $nodes[$name].Type -ne $original[$name].Type){throw "Lost legacy component $name"}
 foreach($prop in $original[$name].Props.Keys | Where-Object {$_ -like 'On*'}){
  if($nodes[$name].Props[$prop] -ne $original[$name].Props[$prop]){throw "Changed legacy event $name.$prop"}
 }
}
foreach($name in $nodes.Keys | Where-Object {!$original.ContainsKey($_)}){
 if($header -notmatch ('\b'+$nodes[$name].Type+'\s*\*\s*'+$name+'\s*;')){throw "Missing IDE field $name"}
}
foreach($name in @('grpOperationProcess','grpOperationCurrent','grpOperationLog','pnlOperationPcMode','pnlOperationPlcMode','localTest','localCali','chkCycle','chkBypass')){
 if($nodes[$name].Parent -ne 'pback'){throw "Incorrect design parent: $name"}
}
foreach($pair in @(@('btnConfig','btnReset'),@('btnManual','btnTrayOut'),@('btnAuto','btnRemeasureInfo'))){
 $top=$nodes[$pair[0]].Props;$bottom=$nodes[$pair[1]].Props
 if($top.Left -ne $bottom.Left -or $top.Width -ne $bottom.Width -or [int]$bottom.Top -lt [int]$top.Top+[int]$top.Height){throw "Button column mismatch: $($pair[1])"}
}
foreach($name in @('pnlOperationPcMode','pnlOperationPlcMode')){
 if($nodes[$name].Type -ne 'TPanel' -or [int]$nodes[$name].Props.Left+[int]$nodes[$name].Props.Width -gt [int]$nodes.btnReset.Props.Left){throw 'Mode panels must be left of action buttons'}
}
if($nodes.ContainsKey('btnOperationCopy') -or $nodes.ContainsKey('lblOperationMode')){throw 'Old combined mode label / COPY button remains'}
if($nodes.btnOperationLogFile.Props.Caption -ne "'LOG FILE'" -or !$view.Contains('ShellExecuteW') -or !$view.Contains('FindNotepadPlusPlus()')){throw 'Notepad++ log file action missing'}
if(!$view.Contains('FILE_APPEND_DATA') -or !$view.Contains('FILE_SHARE_READ | FILE_SHARE_WRITE') -or !$view.Contains('_OPERATION_')){throw 'Persistent readable operation log missing'}
if(!$view.Contains('cycleClock.Start(GetTickCount())') -or !$view.Contains('cycleClock.Elapsed(GetTickCount())') -or $view.Contains('waitStarted')){throw 'Elapsed must time tray cycle, not each state'}
if(!$view.Contains('tiles[i]->Color = i == active ? clLime : clSilver;')){throw 'Active-only process colors'}
if(!$view.Contains('pcModePanel->Color = local ? clRed : clLime;') -or !$view.Contains('valid && Mod_PLC->IsPlcAutoMode() ? clLime : clRed')){throw 'AUTO/non-AUTO colors'}
if(!$view.Contains('currentDetail->Caption = OperatorSignalText(detail)')){throw 'Operator-friendly signal text missing'}
foreach($token in @('AnsiString phase = TOperationViewState::TileName(processTile);',
 'AnsiString key = "[" + phase + "] " + source + " " + message.Trim();',
 'UnicodeString line = Now().FormatString("hh:nn:ss.zzz ") + key;',
 'WriteOperationLog(line)', 'logMemo->Lines->Add(line)',
 'view->commandLogTile = previous;', 'progress.SignalTile(')){
 if(!$view.Contains($token)){throw "Missing process-tagged log contract: $token"}
}
$autoSource=Read-Source 'Stage_AutoInspection.cpp'
if(!$view.Contains('if(TOperationViewState::IsInternalStepTrace(type.c_str(), message.c_str())) return;')){
 throw 'Early internal step traces must stay out of the operator timeline'
}
if(!$view.Contains('Append(i < 6 ? "PLC_RX" : "PC_SET", detail, current);') -or !$view.Contains('(event: ')){
 throw 'Late signal samples must preserve current heading and event context'
}
$commandObserver=[regex]::Match($view,'(?s)void TOperationView::Command\(.*?void TOperationView::FinishCycle').Value
if($commandObserver.Contains('PROBE CLOSED and TRAY IN confirmed')){throw 'DOWN OK must not be logged after measurement command completes'}
if($autoSource -notmatch 'RunAutoInspectionCommand\([^\r\n]+\)\s*\{\s*TOperationCommandLogScope operationLogScope\(this, command\);'){
 throw 'Command phase scope must begin before command-side logs'
}
foreach($name in @('flowChart','GroupBox7','pBase','Panel1','GrpMain','GrpLocal','Panel_State','Panel3','pConInfo','pnlTrayIn','pnlTrayOut','pnlProbeOpen','pnlProbeClose')){
 if($nodes[$name].Parent -ne 'pnlLegacyDisplay'){throw "Legacy control overlaps designer: $name"}
}
if($nodes.pnlLegacyDisplay.Props.Visible -ne 'False' -or [int]$nodes.pnlLegacyDisplay.Props.Left -lt [int]$nodes.TotalForm.Props.ClientWidth){throw 'Legacy storage must be hidden and outside the live canvas'}
foreach($node in $nodes.Values | Where-Object {$_.Parent -eq 'TotalForm' -and $_.Type -notmatch 'Timer|Socket' -and $_.Name -ne 'pback'}){
 if([int]$node.Props.Left -lt 630){throw "Auxiliary control covers designer canvas: $($node.Name)"}
}
$previousBottom=0
foreach($name in @('Panel16','grpOperationProcess','grpOperationCurrent','grpOperationLog')){
 $props=$nodes[$name].Props
 if([int]$props.Top -lt $previousBottom -or [int]$props.Left+[int]$props.Width -gt [int]$nodes.pback.Props.Width){throw "Design bounds overlap / overflow: $name"}
 $previousBottom=[int]$props.Top+[int]$props.Height
}
$tileNames=@('Ready','TrayIn','TrayId','CellData','CloseRequest','CloseConfirmed','Measure','FileSave','ResultTransmit','Complete','OpenRequest','OpenConfirmed','OutRequest','OutConfirmed')
foreach($suffix in $tileNames){
 if($nodes['pOp'+$suffix].Parent -ne 'grpOperationProcess' -or $nodes['lblOp'+$suffix].Parent -ne 'pOp'+$suffix){throw "Design tile hierarchy: $suffix"}
 if(!$view.Contains('owner->pOp'+$suffix) -or !$view.Contains('owner->lblOp'+$suffix)){throw "Display binding missing: $suffix"}
 if($nodes['lblOp'+$suffix].Props.Caption -match '#13|#10|WAIT|DONE|SET'){throw "Obsolete tile state suffix: $suffix"}
}
foreach($node in $nodes.Values | Where-Object {$_.Props.ContainsKey('TabOrder')}){
 $siblings=@($nodes.Values | Where-Object {$_.Parent -eq $node.Parent -and $_.Props.TabOrder -eq $node.Props.TabOrder})
 if($siblings.Count -ne 1){throw "Duplicate sibling TabOrder: $($node.Name)"}
}
'PASS: design-time controls, 14 tile bindings, legacy event preservation, bounds and tab order'
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
