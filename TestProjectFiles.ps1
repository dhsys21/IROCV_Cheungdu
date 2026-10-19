param([switch]$RequireTracked)
$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
$projectFile = @(Get-ChildItem -LiteralPath $root -Filter '*.cbproj' -File)[0]
[xml]$project = [IO.File]::ReadAllText($projectFile.FullName)
$files = @{}
$items = @($project.SelectNodes('/*[local-name()="Project"]/*[local-name()="ItemGroup"]/*[@Include]'))
function Check-File([string]$name) {
    if (!(Test-Path -LiteralPath (Join-Path $root $name) -PathType Leaf)) { throw "Missing project file: $name" }
    $files[$name.Replace('\','/')] = $true
}
foreach ($item in $items | Where-Object { $_.LocalName -in @('CppCompile','PCHCompile','None','FormResources','ResourceCompile','LibFiles') }) {
    $name = $item.GetAttribute('Include')
    Check-File $name
    foreach ($header in @($item.DependentOn)) {
        if ($header -is [string] -and $header) { Check-File $header }
    }
    if ($item.LocalName -eq 'CppCompile' -and $name -match 'Tests\.cpp$') { throw "Register standalone test as None: $name" }
    if ($item.LocalName -eq 'ResourceCompile' -and $item.Form) { throw "Resource is not a form: $name" }
}
foreach ($file in Get-ChildItem -LiteralPath $root -File | Where-Object { $_.Extension -in @('.cpp','.h') }) {
    if ($file.Name -match 'Tests\.cpp$') { continue }
    if (!$files.ContainsKey($file.Name)) { throw "Add new source/header to the project: $($file.Name)" }
}
$entryName = @($project.Project.PropertyGroup.MainSource | Where-Object { $_ })[0]
$bytes = [IO.File]::ReadAllBytes((Join-Path $root $entryName))
if (@($bytes | Where-Object { $_ -gt 127 -or $_ -eq 0 }).Count) { throw "Keep entry point ASCII-only: $entryName" }
$entry = [Text.Encoding]::ASCII.GetString($bytes)
if ($entry -match '(?m)^(<<<<<<<|=======|>>>>>>>)') { throw "Merge conflict in $entryName" }
$forms = @{}
foreach ($item in $items | Where-Object { $_.LocalName -eq 'CppCompile' -and $_.Form }) {
    $name = $item.GetAttribute('Include')
    $header = [IO.Path]::ChangeExtension($name, '.h')
    $dfm = [IO.Path]::ChangeExtension($name, '.dfm')
    Check-File $header
    Check-File $dfm
    $form = [regex]::Match([IO.File]::ReadAllText((Join-Path $root $dfm)), '(?m)^\s*(?:object|inherited)\s+(\w+)\s*:\s*(\w+)')
    if (!$form.Success -or [string]$item.Form -cne $form.Groups[1].Value) { throw "Wrong Form metadata: $name" }
    $forms[$name] = $form.Groups[1].Value
    if ($entry -notmatch ('#include\s+"' + [regex]::Escape($header) + '"') -or
        $entry -notmatch ('USEFORM\(\s*"' + [regex]::Escape($name) + '"\s*,\s*' + [regex]::Escape($form.Groups[1].Value) + '\s*\)')) {
        throw "Wrong or missing form header / USEFORM in $entryName : $name"
    }
}
foreach ($use in [regex]::Matches($entry, 'USEFORM\(\s*"([^"]+)"\s*,\s*(\w+)\s*\)')) {
    $unit = $use.Groups[1].Value
    if (!$forms.ContainsKey($unit) -or $forms[$unit] -cne $use.Groups[2].Value) { throw "Invalid USEFORM: $unit" }
}
if ($RequireTracked) {
    $tracked = @{}
    foreach ($name in @(& git -C $root -c core.quotepath=false ls-files)) { $tracked[$name] = $true }
    if ($LASTEXITCODE -ne 0) { throw 'Could not read Git index.' }
    $files[$projectFile.Name] = $true
    foreach ($name in $files.Keys) { if (!$tracked.ContainsKey($name)) { throw "Required file not added to Git: $name" } }
}
Write-Output "PASS: $($projectFile.Name) source registration and $entryName form consistency."
