object Form_PLCInterface: TForm_PLCInterface
  Left = 0
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'PLC Interface'
  ClientHeight = 861
  ClientWidth = 1297
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
    Width = 1290
    Height = 814
    Caption = 'PLC - PC INTERFACE'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Tahoma'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    OnDblClick = GroupBox_PLC_PCDblClick
    object ListView_PLC: TListView
      Left = 16
      Top = 32
      Width = 630
      Height = 769
      Columns = <
        item
          Caption = 'PLC_Address'
          Width = 120
        end
        item
          Caption = 'PLC_Name'
          Width = 200
        end
        item
          Caption = 'PLC_Value'
          Width = 290
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
      Left = 652
      Top = 32
      Width = 630
      Height = 769
      Columns = <
        item
          Caption = 'PC_Address'
          Width = 116
        end
        item
          Caption = 'PC_Name'
          Width = 200
        end
        item
          Caption = 'PC_Value'
          Width = 290
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
    Left = 1181
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
    Left = 48
    Top = 280
    Width = 721
    Height = 313
    BorderStyle = bsSingle
    TabOrder = 2
    Visible = False
    object Label1: TLabel
      Left = 300
      Top = 8
      Width = 70
      Height = 19
      Caption = 'PLC TEST'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Tahoma'
      Font.Style = []
      ParentFont = False
    end
    object GroupBox1: TGroupBox
      Left = 447
      Top = 50
      Width = 257
      Height = 250
      Caption = 'IR/OCV Value'
      TabOrder = 0
      object Label5: TLabel
        Left = 169
        Top = 40
        Width = 48
        Height = 16
        Caption = 'IR Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 156
        Top = 104
        Width = 61
        Height = 16
        Caption = 'OCV Value'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object editIR: TEdit
        Left = 39
        Top = 62
        Width = 178
        Height = 21
        TabOrder = 0
        Text = '16.5'
      end
      object editOCV: TEdit
        Left = 39
        Top = 126
        Width = 178
        Height = 21
        TabOrder = 1
        Text = '3100.1'
      end
      object btnWriteIrOcvValue: TButton
        Left = 104
        Top = 153
        Width = 113
        Height = 40
        Caption = 'Write IROCV Value'
        TabOrder = 2
        OnClick = btnWriteIrOcvValueClick
      end
    end
    object GroupBox2: TGroupBox
      Left = 8
      Top = 188
      Width = 434
      Height = 112
      Caption = 'IROCV NG Value'
      TabOrder = 1
      object editIrOcvNg: TEdit
        Left = 16
        Top = 30
        Width = 401
        Height = 21
        TabOrder = 0
        Text = 
          '1,22,43,64,85,106,127,148,169,190,211,232,253,274,295,316,337,35' +
          '8,379,400'
      end
      object btnWriteNgValue: TButton
        Left = 304
        Top = 65
        Width = 113
        Height = 40
        Caption = 'Write NG Value'
        TabOrder = 1
        OnClick = btnWriteNgValueClick
      end
    end
    object GroupBox3: TGroupBox
      Left = 8
      Top = 47
      Width = 434
      Height = 135
      Caption = 'Write Value'
      TabOrder = 2
      object Label2: TLabel
        Left = 16
        Top = 22
        Width = 55
        Height = 16
        Caption = 'ADDRESS'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 16
        Top = 75
        Width = 37
        Height = 16
        Caption = 'VALUE'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'Tahoma'
        Font.Style = []
        ParentFont = False
      end
      object cbAddress: TComboBox
        Left = 16
        Top = 44
        Width = 225
        Height = 21
        TabOrder = 0
        Text = '45000'
        Items.Strings = (
          '45000'
          '45001'
          '45002'
          '45003'
          '45004'
          '45005'
          '45006'
          '45007'
          '45008'
          '45009'
          '45010'
          '45020'
          '45021'
          '')
      end
      object editValue: TEdit
        Left = 16
        Top = 98
        Width = 225
        Height = 21
        TabOrder = 1
        Text = '1'
      end
      object btnWriteValue: TButton
        Left = 247
        Top = 56
        Width = 83
        Height = 54
        Caption = 'Write Value'
        TabOrder = 2
        OnClick = btnWriteValueClick
      end
      object Button1: TButton
        Left = 336
        Top = 56
        Width = 83
        Height = 54
        Caption = 'Write Ocv'
        TabOrder = 3
        OnClick = Button1Click
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
