# Verify local encodings and UTF-8 Git index without modifying files or contacting equipment.
param([string]$Git = 'git', [switch]$RequireCRLF)
$ErrorActionPreference = 'Stop'
$root = $PSScriptRoot
$gitPath = (Get-Command $Git -ErrorAction Stop).Source
$version = & $gitPath --version
if ($LASTEXITCODE -ne 0 -or $version -notmatch '(\d+\.\d+\.\d+)') { throw 'Cannot determine Git version.' }
if ([version]$Matches[1] -lt [version]'2.18.0') { throw 'Git 2.18 or newer is required.' }
$utf8 = [Text.UTF8Encoding]::new($false, $true)
$cp949 = [Text.Encoding]::GetEncoding(949, [Text.EncoderFallback]::ExceptionFallback, [Text.DecoderFallback]::ExceptionFallback)
function Read-IndexBytes([string]$name) {
    # Read stdout as bytes; PowerShell text pipes can corrupt legacy encodings.
    if ($name.Contains('"')) { throw "Unsupported filename: $name" }
    $start = New-Object Diagnostics.ProcessStartInfo
    $start.FileName = $gitPath
    $start.WorkingDirectory = $root
    $start.Arguments = 'cat-file blob ":' + $name + '"'
    $start.UseShellExecute = $false
    $start.CreateNoWindow = $true
    $start.RedirectStandardOutput = $true
    $start.RedirectStandardError = $true
    $process = [Diagnostics.Process]::Start($start)
    $memory = New-Object IO.MemoryStream
    try {
        $process.StandardOutput.BaseStream.CopyTo($memory)
        $errorText = $process.StandardError.ReadToEnd()
        $process.WaitForExit()
        if ($process.ExitCode -ne 0) { throw "Cannot read index for ${name}: $errorText" }
        return ,$memory.ToArray()
    } finally { $memory.Dispose(); $process.Dispose() }
}
$names = @(& $gitPath -C $root ls-files -- '*.cpp' '*.h' '*.dfm')
if ($LASTEXITCODE -ne 0 -or !$names.Count) { throw 'Cannot list tracked sources.' }
$legacyCount = 0
$utf8Count = 0
foreach ($name in $names) {
    $attribute = & $gitPath -C $root check-attr working-tree-encoding -- $name
    if ($LASTEXITCODE -ne 0) { throw "Cannot read attributes: $name" }
    $bytes = [IO.File]::ReadAllBytes((Join-Path $root $name))
    if ($attribute -match ': working-tree-encoding: CP949$') {
        $text = $cp949.GetString($bytes)
        if ([Convert]::ToBase64String($cp949.GetBytes($text)) -cne [Convert]::ToBase64String($bytes)) {
            throw "CP949 round-trip mismatch: $name"
        }
        ++$legacyCount
    } elseif ($attribute -match ': working-tree-encoding: unset$' -and
              $name -in @('ChannelLayout.h', 'FormCalibration.cpp')) {
        $text = $utf8.GetString($bytes)
        ++$utf8Count
    } else { throw "Unexpected encoding attribute: $attribute" }
    if ($RequireCRLF -and $text -match '(?<!\r)\n|\r(?!\n)') { throw "Expected CRLF locally: $name" }
    $stored = $utf8.GetString((Read-IndexBytes $name))
    if ($stored -cne $text.Replace("`r`n", "`n")) {
        throw "Index differs from local text: $name. Stage intended edits; initial migration requires git add --renormalize."
    }
}
Write-Output "PASS: $version; $legacyCount CP949 and $utf8Count UTF-8 local sources; all $($names.Count) index blobs are matching UTF-8/LF."
