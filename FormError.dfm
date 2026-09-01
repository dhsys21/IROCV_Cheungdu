object Form_Error: TForm_Error
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Form_Error'
  ClientHeight = 359
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
    Left = 208
    Top = 29
    Width = 268
    Height = 64
    Caption = 'Error Title'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -53
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg1: TLabel
    Left = 30
    Top = 132
    Width = 180
    Height = 40
    Caption = 'Error Msg1'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -33
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg2: TLabel
    Left = 30
    Top = 197
    Width = 180
    Height = 40
    Caption = 'Error Msg2'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -33
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Button_OK: TButton
    Left = 8
    Top = 8
    Width = 150
    Height = 50
    Caption = #30830#35748
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    Visible = False
    OnClick = Button_OKClick
  end
  object btnTrayOut: TButton
    Left = 194
    Top = 273
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
    OnClick = btnTrayOutClick
  end
  object btnRestart: TButton
    Left = 396
    Top = 273
    Width = 150
    Height = 50
    Caption = 'RESTART'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = btnRestartClick
  end
  object Timer_BringToFront: TTimer
    Enabled = False
    OnTimer = Timer_BringToFrontTimer
    Left = 448
    Top = 168
  end
  object timerErrorOff: TTimer
    Enabled = False
    Interval = 500
    OnTimer = timerErrorOffTimer
    Left = 503
    Top = 224
  end
end
