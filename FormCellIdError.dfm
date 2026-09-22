object Form_CellIdError: TForm_CellIdError
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = 'Form_CellIdError'
  ClientHeight = 420
  ClientWidth = 760
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
    Left = 30
    Top = 20
    Width = 700
    Height = 60
    Alignment = taCenter
    AutoSize = False
    Caption = 'CELL ID ERROR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -32
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg1: TLabel
    Left = 30
    Top = 105
    Width = 700
    Height = 60
    AutoSize = False
    WordWrap = True
    Caption = 'The number of cell IDs is different.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -22
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg2: TLabel
    Left = 30
    Top = 180
    Width = 700
    Height = 60
    AutoSize = False
    WordWrap = True
    Caption = 'When you click [Save], '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -22
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Label_Msg3: TLabel
    Left = 30
    Top = 255
    Width = 700
    Height = 60
    AutoSize = False
    WordWrap = True
    Caption = 'the current data will be saved.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clYellow
    Font.Height = -22
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnSAVE: TButton
    Left = 210
    Top = 350
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
    Left = 400
    Top = 350
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
