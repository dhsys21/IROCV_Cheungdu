# 소스 구조 검사: 프로그램 실행이나 PLC/장비 연결 없이 DFM 이벤트 연결을 확인한다.
param([string]$SourceRoot = $PSScriptRoot)
$ErrorActionPreference = 'Stop'
$sourceEncoding = [Text.Encoding]::GetEncoding(949)
[xml]$project = Get-Content -LiteralPath (Join-Path $SourceRoot 'IROCV.cbproj') -Raw
$sourceNames = @($project.Project.ItemGroup.CppCompile.Include | Where-Object { $_ })
$sourceText = ''
foreach ($name in $sourceNames) {
    $path = Join-Path $SourceRoot $name
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

# 컴파일과 별개로 C++Builder 디자이너는 IDE 관리 영역의 선언 순서도 사용한다.
# FormTotal: 컴포넌트 필드를 먼저 모두 선언하고 그 뒤에 이벤트 메서드를 모은다.
$header = [IO.File]::ReadAllText((Join-Path $SourceRoot 'FormTotal.h'), $sourceEncoding)
$headerCode = [regex]::Replace($header, $commentPattern, {
    param($match)
    if ($match.Value.StartsWith('//') -or $match.Value.StartsWith('/*')) { return ' ' }
    return $match.Value
})
$published = [regex]::Match($headerCode, '(?ms)^class\s+TTotalForm\s*:\s*public\s+TForm\s*\{\s*__published:(?<members>.*?)(?=^\s*(?:private|public|protected):)')
if (-not $published.Success) { throw 'Cannot identify TTotalForm IDE-managed declarations' }
$foundMethod = $false
$publishedMethods = @()
foreach ($entry in $published.Groups['members'].Value.Split(';')) {
    $declaration = $entry.Trim()
    if (-not $declaration) { continue }
    $method = [regex]::Match($declaration, '(?s)^void\s+__fastcall\s+(?<name>\w+)\([^;{}]*\)$')
    if ($method.Success) {
        $foundMethod = $true
        $publishedMethods += $method.Groups['name'].Value
        continue
    }
    if ($foundMethod) {
        throw "Component/invalid declaration after event method in TTotalForm: $declaration"
    }
    if ($declaration -notmatch '^\w+\s*\*\s*\w+$') {
        throw "Unexpected IDE-managed component declaration: $declaration"
    }
}
if (-not $foundMethod) { throw 'No TTotalForm event declarations found' }
if (@($publishedMethods | Sort-Object -Unique).Count -ne $publishedMethods.Count) {
    throw 'Duplicate TTotalForm event declarations'
}

# DFM은 메서드 이름을 문자열로 저장하므로 C++ 호출 검색만으로 미사용 여부를 판단하면 안 된다.
$eventCount = 0
foreach ($dfm in (Get-ChildItem -LiteralPath $SourceRoot -Filter '*.dfm' -File)) {
    # 저장소에 남아 있는 미등록 구형 폼은 현재 실행 파일의 이벤트 검사 대상이 아니다.
    if ($sourceNames -notcontains [IO.Path]::ChangeExtension($dfm.Name, '.cpp')) { continue }
    $text = [IO.File]::ReadAllText($dfm.FullName, $sourceEncoding)
    $root = [regex]::Match($text, '(?m)^\s*(?:object|inherited)\s+\w+\s*:\s*(\w+)')
    if (-not $root.Success) { throw "Cannot identify form class: $($dfm.Name)" }
    $className = $root.Groups[1].Value
    # 실행 연결뿐 아니라 디자이너의 폼 단위 탐색도 보호한다.
    # 이벤트 정의는 대응하는 FormName.cpp에 정확히 하나 있어야 한다.
    $formSource = [IO.Path]::ChangeExtension($dfm.FullName, '.cpp')
    $formText = [IO.File]::ReadAllText($formSource, $sourceEncoding)
    $formCode = [regex]::Replace($formText, $commentPattern, {
        param($match)
        if ($match.Value.StartsWith('//') -or $match.Value.StartsWith('/*')) { return ' ' }
        return $match.Value
    })
    foreach ($event in [regex]::Matches($text, '(?m)^\s*On\w+\s*=\s*(\w+)\s*$')) {
        $handler = $event.Groups[1].Value
        if ($handler -eq 'nil') { continue }
        $definition = '(?m)^\s*void\s+__fastcall\s+' + [regex]::Escape($className + '::' + $handler) + '\s*\('
        if ([regex]::Matches($code, $definition).Count -ne 1) {
            throw "Missing/duplicate DFM event definition: $($dfm.Name) -> ${className}::${handler}"
        }
        if ([regex]::Matches($formCode, $definition).Count -ne 1) {
            throw "Designer event must be defined in $formSource : ${className}::${handler}"
        }
        if ($className -eq 'TTotalForm') {
            if ($publishedMethods -notcontains $handler) {
                throw "DFM handler missing from TTotalForm IDE-managed declarations: $handler"
            }
            $body = [regex]::Match($formText, '(?ms)^void __fastcall TTotalForm::' + [regex]::Escape($handler) + '\(.*?^\}\r?\n(?<separator>[^\r\n]*)')
            if (-not $body.Success -or $body.Groups['separator'].Value -ne '//---------------------------------------------------------------------------') {
                throw "Missing IDE-style event separator: TTotalForm::$handler"
            }
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
Write-Output "PASS: $eventCount DFM events resolve uniquely in their own form units; FormTotal component-before-method order, event declarations/separators and production registrations verified."

# 오류창은 표시/선택 전달만 담당한다. PLC 오류 출력이 화면으로 다시 들어가지 않게 검사.
foreach ($name in @('FormError.cpp', 'FormCellIdError.cpp', 'FormNgCountError.cpp')) {
    $text = [IO.File]::ReadAllText((Join-Path $SourceRoot $name), $sourceEncoding)
    if ($text -match 'Mod_PLC\s*->') { throw "Dialog must not control PLC: $name" }
}
$autoSource = [IO.File]::ReadAllText((Join-Path $SourceRoot 'Stage_AutoInspection.cpp'), $sourceEncoding)
foreach ($command in @('CMD_CELL_SERIAL_TIMEOUT', 'CMD_NG_ERROR')) {
    $block = [regex]::Match($autoSource, '(?s)case ' + $command + ':.*?break;').Value
    if ($block -notmatch 'SetValue\(PC_D_IROCV_ERROR, 1\)') {
        throw "Controller must assert PLC error independently of dialog visibility: $command"
    }
}
$force = [regex]::Match($autoSource, '(?ms)^void __fastcall TTotalForm::ForceTrayOut\(\).*?^\}').Value
if ($force -notmatch 'SetValue\(PC_D_IROCV_ERROR, 0\)') { throw 'ForceTrayOut must clear error in controller' }
$plcSource = [IO.File]::ReadAllText((Join-Path $SourceRoot 'Stage_PlcData.cpp'), $sourceEncoding)
if ($sourceText -match 'WriteResultCode\(') { throw 'Obsolete second-pass PLC result writer remains' }
$bad = [regex]::Match($plcSource, '(?ms)^void __fastcall TTotalForm::UpdatePlcResults\(\).*?^\}').Value
if ($bad -notmatch 'SetResultCode\(PC_D_IROCV_RESULT_CODE \+ i, plcNg \? 1 : 0\)' -or
    $bad -match 'GetData\(') { throw 'PLC bit/code must share the same computed NG value' }
Write-Output 'PASS: error-dialog/controller ownership and single-pass PLC results verified.'
