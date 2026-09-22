# DFM 크기/줄바꿈과 실제 Windows 글꼴의 문장 높이를 확인한다. 설비 프로그램은 실행하지 않는다.
param([string]$SourceRoot = $PSScriptRoot)
$ErrorActionPreference = 'Stop'
Add-Type -AssemblyName System.Drawing
Add-Type -AssemblyName System.Windows.Forms
$checks=0
foreach($name in @('FormCellIdError.dfm','FormError.dfm','FormNgCountError.dfm')) {
    $text=[IO.File]::ReadAllText((Join-Path $SourceRoot $name),[Text.Encoding]::GetEncoding(949))
    $width=[int][regex]::Match($text,'ClientWidth = (\d+)').Groups[1].Value
    $height=[int][regex]::Match($text,'ClientHeight = (\d+)').Groups[1].Value
    foreach($match in [regex]::Matches($text,'(?ms)^  object (\w+): (TLabel|TButton)\r?\n(.*?)^  end')) {
        $control=$match.Groups[1].Value;$body=$match.Groups[3].Value
        $values=@{}
        foreach($field in @('Left','Top','Width','Height')) {
            $values[$field]=[int][regex]::Match($body,'(?m)^    '+$field+' = (\d+)').Groups[1].Value
        }
        if($values.Left+$values.Width -gt $width -or $values.Top+$values.Height -gt $height) {
            throw "Control outside dialog: $name / $control"
        }
        ++$checks
        if($control -like 'Label_Msg*') {
            if($body -notmatch 'AutoSize = False' -or $body -notmatch 'WordWrap = True') {
                throw "Missing fixed-width wrapping: $name / $control"
            }
            $fontHeight=[Math]::Abs([int][regex]::Match($body,'Font.Height = (-\d+)').Groups[1].Value)
            $font=New-Object Drawing.Font('Tahoma', $fontHeight, [Drawing.FontStyle]::Bold, [Drawing.GraphicsUnit]::Pixel)
            try {
                foreach($message in @(
                    'CELL SERIAL - BEFORE MEASUREMENT',
                    'Check CELL DATA count and complete CELL SERIAL data.',
                    'SAVE: accept data / CANCEL: read again',
                    'There is too many ng cells. Please check it.',
                    'Select [Tray Out] or [Restart]')) {
                    $size=New-Object Drawing.Size($values.Width,10000)
                    $measured=[Windows.Forms.TextRenderer]::MeasureText($message,$font,$size,
                        ([Windows.Forms.TextFormatFlags]::WordBreak -bor [Windows.Forms.TextFormatFlags]::NoPrefix))
                    if($measured.Height -gt $values.Height) {throw "Text clips: $name / $control / $message"}
                    ++$checks
                }
            } finally {$font.Dispose()}
        }
    }
}
Write-Output "PASS: $checks error-dialog bounds/text-fit checks (96-DPI design)"
