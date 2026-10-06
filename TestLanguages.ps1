param([string]$Compiler='C:\Program Files (x86)\Embarcadero\Studio\18.0\bin\bcc32.exe',[string]$BuiltExecutable)
$ErrorActionPreference='Stop'
$utf8=[Text.UTF8Encoding]::new($false,$true)
$source=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'LanguageSupport.cpp'),$utf8)
$methods=@()
foreach($name in @('ReadLanguage','GetLangStr','Translate')){
 $m=[regex]::Match($source,'(?ms)^(?:void|UnicodeString) __fastcall TForm_Language::'+$name+'\(.*?^\}')
 if(!$m.Success){throw "Missing language method $name"};$methods+=$m.Value
}
$dir=Join-Path ([IO.Path]::GetTempPath()) ('language-tests-'+[Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $dir | Out-Null
$template=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'LanguageTests.cpp.in'),$utf8)
[IO.File]::WriteAllText((Join-Path $dir 'LanguageTests.cpp'),$template.Replace('@@METHODS@@',($methods -join "`r`n")),$utf8)
foreach($name in @('Lang_En.ini','Lang_Ko.ini','Lang_Zh.ini','Languages.rc')){Copy-Item -LiteralPath (Join-Path $PSScriptRoot $name) -Destination $dir}
Push-Location $dir
try {
 & (Join-Path (Split-Path $Compiler) 'brcc32.exe') 'Languages.rc'
 if($LASTEXITCODE -ne 0){throw 'Language resource compile failed'}
 & $Compiler '-tWM' '-tWR' '-tWC' '-DUNICODE;_UNICODE' '-eLanguageTests.exe' 'LanguageTests.cpp' 'Languages.res' 'rtl.lib'
 if($LASTEXITCODE -ne 0){throw 'Language test compile failed'}
 & .\LanguageTests.exe
 if($LASTEXITCODE -ne 0){throw 'Language resource test failed'}
 $dictionaries=@()
 foreach($name in @('Lang_En.ini','Lang_Ko.ini','Lang_Zh.ini')){
  $dict=@{}
  foreach($line in [IO.File]::ReadAllLines((Join-Path $PSScriptRoot $name),$utf8)){
   if($line.StartsWith('[')){continue}
   $index=$line.IndexOf('=');if($index -le 0){throw "Malformed resource: $name"}
   $key=$line.Substring(0,$index)
   if($dict.ContainsKey($key)){throw "Duplicate resource key $name : $key"}
   $dict[$key]=$line.Substring($index+1)
  }
  $dictionaries+=,$dict
 }
 foreach($dict in $dictionaries){foreach($key in $dictionaries[0].Keys){if(!$dict.ContainsKey($key) -or !$dict[$key]){throw "Missing language value $key"}}}
 $form=[IO.File]::ReadAllText((Join-Path $PSScriptRoot 'FormLanguage.cpp'))
 if($form -match 'VLE_|TValueListEditor'){throw 'Old editor-based translation remains'}
 'PASS: all three UTF-8 dictionaries share keys; no obsolete translation tables'
 if($BuiltExecutable){
  # LOAD_LIBRARY_AS_DATAFILE: read resources without executing the production EXE.
  if(!('PrechargerLanguageResources' -as [type])){
   Add-Type @'
using System;
using System.Runtime.InteropServices;
public static class PrechargerLanguageResources {
 [DllImport("kernel32.dll",CharSet=CharSet.Unicode,SetLastError=true)] public static extern IntPtr LoadLibraryExW(string path,IntPtr file,uint flags);
 [DllImport("kernel32.dll",CharSet=CharSet.Unicode,SetLastError=true)] public static extern IntPtr FindResourceW(IntPtr module,string name,IntPtr type);
 [DllImport("kernel32.dll")] public static extern uint SizeofResource(IntPtr module,IntPtr resource);
 [DllImport("kernel32.dll")] public static extern IntPtr LoadResource(IntPtr module,IntPtr resource);
 [DllImport("kernel32.dll")] public static extern IntPtr LockResource(IntPtr resource);
 [DllImport("kernel32.dll")] public static extern bool FreeLibrary(IntPtr module);
}
'@
  }
  $module=[PrechargerLanguageResources]::LoadLibraryExW($BuiltExecutable,[IntPtr]::Zero,2)
  if($module -eq [IntPtr]::Zero){throw 'Cannot read built EXE resources'}
  try {
   foreach($pair in @(@('EN_DATA','Lang_En.ini'),@('KO_DATA','Lang_Ko.ini'),@('ZH_DATA','Lang_Zh.ini'))){
    $resource=[PrechargerLanguageResources]::FindResourceW($module,$pair[0],[IntPtr]10)
    if($resource -eq [IntPtr]::Zero){throw "Language not embedded in production EXE: $($pair[0])"}
    $bytes=[byte[]]::new([PrechargerLanguageResources]::SizeofResource($module,$resource))
    $pointer=[PrechargerLanguageResources]::LockResource([PrechargerLanguageResources]::LoadResource($module,$resource))
    [Runtime.InteropServices.Marshal]::Copy($pointer,$bytes,0,$bytes.Length)
    if($utf8.GetString($bytes) -cne [IO.File]::ReadAllText((Join-Path $PSScriptRoot $pair[1]),$utf8)){throw 'Embedded dictionary differs from source'}
   }
   'PASS: production EXE embeds all three exact dictionaries (EXE was not executed)'
  } finally {[void][PrechargerLanguageResources]::FreeLibrary($module)}
 }
 "Test artifacts: $dir"
} finally {Pop-Location}
