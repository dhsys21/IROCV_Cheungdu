# Mechanical resource generation. Edit LanguageCatalog.tsv, then run this script.
# The optional legacy DFM imports the previous translations once during migration.
param([string]$LegacyDfm,[switch]$Inventory)
$ErrorActionPreference='Stop'
$utf8=[Text.UTF8Encoding]::new($false)
function Decode-Dfm([string]$value) {
 $result=''
 foreach($token in [regex]::Matches($value,"'((?:[^']|'')*)'|#(\d+)")) {
  if($token.Value.StartsWith('#')) {$result += [char][int]$token.Groups[2].Value}
  else {$result += $token.Groups[1].Value.Replace("''", "'")}
 }
 return $result
}
$languages=@{EN=[ordered]@{};KO=[ordered]@{};ZH=[ordered]@{}}
$captionOverrides=@()
$catalogKeys=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
if($LegacyDfm){
 $legacy=[IO.File]::ReadAllText($LegacyDfm)
 foreach($pair in @(@('EN','ENGLISH'),@('KO','KOREAN'),@('ZH','CHINESE'))){
  $body=[regex]::Match($legacy,'(?ms)object VLE_'+$pair[1]+':.*?Strings.Strings = \((.*?)\)\s*TabOrder').Groups[1].Value
  $body=$body -replace "' \+\s*'",''
  foreach($line in ($body -split '\r?\n')){
   $entry=Decode-Dfm $line
   $equals=$entry.IndexOf('=')
   if($equals -gt 0){$languages[$pair[0]][$entry.Substring(0,$equals)]=$entry.Substring($equals+1).Replace('\r\n','\n')}
  }
 }
} else {
 foreach($language in @('EN','KO','ZH')){
  $file=Join-Path $PSScriptRoot ('Lang_'+@{EN='En';KO='Ko';ZH='Zh'}[$language]+'.ini')
  foreach($line in [IO.File]::ReadAllLines($file,$utf8)){
   if($line -match '^(?!UI_|TEXT_|\[)([^=]+)=(.*)$'){$languages[$language][$Matches[1]]=$Matches[2]}
  }
 }
}
foreach($line in [IO.File]::ReadAllLines((Join-Path $PSScriptRoot 'LanguageCatalog.tsv'),$utf8)){
 if(!$line -or $line.StartsWith('#')){continue}
 $fields=$line.Split('|')
 if($fields.Count -ne 4){throw "Expected key / EN / KO / ZH: $line"}
 if(!$catalogKeys.Add($fields[0])){throw "Duplicate catalog key: $($fields[0])"}
 # Per-control captions override inferred DFM translations without changing
 # other controls that share the same English text (for example CONFIG SET).
 if($fields[0].StartsWith('UI_')){$captionOverrides+=,$fields;continue}
 for($i=0;$i -lt 3;++$i){$languages[@('EN','KO','ZH')[$i]][$fields[0]]=$fields[$i+1]}
}
foreach($language in @('KO','ZH')){
 foreach($key in @($languages[$language].Keys)){
  if(!$languages.EN.Contains($key)){$languages[$language].Remove($key)}
 }
 foreach($key in $languages.EN.Keys){
  if(!$languages[$language].Contains($key) -or !$languages[$language][$key]){$languages[$language][$key]=$languages.EN[$key]}
 }
}
$lookup=[Collections.Generic.Dictionary[string,string]]::new([StringComparer]::Ordinal)
foreach($key in $languages.EN.Keys){$lookup[$languages.EN[$key]]=$key}
$missing=[Collections.Generic.HashSet[string]]::new([StringComparer]::Ordinal)
foreach($file in @('RVMO_main.dfm','FormTotal.dfm','FormMeasureInfo.dfm','FormCalibration.dfm','FormPLCInterface.dfm','FormError.dfm','FormCellIdError.dfm','FormNgCountError.dfm','FormRemeasure.dfm')){
 $dfm=[IO.File]::ReadAllLines((Join-Path $PSScriptRoot $file))
 $stack=[Collections.Generic.List[object]]::new()
 $class='';$columnIndex=-1
 for($i=0;$i -lt $dfm.Length;++$i){
  $line=$dfm[$i]
  if($line -match '^(\s*)object (\w+): (\w+)'){
   if(!$class){$class=$Matches[3].ToUpperInvariant()}
   $stack.Add(@{Indent=$Matches[1].Length;Name=$Matches[2]})
  } elseif($line -match '^(\s*)end\s*$'){
   if($stack.Count -and $stack[$stack.Count-1].Indent -eq $Matches[1].Length){$stack.RemoveAt($stack.Count-1)}
  } elseif($line -match '^\s*Columns = <'){
   $columnIndex=0
  } elseif($line -match '^\s*end>'){
   $columnIndex=-1
  } elseif($stack.Count -and $line -match '^(\s*)Caption(?:\.Text)? = (.*)$'){
   $expression=$Matches[2]
   while($expression.TrimEnd().EndsWith('+')){++$i;$expression+=$dfm[$i].Trim()}
   $caption=Decode-Dfm $expression
   if($lookup.ContainsKey($caption)){
    $key='UI_'+$class+'_'+$stack[$stack.Count-1].Name.ToUpperInvariant()
    # Root window caption/version is not an operator label.
    if($stack.Count -eq 1){$key='UI_'+$class+'_CAPTION'}
    if($columnIndex -ge 0){$key+='_COL_'+$columnIndex;++$columnIndex}
    $source=$lookup[$caption]
    foreach($language in @('EN','KO','ZH')){$languages[$language][$key]=$languages[$language][$source]}
   } elseif($caption -match '[A-Za-z]{3}' -and $caption -notmatch 'BT[12]:|STAGE|Ver\.|^T?Form|^Panel|^Label|^clr|^VOLT$|^CURR$|^IR$|^OCV$|^PC:|^PLC:|CELL SERIAL:|^AMS:|^Elapsed|^Current operation|^Waiting for connections|^PC SETTING|PreCharger is under|Before :|New :|^status$|^14\?|^BATCH CHANGED'){
    [void]$missing.Add($caption)
   }
  }
 }
}
if($Inventory){$missing | Sort-Object;exit}
foreach($fields in $captionOverrides){
 for($i=0;$i -lt 3;++$i){$languages[@('EN','KO','ZH')[$i]][$fields[0]]=$fields[$i+1]}
}
foreach($language in @('EN','KO','ZH')){
 $suffix=@{EN='En';KO='Ko';ZH='Zh'}[$language]
 $lines=@('['+$language+']')+@($languages[$language].GetEnumerator() | ForEach-Object {$_.Key+'='+$_.Value})
 [IO.File]::WriteAllLines((Join-Path $PSScriptRoot ('Lang_'+$suffix+'.ini')),$lines,$utf8)
 "$language : $($languages[$language].Count) language keys"
}
if($missing.Count){'Unmapped legacy/diagnostic captions:';$missing | Sort-Object}
