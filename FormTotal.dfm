object TotalForm: TTotalForm
  AlignWithMargins = True
  Left = 0
  Top = 0
  BorderStyle = bsNone
  Caption = '-'
  ClientHeight = 967
  ClientWidth = 1900
  Color = clWhite
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object AdvSmoothPanel1: TAdvSmoothPanel
    Left = 723
    Top = 504
    Width = 652
    Height = 252
    Cursor = crDefault
    CanMove = True
    Caption.Location = plCenterCenter
    Caption.HTMLFont.Charset = DEFAULT_CHARSET
    Caption.HTMLFont.Color = clWindowText
    Caption.HTMLFont.Height = -11
    Caption.HTMLFont.Name = 'Tahoma'
    Caption.HTMLFont.Style = []
    Caption.HTMLURLColor = clBlack
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -24
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = [fsBold]
    Caption.ColorStart = clWhite
    Caption.ColorEnd = clWhite
    Caption.LineColor = clBlack
    Caption.Line = False
    Caption.TextAlignment = taCenter
    Fill.Color = clWhite
    Fill.ColorTo = clWhite
    Fill.ColorMirror = clWhite
    Fill.ColorMirrorTo = clWhite
    Fill.GradientType = gtVertical
    Fill.GradientMirrorType = gtVertical
    Fill.BorderColor = 14922381
    Fill.Rounding = 5
    Fill.ShadowOffset = 0
    Fill.Glow = gmNone
    Version = '1.5.2.1'
    Visible = False
    TabOrder = 8
    TMSStyle = 0
    object Label9: TLabel
      Left = 18
      Top = 10
      Width = 126
      Height = 19
      Caption = 'Configuration 2'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object AdvSmoothButton4: TAdvSmoothButton
      Left = 348
      Top = 158
      Width = 120
      Height = 60
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -17
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Close'
      Color = clWhite
      ParentFont = False
      TabOrder = 0
      Version = '2.1.1.5'
      OnClick = btnCloseConnConfigClick
      TMSStyle = 8
    end
    object AdvSmoothButton5: TAdvSmoothButton
      Left = 172
      Top = 158
      Width = 120
      Height = 60
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -17
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Save '
      Color = clWhite
      ParentFont = False
      TabOrder = 1
      Version = '2.1.1.5'
      OnClick = btnSaveConfigClick
      TMSStyle = 8
    end
    object Panel17: TPanel
      Left = 18
      Top = 66
      Width = 120
      Height = 24
      BevelKind = bkFlat
      BevelOuter = bvNone
      Caption = 'CELL MODEL'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
    end
    object editCellModel: TEdit
      Left = 138
      Top = 66
      Width = 162
      Height = 24
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Text = '-'
    end
    object Panel18: TPanel
      Left = 305
      Top = 66
      Width = 120
      Height = 24
      BevelKind = bkFlat
      BevelOuter = bvNone
      Caption = 'LOT NUMBER'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 4
    end
    object editLotNumber: TEdit
      Left = 425
      Top = 66
      Width = 162
      Height = 24
      Alignment = taCenter
      AutoSize = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      Text = '-'
    end
  end
  object pback: TAdvSmoothPanel
    Left = 3
    Top = 0
    Width = 620
    Height = 913
    Cursor = crDefault
    Caption.HTMLFont.Charset = DEFAULT_CHARSET
    Caption.HTMLFont.Color = clWindowText
    Caption.HTMLFont.Height = -11
    Caption.HTMLFont.Name = 'Tahoma'
    Caption.HTMLFont.Style = []
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -16
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = []
    Fill.Color = clWhite
    Fill.ColorTo = clWhite
    Fill.ColorMirror = clWhite
    Fill.ColorMirrorTo = clWhite
    Fill.GradientType = gtVertical
    Fill.GradientMirrorType = gtVertical
    Fill.BorderColor = 14922381
    Fill.BorderWidth = 2
    Fill.Rounding = 10
    Fill.ShadowOffset = 0
    Fill.Glow = gmNone
    Version = '1.5.2.1'
    TabOrder = 4
    TMSStyle = 0
    object lblStatus: TLabel
      Left = 890
      Top = 891
      Width = 31
      Height = 13
      Alignment = taRightJustify
      Caption = 'Status'
    end
    object lblTitle: TLabel
      Left = 9
      Top = 10
      Width = 66
      Height = 24
      Caption = 'STAGE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 13204573
      Font.Height = -20
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      Transparent = True
      OnDblClick = lblTitleDblClick
    end
    object pConInfo: TPanel
      Left = 11
      Top = 894
      Width = 300
      Height = 13
      Alignment = taLeftJustify
      BevelOuter = bvNone
      Caption = '????'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object btnConfig: TAdvSmoothButton
      Left = 306
      Top = 6
      Width = 100
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -16
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Config'
      Color = clWhite
      ParentFont = False
      TabOrder = 1
      Version = '2.1.1.5'
      OnClick = btnConfigClick
      TMSStyle = 8
    end
    object GroupBox7: TGroupBox
      Left = 10
      Top = 266
      Width = 600
      Height = 62
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      object Panel20: TPanel
        Left = 7
        Top = 4
        Width = 75
        Height = 23
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PROCESS'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
      end
      object pb: TProgressBar
        Left = 83
        Top = 4
        Width = 333
        Height = 23
        Max = 400
        ParentShowHint = False
        Smooth = True
        Step = 1
        ShowHint = False
        TabOrder = 1
      end
      object Panel9: TPanel
        Left = 7
        Top = 30
        Width = 75
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'Channel'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
      object pPos: TPanel
        Left = 83
        Top = 30
        Width = 75
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
      end
      object Panel31: TPanel
        Left = 160
        Top = 30
        Width = 50
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'IR'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 4
      end
      object pIrValue: TPanel
        Left = 211
        Top = 30
        Width = 75
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 5
      end
      object Panel63: TPanel
        Left = 288
        Top = 30
        Width = 50
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'OCV'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 6
      end
      object pOcvValue: TPanel
        Left = 339
        Top = 30
        Width = 77
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
      end
      object pnlIRSpec: TPanel
        Left = 436
        Top = 4
        Width = 148
        Height = 23
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'IR 12.5 ~ 40.5'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 8
      end
      object pnlOCVSpec: TPanel
        Left = 436
        Top = 30
        Width = 148
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'OCV 1200 ~ 3500'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 9
      end
    end
    object flowChart: TPanel
      Left = 10
      Top = 48
      Width = 600
      Height = 110
      BevelInner = bvRaised
      BiDiMode = bdLeftToRight
      BorderStyle = bsSingle
      Color = clWhite
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 3
      object lblProcessInfo: TLabel
        Left = 6
        Top = 2
        Width = 143
        Height = 16
        Caption = 'IR/OCV PROCESS Info.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold, fsUnderline]
        ParentFont = False
      end
      object lblRemeasureAlarmCheck: TLabel
        Left = 264
        Top = 7
        Width = 145
        Height = 13
        Caption = 'Check Remeasure Alarm !'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        Visible = False
      end
      object pReady: TPanel
        Left = 29
        Top = 24
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'READY'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
        OnClick = pReadyClick
      end
      object pTrayIn: TPanel
        Left = 133
        Top = 24
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'TRAY IN'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
      end
      object pBarcode: TPanel
        Left = 237
        Top = 24
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'BARCODE'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
      object pMeasure: TPanel
        Left = 29
        Top = 63
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'MEASURE'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 3
      end
      object pFinish: TPanel
        Left = 133
        Top = 63
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'FINISH'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 4
      end
      object pProbeOpen: TPanel
        Left = 237
        Top = 64
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PROBE OPEN'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 5
      end
      object pTrayOut: TPanel
        Left = 341
        Top = 64
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'TRAY OUT'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 6
      end
      object pProbeDown: TPanel
        Left = 341
        Top = 24
        Width = 98
        Height = 36
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PROBE DOWN'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 7
      end
    end
    object btnReset: TAdvSmoothButton
      Left = 484
      Top = 61
      Width = 110
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -16
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'RESET'
      Color = 4342527
      ParentFont = False
      TabOrder = 4
      Version = '2.1.1.5'
      OnClick = btnResetClick
      TMSStyle = 8
    end
    object btnAuto: TAdvSmoothButton
      Left = 510
      Top = 6
      Width = 100
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -16
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'AUTO'
      Color = 16744448
      ParentFont = False
      TabOrder = 5
      Version = '2.1.1.5'
      OnClick = btnAutoClick
      TMSStyle = 8
    end
    object btnManual: TAdvSmoothButton
      Left = 408
      Top = 6
      Width = 100
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -16
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'MANUAL'
      Color = clWhite
      ParentFont = False
      TabOrder = 6
      Version = '2.1.1.5'
      OnClick = btnManualClick
      TMSStyle = 8
    end
    object btnTrayOut: TAdvSmoothButton
      Left = 484
      Top = 107
      Width = 110
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -16
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'TRAY OUT'
      Color = clWhite
      ParentFont = False
      TabOrder = 7
      Version = '2.1.1.5'
      OnClick = btnTrayOutClick
      TMSStyle = 8
    end
    object Panel16: TPanel
      Left = 10
      Top = 157
      Width = 600
      Height = 110
      BevelInner = bvRaised
      BiDiMode = bdLeftToRight
      BorderStyle = bsSingle
      Color = clWhite
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 8
      object lblTrayInfo: TLabel
        Left = 6
        Top = 5
        Width = 84
        Height = 21
        Caption = 'Tray Info.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = 16744448
        Font.Height = -17
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object chkCycle: TCheckBox
        Left = 112
        Top = 5
        Width = 73
        Height = 25
        Caption = 'TEST MODE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -17
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        Visible = False
        OnMouseUp = chkBypassMouseUp
      end
      object chkBypass: TCheckBox
        Left = 198
        Top = 5
        Width = 86
        Height = 25
        Caption = 'BYPASS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -17
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 1
        Visible = False
        OnMouseUp = chkBypassMouseUp
      end
      object Panel6: TPanel
        Left = 6
        Top = 31
        Width = 100
        Height = 34
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'TRAY ID'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -17
        Font.Name = 'Consolas'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 2
      end
      object Panel3: TPanel
        Left = 6
        Top = 67
        Width = 100
        Height = 34
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'Status'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -17
        Font.Name = 'Consolas'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 3
      end
      object Panel_State: TPanel
        Left = 107
        Top = 67
        Width = 482
        Height = 34
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = '...'
        Color = clWhite
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -20
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 4
      end
      object pTrayid: TPanel
        Left = 107
        Top = 31
        Width = 268
        Height = 34
        BevelOuter = bvNone
        Color = 8552834
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWhite
        Font.Height = -29
        Font.Name = 'Consolas'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 5
        OnDblClick = pTrayidDblClick
        object editTrayId: TEdit
          Left = 0
          Top = 0
          Width = 268
          Height = 34
          Align = alClient
          CharCase = ecUpperCase
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -15
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeMode = imDisable
          ImeName = 'Microsoft Office IME 2007'
          MaxLength = 6
          ParentFont = False
          TabOrder = 0
          Text = 'EDIT1'
          Visible = False
          OnKeyDown = editTrayIdKeyDown
          ExplicitHeight = 26
        end
      end
      object chkCellIdBypass: TCheckBox
        Left = 294
        Top = 5
        Width = 172
        Height = 25
        Caption = 'CELL ID BYPASS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlue
        Font.Height = -17
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 6
        Visible = False
        OnMouseUp = chkBypassMouseUp
      end
    end
    object btnRemeasureInfo: TAdvSmoothButton
      Left = 484
      Top = 161
      Width = 110
      Height = 59
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -15
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'NG Info.'
      Color = clWhite
      ParentFont = False
      TabOrder = 9
      Version = '2.1.1.5'
      OnClick = btnRemeasureInfoClick
      TMSStyle = 8
    end
    object pBase: TPanel
      Left = 10
      Top = 331
      Width = 451
      Height = 323
      BevelOuter = bvNone
      Color = clBlack
      ParentBackground = False
      TabOrder = 10
    end
    object Panel1: TPanel
      Left = 467
      Top = 331
      Width = 143
      Height = 323
      Margins.Top = 1
      Margins.Bottom = 1
      BevelInner = bvRaised
      BiDiMode = bdLeftToRight
      BorderStyle = bsSingle
      Color = clWhite
      Padding.Left = 3
      Padding.Top = 1
      Padding.Right = 3
      Padding.Bottom = 1
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 11
      object cl_line: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 4
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'Ready'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
      end
      object cl_ir: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 35
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'IR'
        Color = 8716164
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
      end
      object cl_ocv: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 66
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 2
        Align = alTop
        BevelOuter = bvNone
        Caption = 'OCV'
        Color = 16770815
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
      object cl_irocv: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 98
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'IR/OCV'
        Color = 16566623
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 3
      end
      object pocv: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 129
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'OCV Fail'
        Color = clBlue
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 4
      end
      object cl_avgover: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 191
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'Avg. Fail'
        Color = 1365955
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 5
      end
      object cl_badir: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 222
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'Remeasure'
        Color = clRed
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 6
      end
      object cl_badocv: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 253
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'CELL Outflow'
        Color = clYellow
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 7
      end
      object cl_no: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 284
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'No CELL'
        Color = clSilver
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 8
      end
      object cl_ce: TPanel
        AlignWithMargins = True
        Left = 7
        Top = 160
        Width = 125
        Height = 29
        Margins.Left = 2
        Margins.Top = 1
        Margins.Right = 2
        Margins.Bottom = 1
        Align = alTop
        BevelOuter = bvNone
        Caption = 'IR Fail'
        Color = 8421631
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 9
      end
    end
    object pnlTrayIn: TAdvSmoothPanel
      Left = 194
      Top = 9
      Width = 54
      Height = 14
      Cursor = crDefault
      Margins.Top = 1
      Margins.Bottom = 1
      Caption.Text = 'T. In'
      Caption.Location = plCenterCenter
      Caption.HTMLFont.Charset = DEFAULT_CHARSET
      Caption.HTMLFont.Color = clWindowText
      Caption.HTMLFont.Height = -11
      Caption.HTMLFont.Name = 'Tahoma'
      Caption.HTMLFont.Style = []
      Caption.HTMLLocation = plBottomCenter
      Caption.HTMLURLColor = clBlack
      Caption.Font.Charset = DEFAULT_CHARSET
      Caption.Font.Color = clWindowText
      Caption.Font.Height = -11
      Caption.Font.Name = 'Tahoma'
      Caption.Font.Style = [fsBold]
      Caption.ColorStart = clWhite
      Caption.ColorEnd = clWhite
      Caption.LineColor = clBlack
      Caption.Line = False
      Caption.TextAlignment = taCenter
      Fill.Color = clRed
      Fill.ColorTo = clRed
      Fill.ColorMirror = clRed
      Fill.ColorMirrorTo = clRed
      Fill.GradientType = gtVertical
      Fill.GradientMirrorType = gtVertical
      Fill.BorderColor = 14922381
      Fill.Rounding = 1
      Fill.ShadowOffset = 0
      Fill.Glow = gmNone
      Version = '1.5.2.1'
      TabOrder = 12
      TMSStyle = 0
    end
    object pnlTrayOut: TAdvSmoothPanel
      Left = 248
      Top = 9
      Width = 54
      Height = 14
      Cursor = crDefault
      Caption.Text = 'T. Out'
      Caption.Location = plCenterCenter
      Caption.HTMLFont.Charset = DEFAULT_CHARSET
      Caption.HTMLFont.Color = clWindowText
      Caption.HTMLFont.Height = -11
      Caption.HTMLFont.Name = 'Tahoma'
      Caption.HTMLFont.Style = []
      Caption.HTMLURLColor = clBlack
      Caption.Font.Charset = DEFAULT_CHARSET
      Caption.Font.Color = clWindowText
      Caption.Font.Height = -11
      Caption.Font.Name = 'Tahoma'
      Caption.Font.Style = [fsBold]
      Caption.ColorStart = clWhite
      Caption.ColorEnd = clWhite
      Caption.LineColor = clBlack
      Caption.Line = False
      Caption.TextAlignment = taCenter
      Fill.Color = clRed
      Fill.ColorTo = clRed
      Fill.ColorMirror = clRed
      Fill.ColorMirrorTo = clRed
      Fill.GradientType = gtVertical
      Fill.GradientMirrorType = gtVertical
      Fill.BorderColor = 14922381
      Fill.Rounding = 1
      Fill.ShadowOffset = 0
      Fill.Glow = gmNone
      Version = '1.5.2.1'
      TabOrder = 13
      TMSStyle = 0
    end
    object pnlProbeOpen: TAdvSmoothPanel
      Left = 194
      Top = 25
      Width = 54
      Height = 14
      Cursor = crDefault
      Caption.Text = 'P. Open'
      Caption.Location = plCenterCenter
      Caption.HTMLFont.Charset = DEFAULT_CHARSET
      Caption.HTMLFont.Color = clWindowText
      Caption.HTMLFont.Height = -11
      Caption.HTMLFont.Name = 'Tahoma'
      Caption.HTMLFont.Style = []
      Caption.HTMLURLColor = clBlack
      Caption.Font.Charset = DEFAULT_CHARSET
      Caption.Font.Color = clWindowText
      Caption.Font.Height = -11
      Caption.Font.Name = 'Tahoma'
      Caption.Font.Style = [fsBold]
      Caption.ColorStart = clWhite
      Caption.ColorEnd = clWhite
      Caption.LineColor = clBlack
      Caption.Line = False
      Caption.TextAlignment = taCenter
      Fill.Color = clRed
      Fill.ColorTo = clRed
      Fill.ColorMirror = clRed
      Fill.ColorMirrorTo = clRed
      Fill.GradientType = gtVertical
      Fill.GradientMirrorType = gtVertical
      Fill.BorderColor = 14922381
      Fill.Rounding = 1
      Fill.ShadowOffset = 0
      Fill.Glow = gmNone
      Version = '1.5.2.1'
      TabOrder = 14
      TMSStyle = 0
    end
    object pnlProbeClose: TAdvSmoothPanel
      Left = 248
      Top = 25
      Width = 54
      Height = 14
      Cursor = crDefault
      Caption.Text = 'P. Close'
      Caption.Location = plCenterCenter
      Caption.HTMLFont.Charset = DEFAULT_CHARSET
      Caption.HTMLFont.Color = clWindowText
      Caption.HTMLFont.Height = -11
      Caption.HTMLFont.Name = 'Tahoma'
      Caption.HTMLFont.Style = []
      Caption.HTMLURLColor = clBlack
      Caption.Font.Charset = DEFAULT_CHARSET
      Caption.Font.Color = clWindowText
      Caption.Font.Height = -11
      Caption.Font.Name = 'Tahoma'
      Caption.Font.Style = [fsBold]
      Caption.ColorStart = clWhite
      Caption.ColorEnd = clWhite
      Caption.LineColor = clBlack
      Caption.Line = False
      Caption.TextAlignment = taCenter
      Fill.Color = clRed
      Fill.ColorTo = clRed
      Fill.ColorMirror = clRed
      Fill.ColorMirrorTo = clRed
      Fill.GradientType = gtVertical
      Fill.GradientMirrorType = gtVertical
      Fill.BorderColor = 14922381
      Fill.Rounding = 1
      Fill.ShadowOffset = 0
      Fill.Glow = gmNone
      Version = '1.5.2.1'
      TabOrder = 15
      TMSStyle = 0
    end
  end
  object GrpMain: TGroupBox
    Left = 10
    Top = 656
    Width = 600
    Height = 236
    Caption = 'STAGE Info.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object StatusImage: TImage
      Left = 70
      Top = 28
      Width = 468
      Height = 197
      AutoSize = True
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000001D40000
        00C50806000000EDDA03E6000000017352474200AECE1CE90000000467414D41
        0000B18F0BFC61050000000970485973000016EA000016EA01E58E4310000031
        AD4944415478DAEDDD0598E4C6B985E15A3B0E333333333333333338CCCCC90D
        73E23033333333DC303333A3E1CE6BDDCACA6D49AD566B7676BDE77B9EB66707
        5A6AA954E7A7FA6B5BD9E0C10F2E7B3CF081E5FADBB695BD37FE79F63DF62887
        2921841042E8E48003CABF365E5FDAD0CD7D365E2FDB78EDBFED739F2B7B9DED
        6CE5B11BFFB8F3C66BDB569F64082184B02BB121AC4FDDD0CF7B6CDB77DF72E3
        3DF72C2FDEEA130A21841076553644F5A6DBF6DBAF7C728F3DCA79B7FA644208
        21845D95FDF72F9F25A87FDF10D4C36DF5C984104208BB2A1B5AFA9F6D1B6EEA
        015B7D22218410C2AE4E04358410429881086A082184300311D4104208610622
        A8218410C20C4450430821841988A0861042083310410D2184106620821A4208
        21CC4004358410429881086A082184300311D4104208610622A8218410C20C44
        50430821841988A0861042083310410D2184106620821A420821CC4004358410
        429881086A082184300311D4104208610622A8218410C20C4450430821841988
        A0861042083310410D2184106620821A420821CC4004358410429881086A0821
        84300311D4104208610622A8218410C20C4450430821841988A0861042083310
        410D2184106620821A420821CC4004358410429881086A082184300311D41042
        08610622A8218410C20C4450430821841988A0861042083310410D2184106620
        821A420821CC4004358410429881086A082184300311D4104208610622A86114
        1BE3A4FCE73FA5FCF18FA5FCF39F1B03675B29473842F33AF4A19B7F8771FCE6
        37CD753CD6B14A39EA51B7FA6C5663BFFD4AF9F7BF4BF9CB5F9AFFFBF7610ED3
        BC0E77B8662CECB1C7569F65085B430435F4F2EB5F97F2D18F96F2C94F96F2C5
        2F96F2C31F96F2F7BF3793280E75A866123DD1894A39F5A94B39EB594B39FDE9
        4B39D3994A39C631563FDE3FFE51CA073ED04CD426E6BDF66A5E8EB3E79EDB5F
        FE4DC0DB2F747D6FFFFDB7BFF6DDB779F9DA67A8E2F0AF7F35C276810B6CFE35
        FDD39F4AB9C2154AF9C6374AB9F18D4B79D29376C8AD9CCCD7BE56CA57BF5ACA
        97BFDC7CFD831F94F2873F34C6551D0704D47D71AF8E79CC528E7BDC524E7082
        524E75AA524E7EF2E6EB939EB494E31C67BD73719F3EF8C1E66BE38E881B0B75
        8C388FF6AB3D0E1884EEBBFFB7BFAEFFF7798C05E3C3D7F5E598C6E2252FD91C
        2F842122A8E16010D2673CA39497BDAC94EF7F7FB5BF35B99DF8C4A59CEB5CA5
        3CE211A59CE214E3FFF617BF28E56C672BE557BF6AFE6D32AC223A34592E0A6A
        FB7BED499400B405B68AACFF5FEC628D986F36AF794D29D7B94EF3F5094FD818
        2BFEBF334134DFF8C652DEF08652BEF9CD527EF7BBF5DE4F148337EE73BABF37
        BC6129E73EF7EAEF635C9EEE74A5FCFEF7CDFD25745E758CF85E7B6C2C464DEA
        38E87A191BC64235B47C7DC0FFCF8C8C0446C5BA064138E413410D07E1FDEF2F
        E54E772AE5EB5F3FF8CF8E7CE4C6FB38CA511A6BDEC4F6D39F6E9F781679CF7B
        4AB9D4A5C61FFB673F2BE53CE769FEBFA3E181BCF7BD9B7B0C1ECF95AF5CCABB
        DEB5FD7BFBEC53CAED6EB7E33F6F173FFE71294F7F7A292F7F79293FFF79FFEF
        F1068F74A4ED62467CA401FEFCE771C76168DDFFFEAB9FDFDFFED6FCED673F5B
        CAF7BED7185EA21A9BCDF18ED71C93A71DC21011D4F05FDEFCE6526E7EF34628
        DB98386F7DEB526E729352CE7296C60B855CE0473E52CA539ED28486DB088F11
        D40B5F78FCF179C3C2AEBFFCE541BF4FC8EBE45DBD09984C85A0FB10C6ADE162
        DE0A4FB486F116FFEE42176A3ECB66F2A94F9572D18B36C7AFF0D43EF4A12684
        B995BCE845A53CEC618D77DAC5118FD8DCCBCB5CA609EF1317DF735F88A93030
        41263CEF7847295FF94ABFA1F5C4279672D7BBAE77BE7FFD6BE3351AB3C6DF90
        B012442988F6F92CA607BC180672DB3CF2F6FBF1AE3FF399266C1DC21011D470
        205FFA522997BBDCC1C58C203DFEF1A5DCF9CEFD7F6B32BDE31D1BCFA672F8C3
        97F2BEF79572BEF38D3F07393A9376157482C823B9FCE59B095138AF3D299A98
        1FF290EEF772DE04CCE4DFCEA3992879C04F7B5A292F7CE1F6DF3FE7394BF9F4
        A737B7A08651F2DCE71EF47B8C93B7BCA594CB5E76F38E3B04617AF0834B79F2
        931B836311E72744EBFE9EF9CC8D71B20C9EA470F1231F59CAB7BE75F09FCB1B
        DFE52EF37D865BDCA29417BCA0FFE7BC6E86E2225D2161C69AE8CC3DEFB9DDC0
        320E8D0D6329842122A8E1408FE92A5729E5DDEF3EF8CF2E7EF1C6D35C3691F2
        5689A19C1B840415909CE31CE3CF831770894B34933C4CF47D8289C73CA694FB
        DCA7FB67049540F74D82267DC73251E20C6768F299CE7B33E0F9312E6A7EB8CD
        F5AF7F50636447A15297D0BCEE75DD3F973B64785CF7BAD3DE5F119BA8C6A2E7
        CF40BBFBDDE7FB1CDE8F00F6F192979472A31BADF69EC6827485712207FCF18F
        37D199108688A086034374727B3594DAE699CF2CE5B6B71DF73E3C0F13254B9F
        554F5055FE8E8570AB80157A1366FBDCE79A02A73E1EFDE852EE7BDFEE9F1154
        61C7D39EB6FFEF79B875623FC9499A4973B3F2648F7A5429F7BB5FF7CFE4A489
        0E0F7047214C7BD39B96F2EA5777FFFC68472BE555AF2AE5D2975EEF38C2F8F2
        D3ED50B2FB76EF7BCFF7598CD1BDF7EEFFF92B5E51CAF5AEB7DA7B1AC357BC62
        F36C086BBFF39D8D7119C21011D430183253ED79D5AB8E7B9F1FFDA8F148E5A0
        08AAAA59559D6331F1DDE006CDD72A614DE843AC2BA8DFFD6E538D2C6F76F4A3
        37A2C6539D1B4B65CE7BDEEDDE7B17849DA7B5A378C0039A906C17C2DECF7E76
        29B7BCE53CC7124E6EE74CA71625F5218C2E9CDEC76B5F5BCA35AFB9FAFB3236
        78E742C3C6E6544F3DEC3E44507773782ABCC8AE5C1784FCEE708771EF2507C7
        D37DFBDB9B821515C3AB2C8F702C15C6B064A78A6B1FEB0A2A8FDC44FBA63735
        4554CE7733D6A2BEF4A58D37D895A3AC585222FC7CFCE3CF7FFC45440218497D
        853C57BF7A63CCD4E2B3755131AC7A5B45381EF4A0521EFAD0F93ECFF39F3F2C
        FEF2B957BBDAEAEF2BD7CE1072DE0F7F786384843044047537C76441F4AC01ED
        4255AAE2A231C52830F1983021E4EBEFC7629295333DF6B19B1C96A60043AC2B
        A868870BDFFAD626CC37279617A98C55C9BB8CB98B75BA50DDEC7C3EF6B1EE9F
        2B26B37CE8FCE79FF7B88C235E1EE4BD85C0E742744594A50F95C00CBD2918CF
        222DD7BAD67058390444507773868A65404855498ECDA35A632994284C2684B9
        8A875A43CF8A8588F832E610D4EF7CA7118FDFFEB6A9FAE549CE097122D284B5
        767EEA5BEA233CCE089153DD2C5EF9CA46DCFA96B438571EFB58036A2C3CDE9A
        C7BCDBDD4A79C213E67B6FF7ADAB8AB7F2B6B735B9F965681CA1625DFE5E0A00
        A20AEE9D30B85C6A0843445077732C9391F71C5AC8CF6B79EC634BB9CD6D1AA1
        1AA2AEF504F15865190A71B36446479A316BFE8604D5B1B5CB5B26A884C53209
        95C5273B59E31DCF856B41447447824A6A62A9EAB40F79BB6B5F7BBE7368A3D8
        8B77DAD7118A11F4BCE70D8BD354BEFDEDC670737F6F76B3E1652EABF2E2170F
        1B428C3C9F7B08E340B5B56BF3C0078E4F7384D02682BA9BC3FA26A816C92F43
        1ECA64B34AA1D1663287A06E26D6F65EF082CDD20B6225B74C502F729146DCBA
        E09DD7CAD2B991A3F5FECEA70BCB6484DA4F79CAF98FCDB8F8C4279A823515D5
        AB547F2F6399A05A0EB6AC5AF9273F69F2BC521FCF7A56633C86B02A11D47060
        086E6C937682A0A9BB7679FAAA6E25CB0455C8F734A7D9BAF3D30CE3A94F6DBE
        66B47CF8C34DF11351EBEBCAE4E70480E8CECDE31E57CABDEED5FF73CD2D88DE
        5CC5483B8A65822A7DE09A0F21CCCD6064F88812C89986B02A11D470A0E7628D
        DD501BBF45E4988426E53D4DC45BC1CE2CA8DAF0C9CDD6BEC4968ED46E539679
        C849F755FD6A423014169E82630969F6AD3B85652172ACBB1ACB045518D7E607
        43A8F67EFDEBB7BE7355D8B589A08603F347D609EA89BA2A3A0B5DE31A8D976B
        DBB61DC9CE2CA86D6F50730AA1D4BA24460194F5AF3A0975A1A9026F76CEEBA9
        71BD2520B68DEB4385B5EE54BB1ACB04554114416DEF56C4C060402A44D2B441
        35AF8E61873D6C534826541FC2AA4450C381683EA0FA539E6F0A3C56851C8475
        33AB54DB0C09AA1CA41CEA5608AAC21BCDF6EB8E3D5D55ADBA260D2D1D99BBD1
        43BBE9461F3CE7B99A39EC489609AA2237EBA2DBDBBB3122ADC1D6D4A3BD4B8E
        4D0A18330C9E105625821AFE8BC9855765A1FC501382218439ADEDDC116DF496
        092A0F752B1A9A0BD7EA610B1EBC96868BDEA62230A2EB9A77C19BD5DCDFE6ED
        73A0AF310FB5F649EE42030A8DF057458E9211C19052114E94BCEA0E41B5D2BB
        2E415105AEA9048FD0FF1549E92B2CCF39A5F5E332415D05E76FE7A4B39F7D9E
        F70BBB1711D4701058EE262821B0553717AF58F2A2DDDB66E756774641E5F510
        06C53DB06C46D7A7AEE54372D0AE531F3CD8BEE6FFABA2E298B133B4CDD9949E
        B7B02445F7A536752797BAF9777B837774AD83157A9D92BB5C26A8BA50F150D1
        DEA09EB8F3D84567EA522F8680261C5336400F21821A3A112254F96B9F4C13CE
        AA9CFEF44D2B3F1B926F1643BBCD6C95A06A2220A76CB2760E0A5CFAD640FA5D
        2D00BB3625802A6A1D8D6A938175B0D180B68ACEAB0FC2A4827B55F4FDD5DE8F
        D73DB49EB90B7BDDEA9FECB36A983FE57E2D1354FDA835E84715FABA3FAEEBC1
        D8B04C466FE729FBF8865089A08641E421F7D9A799306DD1B60ADAE88D5D8E33
        859D4D504DD0965E1051286C6154F4AD29551463E2FEFCE7FBDF53F87D8E460B
        633C54F7D972A829F0F0145B69CE21E42D7C3C24DE44D4BD738D7426B245DA54
        96754A2290B6621BC2F22655D81A976855680FDE105625821A4661A254B4C21B
        501939068D022CC959D693772ABA37F56D03C6D3600CEC4841E54D9AB8857D85
        39855097753DD2314821505F2B40DD85549DAE2338B0D38DC605ED029C45EC00
        632798756158F086E580BB5081ADF86D99C88D65592FDF319D92BEF085E69CDD
        3B55C1763B0A615522A86125EC4A43C8782035EF348470E0D0D65AEBB033092A
        41142E952F05D1B0B6574893B8D6029D1A7204E1D1998707D527A87E5FD381A9
        CDDD2B8EA3C3555FCF66688DE8587360C71AA1D62E142F11B0B90C2DED126F75
        ABFE9F8F11543D7C79CB2AB357D90338843611D43009C534B65AD30B78883BDE
        717BB7A0B919EAFC4350857C4F75AA1D733D88B70959B5EADC083F0A432EEBA3
        3C84F0B2EE4B72A97D9CF18CA57CE6334D61CEBA286EEADBCFF618C728E5B39F
        6D7A27CFC1B2FD50C7082A74475218F5B087354B9D425895086A38B0C10061B4
        C463950DB685224D4243454B3C2BF9D7B9772FC190A05AA04FE47694A0CA174F
        698C310602C78B5DB7D980FCA83EB57DA884D555688E3598BA3D556F7D113953
        82AAA7EF1C3CE739C3BD77C70AAA1A01217145609A6B84B02A11D4706031863C
        148F41479F55F275750FD33E784526340237371A1FDCF39EDD3FDB9182FABDEF
        35053F35B72C37E8BA08FB0AF5D6651AD5C3AC4B4834C817F6B51695276FAD68
        1F73B4235C96AFC55C4B75860455A305823AD71A5B6985A110ED58411DC2BD22
        B60CC31DD5B824EC7A4450C381E132613322C44351083316ADEC784E16F67761
        7F4DB9B475C2957DEC2C826A079E5ACC4338ED16B3EA7A4AD5D04361C6A31EB5
        E9E0B34EC30C3BAA585F3914A63FCB599AC606A215EBA041C4CB5FDEFD335BE4
        11542D19E780D73D549DBCAEA06A40C110110E779CCDDE043EECBA4450C37F37
        F6C6AA4B2774DE511D49BCBAE0FD6A0CBF19EC0C82AAD8870162DD2E844B2D95
        5955907EFAD3A60A77681DE7ED6FDF6CF6BE0E3C391E5D1FBC694539EB169269
        63A9CAB90BD5DF72B973857C9DEFDE7BF7FF7C5D41E569F3B86103F88B5E749E
        F30E873C22A8E120DE84A60436C41EBB31B86217826A9D6317D608CED5166E91
        A175A83BAA2869B1D258CFDEA9052DC2BE438229F76869CE3A95CBAA6B7572EA
        6B79089EA39CED3A7D90ED6CD3B7738DA224823A6613F9313CE319C31B82AF23
        A80C26D5DA961DE9FC45506BD7A5101689A086030B8B5EF7BAE66B0519425BA7
        38C5B8BFB53D99FCA1EDCA1639DEF19AF7D2FA6D33D01EF1410FEAFE9910330F
        7533F76C55C4E2B3EBB003B9419F776A28D31EA942C543CD1778E4447C1DC6EC
        7F6B771663626A97A61D59E5BB59822AD72C5A533D7A3B323DF189F39C733864
        12410DE54A576ADAE055787D433BA1B4E1CD9A3CBB9AE9ABC0E5456E16EDDCE5
        223C6C8D053673D710A16C936CC55A4815A753B1AE578BBCBECDC721FFA84FF0
        5883A70B86C0E52E37DCA109C4DDE799523C646FD5BEBD578934419D6B1D6AED
        72D4C7544115EABDD9CD9A8224E349283FE1DE304404351C58546447948A2A46
        4B5D84BA86D058DCA4DBB5B69167A8C069337BF9CA29CAF9F6C148B8C21536E7
        D83C73D7ADEE69CA23E6D1698EB00ECB9A14D4CFBD6E2EF58B5F6CC2FB3FF8C1
        F0EF9DF6B4A53CF2918DD1A56A792C438DFF8D2F823A5738DEBAD1A17D5C09E1
        B2B1BC0811960AA9DBDD594EA6582BCB69C21011D4DD1CCB372CE897236A237C
        C9F22710F2918BF87D5EC1E22E2310D233990A1B6E168A774CF272827D383F6B
        555711823128C452DCD3AE6235D16AB3B8AE48B86ECBDA152AB8E2399AF0DB9D
        975685A829B6D1FD6A08DE99BCAB48040FDAFDB5CD591B616AEB91E5D2B51514
        B9E86B512907E9D8C47A5D14735DF39ACDB5EF8341A0E04B14A52E615ABC6E75
        F7199F8170EA04D6CE33CF61C484433E11D4DD1C9D7D2CC5A89E561B938C09F4
        D2976EC2732672ADEB78A4BCB1AE095348D264BFAEA7D6C644E83CE52A151A99
        B4EDC139B46E13BC46E7AE0A97D1C0CB10BE9CB22656D88F57AA28453F635B7C
        2DE25A69B9A7788558D44DAD8760D0587264A716F957D5D6DFFEF6F2F3F11918
        1422041AEC2BF099B2348998DEE31E070DF90F61F98E9D841CAF5632DBCFD492
        1C4BA8C6F47966E008372FEE11BB0C394DC7320E8C01C6D4BBDF3DEE7A8D313C
        FAD6E7BAAE0C1D3B038530440475378748E8F1BA6C2799BA8F2461E943584D4E
        739575AC633081CA8199B4C7F40FEE43C7215E961D5C5645C5AA50AC097D1926
        60468A4E52CB8A7AE479E5337946074C7C127D2E422C6F39059E99A6113A3D11
        F6CD8021C3C850A1ECDA683EBF6A830486074F59BFDDA19D6CE6869128446ED3
        F7108688A0EEE658B4CEDBD48C80D56F53713B6E8CE5042728E51CE728E52637
        6984618E3EB08B1054613DE7EAFD85A079395E7503EBBACC87C757BB10791160
        2F7F6B890F8F75A8FD5E1F04F57EF76B4440C37BE7E098B5A5623DAED0676D5F
        A7D1FCB29C1BAF5488570855872A9D957C2EA25C3F57FD6CED4DBA7D26A2528F
        A7886C59A87819048BA7EABC45028C85AE62B3219CB3AA6E024A3C79EBC6877F
        5B7FBA4EF8DDF9C989DB26CE3870AD5C272FEF5BEF47FBBED4EB568D15FFF799
        EAF77CED55EF5F7DD571E3596028AAF4DD8CF699E190450435FC17051896BF78
        994C15ACF81E31F232A198F4151A0901F338549BCEB59EB00F139BF330690A75
        56311D134E5D9C1C4DC2539682F04C859D7DFEA150AEE3C9B1BA5E0464D97A5E
        BF4728083491A8623AF6BAF87BE726FCBA98D75C07DD9434AB3006B45694B396
        536494386EDD41C739CBB75B22A551832543C607436BEC5AE6B1103E2165EF5B
        8DAA6A78AC2B765554EBFF19630C16D79701B56EE7A8B07B10410D2184106620
        821A420821CC4004358410429881086A082184300311D4104208610622A82184
        10C20C4450430821841988A0861042083310410D2184106620821A420821CC40
        04358410429881086A082184300311D4104208610622A8218410C20C44504308
        21841988A0861042083310410D2184106620821A420821CC4004358410429881
        086A082184300311D4104208610622A8218410C20C4450430821841988A086D0
        E29FFF2C65FFFD4B39FCE1B7FA4C4208BB1A11D425FCFBDFA5FCE427A51CF6B0
        A51CE630A5ECB557297BECD1BCB66D2B65E3FA1D3801EFB75F29FBEE5BCA7FFE
        53CA3FFE51CA718FBBDAA4FCAF7F95F28B5F34EF7FE8439772A84395B2E79EDB
        8F05C7691FCBB91180631DAB94231F79ABAFD4AECFF7BE57CA8D6FDCDC8B273D
        A9940B5D68ABCF2884B02B11415DC237BE51CAD9CF5ECA518F5ACA518ED28824
        B1F32274C4CDAB8ADBDFFF5ECAEF7F5FCA35AE51CAF39FDFFCDE18BEF295522E
        7EF146448F74A4E6386D6105116D0BE99FFF5CCA1FFE50CA8B5E54CAF5AEB7D5
        576AD7E7A10F2DE5210F69BEBEC10D4A79D9CBB6FA8C4208BB1211D425F04EAF
        74A552BEFDEDC6F35C85273CA194BBDD6DDCEFFEE847A5DCFCE6A57CF5ABA5FC
        FAD7E3FEE6084728E564272BE5294F69C4384C8761C223FDDAD79A7F1FF398A5
        7CF293A59CF2945B7D6621845D8508EA128474FFF29752FEF8C766B2FDC4274A
        79DBDB4AF9D29796FFED118F58CA1BDE50CAA52E35EE38BCDBBFFDAD09FD7EE6
        33A53CEF79CDFFDB9CF8C4A5DCF0868D809EE6348D37EB38D58B0DD378E52B4B
        B9FEF50FFABD473EB294FBDD6FABCF2C84B0AB10419DC06F7F5BCAB5AF5DCA07
        3FB8FC777990EF7A5729A73EF5EAC791D33BCF794AF9DDEF9A7FCBAF9AF88593
        C37C08A35FFAD207BF9FA73F7D634009F58710C23222A81379FAD34BB9E31DC7
        FDEE452E52CA1BDF58CAD18EB6DA3114209DED6CA57CF9CBCDBF8F7DEC26A77B
        F4A36FF5A73F64F1A10F9572D9CB36C5486D149DBDFAD5A55CEB5A5B7D862184
        5D8108EA4408E435AFD988DE186E7DEB529EF9CCED15BB63F0DE97BCE476CF89
        972BD47CB8C36DF5A73F6471939B94F2929774FF8CE7FAF6B78F2F2E0B21ECBE
        445027F28E77947295AB34E142F94B95BECBB014E32E77197F0C79D5AB5DAD94
        37BFB9F9F759CFDA14CA58C213E6E19BDF2CE58217DC1E565F84F1F2CE773651
        8610421822823A91B6A09EF18C4DAED33299211410BDE6354D78712C0A905EFE
        F2E6EB739FBB948F7CA4590F1BE6E1410F2AE5E10F1FFE9D5BDDAA94673FBB09
        018710421F11D489B405559EF3031F680A95DEFBDEE1BF53A4C4E351A13B865B
        DE72BB505FE0024DF8577152581FCB93CE77BE52BEFFFDE1DF93B31619985258
        1642D87D88A04EA42DA8673A535338642D29EF5318710893F85BDF5ACA318EB1
        FC38B7B94D29CF794EF3F5452FDA0876F279F3F0B4A79572A73B8DFBDDFBDFBF
        94473C62ABCF3884B03313419D485B50CF708652BEF085A6B3114FE6CA576E96
        D60CA1B3D10B5EB03C1F7ABBDB95F2AC67355F2B50B20467B3D69C6A6EA081C5
        77BED39CBF8E4C3E13E13FC5294A39ED690F3915C6D6165BCBFBB9CF35FF96AB
        661459AAD4C5494FDADC5B2D25B7025EB473965E58BCFF3A736940F2D7BF361D
        BD4E74A2CD6B45E91C8C916F7DABC93BEBD8650C6B7F697C9CFCE46983D985F5
        E5AE992AFDDFFCA66951AA318B717596B3947282136CDEB145628C0DC75AA528
        32AC4E0475229A3B988409AAF58A04B5E6365FFAD226544B908618D338E0F6B7
        2F659F7D9AAF559C12F2B90555B8DAFAD677BFBB79F816978F80B09A349DC375
        AFDBFC7F57E64D6F6AEE1F4C6C8455230DDDADFA78EA53C72F959A0B026F3C89
        529894552333E42022A2D04DC5B9FBA62ADCD820A8EED1DE7B97729CE3CC731E
        04DDF571AC1FFEB011D24508EB094FD814705DEE724D439331E2EA5E7CEA538D
        31A0E5A64230698D767B4FCF9971A95BD99FFED48C47057EFEF67FFFB7398EBF
        750EFEDEDFCA793BCFFAF2B7DA75BA2677BD6BF3DE1FFB58F34C3114BD87BFF5
        778EC578705D7D9ECB5C66DA7523A06A2014167EF7BB07BF6EEE97638B6C8996
        9CF39CB30D9D038D2C8D65E4FF19CBAF7D6D538007058FEF794FF3EC339E8F7F
        FCC6C014054BADC07422A813F18068B0E0613FDDE94AF9FCE70FBA9CE5010F68
        047308930221BBFAD5FB7FC7046ECD2B4C52847C2E2BD324F9C007360FDDE283
        7EBCE3359FADAB0DA2F336A93FFAD18D47B2ABE173397FCB6140585D03A26AC2
        E9322860B2B36695006F26BA727DFAD3CD04F896B7341E4DE555AF2AE53AD769
        3A68DDE2164DABCA3ECE7BDE667CF14CD6E175AF2BE59EF76C84B4A235A37B4F
        A48806C16B6352767D8DD9651012E1F755E0D17DFDEB8DC1B96ACF65BDB93FFB
        D9E6391A13F6D7E359F1DA2A30A6B5047DFCE3C7B712B54EDDEF6B413A15C732
        768C1BD75FD73530F6DFFFFEA60EC33D638CBCF0858DA75CB9F0854BF9F087A7
        1F3B445027F3FAD7374548BC02A12E93717BA23550AD6F34A10D218468F09FEB
        5CDD3F6F0BEA15AED0FCEE1C82FAF18F37E7B718E23CC7394A79D8C39A30B6CF
        E673C91F0A032F72AA5395F2E2173739E15D09DE106BDCC4E25AF250782084F6
        AA576D8C962E8804E1F53B7322644BACAC3136E9B9E6AEF7010B4FA616938494
        E012551EC83234A53006A7463588A971A22D66C5FAEB473DAAF16A181F3C4463
        4457A98A6741015DDFB86EC37313195001EF5A0CC18B952EE18113074621C343
        E1DEB2E232C583363D903A1166C52F7FD944809EF18C831F5B1F67BB0FDDEC66
        8DE73D161E34A1AFD5F970AD3CCB448B4728EA602C2DAE63E7619B5B2E7FF971
        C772CE22152264EA2B180A5DD7810164EC30AE88A968CB228CA6C73E76FCE70C
        0727823A119E42DDE145C5AE816C594C1B3926F9D4F644D38587DB24DEF5D0B6
        0555937E9EF1BA2119E7CA43ABD66B4515EBFBDED7840CDBF08288F98F7F7CF0
        F7925B55B54C5C77157800AC739CFFFCCD4454B7DA2320C4AAAF61C76684DDDB
        F77808A14AF9F4BBDF7DB97854089BA556BCB255F9C10F9A0D037EF6B3839E83
        F1BC1899309678A3C4157A4EFBBD55728372D82675A1C83E846A9FF8C4837F5F
        5ED7BD212E5DA8036048F56D76B0D8F9CC673146560D990BCB1361625921A642
        E596BD558C2FCBB1D4512CC2A8150961402DC37B08C52FC3DCA2173983FCA637
        ED5E37CFF062A884E94450272297C572073121525D3D5F152278D0BBC4A80D8B
        9485BE184E6C4FB6C459CE681D41651DCBD708512FE2E1668D77C1A265D91ED0
        315A786CBC845DA1FAD8FD10D6AD4563F24BBA5855E4D8FCDC767A5DF020E49A
        791A7371AF7B35C793C3E345B443AB8BC7E6A1F1AA08A4716562E6D576DDCF8A
        9028CF6C55BAD6E8AA1730D6BBF6FAE59179264CD62ADF851E57EDEAE53921E2
        7DCF8BDA84E73EB7FB675210F7BD6FF7CF5C5B22C54B5DF6B73E1B2384B0ADCA
        7DEE53CA631E73D0EFFDCFFF749F9722379192AEBC2A0166402F83014228CD3D
        221BBCFD2ECC51C68134D54F7F7AF09FBB4FC2BD63220AA19F08EA4484983CDC
        30584D8426BB2E7840C26426EB21EE7CE726F4D5F67EE616D4F69E9F6D58D11E
        709E4517BC140FDBA2570B05243CE731F9B2AD46CEB82E7FE165B96F8BCB9786
        2666DCE846FDAD0AA720DF26F4ECBE1321D75158B70FE155225C0B7E84FD0859
        5FA8DAE7F537AB401415E3480DB461F059F275B18B1DFC6F9C8731C27B168E35
        414FF1E487EA0F8C4FD7A8ABDA9A21428CBB04038C03EFBD88FCEF252ED18828
        A61A883E2FC3B81D1E17B5F25C49A12CC2A81321E94AA78C5DA625B564EC7831
        AA1482758D1D9102E7C0FBF7354FD4E7338E3DD327394973AF37B3DA78772082
        3A11A1374B5A208CE4211F5A52A28FAFE287C5E28D3684D2FBB63DA6B6A00AD3
        B25CA70AAA07C784D70EE15558CA3C9D214C34B50DE22272753CEC9D199E9D8E
        56D5FB61583CF8C107FF3DA14EBFD72E066AC370521DDA3549AE8B902131AAA1
        D34574CE32092E8E010528C6475728EF1EF728E5718F5BFD3C5C83BA3F6C1B5E
        1E6F5431DE22B6C0133A24B82A48A7A0D8C835E8332AE4ED8555BB10CEF4F32E
        789CF2BA8BA919F947D5ADAA7A099374CEAA1B22103646B3906A1B738394495F
        7733D789E7BCC815AFD8182EABE0FC5DB7BEE80A349691D6A82900A1695EAB88
        02E3326D4DD723823A9176CE85A7435025FEFB102A35B175E57FDAC89B104D85
        13680BAA6A600FC3544115D25519DA85BCE2B2D6899668F46D982E47A3A8664C
        B38AAD42D565EDA5EC3C790E7DB9DF76438D2EA688D41884FF8493855517118A
        94E3EE2A025B0C65B761F8D5A5576351B0A54AB8EE74B4084F5161927C73DB0B
        E5251244214893FB1484B1190E7D057D22358460D1FB5DACDE5EC4EF5BC75D9F
        AD8ACF5197AF31128C8B55B7ECFBE2171B6F73317C6B6E60B8F1ECCD013E5BDD
        F798C1E099EC5AFBAC9EC1B55FA5CDA8F7367616A30A15D5F90A9E88754551D9
        2B5ED13C0FAE6B588F08EA44DAE2A2724EC1C3B202060F925C96B0ED10AC4893
        8287BB2DA82C49A1A82982EA61E6F9F61530C8FD98588620F47D4B7C3CAC428E
        633653DF0A545E129CBACC4488F4452FEAFFFD8F7EB4A9FC252C5D5856C4885A
        2CE05A17139C49717163792800E34D75ADEDFCD5AF1A8FB2AB2847E1CA9071D0
        85F1A2104DC1591FC6A1F1208C6AE38639217C72885D111D9F5FC1D3628440D4
        8058F62D7B0283B2FD0CF85DC25F73D07D518B65F81BD5F17340F855094BFFAC
        1A761669EADBA7D9AA04DE77D6996E1E11D489282FBFF7BD9BAF59EBAC5A79C8
        65083BCAB3B0688730F9135E7994273FB9F9DE3A1E2A61105E22025D28A49097
        1BC224E63DFA1A56F070D75943B799F004E4BC098528807C595F814AC57D1A12
        14060843644E5C5BB94B06DA22C274EE4197D7C2DB5145DA958F9B22A86817DE
        0D61FDE41DEED0187F9A7FCC010F8E38765D0774E58587C2BD95C567D5386038
        F12C7D0E7950E1CF55E1DD75856885906B830AAFC567D7786CBF1407C9F5BA9E
        5360D08A622CA2CE8157DFF64EC3FC445027A272AF3ED0C29DC22C7D053D8B08
        8D9AACBB0A7CDA08A7093DD5C9500ED3433145504DB82CFA9FFFBCFBE763BA00
        59C05FD7D14D7D8FAD803161A2A9A1308517965F9864780375C26B237CC84BEA
        CB19430481273B67989BA0CAE799F4175170232FD9E5B5F0C079A842BF8B109A
        BA4C6815E4E48450FB3C9E4578A98A89C6AEA15C86F1A450AF0BC683DC63AD22
        6E6FC32734EEDEBA265D58032AA48C7655EED4A23FCF1623A82B3CCE63542DED
        3CE5279D97F7AFC7E081CBBF7AB9F742C3EB78FB2ABFBB36E8105161C4CFD539
        2B7413419D483BC4C3DA156E12AA1D8BE205EB58DB15815DF0A6F4E1C43A4549
        42821A50F4157AC8ED12992114F398B4FA1A0A8C798FAD4028DAB51BBB19FC2A
        30767880733124A8439DB2881F4165F42C325550617D27C38E113806DE334353
        F4461A601D14CFF94C5D4574848970D47D6ADBD5DB8AFF3C378CDE2E6AC14FDB
        08F14CBDFAD5AB1723C173217FDA759EAE9D30EB8EA24F50AD75974658F79E84
        6122A813B1ACC2F20AB0FA086ADFA2F13E84722DD21F3BD19B08784C533A2569
        49A601459FA0F62D296843944D1C7D4D05B4719B1AAADA2C789A727143A1DB75
        E029F11AE76A473824A84306D590A02EE60D578560883C2C56B00EA1688BE7B7
        6E572F45648AC9BA30D68C3969140554F2C78454D856644745BB1EB68B08ED12
        17E398376D8C303685D3FD6C55181D8EDF752C02C708DA515B2EF609AA6541D6
        4F6FD6C61AA121823A1142582B76E58D84FEC6EE715A21A426AAB115981A3228
        569A324979D885288962DFE7D1477408CB48147074E5E9C00BE20DED4C080BBA
        6EB55045D89C615243BDC4C9D7F59ACA6309C39964DD1F0BE50943DF72277FA7
        7272AE768443823A14F21F1254C5681A58AC831CA3F67C6A07C6F4A62520C45F
        61D33AC8F9CBA5D6284D1B455AC2988ACB6A3FDEF63512D66DB7FF6BC398E599
        5ACE8675B6E71B12D4A1A62F9B415F0E5538DBFDC86E339B4B047522AC63130C
        E4D01437E822B32A3C4693C098A6D41E169ED6142B539187706D5FE86E4C5870
        C843154A1246DBD976A1B1805D280F26359EC92A1B851356D77D288FE8333374
        E6E8143524A8D639AAF2EE624850A72C9BE94395B4622CD7B46BCD6B1B216A63
        621DAFC83178915DED0889830A78C5538A975C7FC76340C1DF884E7415D1A9CE
        6624A963E0D58A30D5FEBEABC233666876857CBDB7DCFD99CF3CCFF55F064FB4
        6BFDAF0D20187EA9F0DD5C22A81361F5D71668C2443CA1A90F8D820A93405F1F
        D28A0207619B2913376FCB929DBE7C8EC94F8FDA21AC975394D455D824EC6DE9
        C1CED46985F1409C6A718A9CB58294552778D5CBF2A407F43C29F28604D564B6
        2E4355BE963D54E360115DB8086AD7E6F696608CE915DCC667351E1574E94AD4
        0E85FA9930A63A82A16A75C57A96F9AC5BF96B9D645FEB44EB3C85A48923634F
        7392DA9C8057AD2ABDAF52B82262C17B9B6A1031668C339FB58BCDA806EFC3D8
        A91D9FDA4450770C11D489B41BACF37C7830CB96610C41CC78207DEB1EE16111
        CE99FAE0CB93F66D4365E36A13CF502E90603A07DEEE22C45EEE66670A29DDF6
        B6DB439D445405E794650342DD72A57D3D76618DB0254DEB32D4D8C1B2299362
        178C06E728FCB8887D516B34652C42E4C2B58C1295B68A7E16D16AD0F75DE32E
        6F55E7309EF62A11812E54EE8AAE74190B6DBA3A28F1CC191443080BEBF0B40E
        EE0D51EE82A12D02D5D79A742E18CD2AC1BB36E388A0EE1822A813F1E0F276A0
        959930CBBA9B03CBC9CA65F6C102E7094F2D7068AFB95BC467F0D00F19058A52
        EAE6D68B98B86A2BC69D014B18780D35AFA5ED9CCFDFD5D47D0C5D4DCFDB3044
        8418DDA375902B241E5DAD071903EE41D7A43824A853D6A1F2947564E275F93F
        83B16BFD2B6F557F6815EF8B1EBC548810FB1C7BE6B6AB78BB906E717F179730
        09C3BA277DCDF6E53889FEBA4B9FDADD96BA907BD6C87E19220D8C66A1EA559F
        73C63841EDDA28C1FB3128772683F79048047502260EE5F0359F653225A8EDED
        99A6206CC5ABEA6B01E8FD153F4D2D7D3749F27EFA9A3BE823ACE55E1F7D9386
        4E51F244631A5BEC2888BBCF53D1D9AAB61D9C42BBDF6B1F42CABC9D75BC0005
        3F04B5ABF06BA85293B7687C74B5B1B38350D736614330BA089190AEF16DDCF5
        195B8C00918BC590A7CA599EF6986DC89621374CD8FBD6965AFFDA276843DBE3
        8DE9103606B965D7AB6F7C3058199D75FDEB229E4DE16A5124CFA78882677195
        B1C49327A85D79F4A12557613E22A81310DE1242A99D51E46C5895537B97B6F1
        50F044BAF23EBC2CC2B54A7FCF4534B057A8D3950F3491330CBA2C63626FD2EC
        0A2759D650AB2C77067877CEB54EBE7A2C2B3A59B50ABB8D701A2B7F28CF6CF1
        BE6610EB6CED26ACEC3E7415B898B04511BA42FEF2DA04A7CB13937FB475D72A
        581FAD72B5365A5F56D8E418729D6D8C89BE252FABE2FA0BCB76E59019729E97
        BE36907EC6185A6C4938262A3316CF87AE528BD7A00D4398212E3CACE29E61C4
        80E251123B825A43E7C2F41A5BAC92EFB7A98339A8AB618CCF6F8ECAB299CD25
        823A0195B906AE26E09576F7957511AE5439BAB8C4452E86F5BACE8E101E7C13
        5357B5A8895A5EB8EB73F4E5785528F3CAA68652E786B764D26A0B9F629D6585
        2963E0012DF366889AD0DAB18F3DED183C3A82DC159617D6E431764528EC0A43
        88BBD619AB521EDAB4BB0BA172D7AD7ACA8C0539CAAEC60772EA0C9876A85111
        9330F1D4CAD92EFA76D411791081E8C3B564A42EEEA62447EC5ECDB58F6FDD3E
        AD6BF94C1BA2E679E17DF24CDBF7DA7536CEB4015D351225BC6EEC74F532B6C4
        483E7C8E6841E827823A12DE0EEB5F488D785AEBD686752C44C38BD0314985E3
        3A0FAA0202C2D72EF967D57A6857DDB4791116ACF064D7521DD6BE709389AB86
        9BE4A6E4E116F373260F4B16BAF6A6DCD1C83DB936F2D08BFB829ADCE5F884C3
        34DF58A5090303C43221EF6DAD222F601972E90A617878C29E6330A99AF00843
        DF36780C29CD447883ED9D8D78B384BEAFF048D19C35C62AC98DCB31D853D458
        6E77C5E2D169FEE1F8B59A9B8725DCAAC1423BEAB11995AD8C2555BB36D2AE68
        946F7C2E136E39E4763A43E8D3D89DB2F1FA10AE8322AE0326CCAAC68A1D8C56
        2D9C334730B4E498FBF6C4F579CD27C2FF0A10A71A7C619808EA1258FCC444E8
        4B586D28875621307A67EA16B34EF5201168EF7CA1B8C379CCE10DF27EB50914
        425BECD4C432968F33F99A3059BEED85F542CEAA9C4DA4533ACBCC8DD09805FA
        CBAA4009A98D942D721F933763D4F88C0C29A1F85551E52AAA601BB221A34358
        54DE5CEE6B68BFDC0A6FC398941B1456E57DF6B5836CE37E1A438EB7AC5FAC71
        260AD335DEE5CCBD785A96D6687E516184F11809FF66B4B9D390A1DDDED2F325
        9CBD2CD7C888E471D7EBA41849D462680FE32978968C19CFEE987B09CFB3E789
        676ADE58050624C3C0D8E9DBB46211F74E1729E29FDEBEF312415D8225133C0D
        625A9B5B2FEE1E51778AF03069722DE42234EAA15AC74AF75EAA89EBDA515E09
        0F69AEB08DF3E5692BD8E0817575A369C3D3E1E5B1C017F794DC4A9C8F022482
        E91E75DD1B6142F7457892673D66F366C2A3EA5A448011B178DFDB4DCEDB63C0
        CB64CAEBF4378A7586FA3C0BB15B72E338757C2D766FAAEFE925BFC98B614408
        31D7B1E9EFEA39D6F3F2773E7B3D1FE35298735907235D8434FB109510C25CE6
        7139BE5D5ADC0BD18FCD2A7EE1391303ED065D2B396B4BB6C68E13C617B40EED
        EBF53B07EEA7F76798F409AB6B26B5C3F0F65C4D411AC65836F6193075DCD4B1
        D91E97751C1803B545E3D8084A1847047509444D28CEC36B10D65D230C5E2F83
        D740F562211AAC263C1E0D6B73EC0E347DF024758A2104C25373341D5FC44366
        D2B77CC0046AB2AA6B4D3DA83C1BF93B21C0295B5B6D363C24D79BC161AD9FEB
        53C5A51A395E0C063BE5F8F9E25E9A5D08A52A12624854B126AC75979AB6E8B5
        058F7079391E0F8F373894F7265EC64C1D5F5EBC965A40624234B6FC8E97F483
        F7E3A9AA2E753E7EDFDF394FE7D8DECDC498F4AA9B5AF3CEC67866C6B470B79C
        BE73E4DD198FCEC1E7753C9EB7F32072C47D9DFCFE5844178436852E19836397
        97A83FE005BA673CBBCD1ECBAE37D1E2094B15A9C4764D8D27F78051AA58681D
        E38367EA7EB89FC64035FAEBD8ACE3B26DE81B97FEC6F5DB596A1F0E29445077
        014C624460478557AB358BB66884507B1C13F96A54EC681C9B3854A369156A58
        742B765D216ACEBD6BBBC070C820821A420821CC4004358410429881086A0821
        84300311D4104208610622A8218410C20C4450430821841988A0861042083310
        410D2184106620821A420821CC4004358410429881086A082184300311D41042
        08610622A8218410C20C4450430821841988A0861042083310410D2184106620
        821A420821CC4004358410429881086A082184300311D4104208610622A82184
        10C20C4450430821841988A0861042083310410D2184106620821A420821CC40
        04358410429881086A082184300311D4104208610622A8218410C20C44504308
        21841988A0861042083310410D2184106620821A420821CC4004358410429881
        086A082184300311D4104208610622A8218410C20C4450430821841988A08610
        42083310410D2184106620821A420821CC4004358410429881086A0821843003
        DBF6DDB7FC73CF3DCB61B6FA44420821845D95FDF72FFB6EDBF8CF67B66D2BE7
        DAEA9309218410765536B4F48B04F5C61B82FAE2AD3E99104208615765BFFDCA
        2DE450F7DA10D527EDB147B9FD569F50082184B0ABB1A1A3CFD8704CEFBAEDFF
        FFB1E786BADE70E31BB7DB789D7DE3B5D7569F60082184B0B3B2E188FE67432B
        BFB4F1DA67E39F2FDBF8FFBEFF0757E508FE261EFA160000000049454E44AE42
        6082}
    end
  end
  object GrpRemeasure: TGroupBox
    Left = 1311
    Top = 462
    Width = 450
    Height = 236
    Caption = 'REMEASURE INFORMATION'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 2
    Visible = False
    object lblRemeasureTime: TLabel
      Left = 24
      Top = 15
      Width = 46
      Height = 13
      Caption = 'hh:nn:ss'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = 12353126
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object BadList: TListView
      Left = 23
      Top = 29
      Width = 398
      Height = 172
      Color = clWhite
      Columns = <
        item
          Caption = 'NO'
          Width = 1
        end
        item
          Caption = 'Channel'
          Width = 100
        end
        item
          Caption = 'IR'
          Width = 70
        end
        item
          Caption = 'OCV'
          Width = 70
        end
        item
          Caption = 'Type'
          Width = 60
        end
        item
          Caption = 'Count'
          Width = 70
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      OwnerDraw = True
      RowSelect = True
      ParentFont = False
      TabOrder = 1
      ViewStyle = vsReport
      OnDrawItem = BadListDrawItem
    end
    object RemeasureAllBtn: TAdvSmoothButton
      Left = 111
      Top = 205
      Width = 100
      Height = 25
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -11
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Remeasure All'
      Color = clWhite
      ParentFont = False
      TabOrder = 2
      Version = '2.1.1.5'
      OnClick = RemeasureAllBtnClick
      TMSStyle = 8
    end
    object RemeasureBtn: TAdvSmoothButton
      Left = 217
      Top = 205
      Width = 100
      Height = 25
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -11
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Remeasure'
      Color = 16744448
      ParentFont = False
      TabOrder = 3
      Version = '2.1.1.5'
      OnClick = RemeasureBtnClick
      TMSStyle = 8
    end
    object TrayOutBtn: TAdvSmoothButton
      Left = 323
      Top = 205
      Width = 100
      Height = 25
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -11
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Tray Out'
      Color = clWhite
      ParentFont = False
      TabOrder = 4
      Version = '2.1.1.5'
      OnClick = TrayOutBtnClick
      TMSStyle = 8
    end
    object pWork: TPanel
      Left = 24
      Top = 103
      Width = 398
      Height = 39
      Caption = 'The equipment is working.'
      Color = clRed
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -20
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 0
    end
  end
  object GrpLocal: TGroupBox
    Left = 1301
    Top = 721
    Width = 600
    Height = 236
    Caption = 'LOCAL MODE'
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentColor = False
    ParentFont = False
    TabOrder = 5
    Visible = False
    object Image5: TImage
      Left = 70
      Top = 26
      Width = 467
      Height = 196
      AutoSize = True
      Picture.Data = {
        0954506E67496D61676589504E470D0A1A0A0000000D49484452000001D30000
        00C40806000000C45ACB3A000000017352474200AECE1CE90000000467414D41
        0000B18F0BFC61050000000970485973000016EA000016EA01E58E431000003F
        AD4944415478DAED9D076014D5F6C6CFA64180D07B6FD27B11A45A403A085204
        4454C4828A28D27B5710E1A1D87B477A15E9A03445457AEF1D426FA9FBBFDFDD
        9D9032B3D9CD6C20FFF7BE9F2F9A6C263377EECCBBDF3DE79E7B8E4314D59FFF
        3838323CA68BC321BD1C2295C5E14827841042084982D32911EADFDB9DB18EE9
        D9C3CB7CB776ED43D18E0E1D7E0EDCE338FF6EA023A4B7FAA5386363EE753B09
        218490348D232010FF965867F4F46C67CBF47154ECF041F7C080A0AF9CCE582D
        B784104208F1028743FD2F506262A27A3A2A77FC7083C311F4803336FA5E378B
        104208F97F052CD4D8D8982D8E4AED3FB8E57038D2DFEB0611420821FF1F8975
        3AA31C953B7C48DF2E21841062038A2921841062138A2921841062138A292184
        1062138A2921841062138A2921841062138A2921841062138A2921841062138A
        2921841062138A2921841062138A2921841062138A2921841062138A29218410
        62138A2921841062138A2921841062138A2921841062138A2921841062138A29
        21841062138A2921841062138A2921841062138A2921841062138A2921841062
        138A2921841062138A2921841062138A2921841062138A2921841062138A2921
        841062138A2921841062138A2921841062138A2921841062138A292184106213
        8A2921841062138A2921841062138A2921841062138A2921841062138A292184
        1062138A2921841062138A2921841062138A2921841062138A2921841062138A
        2921841062138A2921841062138A2921841062138A2921841062138A29F99FC2
        78D91DF7BA21296C7B5A6DB7D3DDB8B4DA3E42521B8A294980D3692237E6DFBA
        8E4FF2CD9D1F1C8E7B37B4E236702F31B14E898D8DD5DF070404E836A159B1FA
        73A7BEA1C0008704A80F03021CF7B4CD46BB639DAE36A3EDF85935CBD536F58F
        EB77EA73F58FABCD01FA77015AC8EE8D9AC5C4C4BA845EF765402AF68DF5BB69
        76DB69F5DD24FF9D504C491C189C03031DAEC11A83B65B90B430E9235CDF1BE8
        E1C8A187703D90BA84CAE11E541D6E21BBBBAF17AE19131D23C1C1819225537A
        299C2F8B142D9055F2E60893B00CC1FA73DC67B412805B11D1722EFCBA1C397D
        458E9EBE2C172EDD92DB1151BAED8181A9270A664445C5E80E4D1F122439B266
        9022F9B24AC1BC992557B60C9231BD6A7750A016CD48755C94BABF1BB7A2E4F4
        856B72FAFC75397BF1BA845F46DBA3D5EF62E3DA7F37F42246897EF37AA5A47E
        B5C2B26DFF59F961C976094A85BE33EEC778379D89DF4D7C1FEF78B37713CFDD
        E19E78A09F08F1271453A2C1205DA7722119F67C03397FF9A6DC5283F5ADC818
        89888C565F514A7C5C561E064FC3A787C11D033706CF74C141922E5D9016838C
        A1C1923B474619F5D11AD9B4ED841682D42646B52F5AB52D5FCE4C52BF6A61A9
        ADEEA55A99BC9259096AA86A5772F77EF37694EC3D122EEBFF3926ABB71C9643
        272EEB81382828752D2D0CEA214AE02B97CA23B52B1594072A15D2E29F410928
        3E4FEEEFD1F608F59CCE5EBC215BF79E913D87CECBF60367E5A06AFF2D754F78
        36784EA901842D6B587AF9666C5BDDE63317AECB5343E72A81BFE6D7C908FAE8
        B9B655A5CD4365E4FC25F56EAA090FDECBDB1131EAFEA3D573776AEB18D6BC0B
        D76422EEDD54EF64FA7481121A12ACDE8774EA9906CA4B6317CAA5ABB753AD6F
        C8FF1E1453A2C1A05CBF5A11F978584BBF9C0F03FDF3A317CAFAADC79315057B
        D7516D57965AFE5C61D2A1713969F36069C9A7BEB76A132C520CB4011ECCB6CB
        6A905DBEE9A07CB3F05F3970E292840405F8DD2D88FE866036AC51543A35292F
        9594986222E20FAEDD8C94D3E7AEC96FFF1C959F96EE94B3CAFA4E0DD180A03D
        DEB8BC8C7DF9A1B8CFC67FF69B7CBB689B1230FF3D73F4D5AB5D6AC94B1D6AF8
        E57C10E4F67D7F56627A8B624AFC06C594682034A16A702F9E3F9BE4CB9D49AA
        94CE2BE58AE792B2EA0B83BE27AEDF8A94DD07CFCBE153976597B28C8E9FB922
        D76E44CAB1D357B42B35B5DC8DB09471EA160DEE93973BDD2F05F3644E720CAC
        ECCDCA3A86C579EAFC756D59434CF32B0BB65EB5C2DA1ACC912583E9F9E13A7D
        EFC7CD3267D56EED4BF4C7C06B58A3D5CBE597573BDF2F35CBE737156AB8728F
        A8FEDC73385C59C997E49CB23C2394158667912F6798DC5724BB942E92430AA8
        7BB69A18C0627D69DC22D9BCDDFFDE01ACDD86A8737E34B4A5D450F760B0E3C0
        397966F87C6D31FA6B02823ECB9E25540AE5CD2245F265916A65F34B99A23954
        1FE448D6A50C8B7DDF11F4E145FD6E9E56D6F3D51B11FADDBCDB4B10E4BF1B8A
        298903561E0671038C852D1B949209BD1B7914927E5396CBA275FBB4B0192F13
        0E0F0A0C4C4521857B3448FA76AB2D4F34AD98A47D10AC59CB77CAB78BB76951
        723A1306A9180133250B659717DA5797E6F54B9907B1A8037F58B24DDEFD76A3
        3EA71D4135029E9E6C51597A75AA21994243921C13ADAEB1F6AF23F2F3B29DF2
        CF9E3372435999469FC68FE645DB3109C05AE5B36DAB4A8982D9939CEB869AE4
        3C35749EEC3D72C1EFEB98B016EB56292C9F0C6F99403431C179EDED5F64D51F
        87FDEA918871BB720D828302E4CDEE75A55BCB4A967F13AE2652CF8E9C2FFB8F
        5E4CD07F987CA4A6FB9EFC6F4231259660F08245F0CDD87652247F16D3632E5F
        BB2D8FBF31435B00A9117862DA2E25A4B0D086BFF0A0B4A87F5F92DF47A8817E
        E257EBE5A75FB6EB81DE53BB209041810E25A835E4C58E352CAD3C88DB5B5FFC
        AEDDC401299821C09243384C9F276BC9D3ADAB9A4E32AEA8BE9CF8D50659FCDB
        3E2D5618F03D5D0BE28CE360910F7EAEBE3C7C7FB104BFBFAE84F8C92173E4C0
        B18B7E7D361830F06EBCF3C6A3D2B46EC924BF5FBAE1800C98B2427F9F5A9329
        58BEF75728A89725D259B8C7FFD871529E1D31FFAEBD97E47F1B8A29B1048335
        82893E1BD946CA97C8657A0CDC665D07CD96F34A4CEF46042C442928204086F4
        6C208F372A6B7ACCB41F36CB873F6FD19691378339CEE954F73AF2A507D539CB
        591EF7FE8F7FC88733B768ABC817F4761775FE979FA8292F5AACFB5DBD1E2103
        A62E97355B8E7ADD6E034C08C23286C894379BC803950BC57D9E5A628AEB952A
        9243BE1EF3980EE849CCCD5B51D26DE85CD97BF842AA598098D4942E9A43BE1C
        ADDA90319DE9316BB61C91DECA4A4EC9E487105FA198124B2032E9D4C0FED9C8
        D652B9545ED3634E9EBB2A4F0E9E23172EDFD2D193A90D2C310852EF2EB54C7F
        0FD7E8F3A317C8EDC8189FDA83C13977F68CF2F5D8B652C864ED15208AF4B5B7
        97CAEFFF1CF3C9858936B77DB88C8CEEF5B0DE7A9418B830874F5F25B357EC96
        F4E9521684846B942D9E53BE1C7547E052CBCD8BC0A3BE4FD591E7DA55B33C06
        C15B6F7DF9BB5E574D0D6019172B904DBE19D75647149BB172F361797DD25206
        1991BB02C5945882C00F0CC29F8E682DD5CAE6333D06811CD80E117E25F5C514
        82717F8502F2C190169641517D26FE2ABF6ED86FE9FAF30482A55E6C5F435EEF
        56DBF2987FF69C9617C72CD2C77A3348BBACB8ECF2C9F0D67ACFA8198BD6EE93
        81D356E88407768C284C08C6BDFAB0B479B08CFE19DB7D7A8C58A0B7CAF84B4C
        21FC39B36690EF26B493021651D3E04CF875E9A62659D82E931A1E0BB8FA0BE5
        C922DF8D6FA79722CCF875E341E9377919C594DC1528A6C412882906C24F9510
        542F672EA6874F5E92A787CD938B576FA7AA981AD1A3EF0F6AAE2370CD8005F6
        CC88F972FD46648A065004FF9428944D0FD06116AE43D07FCA7259A80430B9ED
        1FE83FACD9BEDDA79134A953D2F4186C6341FF617F68B0CD801D44EFB66A584A
        26BEDED8FDB39A1C8C5D247FEC38E5B36BDAF21A6A42D3AD4525BD469B1CEF7C
        BD413E9BFBB7DFB6FCC407A28EB5E2EF3D88E992DFF7CB80A92BEE8AC784108A
        29B1C41B313D70FCA23C3B7CBE5CBA96BA620AABF491FB8BC97B4A4CADF87AE1
        5699F0F9EF291EBC75CA414780B67C1FA85CD0F2B8DFB71E9757C62F7645087B
        B865B4F90125FC1F0F6F6569192EFE4D0DF84A9CFD91B108AE4F644EFA7AEC63
        3A8B122CD53E1397FA2DB216FD933E5DB07C35BA8DDE32951C98DC2000E8AA9A
        DCF8FBDDF0464C17AEDD2B83DF5B45312577058A29B1C41B31DD7734DC35605E
        8F4855771A84E13FFD9BCA23B58A9BFE1E013E7D262D95159B0ED9120EB86FFB
        75F7BC1E887D8ADD87CED3F7EEC9E283A53BF18DC6D2BCDE7D96C7F47DE7576D
        41A5C42D6DDA0FEA997D3DA6AD542DE35AE31E346D85CC5BB5D72F4914303940
        F42EA278F1AC2F5CBA29C7CE5C956A65F35AFE8DDE36E58515EF2BDE88E9BCD5
        7B64D8F455A99A2F9810038A29B1448B69806BCDD44A4C771FBE20CF8D5C20D7
        6EA49E98466B8B2B8B7CA544C26ADD118923B045E71452D9D9183C0DC178F7CD
        261E8F1BA22C9EB9AB765B0A37DA8C353D5889086C3203DB8A3ABCF9B35E5FF4
        D7808FF6F7E95A5B9E6F5F5DFFFCCE371BE4D3D97F279B5231398C4201FF19D0
        541A542BA23F5BB066AFCC59B95B07A85959DE4818015733263BFECC2205312D
        903B4C7E98F0B8A598CE5EB14B467EB8E6AEE75926FF9B504C8925C600FAE988
        5652A35C7ED363EE8698622DB0F583A5F5DAA315B012110885A01B3B5B212082
        F715CE2E33DFE9E83168E7C75FB6CB984FD6598A29D6165B37F4DCE6BF779FD6
        42733B32DA6FDB37205A48AD58A33C263F0ED9A39E0FDCAD76050589F86B942F
        A08513D6382CE017C72C96F55B8FE9F7A34EBC2D3989FB13015B1BFEF56F5A49
        8A29496B504C892571623ABC55829471F1D9E316D3ABA96C990EEA514FBA36B7
        CE76B3F6AFA3F2C6A4A5FA583B16902B5A35547E9AD841F25858940009FC7BA8
        FBB672F3228A7748CFFAD2A55945CB73C00D397CFAEAB84A3BFE02821AEDCE16
        E48F0A38581B46F4ECB8571FD1B98FC15FBB4FE9E77EEB76B4DEEF8BDF598124
        14031108E447518B714F1A7E78EB71C941312569008A29B1C425A60EBD66EA51
        4C472D48D5355388C397A3DBE87CB656CC5DB547467CB85A6719B2234CB856A6
        0C21F289B2B62A94C86D791C122174EC37D3951FD8E47A109F6FC7B6932A65AC
        D7133F9BF3B776C3A646B4AB3FC1C400D6FAB7E3DAE9E41060C8FBAB648E122B
        E4FC45A9BBEFDF6A2785F39A67C942C4728F11F365E7C1F37E8B2AA69892B406
        C594589216C414561106E039EF76D2B549ADF86EF1369DEE4F47C5DAB89EB105
        07C14E75AB16B63CEEE8A9CBD279E06CBD569BD8456B140D9839A9834ECE6EC5
        D4EF37C98733FED4C7A665E0667FB37B1DE9D1B6AAFE1989F79F4604F755D7DE
        625DD5A5732D79A9A37555976F17FDAB9ECF7A3F8B6926B7989AAFA3534CC9DD
        84624A2C716D1571682BAD66F902A6C7A4B698C252C4368F1913DB5B06F280CF
        E7FE2D93BFD9687B5DEECEDED0C6D2A44E09CBE35019A7CBC03972E57AD29A98
        C67A1E2C39AB802930E92BD73E4CBBC141A909DCC5797366D2354BF3BB93347C
        3C738B4C511301C3A246D4724965B97E35E631CB6C44E72FDDD099B24E9DF34F
        AD532DA639DD629A95624AEE3D14536289212C9FDE4331D55B2094307D371E83
        66A8E571FE1353D77D8F7FF51169D9B094E571A844F3C48059BA0077E2355A08
        10AAD1206F6CB6CCE92DCF814A341FCFFA2B4D8B2982A39E7DACAAF47FBAAEFE
        1911C8C8C57CF4F49504015A70054F4A661BD07B3FFC211FFCFC875FB601E1BD
        4021F81F29A6248D40312596C489E97025A615EE9198625B4CFEAC3A076BF6CC
        D662EA2F37A221A648CBD7AA6169CBE3F49A69FF99AA7D49D74C7512F62239E5
        8BD16D244B26EB4C4AD367FC29D394859756DDBCC6FAF137631F5396670EFDD9
        CCE52E810A4A9464C2555CBEB07C3CAC95E5F90E9FBC2C4F0F9F2717FD907A52
        8B690E25A66F534C49DA80624A2C31C4F41325A6F7DF2B3185CB3457987C3FA1
        9DE5A00930C88FFE78AD764BDB094032EEF9ADD71A99961733D8B2EB943C3D74
        9E6955148869F182D9B4DBD3D30400EBBCE33FFBCDAF5B46FC0904B2DDC36564
        AC3B5217E909F1ACB1A52771B171AC35E3B3CF47B6D685E5AD18A39ED10FBF6C
        B76D9DE2BDC8EB16D39C14539206A098124BD28298C23A82AB74C6A40E7AF0B4
        62E9FA033ADB8FDDE40046D6A7C97D9BC843358B5A1E8748D6611FAC4E222AC0
        18E8910CDED3F69AE59B0EE93CBFB1B1F6B6F3A4064E77201612761811C9A8C2
        F2CA84C5821AE7AE479DB0CD70093FD9A2A28C79F961CBF3EE38704E6FA9D1FB
        816DBC2F145392D6A098124BD28298E2E5C46967BDD3514A14CA6E791C0A41BF
        3C7EB1B6A6EC08132CACD074C1327D7073CB4415003980E15A36B32AE12A0E09
        0E9059933BEA5CB956A048008272AEA530317F6AA27321D72A2653FB358D13A3
        99CB76C96FFF1CD3C5D4617D43D0F4CD1A7D87A0A0DC99E5CDEE0FE83EB4E2B5
        B77F91651B0FD94A31483125690D8A29B1242D8829C0203D6D603379B04651CB
        638E9FB92A9DFACFD405B1EDB403D7423D5014BEB6126FACE3A2D2CB5FBB4F7B
        4C27F8C5A83696FD06A2A2639498CED5D69ABFB68CF803634BD4D4FE4DA561F5
        A27E3FFF86ADC7A5971785023C413125690D8A29B1E46E8A69ACDBC2C119125B
        96109D579EF0BC8F1185BB3BF69B254794B56767F08450E6CB15A6F7B522F8C6
        0C041F2190C6D33DA3CD6F747B407AB4ADE6E972F2FE8F9BE5FD197FA6A9C40D
        B04A51E6EE9361AD4CD784ED82C85FA451DC6823C5E0DD1453E3DDF457CA47F2
        DF09C5945872B7C41463155C8718B8611962B08D0FF2DC3E7C7F51993EA885C7
        73F49FB24C16FDB65FD2D908E88108D6AE5850E7A0B572177F31EF1F99F8D57A
        8F0218A9DB5C4CD75FF504FAAFC7C8F969C6D58B678E0161629FC6710158D84B
        BB78DD7E9D32D270EFA2BFA3555F1940B002D53344C27EF44BA35AC57414B615
        283D3770EAF2140BDDDD12539D34243840471FE3BDC4FB498819145362C9DDC8
        80044B308F1A1407F6A8A7235F91626FED5F471204F660E044F203240E40D92D
        2BBE5FB25DC67EBACE9698DE8E88D616F06B5D6B9BFE1E25DABA0F9D9B6C6ABC
        189D6C2254BE19D3D663E6268001FFA7A53B247D1AD86F8AC944C59279E4CB31
        8FC5ED7F9DBF7A8FABC8B612CB784BA4FAFDB8C39D286A88CED36DAAC8100F05
        C4E18E476EE394BAB8EF460624F405B684F5EA5853BF176F7DF9BB1C3F7D856E
        63620AC59458E24D3D53BB621A191923FD9FA9AB07DF2BEA1C9D07CCD2D98512
        0F58B0F486BDD0503A37AD6079AEBDA8AD3A7C5E8AAD3CBDC754FDF3FEC0E6D2
        A07A11D36316ADDB2783A7ADF42A393D2CEA014FD751F756D5E37127CE5ED535
        614F9EBB76CFD74ED1CFA37A3D241D1A97D33FC31283E5BC79FB49AF5DB27AF2
        A3AC45E4EBCD9733CCF2B89F97EDD4DB99529202D29B7AA676C414F78DC9CD7B
        039B49AD8A0565EB9E33FA1959E5622684624A2C891353D4332DEB7F31C5C08D
        99FF87835B4886D0605D1F73E8FBAB4C850AD64E8592B975504FC650EB48D157
        DF5A222B361D4E51A4285C98C5F267956FD5006D96160FEECE9EA3162AABF49C
        E9969824E78B76ED37FD724C1B4BEBC960DDDF4765C09415BA949D3FD6296155
        618DCF17213112DAC74F0B88FDB428A116E93E9FD7E752CFB6DFD3AE49921598
        3CC1CAC71AB4AFF79CDA628A89D033ADABE8891E18FBC93AF97EC936BF157127
        FF7D504C89254EF7467C8869558BEA272915530C869942B105A58554730B35F6
        5C2E5CBBD772C082400C79AE8174696E5DD66CE3B613F2F2B8456E0BC23771BF
        1D1125BD3AD594DE5DCC5DBCD37ED82C1FCDDCE253D00C260C38E72B4FDC9FEC
        B1ABFF3C2C233F5A2BE7C2AFEB6BF8DA7EBD8E19E3DA1A84356EB852771D3AEF
        B12E6BE2B60EED99B07F477EE47641FB28227856954BE5D56BCF193C647842E2
        8A099FFFA6C434D027EBD4C88C85FCC756291B532AA6E887B2C573C927C35AEA
        442178B7BB0D9923078E5FBAE79E039276A198124B10C588F547BD71BFB4FFC4
        D435E8C7CA1B4FD6961EED5CD1AE679580A00ACB854B372DCF13ED5E5FFD7868
        4B9D58DD0AD408850BD19735485891B074B056889CAF8959B9F9900CF8CF0A3D
        D0FA62A1C15D0831F9CF80A6DA5D981C10BFFF7CBF49D74B853518AC45C6DCA5
        EC7477A60EDA527D83EB942D964B3A3C5A4E5A3528259BB69F90DE6F2FD58142
        C909B391B5095B82B2B9B3369D3A7F4DEF833DAF9E494AD2FF6132F6C1909652
        B74A21CB632E5DBDAD8BBA1F3E71C927EB14625AB4403625A66D2D93EBA7444C
        715EA477FC4FFF66F24065D7F35AFFEF71E93576B1FE9E2E5E6205C594588241
        1A030B52C4C1C56A06C4F4D991F3938869E231C7E9FE972B12D4A907FCA13D1B
        C6CDF47FF97DBFB64C931BF80CD7F0E4BE8F5A46719EBB78435E9EB05876EC3F
        EF95BB1703282CA309AF3D224DEB244D2188F479FDDE5D2667D579BDB5F2E203
        2B0DE23FE5CDA65AB09203F7082B1511AF58AB33A268E347926250475B60C543
        FC6B552828F5AB17511669FE38CB5E6F299AB0447EFFE758B26E6933AB1F16E9
        984FD669914B8986C055DABA61295D81C713081C1BF7E93A9F2C7EF4C77D8573
        6897B455FEE359CB77E91AB7F1DF29B3FB30DE4D9C1313B001CFD4934E4DCAC7
        FD1E91DB88E04E4BDB9748DA83624A128097C1A906ED18BD4525468A22C9FCD8
        B6BA0C9719FB8E86CBAB137E5103FEED04D64FE2970ABFC1E08FF5AD566A80ED
        DABC5202CB71C87B2B65CEAA3D5E45E21ADB4E46F77AC872BDECE8A92B4A08D6
        CAC66DC75D5B6F9420C4B72821E8B8476DED66CF287D9FAA23AD1F4C9AD81E99
        95B08E8B20213B3974D19798904CE8DDC82B4105681B4A97ED3D1C2E874E5E54
        139648BDAE092B116BCC28F356BA684EFD6CC2328424E8FFF02BB7E4DB85FF6A
        41B97633C2D232451F20E76E836A4574628CF82ED937272F93B9AB764B46756E
        5FF758A27F11F95CA6584E5D3ECF5346A41BB7A2E4F5494B65CD9F472458F531
        A286CDAE87E7086F09263F78071E7DA0844C1BD0CCD2A29DBF7AAF7621C78F42
        361BEC702D4CEAE09978B245A50439999122B1CBC0D9B2EF4878AAECB925FF3D
        504C491C86D508B7592135B060D06FD9A0749CBBCB0C0C6A672E5C77A5961357
        34ACFB9B04189654E64CE9935812E1976FEA8C42874F5DF6DAF28300C0421DD6
        B381DC572487E931583384758775D883C72FE942DED1EE409A744AC8B1DDA676
        C542D2B545452995E81CE887392B77CB94EF366957A43FD6CAD057C50B64D3DB
        80EA79283C6E0708D8D2F5FBE5EB055B65EFD18B1202ABD244985CA2E4DA7254
        5F0969AF8E3574B28AF820200C29133191B87A23D252E412F75BB4763987A8F3
        6592F68DCAC953AD2A27DBEEB3E137E4AB05FFC8A66D27E5E8E9CBBAAFE2BF0B
        3827261158C32C922F8B94519388F68DCB4B8942D6131304735D50938A3BAFA4
        D3544D1DEABCE827B8B713AFEF6ED9794A5E1ABF58BF6F4CDA403C4131251AAC
        19962B914BDEEC5E47479E16C81376D7DC5AD876F1DCC8F9290A14C11A6A8FB6
        55B5559939A3B9BB0FD6C5D19397E5A212457C0F51802507F1304B9E8FF5BB4F
        E7FE2D4BD6ED97E8D8D814B976AD806589011B6E6E5841F97385D93FA9B88463
        CD96233263E94ED9BAEF8C2BD980C504C0A805DAF7A907F49ED2FCB9ADDB80FE
        C256A563A7AFC8D4EF377BCC3085F362AF70FF67EA48313569C0842C2CA37509
        3AD3FB5056F4915357E48725DBF5FE56780320A498D4756A5A5E6FB9C173B35B
        C2CD5B3E9DFD97AE939B16F60093B40DC594687496A19A4575742D885122121D
        15ABC504168C91524D67C871DED993696004C938DCD5448CEF61151965D18CEF
        B1B6AABFDCDF63B0FA6CCE5F29DA76E06A5BAC8EBE6CD9A094BA87625AA07C75
        C9A1C837F6A92E5196ECB28D077540544A226ABD21D6ED422F9C378B3C5AA784
        B4A85F4A894F569FEFFFD6ED6825729765C5E643B2FACF237AFD1ACF24B9F551
        4C9CD05F9F8F6AAD272070B3A23D4E1DCCA49FB2B6D6F00FB2FF640C0D910865
        F12205E09F3B4F5A9E1FA2070145851F9C1713074C78F02EC5BABD1E46BD58BC
        3977DE19D77B80490EFA1CD56ABE9CB755DEFEF2772D623807DCF0983419D781
        87213AD6655DC79DD76D79C67F371DEE7FC77F1F8D823777DECD3BEFA8F16E62
        0285F6BF3066A19AEC9DF06A2B14F9DF86624A3418EC60E5DD5FB180CE738B81
        1A0203B7217EC6001CEB5E678CD55FB171AE5D10A807A1807822293AB51C0625
        FD1514A02D9A607CA98109555542828324347D906CDE7652AF0DDA49A717ED4E
        41081775E5D279F45A1DDCD4A8DA82AD13B826AE1FEB5E2785C575F6C2756505
        5DD696E8F6036765DFD18BBA3418521BE25E521B0881DE22940151B839A5E27D
        79749BE1BA847700C2823E748A2B480ACF034150FB8F85CB893357659B6AF381
        E317E5C6CD482D4CDE4E20F01CE16A47559C9BEA395FBC7253AEDF8CD2DB6A20
        2010A2A0C0406DD9220B12DC9F59C2D2E96028ACC55AB93B216AB0BAEB5429AC
        C5194169787F2222A3F4642D3ADAB5DE19A3263F103C2DA05AB85CEF03D655F1
        F758073F79F6AAEC529303FC1ECF0CCF130147376E45C6BD9378476F47A2DD77
        DE494C06707E2358CB2594AE77316E1287EBBAF7E0E21E83742A44D7FD62F200
        318788A34F61EDBB2A11A5FAEB40FE9F4331257160908D8A57C22CE14CDE3A52
        373E095E26A733C1CF4E93B52B632FABBFF2D21A62A9CBA085046A3180C50711
        87B5650457C1B281A06260C600AF73CB0638EE495D51639D116D4754310425BD
        6A7B90D12FCE3B0161486B071181B567A7CDB8268433EE191BCF3CFE31EE8716
        EBB626130771999F17EEF7E8B8C41B89DF1FEB685AD7BB6258C7B05213AF99E2
        39E9763AE259B5C99C3BC9758CEFE22F9FC6FB3EBE758B6F98A481780BC594FC
        D78281510F8A7183A5CBB9286254A791B45794FBFF619B09211453420821C436
        1453420821C4261453420821C4261453420821C4261453420821C42614534208
        21C4261453420821C4261453420821C4261453420821C4261453420821C42614
        53420821C4261453420821C4261453420821C4261453420821C4261453420821
        C4261453420821C4261453420821C4261453420821C4261453420821C4261453
        420821C4261453425219FC1FCC71AF1B4108495528A624C5C4C63AB54AB884C2
        2D178955C399F00727FEC4E1505FFE6D8BD3E93AB7C7F638137EE3EFB6A03F62
        D549F15FDD1EF559803EBF23AE8DF85D4080C3F5E5FE9DDDEBE33ACE04CF22D1
        8D3B2CFEC8E4076792DF4982F3E853A1CD7EEAAF04E7356B6C7217727AFE85D3
        E438F43D21FE86624A520404207DBA20898D714A744CACC4A8813146FDD7EC65
        826860000B0A0C90E0E040898888D6A2E34F70FE742181AA2DAA1DD1688FAB4D
        9A78A6218E0BD45F0112A2DA12A58E8D8C8E49B138E0D4D1EAEF41E68CE92557
        B60C52B44056299A3FABFE3E9DBA465060A0BE5FF4D3E56BB7E5C8A9CB72F0F8
        25397FE986845FB9A5FB2D3828204E747D2548FD6D3A7D2F4E7DDFB1EE7B87C0
        26D1CCF81A8BE7E2B833A1409F24147A89FB03E39C915131BACFF073A07A9EF8
        9B94341BE70F4D1FACEF5DBF3BBADDAEC988B82746BEBC21F145DE68BF712F0E
        F7F781EABFE8911BB7A252F8B409B186624A7C06835EA60C2132F2A507254F8E
        8C72E9CA6DB9793B4A6E4544A9C1510D8C8605A606AFC040978862E00C537F93
        27472699F6C36659B9F99016337F8001BE69DD92F27CFBEA72E57A845CBF11A1
        DA132D1191512E7175B705ED80E066506DC9101A2C057285C994EF36C9AF1B0E
        A8CF837CBAA64B446325BDFABB2A65F24ABDAA85A56685FC52345F36C9A8CE9D
        9CC0DC8E8C96F3176FC8965DA765FD3FC764FDD6E3AAEDB77D16D52825E4B8F6
        C067EB6961BEA98402E7BEAD262CF81DEEDD102908548021A0EEC98DF1856791
        4E4D8E703FE8A3603501080A7289903356545F46CB4DF57C2F5CBE29E1976FC9
        89B357E59F3D67E4D0898B5A9C7C693704341FFABE5F13D53691EB3723749BF1
        1C23A36275BB6313B55BF779026BDF35A1837C1A93017D4FEA0BF7A2EF273848
        424202F54423443FF7103979EEAABC3C7E893E2FED53E24F28A6C4670C319D3E
        A8B9542D9BCFE7BF5FFAFB01E9376599B66CECE2B2609C32B14F632DA8BED2EF
        DD65B270DD3E2D22DE020B13D66D836A45E5C99615A54AE97C5A80CC80150720
        369EFA73CF910BF2DDE26DB26CC3412D2C415EF60D04E8A19A4565FAE016B6FB
        D2573081DA77245C66ADDC25CB371E54A218A9EE33F90912FA0F13996FC7B795
        DCD933DDD5361F3F73455ABFF693EE737F2F3590FF6D28A62445C01AC8933DA3
        64CF12AABF4A17CD29154BE692FB2B14D4569F27603D3E35648E1C3C71C96BD1
        B0020373917C59E4FB098F4BD6B0F41E8FC560BF6DDF59D979E89C6C5556D5F9
        4B37E5B8B2B06EDE8AF4DAAA8A50E255286F66E9D3A5B6347EA07812F18055B5
        FDC079D9A02CCD7FF79D911BEA9AF83F18ACF24AA5F248DD2A85F47FE11E4D0C
        26066BB61C9677BFDD28078E5FD4965572E06F42D3074991BC59247FEECC5255
        59C9658AE5940A25736B0BDC1B20C8DAB3A0BEA2DD567CA89A5C84650CD16EF9
        E4DBE094AD7BCFC814D5EE3F779ED2566172FD89C908ACD36C9943B54BBC9A9A
        94D5AA5040DD43984FCFDF576099B6EEFDA3F658504C893FA198921403775DAC
        D31D58E3769BBDD4A9A6F4EE5C2BD9BF9D3EE34F99FED31FB65DBDB0E27AB6AD
        267DBBD7F1DC56D5D0911FAE96392B77BBAD12977B3028D0E19390D6AF5A5806
        3F575F0B40620E2A019CF6E36659FFCF71B9E11668E3D4103DF451A6D01025C2
        25741FE5CB656E951D53D6D3F0E9ABE48F1DA7BCEA1F9C3B3A26C665A5AB7F05
        29816F5CBBB8BCDDA791A5A5887E7BEFC73F64FFD170EDA6457B6F4544EB678A
        76633D3C4BA67492376726ED46AE5BB990E45293274F5C531387495FAD97D92B
        76EB75DCE47A156E721D3CE574B9E2CBAA49C0947E4DA55881AC967FF3F582AD
        BA5F82E22C7DA7F13FB73BD8359C0538022463866035B92B20CDEA968C73E39F
        B9705DDAF59DA12756015453E24728A6C46FC0A559BA680EF9E1ADC793759B1E
        5256E95343E7CA5565A5A634BA12A2985E59659F8D682D95EECBE3F158ACF175
        1E385B2E5FBD9522F73284F4512582235F6CA8ADA9C46CDA7642864D5FADDD88
        589FB31AA821A8119131BABD135F6FA484239BE97117AFDC92D7272D953F94A5
        97CEC70907AC2E58AB5F8C6C2D152DFA25FCF24DE9D47F9616EE20F77A275A6C
        B4DA10661DB3A43E84E5DBB5652569F74859094D676DF1E21D18FBC95A99B562
        97572EDFF840D4C7BEFCB0746A5ADEF218AC77628DDBDB490678534DB47AB4AD
        AABFBF7049DDF7809972FEE24D46F512BF4231257E03D645CEACA1B2705A17BD
        A69A1C83A6AD9479AB76FB1CFC6300F76483EA45E4A3A12D933D76FFB1707942
        89474ADC7BFA3AD58AC85BAF3592AC9993BA92119DFBC2D88572FCF455AF2D6D
        887395D279E5FD41CD25479650D3638E9CBC2CBDC62F76099E0F130088604040
        80BC37B099B62ACD3875FE9A74579399D3CA52F3E6DC70A783560D4BC9D09E0D
        7590951508A47AEDEDA5DAE5EB69AD38310860EBD3B5B6BCD4B1A6E5312F8E5D
        24EBFE3AEA753FEBF5D9DC99E587098F4B0EF56E229A1A93B8C36A32E78F357B
        420C28A6C46FC052CC9C299D12D3CEA6D65B6236FE7B5C5E99B044A2D4809712
        971B06CA49AF3F2ACDEA251F78B4FBD079E9D86FA6CF0328AE51304F66F96478
        2B29ACAC33335212C4041021DBF3F1EAF246B7072C8F59B1F9903AFF72BD15C5
        5B77B4D3BDE1766AFFA63A38C98CA3A72FCB33C3E7EB88626FFB04A7C5C40241
        57837BD4F7D89E1D07CEC90B6316C9B51BDE7B1E10810C217DADABF53201DABC
        79FB099F9607E04E1ED5EB4179BC51396DFDF61CBD40FEDD7BD627A127243928
        A6C46F18623A6FCA1392335B063D38C25AB5B262B0B7F0F9518B64E3B6E33EAF
        9D6A9772911CF2E598C7F4DA1ED6FAF019D6FACCC0E0DEA9FF4C9F5C8FC61ADC
        F8DE8DA445FDFB4C8FD9BCFDA4BCACAC47EC55F5754280BEC9AE2C5D044F41B0
        4DFB543562E0D415B24889B5B77D64ACCF4E79B38934AA5DDCF418047FF51831
        5F6FA709F4C1DD69ECFF9CDCF751BD2EEB89B7BEF85DBE5AB0D5EB4906DE9717
        3BD4903E4FD6B63CA6DB9039F2D7AED33EBD2F980034AC5E443E1CDA52BFA3AF
        4DFC45566E3EECB7AD5984008A29F11B71623A558969D60C7236FCBAACF9F388
        746C52C1D2B5BAE4F7FDD27FCA726D1DF92245182061D13DD7AE9AFE19D74192
        84F225739B1E8F68D3AE8366FB24A6B8C623B58AC9D47E4D2DADB7511FAD911F
        97EEF0D92A3580BB77508F7AF254CBCA96C720F2186E6404087923D8103C4C2E
        262B316D52A784E931078E5D946747CE974B576FFB24A646BF542D934F3E1BD9
        CAE3FAE98EFDE7E439650562EFAB37D629C4B4E7E3D5A4EF53D6C1645D07CD91
        7FF6242FA6C67A29BA0BEF252293BF1CFD98945213B0319FAC95EF176FB79C78
        11921228A6C46F60D08295387F5A67657185EA0DFE7D262D9521CF35D0919A66
        C00D08D7DDEEC317BC76BBC1A2C3B69CEFC6B7D3D1A67097BEFECEAFF24C9BAA
        52B37C7ED3BFF1554C758203D59C8F86B5D25B36CC8010751E304B4E9EBF6ABA
        D5C51B204CF5AB15968FD575ACDBE2D46BA76BB778BF56084B19D663B3BAE616
        F5DE23E1F2DCA8057A0DD15731D596AF7A06EF0F6EAE2D3ECBE3D43F5897DDB2
        D33B4B1211C6CFB5ADA60386AC407FFFBBEF6CB2E733B27119199AF0CE94299A
        437264C920474E5F9653E7AE310089F8158A29F11B5A4CC3D2C982695D245B58
        7A1D31DA45591258B743861E2BBE5EF8AF76097A1BB50A017ABA4D15E9FF745D
        FD33B20721F2F5D3E1ADA472E9BCA67F03D7E05343E7782DA6B846AD4A05E4A3
        212D2D03A4B076877541578EDF94F5992B40264CBE1AD356F2E5B44E603073F9
        2E19F1C16AEFC534CA2DA6F5CCC574D7A1F3D273D4429FD634E383094CA72615
        74162C4F4CFE66837C3EF71FAFC5F4D9C7AAC63DD7C44010BB0C9CA55DF6C93D
        C7E71FAF2E85F26691194B77E889142296B10C8089892B0D228594F8178A29F1
        1B105344BB2E7EAFAB76AB613DEEA92173F51E466C97C99FCB7C433EF6FEE1B8
        D317AE251B0CA35D7619D2C917A3DBE86D38E00D6595620DEC9B716DA57229F3
        AD20882C7D7AD85CAFC51403EF1BDD6A4B8FB6D52C8F81484CF96EA3ADC41346
        72FEAF463FA6132E58E1ABF8414C27BDF1A8E55A2F04E9F9D10B5DFB2D53202C
        08EA295938BBCC98D8C132FB1358F2DB7EE93B7999C7630C9213535CB3CBA0D9
        B2F3A0B598C22245E2876FC7B593DCD9334A9F894BE5D78D077DDE5E4488AF50
        4C89DF80E5903B5B06EDE645720288E933C3E6E95479FDBAD7D191AB56C082F9
        6CCEDFC96E938145D4BE713919F3F2C3FA6788CCD3EA1A10D9CF47B5F18B98C2
        7A41E69F6FC6B69572C573591E37F4FD557A3F654AD74B0D20224887D8FAC1D2
        96C7204311F685624B479017EE709C1391CED8CA62C6F6FD67B598DEF0723D33
        3178D6F03E7CA92635250A65B73C0EF97B91EDCA9B88E1E4C4141304882922B3
        AD9EA3DE0F5CBBB8FC6740337DFC4BE316CBA66DC77DDEF34A88AF504C89DFC0
        009B3F572699F3EE133A82578BE9F079B2EF68B80EFCF8664C5BD37D9A0022D1
        2D99240E3A4943BA20F964582B9D5C1E8CD6C124DB74C596CF46B6F68B98C2BA
        295A209BFCA8AC69ABFDB2684B2F3550AFFBDBFB754C2B90C4E1A54E3592CD1C
        F5DCC805B2E15FEF229F931353A4557C614CCAC5D495692940A629D1AA5BA5B0
        E57178F6F03A20497E72C153C9892926525836D87338A9981A65E8E051C07EE0
        360F95D6F7F6FCE805B295DB60C85D80624AFC0644A850BE2C32EB9D8E3A2FAC
        21A6C87684C177C40B0F4AC726D6D96D467CB8467EFE75A7A54B108369933A25
        F5FE49806409B04A91D5065569FC25A691EE6C478886B55A5BD3FB15472DD0C1
        3076076A5CAFCD43656442EF473C1E374C59C2B357EE4E2362EADADA34E9F5C6
        96EBB2E0D0C94BD27DC83C9DC821B9EB2427A6C87BDCB1DF2CEDE64DEC5AC7B9
        F11C1EA85448BBB73199BB7A23429E1D3E5F7B46ECE68026243928A6C46F404C
        8B15CC263326B6D75B26128B69A5FBF26AC1B3DA770A617A61F442532BC6C8EA
        337D7073A953B990FEECFD1FFF90E933FE7097DC0AF29B98628B46F7D6956550
        8FFA96C7200A16F7B6FFD845DB0335C4B45EB5C2DAE2F60482B410ACE5CDFA5F
        6A8BA9D14F9800B47DA4ACE5312E319DAB8B1BD81553BC03CB361E5293A71BDA
        128D8DBD53922D345D905E2B459A46C39BA0B31DA96B1F3EC96C4724F5A19812
        BF81C8D45285DDB979D5E0165F4C21387003A38665A35AE69BFD3158BEF9EE32
        59F2DB8124D629040722FAF1B0967A6044EEDA2787CC9163A7AF68EBD19F628A
        EA29481CE029AD1DB6FDC02A3EAAAC63BB03352CAE4AA5F26AB7B227267FB351
        3E9BFB779A1153ACE38E7BF561E9D0D8DADB80348EDDE0E6BD6DDFCDEB2B97AE
        DE926E83E7EA6C4F145392DA504C89DF8098623FE9B7E3DBE9A09CC4626AECA9
        FC70484BCB011CA5CB5E796B495CF592F8E7C6560FB879C18C5F77CA988FD74A
        205CAC4A84FD2DA6037BD4D3FB56ADF0B798962B964B664EEEE8F1B8099FFF26
        DF2CDA9666C414FD345E59A648D36705029D9E1C3C4774196F2F0AA6FB5D4C95
        90FBE31911921C1453E237B075A1E27DB9F59E49589610D36795981A754BF51E
        BF8000F960480BA95DA9A0E93960BDC2D51B3FD006090890141ED561B0168B41
        FC69755E63BF21CE8B286044F356B4C880E4AB9B1765D69E6A659D9508033592
        4DA0EEA85D372FC4B4AC12D359C988E9B00F56CBECE5BBD2C49A2940E0D45B7D
        1A491B0F51C8ABFF3C22BDC62DF2AA988137620A57F7E19397B537C295EDD1A9
        D76F03031D92352C541E50EF55D37A25F533B972EDB67457131E7F3C23429283
        624AFC062229B157F20B256A18F0CD04074144085879F7CD2696E759B1E9A0BC
        F1CEB2B87AA0F1139583A5EB0FC880A9CBC5B0760C3145BAB8F225CCB7B2F822
        A6704922C90406762BB0DF131984761C386F3B0009628A52693FBDDDDEE371BE
        544CB91BD1BCE87F3C47A45CB402DB9D267FBBD16B6BBA87EAF37E1EC4B47DDF
        9F751206B33E4093509FF6BD41CDE5C11A45F51EDA1E23E7CBCE83E729A624D5
        A19812BF0131453A3F64220AD6627A5B9E1D315F17A036F6462268244368B0AE
        C262558314828B6D207FED3EAD077AACC37E35E6319DF717AEE297272C91F5FF
        1C8B1B50FD2DA62805F6EA13B5E495CEF75B1E03ABECC5B10B75A27BBB5B6370
        4FF7572CA0133758F6AD3AA643BF993AE0C91BF14E6D31C57344CDD40F06B794
        EAE5F2591ED7FBEDA57A72E4D50420225AE75AB6934E10EFCE63888C7EAD91CE
        658C7B44F62B6E8D21A90DC594F80D585870DF7E34B4951EBC104D0931DD7724
        3C41A2010851E7661564F80B0D2DCF357FCD5E193C6D85DE40D8FF99BAD2BD75
        15FD3936E0F71AB744BB838D35387F8B29066424E71F954CAABCD7DEFE459621
        BB8ECDA40D7A2B4E9D123AA1BE15D80684F567ACD57A930738D59336C4C4EA0C
        43C88F9CCF22B3D5F94B37F49A250AB37B6319BA12DD5797BE4F5997A44B4E4C
        31A12B573CA79E7C21080E7B817FFBFB182BC4905487624AFC06C414C5A8A70F
        6EE15AB3BA1EA1CB7C254E62AFD30E86A597AFC73D26C5F267333D17F6081AA9
        0891B22EBBBB80362ACC242E47E66F31C57D207218F7E169101EFBE93A9D30C2
        1F62DAA5594519FA7C03CB63966F3C246FBCB3546F0FF2260F7072628ABD9A48
        4F98D2748210AD0A2573CB8F6F3F6E19A5BB62D3219DEAD170D727DB665892ED
        ABCBEBDD522EA6283D87EC5BDF4F6827C50A64D3D1E18BD5FB62F71911921C14
        53E237200A58AB7A6F60331D3D09418498EE3A94B4220C8EC5C0F95A57EBDA95
        3F2DDDA137FBBFD0BE86FE79EF910BD27DE8BC24FB50FD2DA6107B94739B3DB9
        9365C626F0C32FDB65C267BFD98E1485258C3DAD9E029E10C98B3DA6DEA62E84
        F5FFCE1B8DA545037331DDA3263858F3C584272549DF21D6DD5B55D1E5E3AC80
        90FEB2FE80D77971BDA967EA4DD5183C3F447DE7C991512F0760CD9ED1BC24B5
        A19812BF01814431EA29A8FFA9066858953D462C90ED07CE261131B809E11EFC
        765C5B35E899574B81202018289B5BD0267C8EA405498B4D1B62FAF598C7A46C
        71FB626A54168165FA8045D43140200C02AC62E3B99C53DA6F584386556F06A2
        A2513EEEE4D9AB5E8B42725563B0F6DA2385F54C758170F52FF40FB63A99F68D
        AEC1BA48475E7B6BF9424C5FEA58C3E304CBDB126C4685187848E25F1F831DD6
        9F41E2DF1162078A29F11B18C0518C7A72DF267A9042200F0289203A662286E3
        116CE2296AD600EB6EB04ACF5DBC9E44500C3145D5983245CDEBA6FA5A35066D
        43C5184FEB77C823DC75F01C396223C30ED67E51481D6B7C45F265313D66CECA
        DD32E28335BA4FBD15EDE4C4F4E0F14B7A3DFBE2D55B3E8B2984AA6CF19CDA13
        106692BB18930BB8571175EDCB5A25C4B457A79AD2BB8B758E626FC5D40C5DC0
        403DFFCECD2A4A91FC5964C5C643F2FBD6638CF4257E81624AFC06067094FC9A
        F87A63BD4E0657604F44E5EE392D2126228641B974911CF2E598369225537A8F
        E7FE74F65FF22EB65898B839B14E16AAC5B45D5C59B6C4F82AA6481251B25076
        2D7258DFB5622C12ED2FD99EE23539F41982B6B087D6CC4A4244EA9D0989F783
        7E72628A147B10D30B977D1753546619F46C3D4BB7F492DFF7CBE0F756E9C4F3
        BE58ECB8D7579FA829AF744E1D3145BB1BA3A24CFFA6FAFD8465BE69DB095694
        217E81624AFC06062B6CE047D50E00B14432F83F76586F1FC11E526C63B00A94
        0158D7EBA62CC04316E5C752434C75DB94A08EE9F590C7DCB31BFF3D2EAF4C58
        A28F75A4C0D70B5736A2959F6953C5F4F73F2F43A6A7753A2981B73875BFC668
        0F41D3BA254D8F3976E68A2E8F77EEE20D9FAC6A88748512B975B6296C554A0C
        72F1BE3476B19C3CE75D046F7C20A6BD3BDF2F2F3F61BD2529A5628AA4FC9933
        A4934F46B492F2AAFD48F881002C2C45D0D54BFC01C594F80D08C3E38DCACAD8
        571E8EFB0CFBFCD6FD7DCC3208058373CD0A05B465666579CD5BB547864D5F65
        19C9AAC5345DB07C3FBE9D2E586DC61625A6DD7D14534C06503AEE8B51AD255B
        E650D363E0D2ECFDF62FB272F3219FAD53EDE2CD12AAB79714C89339C9EF8F9E
        BA223D472F90D3E7932F9A1E1FA3A20B122AA0FA8D19A7D439E1363FE3454176
        034C18C232A69329EABC6619ACB0FEDAF79D5F65D3F61329B21C21A6AF75A9A5
        5DBD56A4544CF19E21B0E979774DDDCFE7FE2DEF7CBD8151BEC46F504C89DF70
        EDCF2C2FA35E7A28EEB357DFFA456FDAB71AB4B08E058BEEFD41CD4D037060ED
        C255BC65F72953573180986650628A04FBC50B9A6FB5419282CE0367F9ECD2C3
        3D3DDDA6AA0C78C63A2BCF8E83E7750A44441EFB628D61F281F54104DD240681
        5758775CFDC711CB927456404CD1279E8A0AF8BA0714291D332B211DF25C7D69
        D53069FA40EC291E3C6DA5ACFAF3708A8BA5434CFB74AD6DDA1F062911532C37
        34AC5644A60E68A6ABCB60EB13ACD23F779EA48B97F80D8A29F11B180C9F4E54
        BA6CC0D415327FCD1E8F032C4405814B469DD2F820B7EB1B93966A71B072A31A
        9629EAA816CA9BD9F498BD47C2A553FF995A687CF1C6C2F284D80C7FB1A1CEAC
        63C58C5F77E8686344292767E9E1FF709118E06B14D5AED8C425E960458DFBF4
        3799B97C678A036D90D80169F5EA5629647A0CC4AFCBC0D9BAA24A506060923E
        71BA12DF2A6BD4A9CF779FB2F8FB3E55471A542F92E45C10E4911FAD91F5FF1C
        F759F8E38309C4D09E0D3C6E11EAD41F627AC6BB7E71BADDD2F7E5D6567AE1BC
        AE002F64E442217A6F2AD910E22D1453621B080E5C8060FCAB8FC8630FDF119D
        0F7EFE53A67EB749BB7031C03B10916AF2F728EE8DF26A48686F0057E5EB937E
        D59BFFCD064F88688C1AEC6169601D0CEE52AB5AA9E1976FEAA4E7FBD4408A73
        05EAC858EF0652B86333A9F30E7BBEA134AF6F5D081BE237F5BBCD72F1CA4DF7
        B68B846E6908145CC7D0DA4794C538A4677DC9952D6382732089C2A4AF37C8EC
        15BB7C6AA3717E8839ACC86205B2CAD763DA4ADE9CE6DB8E2024D8038CFDA6B1
        827E34F2EDBA262D9810601DBA58C1ACDABA45F172441D2766DDDF47E59DAF36
        E8BD9C29137ED7F3C733CC9C29445714AA5E2EBFE5F1089AD2C5C16151BA05DF
        14750F41AAFF6B94CF27BD3BD79222F9B3C6FDEAEB05FFCAA4AFD69BAEBF1392
        5228A624C560E046F006DC7F280ADEA05A11E9D6B25202972EEA8E7E397FAB6C
        DD735A8E9CBE2257AFDF562228492248619D3ED1B4828C78F14E8A4144B02292
        15036D7C51C1E00B45866BB770BE2C52425DBB4393F252AD4C3E8FED4520D4EC
        15BB758D4D04C8DCBA1DAD3FF7260005C28EEBBDD4A9A6746D5ED1D23D88C016
        040DE15A672F5C775976E2D4F70BEBBC54D19CD2EE9132D2A27EA924E273E2CC
        15795B0DF22BFF382CC126D6A215B1EE7D9FA1CA2AC4DA2BB607B551139ADA15
        0B7AFCBB33E1D7E56CF80D397DE19A9CBF785307E30054E6C9A744B8A812209C
        0F3F27E6C4D92BEAB9FE2B0BD6ECD15BA060DDFA82D3FDFE602D3D6FCE306DF9
        22A562F37AF779FCBBD3AA4FE1B675B84FE28C3B5B421CBA6078B064CF923EC1
        B3C2355F9BB854F7B1B7C92408F1068A29F119C355DAB5454579E4FEE23A472B
        B2CD785A7F82BBEDFCA59B72EED20D59F2DB7E99B174470211BB9362B0AD1473
        5B1143A7AFD6165AFC410FC2FA50CD62F2648B4A9207D75583BED960EF896BCA
        FA3BA74404796EDFFFE90FF97BF729AF3323C11A7EA866519D95A98245B937FC
        1FEA82BA4FB83FE14E85A0A28DE8A78279C2F4201F1F4C247EDD70403EFC798B
        76BBFA62E1C12380E8DA979FA829797364D29628828452030811923DFCB27EBF
        2C5ABB4F4E29610B4E41E203FDAC33A7D76EE3FB0A6597BCB93249B6B0505B89
        2FBCE58C6A335CC5A868C4285EE24F28A6C4678CA021EC6384BB12AE4B04EA20
        B34C74AC6B8D4DAF71AA7F3060E10B6E5E047F40B4B0991F3976130F6610DC67
        DB56D51197FB8F5E5416C42F3A3142FCE3B02EFB72BC8DFDF81B7D5D35D0C7B8
        C54E8B5EACEBB5C6000D772BCE01EB10833F2ADA188235E83F2B64EEAA3D3A29
        BA77F78E609C685D3BF3C1EA4574300E521866094BEFD5DF1BA07D672EDC90CD
        3B4EC8FCD57B74851C7CE66B75934863EFE48066FA67F403C419930E885F0CFA
        23C6D51FBA0FD4FDA34C19DCD070BB070507B85CD289940CCF14962AB6252151
        C6969DA7F5A403E5CC2044FAEF5398EC006D2C94378BCC9CD441326508D16D83
        6B1ADBA4F0BDF11C9DF19EA7EB618A7B89E04EF20AFCD795FBD7F519DEB9C080
        3BEF9DF1DCD15E1CB3544D5AFA4D5EC6F482C4EF504C498A4109358808AC2F64
        AF89888AD603A21E0C6363E3D6DEF015A24402EB99102164DDD9B1FF9C49D08B
        538B1C2CD4DB4A1050DC39B1E0E2DCC50B64D3AEDDEB6AB0C775311043545CD7
        8E75096B8CEBB54E2C20704143D0D387046AF734C4E124B69EA4C0BA82E020E0
        069674A55279A4B8B2B2908402E91121CE81EE8C45680BACD3EB3723F4FE4E58
        77FB8E5E909D07CEEB6D2F4E750CDA94123B09EDC89D23A35429955757808988
        8CD27D0757A8D127E80F881204D39848C0DAC7F7703DA7777F869FF10C10418D
        35D5F0CBB7F45A33A29471AFC01F29F8B44B5A59EAF75728A005F396BBADB806
        F6C746B99F23FA2D468B6BACCBDC77489C606AF1C4474A13031C6893E8FBBBF3
        BC5D93054C4ED0B7784E98CC1D387E490E9EB8C8C023E27728A624C5C0FAC138
        8781CCE1361BF4109528EAC679E75B3DA8072238C4C202338EC119AC066D585C
        469204D7A5E2592A89AF6F9C545CE3B111A56AE49745204B4A12BDC7C7B08AB5
        E5EB1EB8B1BE8A440B68237E1F1515AB44232A4E305C85ACFD931B36C61DC013
        273071569A1BF7E7CEF8CFC369F487335E1C8FF1A45C7F6F88536AB843B5851F
        151D772DD3E768F62CCD4E647C6BF2B133C1B3774566337D20490D28A684F811
        2DD26EA5BA234D62EAA22484FCF74031258410426C4231258410426C42312584
        10426C4231258410426C4231258410426C4231258410426C4231258410426C42
        31258410426C4231258410426C4231258410426C4231258410426C4231258410
        426C4231258410426C4231258410426C4231258410426C4231258410426C4231
        258410426C4231258410426C4231258410426C4231258410426C423125841042
        6C4231258410426C4231258410426C4231258410426C4231258410426C423125
        8410426C4231258410426C4231258410426C4231258410426C4231258410426C
        4231258410426C4231258410426C4231258410426C4231258410426C42312584
        10426C4231258410426C4231258410426C4231258410426C4231258410426C42
        31258410426CE11047A5F61FDE763824DDBD6E0A218410F2FF11A738A36199FE
        E90808ACE18C8DB9D7ED21841042FE5FA1F4539C4EE71647E5F6D39F09080CF9
        22D6A9C4D4498F2F218410E2150E87FA5FA0C4C6443FE7E8D0E1E7C07DCEF3EF
        3902435E82983A9DB450092184104FC022053131D11F85640FECEDC00FD59FFF
        3838FA62F4932201AF2A39ADE8703882EE754309218490B448ACD3192DE2DCEE
        7438DE8F95B3DFED9A392AF2FF003108E4ECCBBB37A10000000049454E44AE42
        6082}
      Stretch = True
    end
    object localTest: TAdvSmoothButton
      Left = 125
      Top = 178
      Width = 150
      Height = 40
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -11
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'MSA'
      Color = clWhite
      ParentFont = False
      TabOrder = 0
      Version = '2.1.1.5'
      OnClick = localTestClick
      TMSStyle = 8
    end
    object localCali: TAdvSmoothButton
      Left = 325
      Top = 178
      Width = 150
      Height = 40
      Appearance.GlowPercentage = 50
      Appearance.PictureAlignment = taCenter
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -13
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'CALIBRATION'
      Color = clWhite
      ParentFont = False
      TabOrder = 1
      Version = '2.1.1.5'
      OnClick = localCaliClick
      TMSStyle = 8
    end
  end
  object GroupBox3: TGroupBox
    Left = 723
    Top = 737
    Width = 474
    Height = 185
    Caption = 'GroupBox3'
    TabOrder = 6
    object pdev1: TPanel
      Left = 15
      Top = 56
      Width = 65
      Height = 25
      BevelOuter = bvNone
      Caption = 'IR1'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 0
      Visible = False
    end
    object pdev2: TPanel
      Left = 86
      Top = 56
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'IR2'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 1
      Visible = False
    end
    object pdev3: TPanel
      Left = 122
      Top = 56
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'IR3'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 2
      Visible = False
    end
    object pdev4: TPanel
      Left = 154
      Top = 56
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'IR4'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 3
      Visible = False
    end
    object pdev5: TPanel
      Left = 15
      Top = 25
      Width = 65
      Height = 25
      BevelOuter = bvNone
      Caption = 'OCV1'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 4
      Visible = False
    end
    object pdev6: TPanel
      Left = 86
      Top = 25
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'OCV2'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 5
      Visible = False
    end
    object pdev7: TPanel
      Left = 122
      Top = 25
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'OCV3'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 6
      Visible = False
    end
    object pdev8: TPanel
      Left = 158
      Top = 25
      Width = 30
      Height = 25
      BevelOuter = bvNone
      Caption = 'OCV4'
      Color = 16771289
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentBackground = False
      ParentFont = False
      TabOrder = 7
      Visible = False
    end
    object clrConInfo: TPanel
      Left = 282
      Top = 112
      Width = 185
      Height = 41
      Caption = 'clrConInfo'
      Color = 12353126
      TabOrder = 8
      Visible = False
    end
    object pon: TPanel
      Left = 282
      Top = 18
      Width = 185
      Height = 41
      Caption = 'pon'
      Color = clLime
      ParentBackground = False
      TabOrder = 9
      Visible = False
    end
    object poff: TPanel
      Left = 282
      Top = 65
      Width = 185
      Height = 41
      Caption = 'Panel59'
      Color = clWhite
      ParentBackground = False
      TabOrder = 10
      Visible = False
    end
    object GroupBox2: TGroupBox
      Left = 30
      Top = 87
      Width = 227
      Height = 87
      Caption = '????? ??? ?? ??'
      Color = 16777088
      ParentBackground = False
      ParentColor = False
      TabOrder = 11
      Visible = False
      object pnormal2: TPanel
        Left = 90
        Top = 41
        Width = 41
        Height = 19
        Caption = '??'
        Color = 16770815
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
        Visible = False
      end
      object pnormal1: TPanel
        Left = 30
        Top = 43
        Width = 54
        Height = 15
        Caption = '??1'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 0
        Visible = False
      end
      object p0: TPanel
        Left = 146
        Top = 36
        Width = 41
        Height = 19
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'READY'
        Color = 8454016
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -12
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
    end
  end
  object GrpAlarm: TGroupBox
    Left = 1342
    Top = 10
    Width = 404
    Height = 300
    Caption = 'STAGE ALARM'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Visible = False
    object Image3: TImage
      Left = 30
      Top = 26
      Width = 346
      Height = 265
      Picture.Data = {
        0A544A504547496D61676546150100FFD8FFE0E4CA4A4658580013A07AFAF0EE
        EF8E89EA5047E94940E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A
        41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E9
        4A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41
        E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A
        41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E9
        4A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41
        E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A
        41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E9
        4A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41
        E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A
        41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E9
        4A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41
        E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A
        41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E94A41E9
        4A41E94A41E94A41E94A41E94A41E94A41E84941E95048EF8A86FBEFECF29A95
        E73026E73027E63226E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E63125E63025E63125F0918BEB5F59
        E53129E82F28E63227E73228E73228E73228E73228E73228E73228E73228E732
        28E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E7
        3228E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228
        E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E732
        28E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E7
        3228E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228
        E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E732
        28E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E7
        3228E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228
        E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E732
        28E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E7
        3228E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228
        E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E732
        28E73228E73228E73228E73228E73228E73228E73228E73228E73228E73228E7
        3228E73228E73228E73228E73228E73228E73029E63026E53225EA524BEB5A51
        E73026E73027E73127E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E73127E73128E83127E9463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E73128E63127E63127E63127E73126E73127E73127E73127E73127E731
        27E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E7
        3127E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127
        E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E731
        27E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E7
        3127E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127
        E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E731
        27E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E7
        3127E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127
        E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E731
        27E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E7
        3127E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127
        E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E731
        27E73127E73127E73127E73127E73127E73127E73127E73127E73127E73127E7
        3127E73127E73127E63127E73128E73128E73127E83228E83228EA463DEC5A52
        E73127E83128E73027E63024E63027E63129E83129E83129E83129E83129E831
        29E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E8
        3129E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129
        E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E831
        29E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E8
        3129E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129
        E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E831
        29E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E8
        3129E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129
        E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E831
        29E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E8
        3129E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129
        E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E831
        29E83129E83129E83129E83129E83129E83129E83129E83129E83129E83129E8
        3129E83129E83129E63027E83025E63125E63127E83228E83228EA463DEC5A52
        E73127E83128E53127E33227E82F26E53125E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227
        E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E732
        27E73227E73227E73227E73227E73227E73227E73227E73227E73227E73227E7
        3227E73227E73227E63027E73029E53128E63127E83228E83228EA463DEC5A52
        E73127E83128E63730EE7169ED807BED807BEF807CEF807CEF807CEF807CEF80
        7CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF
        807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807C
        EF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF80
        7CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF
        807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807C
        EF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF80
        7CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF
        807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807C
        EF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF80
        7CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF
        807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807C
        EF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF80
        7CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF807CEF
        807CEF807CEF807CEE7F7BED7E77E94B42E73026E83228E83228EA463DEC5A52
        E73127E83128E43226E43427E63428E73429E7342AE7342AE7342AE7342AE734
        2AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7
        342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342A
        E7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE734
        2AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7
        342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342A
        E7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE734
        2AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7
        342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342A
        E7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE734
        2AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7
        342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342A
        E7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE734
        2AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7342AE7
        342AE7342AE7342AE73328E63428E53427E63126E83228E83228EA463DEC5A52
        E73127E73128E63128E83128E63127E63127E73229E73229E73229E73229E732
        29E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E7
        3229E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229
        E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E732
        29E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E7
        3229E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229
        E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E732
        29E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E7
        3229E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229
        E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E732
        29E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E7
        3229E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229
        E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E732
        29E73229E73229E73229E73229E73229E73229E73229E73229E73229E73229E7
        3229E73229E73229E53126E73027E73028E73127E83228E83228EA463DEC5A52
        E73127E83128E73026E63126E73127E83027E83127E83127E83127E83127E831
        27E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E8
        3127E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127
        E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E831
        27E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E8
        3127E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127
        E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E831
        27E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E8
        3127E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127
        E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E831
        27E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E8
        3127E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127
        E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E831
        27E83127E83127E83127E83127E83127E83127E83127E83127E83127E83127E8
        3127E83127E83127E83128E63027E63126E83127E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5A52
        E73127E83128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228EA463DEC5952
        E73126E73128E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E73127E73127E73127E9463DEB5A51
        E73126E43227E73127E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E63127E73127E73127E9453CED5851
        E53127E73126E73127E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E73127E73127E73127E9483FEC7470
        E53226E63126E73128E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228
        E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E832
        28E83228E83228E83228E83228E83228E83228E83228E83228E83228E83228E8
        3228E83228E83228E83228E83228E83228E73228E73228E73127EE6C64F8D7D4
        EB655EE94840E94840E94940E94940E94940E94940E94940E94940E94940E949
        40E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E9
        4940E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940
        E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E949
        40E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E9
        4940E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940
        E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E949
        40E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E9
        4940E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940
        E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E949
        40E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E9
        4940E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940
        E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E949
        40E94940E94940E94940E94940E94940E94940E94940E94940E94940E94940E9
        4940E94940E94940E94940E94940E94940E84840E74A3FEC635CF8D4D1FFE000
        104A46494600010001006400640000FFFE001F4C45414420546563686E6F6C6F
        6769657320496E632E2056312E303100FFDB0043000202020202020202020202
        0202020202020202020202020202020202020202020202020202020202020202
        020202020202020202020202020202020202020202FFC401A200000105010101
        01010100000000000000000102030405060708090A0B01000301010101010101
        01010000000000000102030405060708090A0B10000201030302040305050404
        0000017D01020300041105122131410613516107227114328191A1082342B1C1
        1552D1F02433627282090A161718191A25262728292A3435363738393A434445
        464748494A535455565758595A636465666768696A737475767778797A838485
        868788898A92939495969798999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BA
        C2C3C4C5C6C7C8C9CAD2D3D4D5D6D7D8D9DAE1E2E3E4E5E6E7E8E9EAF1F2F3F4
        F5F6F7F8F9FA1100020102040403040705040400010277000102031104052131
        061241510761711322328108144291A1B1C109233352F0156272D10A162434E1
        25F11718191A262728292A35363738393A434445464748494A53545556575859
        5A636465666768696A737475767778797A82838485868788898A929394959697
        98999AA2A3A4A5A6A7A8A9AAB2B3B4B5B6B7B8B9BAC2C3C4C5C6C7C8C9CAD2D3
        D4D5D6D7D8D9DAE2E3E4E5E6E7E8E9EAF2F3F4F5F6F7F8F9FAFFC00011080108
        015A03011100021100031100FFDA000C03010002110311003F00B5F1ABE2D78D
        3C79F103C4B77A86BBAAC1A759EB5A8D8E8DA3C17F750D8697A7D95DCD6D6D14
        16D1489079F2471AC97773B0493CCCEC76AF9413F0BCE734C5E3B1F8994F1159
        4215AA428D2D153A34E15395A82D2EE493B3EBABBF53FD2BF0FB82387F86785F
        2AA183CB7072C657CBF0789C7E3EA61A8CF138EC4E269D2AD88954AD35ED5528
        CA6E3428CB4A74E108C75E673F25FEDAD67FE82DA9FF00E075D7FF001EAF27DB
        54FF009FB5BEF5FE67DBFF0067E03FE80307FF0084D47FC83FB6B59FFA0B6A7F
        F81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B5
        9FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D4
        7FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE803
        07FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F
        67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED
        6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8
        F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D
        75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA
        0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC8
        3FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF
        0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E0
        3FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD
        7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D5
        3FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF
        00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A
        7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6
        B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084
        D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE8
        0307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F98
        7F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7
        ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7
        A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF8
        1D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59F
        FA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47F
        C83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307
        FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67
        E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6F
        BD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6
        D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75
        FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B
        6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83F
        B6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF00
        84D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03F
        E80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F
        987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53F
        E7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00
        C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7F
        F81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B5
        9FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D4
        7FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE803
        07FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F
        67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8F6D53FE7ED
        6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D75FF00C7A8
        F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA0B6A7FF81D
        75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC83FB6B59FFA
        0B6A7FF81D75FF00C7A8F6D53FE7ED6FBD7F987F67E03FE80307FF0084D47FC8
        D0D2BC63E2CD0750B7D4F46F12EBBA6EA16922CB05D5A6A7790CB1BA30618659
        80656206E8D83A3A8657054946D2963315869C2AD0C4D7A738493528494651B7
        D9DD5E12FB563971B9064998E16AE0F1B9465F8AC3D78CA9CE857C25074AD28D
        9C9F32BC65AFBB3859C5AE65EF28B3F4F3C3BFB6348DE1FD09B55D145CEA8DA3
        698DA95C44ED147717E6CA0379347188184692DC79922206608AC172719AFD2B
        0FC58FD850F6B494AAFB1A5ED24B6954E48F3B5A6CE5768FE3FCD3C0784733CC
        6382C7CA8E0E38FC5AC2529D3E69D2C32C4545429CA5ED5734A14B92329595DA
        6EC8FCBEF16FFC8D7E26FF00B18759FF00D39DC57E698AFF007BC4FF00D7EABF
        FA72A1FD8991FF00C89728FF00B1565DFF00A8D40C1AE73D30A002800A002800
        A002800A002800A002800A002800A002800A002800A002800A002800A002800A
        002800A002800A002800A002800A002800A002800A002800A002800A002800A0
        0F70D27FE415A67FD83ECBFF0049A3AF728FF0A97FD7B87FE928FCF31BFEFB8B
        FF00B0AC47FE9D99E5BE2DFF0091AFC4DFF630EB3FFA73B8AF2F15FEF789FF00
        AFD57FF4E543EC323FF912E51FF62ACBBFF51A81835CE7A61400500140050014
        0050014005001400500140050014005001400500140050014005001400500140
        0500140050014005001400500140050014005001400500140050014005001401
        EE1A4FFC82B4CFFB07D97FE93475EE51FE152FFAF70FFD251F9E637FDF717FF6
        1588FF00D3B33CB7C5BFF235F89BFEC61D67FF004E7715E5E2BFDEF13FF5FAAF
        FE9CA87D8647FF00225CA3FEC55977FEA350306B9CF4C2800A002800A002800A
        002800A002800A002800A002800A002800A002800A002800A002800A002800A0
        02800A002800A002800A002800A002800A002800A002800A002800A002803DC3
        49FF00905699FF0060FB2FFD268EBDCA3FC2A5FF005EE1FF00A4A3F3CC6FFBEE
        2FFEC2B11FFA766796F8B7FE46BF137FD8C3ACFF00E9CEE2BCBC57FBDE27FEBF
        55FF00D3950FB0C8FF00E44B947FD8AB2EFF00D46A060D739E98500140050014
        0050014005001400500140050014005001400500140050014005001400500140
        0500140050014005001400500140050014005001400500140050014005001400
        5007B8693FF20AD33FEC1F65FF00A4D1D7B947F854BFEBDC3FF4947E798DFF00
        7DC5FF00D85623FF004ECCF2DF16FF00C8D7E27FFB18359E07FD84EE2BCBC57F
        BD627B7B6ABD547FE5E54EAD34BD5A6BC8FB0C8FFE44B942FF00A9565DB69FF3
        0F43C9FE4FD19CF83DB23D4631D0E791DC0F7239C823BD616B7D89C7F9795F32
        7F350B7DC7A4B6524A6A2DB49B4A2935BDB99A6FFF000143B1FE7FC8A2DFDD9F
        DCFF00F901E9E7F7C3FCC31FE7FC8A2DFDD9FDCFFF00900D3CFEF87F9863FCFF
        009145BFBB3FB9FF00F201A79FDF0FF30C7F9FF228B7F767F73FFE4034F3FBE1
        FE618FF3FE4516FEECFEE7FF00C8069E7F7C3FCC31FE7FC8A2DFDD9FDCFF00F9
        00D3CFEF87F9863FCFF9145BFBB3FB9FFF00201A79FDF0FF0030C7F9FF00228B
        7F767F73FF00E4034F3FBE1FE618FF003FE4516FEECFEE7FFC8069E7F7C3FCC3
        1FE7FC8A2DFDD9FDCFFF00900D3CFEF87F9863FCFF009145BFBB3FB9FF00F201
        A79FDF0FF30C7F9FF228B7F767F73FFE4034F3FBE1FE618FF3FE4516FEECFEE7
        FF00C8069E7F7C3FCC31FE7FC8A2DFDD9FDCFF00F900D3CFEF87F9863FCFF914
        5BFBB3FB9FFF00201A79FDF0FF0030C7F9FF00228B7F767F73FF00E4034F3FBE
        1FE618FF003FE4516FEECFEE7FFC8069E7F7C3FCC31FE7FC8A2DFDD9FDCFFF00
        900D3CFEF87F9863FCFF009145BFBB3FB9FF00F201A79FDF0FF30C7F9FF228B7
        F767F73FFE4034F3FBE1FE618FF3FE4516FEECFEE7FF00C8069E7F7C3FCC31FE
        7FC8A2DFDD9FDCFF00F900D3CFEF87F9863FCFF9145BFBB3FB9FFF00201A79FD
        F0FF0030C7F9FF00228B7F767F73FF00E4034F3FBE1FE618FF003FE4516FEECF
        EE7FFC8069E7F7C3FCC31FE7FC8A2DFDD9FDCFFF00900D3CFEF87F9863FCFF00
        9145BFBB3FB9FF00F201A79FDF0FF30C7F9FF228B7F767F73FFE4034F3FBE1FE
        618FF3FE4516FEECFEE7FF00C8069E7F7C3FCC31FE7FC8A2DFDD9FDCFF00F900
        D3CFEF87F9863FCFF9145BFBB3FB9FFF00201A79FDF0FF0030C7F9FF00228B7F
        767F73FF00E4034F3FBE1FE618FF003FE4516FEECFEE7FFC8069E7F7C3FCC31F
        E7FC8A2DFDD9FDCFFF00900D3CFEF87F9863FCFF009145BFBB3FB9FF00F201A7
        9FDF0FF30C7F9FF228B7F767F73FFE4034F3FBE1FE618FF3FE4516FEECFEE7FF
        00C8069E7F7C3FCC31FE7FC8A2DFDD9FDCFF00F900D3CFEF87F9863FCFF9145B
        FBB3FB9FFF00201A79FDF0FF0031391C0FC3A0FE807D00393459ED18BBFF002C
        9B8BB775EE25F882B26B5518ABDEFD2EB4BB8AE5577A25CC9B7D18A3A7A7FF00
        5FF2EBEDC7D697CB97CAE9DBBEB1B212DBFC938DBCAD2D6FDFA76D0F70D27FE4
        15A67FD83ECBFF0049A3AF728FF0A97FD7B87FE928FCF71BFEFB8BFF00B0AC47
        FE9D99E5BE2DFF0091AFC4FF00F6306B5C74FF00989DC7E55E662B4C5E2778DA
        BD5D56EBF795365DCFAFC934C9329B5F4CAB2EB5926F5C350D93D3EFD0DBB5F8
        9FF11ACADE0B3B4F1CF8AADAD6DA3482DEDE0D6F518A18228D76C71C71ACE8A8
        88AB85545C01C702B5866598528A853C7636108ED18D49452F449A4BE479D578
        37852B569D7ADC399356AF524E556AD6CBB07ED6527BCA4F96F26DEEDEA58FF8
        5B1F13BFE87FF17FFE0FF52FFE49ABFED6CCBFE8618EFF00C1B3FF00E488FF00
        523843FE898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F83FD4BFF9
        268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00A26322FF00C3760FFF00910F
        F85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CFFF00920F
        F523843FE898C8BFF0DD83FF00E443FE16C7C4EFFA1FFC5FFF0083FD4BFF0092
        68FED6CCBFE8618EFF00C1B3FF00E483FD48E10FFA26322FFC3760FF00F910FF
        0085B1F13BFE87FF0017FF00E0FF0052FF00E49A3FB5B32FFA1863BFF06CFF00
        F920FF00523843FE898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F8
        3FD4BFF9268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00A26322FF00C3760F
        FF00910FF85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CF
        FF00920FF523843FE898C8BFF0DD83FF00E443FE16C7C4EFFA1FFC5FFF0083FD
        4BFF009268FED6CCBFE8618EFF00C1B3FF00E483FD48E10FFA26322FFC3760FF
        00F910FF0085B1F13BFE87FF0017FF00E0FF0052FF00E49A3FB5B32FFA1863BF
        F06CFF00F920FF00523843FE898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00
        C5FF00F83FD4BFF9268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00A26322FF
        00C3760FFF00910FF85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863B
        FF0006CFFF00920FF523843FE898C8BFF0DD83FF00E443FE16C7C4EFFA1FFC5F
        FF0083FD4BFF009268FED6CCBFE8618EFF00C1B3FF00E483FD48E10FFA26322F
        FC3760FF00F910FF0085B1F13BFE87FF0017FF00E0FF0052FF00E49A3FB5B32F
        FA1863BFF06CFF00F920FF00523843FE898C8BFF000DD83FFE443FE16C7C4EFF
        00A1FF00C5FF00F83FD4BFF9268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00
        A26322FF00C3760FFF00910FF85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF
        00A1863BFF0006CFFF00920FF523843FE898C8BFF0DD83FF00E443FE16C7C4EF
        FA1FFC5FFF0083FD4BFF009268FED6CCBFE8618EFF00C1B3FF00E483FD48E10F
        FA26322FFC3760FF00F910FF0085B1F13BFE87FF0017FF00E0FF0052FF00E49A
        3FB5B32FFA1863BFF06CFF00F920FF00523843FE898C8BFF000DD83FFE443FE1
        6C7C4EFF00A1FF00C5FF00F83FD4BFF9268FED6CCBFE8618EFFC1B3FFE483FD4
        8E10FF00A26322FF00C3760FFF00910FF85B1F13BFE87FF17FFE0FF52FFE49A3
        FB5B32FF00A1863BFF0006CFFF00920FF523843FE898C8BFF0DD83FF00E443FE
        16C7C4EFFA1FFC5FFF0083FD4BFF009268FED6CCBFE8618EFF00C1B3FF00E483
        FD48E10FFA26322FFC3760FF00F910FF0085B1F13BFE87FF0017FF00E0FF0052
        FF00E49A3FB5B32FFA1863BFF06CFF00F920FF00523843FE898C8BFF000DD83F
        FE443FE16C7C4EFF00A1FF00C5FF00F83FD4BFF9268FED6CCBFE8618EFFC1B3F
        FE483FD48E10FF00A26322FF00C3760FFF00910FF85B1F13BFE87FF17FFE0FF5
        2FFE49A3FB5B32FF00A1863BFF0006CFFF00920FF523843FE898C8BFF0DD83FF
        00E443FE16C7C4EFFA1FFC5FFF0083FD4BFF009268FED6CCBFE8618EFF00C1B3
        FF00E483FD48E10FFA26322FFC3760FF00F910FF0085B1F13BFE87FF0017FF00
        E0FF0052FF00E49A3FB5B32FFA1863BFF06CFF00F920FF00523843FE898C8BFF
        000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F83FD4BFF9268FED6CCBFE8618
        EFFC1B3FFE483FD48E10FF00A26322FF00C3760FFF00910FF85B1F13BFE87FF1
        7FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CFFF00920FF523843FE898C8BF
        F0DD83FF00E443FE16C7C4EFFA1FFC5FFF0083FD4BFF009268FED6CCBFE8618E
        FF00C1B3FF00E483FD48E10FFA26322FFC3760FF00F910FF0085B1F13BFE87FF
        0017FF00E0FF0052FF00E49A3FB5B32FFA1863BFF06CFF00F920FF00523843FE
        898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F83FD4BFF9268FED6C
        CBFE8618EFFC1B3FFE483FD48E10FF00A26322FF00C3760FFF00910FF85B1F13
        BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CFFF00920FF523843F
        E898C8BFF0DD83FF00E443FE16C7C4EFFA1FFC5FFF0083FD4BFF009268FED6CC
        BFE8618EFF00C1B3FF00E483FD48E10FFA26322FFC3760FF00F910FF0085B1F1
        3BFE87FF0017FF00E0FF0052FF00E49A3FB5B32FFA1863BFF06CFF00F920FF00
        523843FE898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F83FD4BFF9
        268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00A26322FF00C3760FFF00910F
        F85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CFFF00920F
        F523843FE898C8BFF0DD83FF00E443FE16C7C4EFFA1FFC5FFF0083FD4BFF0092
        68FED6CCBFE8618EFF00C1B3FF00E483FD48E10FFA26322FFC3760FF00F910FF
        0085B1F13BFE87FF0017FF00E0FF0052FF00E49A3FB5B32FFA1863BFF06CFF00
        F920FF00523843FE898C8BFF000DD83FFE443FE16C7C4EFF00A1FF00C5FF00F8
        3FD4BFF9268FED6CCBFE8618EFFC1B3FFE483FD48E10FF00A26322FF00C3760F
        FF00910FF85B1F13BFE87FF17FFE0FF52FFE49A3FB5B32FF00A1863BFF0006CF
        FF00920FF523843FE898C8BFF0DD83FF00E448E4F8ABF12D91A37F1EF8B5E375
        64746D7B532AC8C0AB2B2FDA082ACAC410460826A5E699934E3F5FC5F23566A7
        56A6B7E96E6B58A8F05708C25194786B23838CA328CA19760D4E328BE68B5EEE
        8D4B58BDD3D51C112496249C962C49392598E4927D493927A93D6B85BD5BBDDB
        77BED76F767D2C528C54629C6314A314D28DA29592E58B6924B6B743DC349FF9
        05699FF60FB2FF00D268EBDBA3FC2A5FF5EE1FFA4A3F3DC6FF00BEE2FF00EC2B
        11FF00A766796F8B7FE46BF137FD8C3ACFFE9CEE2BCBC57FBDE27FEBF55FFD39
        50FB0C8FFE44B947FD8AB2EFFD46A060D739E985001400500140050014005001
        4005001400500140050014005001400500140050014005001400500140050014
        0050014005001400500140050014005001400500140050014005007B8693FF00
        20AD33FEC1F65FFA4D1D7B947F854BFEBDC3FF004947E798DFF7DC5FFD85623F
        F4ECCF2DF16FFC8D7E26FF00B18759FF00D39DC57978AFF7BC4FFD7EABFF00A7
        2A1F6191FF00C89728FF00B1565DFF00A8D40C1AE73D30A002800A002800A002
        800A002800A002800A002800A002800A002800A002800A002800A002800A0028
        00A002800A002800A002800A002800A002800A002800A002800A002800A00F70
        D27FE415A67FD83ECBFF0049A3AF728FF0A97FD7B87FE928FCF31BFEFB8BFF00
        B0AC47FE9D99E5BE2DFF0091AFC4DFF630EB3FFA73B8AF2F15FEF789FF00AFD5
        7FF4E543EC323FF912E51FF62ACBBFF51A81835CE7A614005001400500140050
        0140050014005001400500140050014005001400500140050014005001400500
        140050014005001400500140050014005001400500140050014005001401EE1A
        4FFC82B4CFFB07D97FE93475EE51FE152FFAF70FFD251F9E637FDF717FF61588
        FF00D3B33CB7C5BFF235F89BFEC61D67FF004E7715E5E2BFDEF13FF5FAAFFE9C
        A87D8647FF00225CA3FEC55977FEA350306B9CF4C2800A002800A002800A0028
        00A002800A002800A002800A002800A002800A002800A002800A002800A00280
        0A002800A002800A002800A002800A002800A002800A002800A002803DC349FF
        00905699FF0060FB2FFD268EBDCA3FC2A5FF005EE1FF00A4A3F3CC6FFBEE2FFE
        C2B11FFA766796F8B7FE46BF137FD8C3ACFF00E9CEE2BCBC57FBDE27FEBF55FF
        00D3950FB0C8FF00E44B947FD8AB2EFF00D46A060D739E985001400500140050
        0140050014005001400500140050014005001400500140050014005001400500
        1400500140050014005001400500140050014005001400500140050014005007
        B8693FF20AD33FEC1F65FF00A4D1D7B947F854BFEBDC3FF4947E798DFF007DC5
        FF00D85623FF004ECCF2DF16FF00C8D7E26FFB18759FFD39DC57978AFF007BC4
        FF00D7EABFFA72A1F6191FFC89728FFB1565DFFA8D40C1AE73D30A002800A002
        800A002800A002800A002800A002800A002800A002800A002800A002800A0028
        00A002800A002800A002800A002800A002800A002800A002800A002800A00280
        0A00F70D27FE415A67FD83ECBFF49A3AF728FF000A97FD7B87FE928FCF31BFEF
        B8BFFB0AC47FE9D99E5BE2DFF91AFC4DFF00630EB3FF00A73B8AF2F15FEF789F
        FAFD57FF004E543EC323FF00912E51FF0062ACBBFF0051A81835CE7A61400500
        1400500140050014005001400500140050014005001400500140050014005001
        4005001400500140050014005001400500140050014005001400500140050014
        005001401EE1A4FF00C82B4CFF00B07D97FE93475EE51FE152FF00AF70FF00D2
        51F9E637FDF717FF0061588FFD3B33CB7C5BFF00235F89BFEC61D67FF4E7715E
        5E2BFDEF13FF005FAAFF00E9CA87D8647FF225CA3FEC55977FEA350306B9CF4C
        2800A002800A002800A002800A002800A002800A002800A002800A002800A002
        800A002800A002800A002800A002800A002800A002800A002800A002800A0028
        00A002800A002803DC349FF905699FF60FB2FF00D268EBDCA3FC2A5FF5EE1FFA
        4A3F3CC6FF00BEE2FF00EC2B11FF00A766796F8B7FE46BF137FD8C3ACFFE9CEE
        2BCBC57FBDE27FEBF55FFD3950FB0C8FFE44B947FD8AB2EFFD46A060D739E985
        0014005001400500140050014005001400500140050014005001400500140050
        0140050014005001400500140050014005001400500140050014005001400500
        140050014005007B8693FF0020AD33FEC1F65FFA4D1D7B947F854BFEBDC3FF00
        4947E798DFF7DC5FFD85623FF4ECCF2DF16FFC8D7E26FF00B18759FF00D39DC5
        7978AFF7BC4FFD7EABFF00A72A1F6191FF00C89728FF00B1565DFF00A8D40C1A
        E73D30A002800A002800A002800A002800A002800A002800A002800A002800A0
        02800A002800A002800A002800A002800A002800A002800A002800A002800A00
        2800A002800A002800A00F70D27FE415A67FD83ECBFF0049A3AF728FF0A97FD7
        B87FE928FCF31BFEFB8BFF00B0AC47FE9D99E5BE2DFF0091AFC4DFF630EB3FFA
        73B8AF2F15FEF789FF00AFD57FF4E543EC323FF912E51FF62ACBBFF51A81835C
        E7A6140050014005001400500140050014005001400500140050014005001400
        5001400500140050014005001400500140050014005001400500140050014005
        00140050014005001401EE1A4FFC82B4CFFB07D97FE93475EE51FE152FFAF70F
        FD251F9E637FDF717FF61588FF00D3B33CB7C5BFF235F89BFEC61D67FF004E77
        15E5E2BFDEF13FF5FAAFFE9CA87D8647FF00225CA3FEC55977FEA350306B9CF4
        C2800A002800A002800A002800A002800A002800A002800A002800A002800A00
        2800A002800A002800A002800A002800A002800A002800A002800A002800A002
        800A002800A002803DC349FF00905699FF0060FB2FFD268EBDCA3FC2A5FF005E
        E1FF00A4A3F3CC6FFBEE2FFEC2B11FFA766796F8B7FE46BF137FD8C3ACFF00E9
        CEE2BCBC57FBDE27FEBF55FF00D3950FB0C8FF00E44B947FD8AB2EFF00D46A06
        0D739E9850014005001400500140050014005001400500140050014005001400
        5001400500140050014005001400500140050014005001400500140050014005
        001400500140050014005007B8693FF20AD33FEC1F65FF00A4D1D7B947F854BF
        EBDC3FF4947E798DFF007DC5FF00D85623FF004ECCF2DF16FF00C8D7E26FFB18
        759FFD39DC57978AFF007BC4FF00D7EABFFA72A1F6191FFC89728FFB1565DFFA
        8D40C1AE73D30A002800A002800A002800A002800A002800A002800A002800A0
        02800A002800A002800A002800A002800A002800A002800A002800A002800A00
        2800A002800A002800A002800A00F70D27FE415A67FD83ECBFF49A3AF728FF00
        0A97FD7B87FE928FCF31BFEFB8BFFB0AC47FE9D99E5BE2DFF91AFC4DFF00630E
        B3FF00A73B8AF2F15FEF789FFAFD57FF004E543EC323FF00912E51FF0062ACBB
        FF0051A81835CE7A614005001400500140050014005001400500140050014005
        0014005001400500140050014005001400500140050014005001400500140050
        014005001400500140050014005001401EE1A4FF00C82B4CFF00B07D97FE9347
        5EE51FE152FF00AF70FF00D251F9E637FDF717FF0061588FFD3B33CB7C5BFF00
        235F89BFEC61D67FF4E7715E5E2BFDEF13FF005FAAFF00E9CA87D8647FF225CA
        3FEC55977FEA350306B9CF4C2800A002800A002800A002800A002800A002800A
        002800A002800A002800A002800A002800A002800A002800A002800A002800A0
        02800A002800A002800A002800A002800A002803DC349FF905699FF60FB2FF00
        D268EBDCA3FC2A5FF5EE1FFA4A3F3CC6FF00BEE2FF00EC2B11FF00A766796F8B
        7FE46BF137FD8C3ACFFE9CEE2BCBC57FBDE27FEBF55FFD3950FB0C8FFE44B947
        FD8AB2EFFD46A060D739E9850014005001400500140050014005001400500140
        0500140050014005001400500140050014005001400500140050014005001400
        500140050014005001400500140050014005007B8693FF0020AD33FEC1F65FFA
        4D1D7B947F854BFEBDC3FF004947E798DFF7DC5FFD85623FF4ECCF2DF16FFC8D
        7E26FF00B18759FF00D39DC57978AFF7BC4FFD7EABFF00A72A1F6191FF00C897
        28FF00B1565DFF00A8D40C1AE73D30A002800A002800A002800A002800A00280
        0A002800A002800A002800A002800A002800A002800A002800A002800A002800
        A002800A002800A002800A002800A002800A002800A00F70D27FE415A67FD83E
        CBFF0049A3AF728FF0A97FD7B87FE928FCF31BFEFB8BFF00B0AC47FE9D99E5BE
        2DFF0091AFC4DFF630EB3FFA73B8AF2F15FEF789FF00AFD57FF4E543EC323FF9
        12E51FF62ACBBFF51A81835CE7A6140050014005001400500140050014005001
        4005001400500140050014005001400500140050014005001400500140050014
        00500140050014005001400500140050014005001401EE1A4FFC82B4CFFB07D9
        7FE93475EE51FE152FFAF70FFD251F9E637FDF717FF61588FF00D3B33CB7C5BF
        F235F89BFEC61D67FF004E7715E5E2BFDEF13FF5FAAFFE9CA87D8647FF00225C
        A3FEC55977FEA350306B9CF4C2800A002800A002800A002800A002800A002800
        A002800A002800A002800A002800A002800A002800A002800A002800A002800A
        002800A002800A002800A002800A002800A002803DC349FF00905699FF0060FB
        2FFD268EBDCA3FC2A5FF005EE1FF00A4A3F3CC6FFBEE2FFEC2B11FFA766796F8
        B7FE46BF137FD8C3ACFF00E9CEE2BCBC57FBDE27FEBF55FF00D3950FB0C8FF00
        E44B947FD8AB2EFF00D46A060D739E9850014005001400500140050014005001
        4005001400500140050014005001400500140050014005001400500140050014
        005001400500140050014005001400500140050014005007B8693FF20AD33FEC
        1F65FF00A4D1D7B947F854BFEBDC3FF4947E798DFF007DC5FF00D85623FF004E
        CCF2DF16FF00C8D7E26FFB18759FFD39DC57978AFF007BC4FF00D7EABFFA72A1
        F6191FFC89728FFB1565DFFA8D40C1AE73D30A002800A002800A002800A00280
        0A002800A002800A002800A002800A002800A002800A002800A002800A002800
        A002800A002800A002800A002800A002800A002800A002800A00F70D27FE415A
        67FD83ECBFF49A3AF728FF000A97FD7B87FE928FCF31BFEFB8BFFB0AC47FE9D9
        9E5BE2DFF91AFC4DFF00630EB3FF00A73B8AF2F15FEF789FFAFD57FF004E543E
        C323FF00912E51FF0062ACBBFF0051A81835CE7A614005001400500140050014
        0050014005001400500140050014005001400500140050014005001400500140
        050014005001400500140050014005001400500140050014005001401EE1A4FF
        00C82B4CFF00B07D97FE93475EE51FE152FF00AF70FF00D251F9E637FDF717FF
        0061588FFD3B33CB7C5BFF00235F89BFEC61D67FF4E7715E5E2BFDEF13FF005F
        AAFF00E9CA87D8647FF225CA3FEC55977FEA350306B9CF4C2800A002800A0028
        00A002800A002800A002800A002800A002800A002800A002800A002800A00280
        0A002800A002800A002800A002800A002800A002800A002800A002800A002803
        DC349FF905699FF60FB2FF00D268EBDCA3FC2A5FF5EE1FFA4A3F3CC6FF00BEE2
        FF00EC2B11FF00A76679778B78F15F89BB7FC543ACFB7FCC4EE0D7978AFF007B
        C52ED5EB2B76B54A973EC324D325CA23B3FECACBECB67A61A83765E4B57D96A6
        05739E9850014005001400500140050014005001400500140050014005001400
        5001400500140050014005001400500140050014005001400500140050014005
        0014005001400500140074E3A63B74C66803DC349FF905699FF60FB2FF00D268
        EBDCA2BF754BFEBDC3FF004947E798DFF7DC5FFD85623FF4ECCC3F8A7F0F3C61
        E11F1FF8AB4CD5B40D5626FEDED5A7B4BA4D3EECDA6A163717D34F6B7B6570B1
        B453C1710C91B831BB6C2CD0C8125478D70CD32EC560F30C5529E1EB457D62B5
        484FD9CDC67094A728CA1249A926A49E8DDB5BDACEDDBC17C5191675C3392E2F
        0398E09C565981A75E87D6A92AD83C552C353A55E857A739AA94A71A90945A9C
        529AB4A0E509C652F3EFEC5D63FE813A9FFE005D7FF1AAF3FD856FF9F357FF00
        05CFFC8FAAFED0C07FD07613FF000A68FF00F261FD8BAC7FD02753FF00C00BAF
        FE3547B0ADFF003E6AFF00E0B9FF00907F68603FE83B09FF0085347FF930FEC5
        D63FE813A9FF00E005D7FF001AA3D856FF009F357FF05CFF00C83FB4301FF41D
        84FF00C29A3FFC987F62EB1FF409D4FF00F002EBFF008D51EC2B7FCF9ABFF82E
        7FE41FDA180FFA0EC27FE14D1FFE4C3FB1758FFA04EA7FF80175FF00C6A8F615
        BFE7CD5FFC173FF20FED0C07FD07613FF0A68FFF00261FD8BAC7FD02753FFC00
        BAFF00E3547B0ADFF3E6AFFE0B9FF907F68603FE83B09FF85347FF00930FEC5D
        63FE813A9FFE005D7FF1AA3D856FF9F357FF0005CFFC83FB4301FF0041D84FFC
        29A3FF00C987F62EB1FF00409D4FFF00002EBFF8D51EC2B7FCF9ABFF0082E7FE
        41FDA180FF00A0EC27FE14D1FF00E4C3FB1758FF00A04EA7FF0080175FFC6A8F
        615BFE7CD5FF00C173FF0020FED0C07FD07613FF000A68FF00F261FD8BAC7FD0
        2753FF00C00BAFFE3547B0ADFF003E6AFF00E0B9FF00907F68603FE83B09FF00
        85347FF930FEC5D63FE813A9FF00E005D7FF001AA3D856FF009F357FF05CFF00
        C83FB4301FF41D84FF00C29A3FFC987F62EB1FF409D4FF00F002EBFF008D51EC
        2B7FCF9ABFF82E7FE41FDA180FFA0EC27FE14D1FFE4C3FB1758FFA04EA7FF801
        75FF00C6A8F615BFE7CD5FFC173FF20FED0C07FD07613FF0A68FFF00261FD8BA
        C7FD02753FFC00BAFF00E3547B0ADFF3E6AFFE0B9FF907F68603FE83B09FF853
        47FF00930FEC5D63FE813A9FFE005D7FF1AA3D856FF9F357FF0005CFFC83FB43
        01FF0041D84FFC29A3FF00C987F62EB1FF00409D4FFF00002EBFF8D51EC2B7FC
        F9ABFF0082E7FE41FDA180FF00A0EC27FE14D1FF00E4C3FB1758FF00A04EA7FF
        0080175FFC6A8F615BFE7CD5FF00C173FF0020FED0C07FD07613FF000A68FF00
        F261FD8BAC7FD02753FF00C00BAFFE3547B0ADFF003E6AFF00E0B9FF00907F68
        603FE83B09FF0085347FF930FEC5D63FE813A9FF00E005D7FF001AA3D856FF00
        9F357FF05CFF00C83FB4301FF41D84FF00C29A3FFC987F62EB1FF409D4FF00F0
        02EBFF008D51EC2B7FCF9ABFF82E7FE41FDA180FFA0EC27FE14D1FFE4C3FB175
        8FFA04EA7FF80175FF00C6A8F615BFE7CD5FFC173FF20FED0C07FD07613FF0A6
        8FFF00261FD8BAC7FD02753FFC00BAFF00E3547B0ADFF3E6AFFE0B9FF907F686
        03FE83B09FF85347FF00930FEC5D63FE813A9FFE005D7FF1AA3D856FF9F357FF
        0005CFFC83FB4301FF0041D84FFC29A3FF00C987F62EB1FF00409D4FFF00002E
        BFF8D51EC2B7FCF9ABFF0082E7FE41FDA180FF00A0EC27FE14D1FF00E4C3FB17
        58FF00A04EA7FF0080175FFC6A8F615BFE7CD5FF00C173FF0020FED0C07FD076
        13FF000A68FF00F261FD8BAC7FD02753FF00C00BAFFE3547B0ADFF003E6AFF00
        E0B9FF00907F68603FE83B09FF0085347FF930FEC5D63FE813A9FF00E005D7FF
        001AA3D856FF009F357FF05CFF00C83FB4301FF41D84FF00C29A3FFC987F62EB
        1FF409D4FF00F002EBFF008D51EC2B7FCF9ABFF82E7FE41FDA180FFA0EC27FE1
        4D1FFE4C3FB1758FFA04EA7FF80175FF00C6A8F615BFE7CD5FFC173FF20FED0C
        07FD07613FF0A68FFF00261FD8BAC7FD02753FFC00BAFF00E3547B0ADFF3E6AF
        FE0B9FF907F68603FE83B09FF85347FF00930FEC5D63FE813A9FFE005D7FF1AA
        3D856FF9F357FF0005CFFC83FB4301FF0041D84FFC29A3FF00C987F62EB1FF00
        409D4FFF00002EBFF8D51EC2B7FCF9ABFF0082E7FE41FDA180FF00A0EC27FE14
        D1FF00E4C3FB1758FF00A04EA7FF0080175FFC6A8F615BFE7CD5FF00C173FF00
        20FED0C07FD07613FF000A68FF00F261FD8BAC7FD02753FF00C00BAFFE3547B0
        ADFF003E6AFF00E0B9FF00907F68603FE83B09FF0085347FF930FEC5D63FE813
        A9FF00E005D7FF001AA3D856FF009F357FF05CFF00C83FB4301FF41D84FF00C2
        9A3FFC987F62EB1FF409D4FF00F002EBFF008D51EC2B7FCF9ABFF82E7FE41FDA
        180FFA0EC27FE14D1FFE4C3FB1758FFA04EA7FF80175FF00C6A8F615BFE7CD5F
        FC173FF20FED0C07FD07613FF0A68FFF00261FD8BAC7FD02753FFC00BAFF00E3
        547B0ADFF3E6AFFE0B9FF907F68603FE83B09FF85347FF00930FEC5D63FE813A
        9FFE005D7FF1AA3D856FF9F357FF0005CFFC83FB4301FF0041D84FFC29A3FF00
        C987F62EB1FF00409D4FFF00002EBFF8D51EC2B7FCF9ABFF0082E7FE41FDA180
        FF00A0EC27FE14D1FF00E4C3FB1758FF00A04EA7FF0080175FFC6A8F615BFE7C
        D5FF00C173FF0020FED0C07FD07613FF000A68FF00F264B6FE1BF10DDCF1DAD9
        E83AD5CDCCCEA90DBDBE977D34D2BB70A9143140D23B9E81514924F033551C36
        21CA30850ACE4F48C634A6DBF249477D76EB7F333AB9B65586A73AB5F32CBE85
        2A71E79D5AB8CC352A74E29D9CA539D48C2296EEED596AF4D4FD10F0DFEC8DE3
        29BC3BA0CD7B751E9F792E8BA5CB77613ED13595CC96303CF693052CA25B694B
        C326D661BD0E091CD7DFE1B84F16F0F425371A737469394256E6849C22E50959
        DAF1774EDD51FCB59B78DF90D3CD733A787A2F1587A798632143134F9FD9E228
        C7135234ABC2F04F92B4146A46E93E592BA47FFFD9}
      Stretch = True
    end
    object modAlarm1: TLabel
      Left = 46
      Top = 46
      Width = 73
      Height = 14
      Caption = 'Device Error'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object modAlarm3: TLabel
      Left = 50
      Top = 105
      Width = 39
      Height = 14
      Alignment = taCenter
      Caption = 'status'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object modAlarm4: TLabel
      Left = 50
      Top = 167
      Width = 39
      Height = 14
      Alignment = taCenter
      Caption = 'status'
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentColor = False
      ParentFont = False
      Transparent = True
    end
    object AlarmTime: TLabel
      Left = 50
      Top = 243
      Width = 77
      Height = 14
      Caption = '14? 54? 35?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWhite
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
  end
  object GrpError: TGroupBox
    Left = 1434
    Top = 142
    Width = 404
    Height = 300
    Caption = 'STAGE ERROR'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -17
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Visible = False
    object Image2: TImage
      Left = 30
      Top = 26
      Width = 346
      Height = 265
      Picture.Data = {
        0A544A504547496D616765E0100000FFD8FFE000104A46494600010200006400
        640000FFEC00114475636B79000100040000003C0000FFEE000E41646F626500
        64C000000001FFDB0084000604040405040605050609060506090B080606080B
        0C0A0A0B0A0A0C100C0C0C0C0C0C100C0E0F100F0E0C1313141413131C1B1B1B
        1C1F1F1F1F1F1F1F1F1F1F010707070D0C0D181010181A1511151A1F1F1F1F1F
        1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F1F
        1F1F1F1F1F1F1F1F1F1F1F1FFFC00011080133019103011100021101031101FF
        C400980001010101010101000000000000000000000402050603080101000203
        0101000000000000000000000003050204060701100100000209040200040407
        00000000000001030292E2530414940565B17233161112218113153141220661
        71C1425282231101000101050802020005030501000000000201920313041531
        5161B1D1E15363723311122141711405813252426282A20616FFDA000C030100
        02110311003F00FD098EDC31337114FE2652A1428C630A3468C630FC21FE4F17
        FF0035FE7F337D9897E27284232AD2948D6B4D9FD36D56F73711A469FC13E6B1
        37D4EB4551A9667CB796A5D52E1C7750CD626FA9D689A9667CB796A5D4C38EEA
        19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A599F2DE5A97530E3B
        A866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9667CB796A5D4C38
        EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A599F2DE5A97530
        E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9667CB796A5D4
        C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A599F2DE5A97
        530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9667CB796A
        5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A599F2DE5
        A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9667CB7
        96A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A599F2
        DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9667
        CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26A59
        9F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D689A9
        667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75A26
        A599F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9D68
        9A9667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BEA75
        A26A599F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626FA9
        D689A9667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD433589BE
        A75A26A599F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD626
        FA9D689A9667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD43358
        9BEA75A26A599F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C7750CD
        626FA9D689A9667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871DD43
        3589BEA75A26A599F2DE5A97530E3BA866B137D4EB44D4B33E5BCB52EA61C775
        0CD626FA9D689A9667CB796A5D4C38EEA19AC4DF53AD1352CCF96F2D4BA9871D
        D433589BEA75A26A599F2DE5A97530E3BA8FA49C7E2E54C853A336947E3F8D1A
        518C611FCA2D9CA7F9DCDDC5E5271BC957856B5AD2BFD695612B98CA9F8FC3B7
        FBBC9FF8C5E99FFEAEE7FE3557FF006D579F9DE699DD1EAF25CE7DD3F94B9ACE
        1B28C35D90000000000000000000000000000000000000000000000000000000
        000000000000000002C7468134EF34CEE8F552673EE9FCA5CD2C365186BB2000
        0000000000000000000000000000000000000000000000000000000000000000
        0000058E8D0269DE699DD1EAA4CE7DD3F94B9A586CA30D764000000000000000
        000000000000000000000000000000000000000000000000000000000B1D1A04
        D3BCD33BA3D5499CFBA7F29734B0D9461AEC8000000000000000000000000000
        00000000000000000000000000000000000000000000163A3409A779A67747AA
        9339F74FE52E6961B28E2EEFFDC3FB6E268C8FDB31F8DFB50853FD5C248FD597
        0F98C61F58D2FB43FABF0FE0CEE329891FCFEF08FCABF8252FC7F243EEDC0EF1
        A4B69B4EF65D5AECF989C2A7BB703BC692D9A77B2EAD76313854F76E0778D25B
        34EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE3496CD3BD97
        56BB189C2A7BB703BC692D9A77B2EAD76313854F76E0778D25B34EF65D5AEC62
        70A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE3496CD3BD9756BB189C2A7BB
        703BC692D9A77B2EAD76313854F76E0778D25B34EF65D5AEC6270A9EEDC0EF1A
        4B669DECBAB5D8C4E153DDB81DE3496CD3BD9756BB189C2A7BB703BC692D9A77
        B2EAD76313854F76E0778D25B34EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D
        8C4E153DDB81DE3496CD3BD9756BB189C2A7BB703BC692D9A77B2EAD76313854
        F76E0778D25B34EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81D
        E3496CD3BD9756BB189C2A7BB703BC692D9A77B2EAD76313854F76E0778D25B3
        4EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE3496CD3BD975
        6BB189C2A7BB703BC692D9A77B2EAD76313854F76E0778D25B34EF65D5AEC627
        0A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE3496CD3BD9756BB189C2A7BB7
        03BC692D9A77B2EAD76313854F76E0778D25B34EF65D5AEC6270A9EEDC0EF1A4
        B669DECBAB5D8C4E153DDB81DE3496CD3BD9756BB189C2A7BB703BC692D9A77B
        2EAD76313854F76E0778D25B34EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8
        C4E153DDB81DE3496CD3BD9756BB189C2A7BB703BC692D9A77B2EAD76313854F
        76E0778D25B34EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE
        3496CD3BD9756BB189C2A7BB703BC692D9A77B2EAD76313854F76E0778D25B34
        EF65D5AEC6270A9EEDC0EF1A4B669DECBAB5D8C4E153DDB81DE3496CD3BD9756
        BB189C2A7BB703BC692D9A77B2EAD763138554EDBFDD19EC6CBC2FED1B9617F5
        3E7FF7C4E1FF004E551FAD18D2FEAA5F68FC7CFC7C43FC51DF64BF48D65FBDDC
        B8525F9ABED27F9FE55771A4C963A3409A779A67747AA9339F74FE52E6961B28
        C35D900000000000000000000000000000000000000000000000000000000000
        00000000000002C7468134EF34CEE8F552673EE9FCA5CD2C365186BB20000000
        0000000000000000000000000000000000000000000000000000000000000000
        058E8D0269DE699DD1EAA4CE7DD3F94B9A586CA30D7640000000000000000000
        00000000000000000000000000000000000000000000000000000B1D1A04D3BC
        D33BA3D5499CFBA7F29734B0D9461AEC80000000000000000000000000000000
        0000000000000000000000000000000000000000163A3409A779A67747AA9339
        F74FE52E6961B28C35D900000000000000000000000000000000000000000000
        00000000000000000000000000002C7468134EF34CEE8F552673EE9FCA5CD2C3
        65186BB200000000000000000000000000000000000000000000000000000000
        000000000000000058E8D0269DE699DD1EAA4CE7DD3F94B9A586CA30D7640000
        0000000000000000000000000000000000000000000000000000000000000000
        0000B1D1A04D3BCD33BA3D5499CFBA7F29734B0D9461AEC80000000000000000
        0000000000000000000000000000000000000000000000000000000163A3409A
        779A67747AA9339F74FE52E6961B28C35D900000000000000000000000000000
        00000000000000000000000000000000000000000002C7468134EF34CEE8F552
        673EE9FCA5CD2C365186BB200000000000000000000000000000000000000000
        000000000000000000000000000000058E8D0269DE699DD1EAA4CE7DD3F94B9A
        586CA30D76400000000000000000000000000000000000000000000000000000
        0000000000000000000B1D1A04D3BCD33BA3D5499CFBA7F29734B0D9461AEC80
        0000000000000000000000000000000000000000000000000000000000000000
        000000163A3409A779A67747AA9339F74FE52E6961B28C35D900000000000000
        00000000000000000000000000000000000000000000000000000000002C7468
        134EF34CEE8F552673EE9FCA5CD2C365186BB200000000000000000000000000
        000000000000000000000000000000000000000000000058E8D0269DE699DD1E
        AA4CE7DD3F94B9A586CA30D76400000000000000000000000000000000000000
        0000000000000000000000000000000000B1D1A04D3BCD33BA3D5499CFBA7F29
        734B0D9461AEC800000000000000000000000000000000000000000000000000
        000000000000000000000163A3409A779A67747AA9339F74FE52E6961B28C35D
        9000000000000000000000000000000000000000000000000000000000000000
        0000000002C7468134EF34CEE8F552673EE9FCA5CD2C365186BB200000000000
        000000000000000000000000000000000000000000000000000000000000058E
        8D0269DE699DD1EAA4CE7DD3F94B9A586CA30D76400000000000000000000000
        0000000000000000000000000000000000000000000000000B1D1A04D3BCD33B
        A3D5499CFBA7F29734B0D9461AEC800000000000000000000000000000000000
        000000000000000000000000000000000000163A3409A779A67747AA9339F74F
        E52E6961B28C35D9000000000000000000000000000000000000000000000000
        0000000000000000000000002C7468134EF34CEE8F552673EE9FCA5CD2C36518
        6BB2000000000000000000000000000000000000000000000000000000000000
        00000000000058E8D0269DE699DD1EAA4CE7DD3F94B9A586CA30D76400000000
        0000000000000000000000000000000000000000000000000000000000000000
        B1D1A04D3BCD33BA3D5499CFBA7F29734B0D9461AEC800000000000000000000
        000000000000000000000000000000000000000000000000000163A3409A779A
        67747AA9339F74FE52E6961B28C35D9000000000000000000000000000000000
        0000000000000000000000000000000000000002C7468134EF34CEE8F552673E
        E9FCA5CD2C365186BB2000000000000000000000000000000000000000000000
        00000000000000000000000000058E8D0269DE699DD1EAA4CE7DD3F94B9A586C
        A30D764000000000000000000000000000000000000000000000000000000000
        000000000000000B1D1A04D3BCD33BA3D5499CFBA7F29734B0D9461AEC800000
        0000000000000000000000000000000000000000000000000000000000000000
        00163A3409A779A67747AA9339F74FE52E6961B28C35D9000000000000000000
        0000000000000000000000000000000000000000000000000000002C7468134E
        F34CEE8F552673EE9FCA5CD2C365186BB2000000000000000000000000000000
        00000000000000000000000000000000000000000058E8D0269DE699DD1EAA4C
        E7DD3F94B9A586CA30D764000000000000000000000000000000000000000000
        000000000000000000000000000000B1D1A04D3E1184F9908FE118528FCC3F35
        367A35A5FCE95DBFBCB9A587FB68C35590000000000000000000000000000000
        000000000000000000000000000000000000000003A594C4DDD2765A5667FE12
        6A62477B1BC7D7374FC7F6FE7F4FB7DBFEDFEDF941FF00D6FEBFDDCBEBFDBFED
        FDBF6FFCBFE9FCFF004FF56595FCFEBFCD03946C800000000000000000000000
        00000000000000000000000000000000000000000000000A301F5CC50F9FD3F9
        F987C7EA7DBE3E7F2FF55BFF0083FD7FB98FE70F6D3F189FB7E3FF005FE16BF8
        22BEFF006FF3FF0047A97BAA99FFD9}
      Stretch = True
    end
    object error1: TLabel
      Left = 46
      Top = 46
      Width = 103
      Height = 14
      Caption = 'BATCH CHANGED'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object error3: TLabel
      Left = 50
      Top = 105
      Width = 141
      Height = 14
      Caption = 'Before : BAEQERTIFECE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object error4: TLabel
      Left = 50
      Top = 167
      Width = 127
      Height = 14
      Caption = 'New : BACEKFEOFJEC'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object ErrorTime: TLabel
      Left = 50
      Top = 243
      Width = 77
      Height = 14
      Caption = '14? 54? 35?'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      Transparent = True
    end
    object AlarmConfirmBtn: TAdvSmoothButton
      Left = 284
      Top = 251
      Width = 83
      Height = 33
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -11
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Confirm'
      Color = clWhite
      ParentFont = False
      TabOrder = 0
      Version = '2.1.1.5'
      OnClick = AlarmConfirmBtnClick
      TMSStyle = 8
    end
  end
  object GroupBox1: TGroupBox
    Left = 1697
    Top = 10
    Width = 295
    Height = 185
    Caption = 'GroupBox3'
    TabOrder = 9
    object btnMeasureInfo: TAdvSmoothButton
      Left = 23
      Top = 21
      Width = 147
      Height = 60
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -15
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Measure Info'
      Color = clWhite
      ParentFont = False
      TabOrder = 0
      Version = '2.1.1.5'
      OnClick = btnMeasureInfoClick
      TMSStyle = 8
    end
  end
  object pnlConfig: TAdvSmoothPanel
    Left = 728
    Top = 34
    Width = 600
    Height = 464
    Cursor = crDefault
    CanMove = True
    Caption.Location = plCenterCenter
    Caption.HTMLFont.Charset = DEFAULT_CHARSET
    Caption.HTMLFont.Color = clWindowText
    Caption.HTMLFont.Height = -11
    Caption.HTMLFont.Name = 'Tahoma'
    Caption.HTMLFont.Style = []
    Caption.HTMLURLColor = clBlack
    Caption.Font.Charset = DEFAULT_CHARSET
    Caption.Font.Color = clWindowText
    Caption.Font.Height = -24
    Caption.Font.Name = 'Tahoma'
    Caption.Font.Style = [fsBold]
    Caption.ColorStart = clWhite
    Caption.ColorEnd = clWhite
    Caption.LineColor = clBlack
    Caption.Line = False
    Caption.TextAlignment = taCenter
    Fill.Color = clWhite
    Fill.ColorTo = clWhite
    Fill.ColorMirror = clWhite
    Fill.ColorMirrorTo = clWhite
    Fill.GradientType = gtVertical
    Fill.GradientMirrorType = gtVertical
    Fill.BorderColor = 14922381
    Fill.Rounding = 5
    Fill.ShadowOffset = 0
    Fill.Glow = gmNone
    Version = '1.5.2.1'
    Visible = False
    TabOrder = 7
    TMSStyle = 0
    object Label5: TLabel
      Left = 18
      Top = 10
      Width = 111
      Height = 19
      Caption = 'Configuration'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object GroupBox4: TGroupBox
      Left = 10
      Top = 38
      Width = 440
      Height = 107
      Caption = 'IR/OCV'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object editIROCVIPAddress: TEdit
        Left = 103
        Top = 33
        Width = 199
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 0
        Text = '192.168.100.101'
      end
      object Panel23: TPanel
        Left = 15
        Top = 33
        Width = 88
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'IP ADDRESS'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
      end
      object Panel24: TPanel
        Left = 15
        Top = 64
        Width = 88
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PORT'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
      object editIROCVPort: TEdit
        Left = 103
        Top = 64
        Width = 199
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 3
        Text = '5025'
      end
      object btnConnectIROCV: TAdvSmoothButton
        Left = 323
        Top = 14
        Width = 99
        Height = 38
        Appearance.Font.Charset = DEFAULT_CHARSET
        Appearance.Font.Color = clWindowText
        Appearance.Font.Height = -13
        Appearance.Font.Name = 'Tahoma'
        Appearance.Font.Style = [fsBold]
        Appearance.Spacing = 0
        Appearance.Rounding = 3
        Appearance.WordWrapping = False
        Status.Caption = '0'
        Status.Appearance.Fill.Color = clRed
        Status.Appearance.Fill.ColorMirror = clNone
        Status.Appearance.Fill.ColorMirrorTo = clNone
        Status.Appearance.Fill.GradientType = gtSolid
        Status.Appearance.Fill.GradientMirrorType = gtSolid
        Status.Appearance.Fill.BorderColor = clGray
        Status.Appearance.Fill.Rounding = 0
        Status.Appearance.Fill.ShadowOffset = 0
        Status.Appearance.Fill.Glow = gmNone
        Status.Appearance.Font.Charset = DEFAULT_CHARSET
        Status.Appearance.Font.Color = clWhite
        Status.Appearance.Font.Height = -11
        Status.Appearance.Font.Name = 'Tahoma'
        Status.Appearance.Font.Style = []
        BevelColor = clMedGray
        Caption = 'Connect'
        Color = clWhite
        ParentFont = False
        TabOrder = 4
        Version = '2.1.1.5'
        OnClick = btnConnectIROCVClick
        TMSStyle = 8
      end
      object btnDisConnectIROCV: TAdvSmoothButton
        Left = 323
        Top = 58
        Width = 99
        Height = 38
        Appearance.Font.Charset = DEFAULT_CHARSET
        Appearance.Font.Color = clWindowText
        Appearance.Font.Height = -13
        Appearance.Font.Name = 'Tahoma'
        Appearance.Font.Style = [fsBold]
        Appearance.Spacing = 0
        Appearance.Rounding = 3
        Appearance.WordWrapping = False
        Status.Caption = '0'
        Status.Appearance.Fill.Color = clRed
        Status.Appearance.Fill.ColorMirror = clNone
        Status.Appearance.Fill.ColorMirrorTo = clNone
        Status.Appearance.Fill.GradientType = gtSolid
        Status.Appearance.Fill.GradientMirrorType = gtSolid
        Status.Appearance.Fill.BorderColor = clGray
        Status.Appearance.Fill.Rounding = 0
        Status.Appearance.Fill.ShadowOffset = 0
        Status.Appearance.Fill.Glow = gmNone
        Status.Appearance.Font.Charset = DEFAULT_CHARSET
        Status.Appearance.Font.Color = clWhite
        Status.Appearance.Font.Height = -11
        Status.Appearance.Font.Name = 'Tahoma'
        Status.Appearance.Font.Style = []
        BevelColor = clMedGray
        Caption = 'Disconnect'
        Color = clWhite
        ParentFont = False
        TabOrder = 5
        Version = '2.1.1.5'
        OnClick = btnDisConnectIROCVClick
        TMSStyle = 8
      end
    end
    object GroupBox5: TGroupBox
      Left = 10
      Top = 148
      Width = 440
      Height = 138
      Caption = 'PLC CONNECTION'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object editPLCIPAddress: TEdit
        Left = 103
        Top = 33
        Width = 199
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 0
        Text = '192.168.100.102'
      end
      object Panel25: TPanel
        Left = 15
        Top = 33
        Width = 88
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'IP ADDRESS'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 1
      end
      object Panel26: TPanel
        Left = 15
        Top = 64
        Width = 88
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PORT - PC'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 2
      end
      object editPLCPortPC: TEdit
        Left = 103
        Top = 64
        Width = 199
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 3
        Text = '8901'
      end
      object btnConnectPLC: TAdvSmoothButton
        Left = 323
        Top = 32
        Width = 99
        Height = 38
        Appearance.Font.Charset = DEFAULT_CHARSET
        Appearance.Font.Color = clWindowText
        Appearance.Font.Height = -13
        Appearance.Font.Name = 'Tahoma'
        Appearance.Font.Style = [fsBold]
        Appearance.Spacing = 0
        Appearance.Rounding = 3
        Appearance.WordWrapping = False
        Status.Caption = '0'
        Status.Appearance.Fill.Color = clRed
        Status.Appearance.Fill.ColorMirror = clNone
        Status.Appearance.Fill.ColorMirrorTo = clNone
        Status.Appearance.Fill.GradientType = gtSolid
        Status.Appearance.Fill.GradientMirrorType = gtSolid
        Status.Appearance.Fill.BorderColor = clGray
        Status.Appearance.Fill.Rounding = 0
        Status.Appearance.Fill.ShadowOffset = 0
        Status.Appearance.Fill.Glow = gmNone
        Status.Appearance.Font.Charset = DEFAULT_CHARSET
        Status.Appearance.Font.Color = clWhite
        Status.Appearance.Font.Height = -11
        Status.Appearance.Font.Name = 'Tahoma'
        Status.Appearance.Font.Style = []
        BevelColor = clMedGray
        Caption = 'Connect'
        Color = clWhite
        ParentFont = False
        TabOrder = 4
        Version = '2.1.1.5'
        OnClick = btnConnectPLCClick
        TMSStyle = 8
      end
      object btnDisConnectPLC: TAdvSmoothButton
        Left = 323
        Top = 76
        Width = 99
        Height = 38
        Appearance.Font.Charset = DEFAULT_CHARSET
        Appearance.Font.Color = clWindowText
        Appearance.Font.Height = -13
        Appearance.Font.Name = 'Tahoma'
        Appearance.Font.Style = [fsBold]
        Appearance.Spacing = 0
        Appearance.Rounding = 3
        Appearance.WordWrapping = False
        Status.Caption = '0'
        Status.Appearance.Fill.Color = clRed
        Status.Appearance.Fill.ColorMirror = clNone
        Status.Appearance.Fill.ColorMirrorTo = clNone
        Status.Appearance.Fill.GradientType = gtSolid
        Status.Appearance.Fill.GradientMirrorType = gtSolid
        Status.Appearance.Fill.BorderColor = clGray
        Status.Appearance.Fill.Rounding = 0
        Status.Appearance.Fill.ShadowOffset = 0
        Status.Appearance.Fill.Glow = gmNone
        Status.Appearance.Font.Charset = DEFAULT_CHARSET
        Status.Appearance.Font.Color = clWhite
        Status.Appearance.Font.Height = -11
        Status.Appearance.Font.Name = 'Tahoma'
        Status.Appearance.Font.Style = []
        BevelColor = clMedGray
        Caption = 'Disconnect'
        Color = clWhite
        ParentFont = False
        TabOrder = 5
        Version = '2.1.1.5'
        OnClick = btnDisConnectPLCClick
        TMSStyle = 8
      end
      object pnlportplc: TPanel
        Left = 15
        Top = 95
        Width = 88
        Height = 25
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = 'PORT - PLC'
        Color = 16771289
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        TabOrder = 6
      end
      object editPLCPortPLC: TEdit
        Left = 103
        Top = 95
        Width = 199
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 7
        Text = '8902'
      end
    end
    object btnCloseConnConfig: TAdvSmoothButton
      Left = 463
      Top = 115
      Width = 120
      Height = 60
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -17
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'CANCEL'
      Color = clWhite
      ParentFont = False
      TabOrder = 2
      Version = '2.1.1.5'
      OnClick = btnCloseConnConfigClick
      TMSStyle = 8
    end
    object btnSaveConnConfig: TAdvSmoothButton
      Left = 463
      Top = 48
      Width = 120
      Height = 60
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -17
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'SAVE'
      Color = clWhite
      ParentFont = False
      TabOrder = 3
      Version = '2.1.1.5'
      OnClick = btnSaveConfigClick
      TMSStyle = 8
    end
    object Button1: TButton
      Left = 376
      Top = 7
      Width = 75
      Height = 25
      Caption = 'Button1'
      TabOrder = 4
      Visible = False
      OnClick = Button1Click
    end
    object Panel4: TPanel
      Left = 10
      Top = 349
      Width = 580
      Height = 110
      BevelInner = bvRaised
      BiDiMode = bdLeftToRight
      BorderStyle = bsSingle
      Color = clWhite
      ParentBiDiMode = False
      ParentBackground = False
      TabOrder = 5
      object grpIrSpec: TGroupBox
        Left = 5
        Top = 10
        Width = 280
        Height = 50
        Caption = 'IR SPEC (m'#937')'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        object Label1: TLabel
          Left = 20
          Top = 28
          Width = 26
          Height = 16
          Caption = 'Min.'
        end
        object Label3: TLabel
          Left = 182
          Top = 28
          Width = 30
          Height = 16
          Caption = 'Max.'
        end
        object irEdit1: TEdit
          Left = 60
          Top = 20
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 0
          Text = '2'
        end
        object Panel5: TPanel
          Left = 140
          Top = 20
          Width = 20
          Height = 25
          BevelOuter = bvNone
          Caption = '~'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object irEdit2: TEdit
          Left = 222
          Top = 20
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 2
          Text = '2'
        end
      end
      object grpOcvSpec: TGroupBox
        Left = 291
        Top = 10
        Width = 280
        Height = 50
        Caption = 'OCV SPEC (mV)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        object Label2: TLabel
          Left = 20
          Top = 28
          Width = 26
          Height = 16
          Caption = 'Min.'
        end
        object Label4: TLabel
          Left = 182
          Top = 28
          Width = 30
          Height = 16
          Caption = 'Max.'
        end
        object ocvEdit1: TEdit
          Left = 60
          Top = 20
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 0
          Text = '2'
        end
        object Panel8: TPanel
          Left = 140
          Top = 20
          Width = 20
          Height = 25
          BevelOuter = bvNone
          Caption = '~'
          Color = clWhite
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -16
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          TabOrder = 1
        end
        object ocvEdit2: TEdit
          Left = 222
          Top = 20
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 2
          Text = '2'
        end
      end
      object Panel7: TPanel
        Left = 26
        Top = 215
        Width = 375
        Height = 30
        BevelKind = bkFlat
        BevelOuter = bvNone
        Color = 15658734
        ParentBackground = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 2
        object RemeasureChk: TCheckBox
          Left = 238
          Top = 5
          Width = 111
          Height = 17
          Caption = 'Auto Remeasure'
          Color = 15658734
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          TabOrder = 0
        end
        object chkRemBypass: TCheckBox
          Left = 4
          Top = 5
          Width = 218
          Height = 17
          Caption = 'Tray out when finish remeasure'
          Checked = True
          Color = 15658734
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentColor = False
          ParentFont = False
          State = cbChecked
          TabOrder = 1
        end
      end
      object Panel15: TPanel
        Left = 6
        Top = 64
        Width = 195
        Height = 30
        Alignment = taLeftJustify
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = '     NG ALARM COUNT'
        Color = 15658734
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 3
      end
      object editNgAlarmCount: TEdit
        Left = 201
        Top = 64
        Width = 84
        Height = 30
        Alignment = taCenter
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Orientation = 5
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        NumbersOnly = True
        ParentFont = False
        TabOrder = 4
        Text = '20'
      end
      object RemeasureEdit: TEdit
        Left = 401
        Top = 215
        Width = 100
        Height = 30
        Alignment = taCenter
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Orientation = 5
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        NumbersOnly = True
        ParentFont = False
        TabOrder = 5
        Text = '2'
      end
      object grpIrAvg: TGroupBox
        Left = 5
        Top = 111
        Width = 280
        Height = 50
        Caption = 'IR SPEC (m'#937')'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 6
        object Label6: TLabel
          Left = 20
          Top = 28
          Width = 30
          Height = 16
          Caption = 'Avg.'
        end
        object Label10: TLabel
          Left = 130
          Top = 28
          Width = 82
          Height = 16
          Caption = 'Range (+/-)'
        end
        object editIrAvg: TEdit
          Left = 60
          Top = 22
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 0
          Text = '2'
        end
        object editIrRange: TEdit
          Left = 220
          Top = 22
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 1
          Text = '2'
        end
      end
      object grpOcvAvg: TGroupBox
        Left = 290
        Top = 111
        Width = 280
        Height = 50
        Caption = 'OCV SPEC (mV)'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 7
        object Label11: TLabel
          Left = 20
          Top = 28
          Width = 30
          Height = 16
          Caption = 'Avg.'
        end
        object Label12: TLabel
          Left = 130
          Top = 28
          Width = 82
          Height = 16
          Caption = 'Range (+/-)'
        end
        object editOcvAvg: TEdit
          Left = 60
          Top = 22
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 0
          Text = '2'
        end
        object editOcvRange: TEdit
          Left = 220
          Top = 22
          Width = 50
          Height = 24
          Alignment = taCenter
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clBlack
          Font.Height = -13
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ImeName = 'Microsoft Office IME 2007'
          ParentFont = False
          TabOrder = 1
          Text = '2'
        end
      end
      object Panel2: TPanel
        Left = 291
        Top = 64
        Width = 195
        Height = 30
        Alignment = taLeftJustify
        BevelKind = bkFlat
        BevelOuter = bvNone
        Caption = '     REMEASURE ALARM COUNT'
        Color = 15658734
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentBackground = False
        ParentFont = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 8
      end
      object editRemeasureAlarmCount: TEdit
        Left = 486
        Top = 64
        Width = 84
        Height = 30
        Alignment = taCenter
        AutoSize = False
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Orientation = 5
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        NumbersOnly = True
        ParentFont = False
        TabOrder = 9
        Text = '5'
      end
    end
    object chkUseAverage: TCheckBox
      Left = 456
      Top = 7
      Width = 128
      Height = 25
      Caption = 'Use Average'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlue
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      ParentShowHint = False
      ShowHint = False
      TabOrder = 6
      Visible = False
      OnClick = chkUseAverageClick
      OnMouseUp = chkBypassMouseUp
    end
    object GroupBox6: TGroupBox
      Left = 10
      Top = 287
      Width = 319
      Height = 58
      Caption = 'MODEL NAME'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 7
      object editModelName: TEdit
        Left = 63
        Top = 25
        Width = 234
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        TabOrder = 0
        Text = '20PQ'
      end
    end
    object GroupBox8: TGroupBox
      Left = 335
      Top = 287
      Width = 250
      Height = 58
      Caption = 'Password'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 8
      OnDblClick = GroupBox8DblClick
      object editPwd: TEdit
        Left = 63
        Top = 25
        Width = 178
        Height = 24
        Alignment = taCenter
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clBlack
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ImeName = 'Microsoft Office IME 2007'
        ParentFont = False
        PasswordChar = '*'
        TabOrder = 0
        Text = 'Eveml@123'
      end
    end
    object RadioGroup1: TRadioGroup
      Left = 456
      Top = 224
      Width = 129
      Height = 62
      Caption = 'SPEED MODE'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 9
    end
    object rbSpeedMed: TRadioButton
      Tag = 1
      Left = 462
      Top = 262
      Width = 54
      Height = 17
      Caption = 'MED'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 10
      OnClick = rbSpeedFastClick
    end
    object rbSpeedFast: TRadioButton
      Tag = 2
      Left = 522
      Top = 262
      Width = 54
      Height = 17
      Caption = 'FAST'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 11
      TabStop = True
      OnClick = rbSpeedFastClick
    end
    object rbSpeedSlow: TRadioButton
      Left = 462
      Top = 243
      Width = 54
      Height = 17
      Caption = 'SLOW'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -12
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 12
      OnClick = rbSpeedFastClick
    end
    object editMaxDelayTime: TEdit
      Left = 456
      Top = 194
      Width = 129
      Height = 24
      Alignment = taCenter
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ImeName = 'Microsoft Office IME 2007'
      NumbersOnly = True
      ParentFont = False
      TabOrder = 13
      Text = '50'
      Visible = False
    end
  end
  object pPassword: TPanel
    Left = 309
    Top = 48
    Width = 206
    Height = 70
    BevelInner = bvLowered
    BevelKind = bkFlat
    BevelWidth = 3
    Color = clWhite
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    Visible = False
    object Panel61: TPanel
      Left = 7
      Top = 7
      Width = 80
      Height = 25
      BevelKind = bkFlat
      BevelOuter = bvNone
      BevelWidth = 2
      Caption = 'PassWord'
      Color = 14670047
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentBackground = False
      ParentFont = False
      TabOrder = 0
    end
    object PassEdit: TEdit
      Left = 89
      Top = 7
      Width = 105
      Height = 25
      BevelInner = bvLowered
      BevelKind = bkFlat
      BorderStyle = bsNone
      Color = clWhite
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBackground
      Font.Height = -15
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ImeMode = imDisable
      ImeName = 'Microsoft Office IME 2007'
      ParentFont = False
      PasswordChar = '*'
      TabOrder = 1
      OnKeyPress = PassEditKeyPress
    end
    object cancelBtn2: TAdvSmoothButton
      Left = 116
      Top = 32
      Width = 78
      Height = 29
      Appearance.PictureAlignment = taCenter
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -13
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'Cancel'
      Color = clWhite
      ParentFont = False
      TabOrder = 2
      Version = '2.1.1.5'
      OnClick = cancelBtn2Click
      TMSStyle = 8
    end
    object PasswordBtn: TAdvSmoothButton
      Left = 37
      Top = 32
      Width = 78
      Height = 29
      Appearance.PictureAlignment = taCenter
      Appearance.Font.Charset = DEFAULT_CHARSET
      Appearance.Font.Color = clWindowText
      Appearance.Font.Height = -13
      Appearance.Font.Name = 'Tahoma'
      Appearance.Font.Style = [fsBold]
      Appearance.Spacing = 0
      Appearance.Rounding = 3
      Appearance.WordWrapping = False
      Status.Caption = '0'
      Status.Appearance.Fill.Color = clRed
      Status.Appearance.Fill.ColorMirror = clNone
      Status.Appearance.Fill.ColorMirrorTo = clNone
      Status.Appearance.Fill.GradientType = gtSolid
      Status.Appearance.Fill.GradientMirrorType = gtSolid
      Status.Appearance.Fill.BorderColor = clGray
      Status.Appearance.Fill.Rounding = 0
      Status.Appearance.Fill.ShadowOffset = 0
      Status.Appearance.Fill.Glow = gmNone
      Status.Appearance.Font.Charset = DEFAULT_CHARSET
      Status.Appearance.Font.Color = clWhite
      Status.Appearance.Font.Height = -11
      Status.Appearance.Font.Name = 'Tahoma'
      Status.Appearance.Font.Style = []
      BevelColor = clMedGray
      Caption = 'OK'
      Color = clWhite
      ParentFont = False
      TabOrder = 3
      Version = '2.1.1.5'
      OnClick = PasswordBtnClick
      TMSStyle = 8
    end
  end
  object Client: TClientSocket
    Active = False
    ClientType = ctNonBlocking
    Host = '192.168.100.202'
    Port = 45000
    OnConnecting = ClientConnecting
    OnConnect = ClientConnect
    OnDisconnect = ClientDisconnect
    OnRead = ClientRead
    OnError = ClientError
    Left = 632
    Top = 176
  end
  object ReContactTimer: TTimer
    Enabled = False
    Interval = 2000
    OnTimer = ReContactTimerTimer
    Left = 627
    Top = 56
  end
  object SendTimer: TTimer
    Enabled = False
    Interval = 100
    OnTimer = SendTimerTimer
    Left = 742
    Top = 8
  end
  object StatusTimer: TTimer
    OnTimer = StatusTimerTimer
    Left = 632
    Top = 120
  end
  object rxTimer: TTimer
    Interval = 10
    OnTimer = rxTimerTimer
    Left = 694
    Top = 120
  end
  object Timer_AutoInspection: TTimer
    Interval = 200
    OnTimer = Timer_AutoInspectionTimer
    Left = 708
    Top = 72
  end
  object Timer_PLCConnect: TTimer
    Enabled = False
    OnTimer = Timer_PLCConnectTimer
    Left = 646
    Top = 8
  end
  object TrayDownTimer: TTimer
    Left = 640
    Top = 240
  end
  object TrayUpTimer: TTimer
    Left = 648
    Top = 304
  end
end
