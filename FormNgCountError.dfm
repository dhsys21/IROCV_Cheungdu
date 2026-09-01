object Form_NgCountError: TForm_NgCountError
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Form_NgCountError'
  ClientHeight = 375
  ClientWidth = 651
  Color = clBlack
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label_Title: TLabel
    Left = 90
    Top = 29
    Width = 471
    Height = 52
    Alignment = taCenter
    AutoSize = False
    Caption = 'Error Title'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -48
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg1: TLabel
    Left = 30
    Top = 132
    Width = 176
    Height = 39
    Caption = 'Error Msg1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg2: TLabel
    Left = 30
    Top = 197
    Width = 176
    Height = 39
    Caption = 'Error Msg2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnOK: TButton
    Left = 350
    Top = 285
    Width = 150
    Height = 50
    Caption = 'OK'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = btnOKClick
  end
  object btnTrayOut: TButton
    Left = 150
    Top = 285
    Width = 150
    Height = 50
    Caption = 'TRAY OUT'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Visible = False
    OnClick = btnTrayOutClick
  end
  object Timer_BringToFront: TTimer
    Enabled = False
    OnTimer = Timer_BringToFrontTimer
    Left = 448
    Top = 136
  end
  object timerErrorOff: TTimer
    Enabled = False
    Interval = 500
    OnTimer = timerErrorOffTimer
    Left = 575
    Top = 152
  end
end
