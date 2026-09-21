# 소스 구조 검사: 프로그램 실행이나 PLC/장비 연결 없이 DFM 이벤트 연결을 확인한다.
param()
$ErrorActionPreference = 'Stop'
$sourceEncoding = [Text.Encoding]::GetEncoding(949)
[xml]$project = Get-Content -LiteralPath (Join-Path $PSScriptRoot 'IROCV.cbproj') -Raw
$sourceNames = @($project.Project.ItemGroup.CppCompile.Include | Where-Object { $_ })
$sourceText = ''
foreach ($name in $sourceNames) {
    $path = Join-Path $PSScriptRoot $name
    if (-not (Test-Path -LiteralPath $path)) { throw "Missing project source: $name" }
    $sourceText += [IO.File]::ReadAllText($path, $sourceEncoding) + "`n"
}

# 문자열 안의 // 또는 /*는 주석으로 취급하지 않는다.
$commentPattern = '(?s)"(?:\\.|[^"\\])*"|''(?:\\.|[^''\\])*''|/\*.*?\*/|//[^\r\n]*'
$code = [regex]::Replace($sourceText, $commentPattern, {
    param($match)
    if ($match.Value.StartsWith('//') -or $match.Value.StartsWith('/*')) { return ' ' }
    return $match.Value
})

# DFM은 메서드 이름을 문자열로 저장하므로 C++ 호출 검색만으로 미사용 여부를 판단하면 안 된다.
$eventCount = 0
foreach ($dfm in (Get-ChildItem -LiteralPath $PSScriptRoot -Filter '*.dfm' -File)) {
    # 저장소에 남아 있는 미등록 구형 폼은 현재 실행 파일의 이벤트 검사 대상이 아니다.
    if ($sourceNames -notcontains [IO.Path]::ChangeExtension($dfm.Name, '.cpp')) { continue }
    $text = [IO.File]::ReadAllText($dfm.FullName, $sourceEncoding)
    $root = [regex]::Match($text, '(?m)^\s*(?:object|inherited)\s+\w+\s*:\s*(\w+)')
    if (-not $root.Success) { throw "Cannot identify form class: $($dfm.Name)" }
    $className = $root.Groups[1].Value
    foreach ($event in [regex]::Matches($text, '(?m)^\s*On\w+\s*=\s*(\w+)\s*$')) {
        $handler = $event.Groups[1].Value
        if ($handler -eq 'nil') { continue }
        $definition = '\b' + [regex]::Escape($className + '::' + $handler) + '\s*\('
        if (-not [regex]::IsMatch($code, $definition)) {
            throw "Unresolved DFM event: $($dfm.Name) -> ${className}::${handler}"
        }
        ++$eventCount
    }
}

# 역할별 구현 파일은 프로젝트에 한 번씩만 등록되어야 한다.
foreach ($name in @('AutoInspectionSequence.cpp', 'Stage_AutoInspection.cpp',
    'Stage_Measurement.cpp', 'Stage_PlcData.cpp', 'Stage_TrayData.cpp', 'Stage_CellDisplay.cpp')) {
    if (@($sourceNames | Where-Object { $_ -eq $name }).Count -ne 1) {
        throw "Project source registration must occur exactly once: $name"
    }
}
Write-Output "PASS: $eventCount DFM event bindings resolved; all production units registered."
