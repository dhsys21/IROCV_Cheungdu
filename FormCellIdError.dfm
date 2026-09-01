object Form_CellIdError: TForm_CellIdError
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Form_CellIdError'
  ClientHeight = 375
  ClientWidth = 640
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
    Left = 110
    Top = 24
    Width = 420
    Height = 64
    AutoSize = False
    Caption = 'CELL ID ERROR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -53
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg1: TLabel
    Left = 30
    Top = 115
    Width = 580
    Height = 40
    Caption = 'The number of cell IDs is different.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -33
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg2: TLabel
    Left = 30
    Top = 175
    Width = 390
    Height = 40
    Caption = 'When you click [Save], '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -33
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg3: TLabel
    Left = 30
    Top = 235
    Width = 508
    Height = 40
    Caption = 'the current data will be saved.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -33
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnSAVE: TButton
    Left = 150
    Top = 305
    Width = 150
    Height = 50
    Caption = 'SAVE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = btnSAVEClick
  end
  object btnCANCEL: TButton
    Left = 340
    Top = 305
    Width = 150
    Height = 50
    Caption = 'CANCEL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -20
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    OnClick = btnCANCELClick
  end
  object timerErrorOff: TTimer
    Enabled = False
    Interval = 500
    OnTimer = timerErrorOffTimer
    Left = 575
    Top = 320
  end
  object Timer_BringToFront: TTimer
    Enabled = False
    OnTimer = Timer_BringToFrontTimer
    Left = 576
    Top = 240
  end
end
