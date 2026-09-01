object Form_PLCInterface: TForm_PLCInterface
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'PLC Interface'
  ClientHeight = 861
  ClientWidth = 1082
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label4: TLabel
    Left = 376
    Top = 16
    Width = 31
    Height = 13
    Caption = 'Label4'
  end
  object GroupBox_PLC_PC: TGroupBox
    Left = 2
    Top = 50
    Width = 1071
    Height = 814
    Caption = 'PLC - PC INTERFACE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnClick = GroupBox_PLC_PCClick
    object ListView_PLC: TListView
      Left = 15
      Top = 32
      Width = 520
      Height = 769
      Columns = <
        item
          Caption = 'PLC_Address'
          Width = 120
        end
        item
          Caption = 'PLC_Name'
          Width = 180
        end
        item
          Caption = 'PLC_Value'
          Width = 200
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
    end
    object ListView_PC: TListView
      Left = 539
      Top = 32
      Width = 520
      Height = 769
      Columns = <
        item
          Caption = 'PC_Address'
          Width = 120
        end
        item
          Caption = 'PC_Name'
          Width = 180
        end
        item
          Caption = 'PC_Value'
          Width = 200
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      GridLines = True
      ReadOnly = True
      RowSelect = True
      ParentFont = False
      TabOrder = 1
      ViewStyle = vsReport
    end
  end
  object AdvSmoothButton_Close: TAdvSmoothButton
    Left = 966
    Top = 4
    Width = 100
    Height = 40
    Appearance.Font.Charset = DEFAULT_CHARSET
    Appearance.Font.Color = clBlack
    Appearance.Font.Height = -15
    Appearance.Font.Name = 'Tahoma'
    Appearance.Font.Style = [fsBold]
    Appearance.Rounding = 3
    Status.Caption = '0'
    Status.Appearance.Fill.Color = clRed
    Status.Appearance.Fill.ColorMirror = clNone
    Status.Appearance.Fill.ColorMirrorTo = clNone
    Status.Appearance.Fill.GradientType = gtSolid
    Status.Appearance.Fill.GradientMirrorType = gtSolid
    Status.Appearance.Fill.BorderColor = clGray
    Status.Appearance.Fill.Rounding = 8
    Status.Appearance.Fill.ShadowOffset = 0
    Status.Appearance.Fill.Glow = gmNone
    Status.Appearance.Font.Charset = DEFAULT_CHARSET
    Status.Appearance.Font.Color = clWhite
    Status.Appearance.Font.Height = -11
    Status.Appearance.Font.Name = 'Tahoma'
    Status.Appearance.Font.Style = []
    BevelColor = clSilver
    Caption = 'Close'
    Color = 14935011
    ParentFont = False
    TabOrder = 1
    Version = '2.1.1.5'
    OnClick = AdvSmoothButton_CloseClick
    TMSStyle = 8
  end
  object Panel1: TPanel
    Left = 1090
    Top = 8
    Width = 408
    Height = 845
    BorderStyle = bsSingle
    Color = 15790320
    ParentBackground = False
    TabOrder = 2
    Visible = False
    object Label1: TLabel
      Left = 16
      Top = 12
      Width = 78
      Height = 19
      Caption = 'PLC TEST'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = [fsBold, fsUnderline]
      ParentFont = False
    end
    object lblConnection: TLabel
      Left = 224
      Top = 15
      Width = 153
      Height = 16
      Alignment = taRightJustify
      AutoSize = False
      Caption = 'PC PLC : DISCONNECTED'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object lblTestStatus: TLabel
      Left = 16
      Top = 680
      Width = 361
      Height = 42
      AutoSize = False
      Caption = 'Select a test item.'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clNavy
      Font.Height = -13
      Font.Name = 'Tahoma'
      Font.Style = [fsBold]
      ParentFont = False
      WordWrap = True
    end
    object GroupBox1: TGroupBox
      Left = 10
      Top = 438
      Width = 382
      Height = 226
      Caption = 'IR / OCV Result Data (400 CH)'
      TabOrder = 0
      object Label5: TLabel
        Left = 16
        Top = 31
        Width = 79
        Height = 16
        Caption = 'IR Base Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 16
        Top = 68
        Width = 92
        Height = 16
        Caption = 'OCV Base Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 199
        Top = 103
        Width = 24
        Height = 13
        Caption = 'STEP'
      end
      object Label9: TLabel
        Left = 16
        Top = 132
        Width = 345
        Height = 26
        AutoSize = False
        Caption = 'IR raw = Base x 100, OCV raw = Base x 10 + channel STEP'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGrayText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object editIR: TEdit
        Left = 160
        Top = 27
        Width = 201
        Height = 21
        TabOrder = 0
        Text = '16.5'
      end
      object editOCV: TEdit
        Left = 160
        Top = 64
        Width = 201
        Height = 21
        TabOrder = 1
        Text = '3100.1'
      end
      object chkChannelIncrement: TCheckBox
        Left = 16
        Top = 103
        Width = 177
        Height = 17
        Caption = 'Increment each channel'
        Checked = True
        State = cbChecked
        TabOrder = 2
      end
      object editIncrement: TEdit
        Left = 242
        Top = 99
        Width = 119
        Height = 21
        TabOrder = 3
        Text = '1'
      end
      object btnWriteIrOcvValue: TButton
        Left = 220
        Top = 166
        Width = 141
        Height = 42
        Caption = 'APPLY 400 CH'
        TabOrder = 4
        OnClick = btnWriteIrOcvValueClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 10
      Top = 267
      Width = 382
      Height = 160
      Caption = 'IROCV NG Channels'
      TabOrder = 1
      object Label7: TLabel
        Left = 16
        Top = 23
        Width = 345
        Height = 16
        AutoSize = False
        Caption = 'Channel or range example : 1,3,5-10,400'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clGrayText
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object lblNgStatus: TLabel
        Left = 16
        Top = 119
        Width = 345
        Height = 18
        AutoSize = False
        Caption = 'Not applied'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = [fsBold]
        ParentFont = False
      end
      object editIrOcvNg: TEdit
        Left = 16
        Top = 44
        Width = 345
        Height = 21
        TabOrder = 0
        Text = 
          '1,22,43,64,85,106,127,148,169,190,211,232,253,274,295,316,337,35' +
          '8,379,400'
      end
      object btnWriteNgValue: TButton
        Left = 16
        Top = 75
        Width = 105
        Height = 32
        Caption = 'APPLY'
        TabOrder = 1
        OnClick = btnWriteNgValueClick
      end
      object btnClearNg: TButton
        Left = 128
        Top = 75
        Width = 105
        Height = 32
        Caption = 'CLEAR (ALL OK)'
        TabOrder = 2
        OnClick = btnClearNgClick
      end
      object btnAllNg: TButton
        Left = 240
        Top = 75
        Width = 121
        Height = 32
        Caption = 'ALL NG'
        TabOrder = 3
        OnClick = btnAllNgClick
      end
    end
    object GroupBox3: TGroupBox
      Left = 10
      Top = 47
      Width = 382
      Height = 208
      Caption = 'PC Word Read / Write'
      TabOrder = 2
      object Label2: TLabel
        Left = 16
        Top = 22
        Width = 101
        Height = 16
        Caption = 'DEVICE ADDRESS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 16
        Top = 81
        Width = 78
        Height = 16
        Caption = 'WORD VALUE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object lblWordArea: TLabel
        Left = 16
        Top = 142
        Width = 345
        Height = 42
        AutoSize = False
        Caption = 'Address area is detected automatically.'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clNavy
        Font.Height = -11
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
        WordWrap = True
      end
      object cbAddress: TComboBox
        Left = 16
        Top = 44
        Width = 345
        Height = 21
        TabOrder = 0
        Text = 'D45001 - STAGE AUTO READY'
        Items.Strings = (
          'D45000 - HEART BEAT'
          'D45001 - STAGE AUTO READY'
          'D45002 - PC ERROR'
          'D45003 - TRAY OUT'
          'D45004 - PROB OPEN'
          'D45005 - PROB CLOSE'
          'D45006 - MEASURING'
          'D45007 - NG ALARM'
          'D45008 - WRITE COMPLETE'
          'D45009 - REMEASURE'
          'D45010 - NG COUNT'
          'D45011 - IR MIN LOW WORD'
          'D45013 - IR MAX LOW WORD'
          'D45015 - OCV MIN LOW WORD'
          'D45017 - OCV MAX LOW WORD'
          'D45030 - OK/NG WORD #1'
          'D45070 - IR WORD #1'
          'D46000 - OCV WORD #1'
          'D47000 - RESULT CODE #1')
      end
      object editValue: TEdit
        Left = 16
        Top = 101
        Width = 113
        Height = 21
        TabOrder = 1
        Text = '1'
      end
      object btnWriteValue: TButton
        Left = 208
        Top = 94
        Width = 73
        Height = 34
        Caption = 'WRITE'
        TabOrder = 2
        OnClick = btnWriteValueClick
      end
      object btnReadValue: TButton
        Left = 133
        Top = 94
        Width = 69
        Height = 34
        Caption = 'READ'
        TabOrder = 3
        OnClick = btnReadValueClick
      end
      object btnSetZero: TButton
        Left = 287
        Top = 94
        Width = 34
        Height = 34
        Caption = '0'
        TabOrder = 4
        OnClick = btnSetPresetClick
      end
      object btnSetOne: TButton
        Tag = 1
        Left = 327
        Top = 94
        Width = 34
        Height = 34
        Caption = '1'
        TabOrder = 5
        OnClick = btnSetPresetClick
      end
    end
  end
  object Timer_Update: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer_UpdateTimer
    Left = 258
    Top = 24
  end
end
