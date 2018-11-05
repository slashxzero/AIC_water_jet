object Form1: TForm1
  Left = 74
  Top = 37
  Width = 1347
  Height = 716
  Caption = 'Form1'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 16
    Top = 16
    Width = 36
    Height = 24
    Caption = 'Hue'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label2: TLabel
    Left = 232
    Top = 16
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label3: TLabel
    Left = 440
    Top = 16
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label4: TLabel
    Left = 16
    Top = 56
    Width = 31
    Height = 24
    Caption = 'Sat.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label5: TLabel
    Left = 232
    Top = 56
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label6: TLabel
    Left = 440
    Top = 56
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label7: TLabel
    Left = 16
    Top = 96
    Width = 32
    Height = 24
    Caption = 'Val.'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label8: TLabel
    Left = 232
    Top = 96
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label9: TLabel
    Left = 440
    Top = 96
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Image_Com: TImage
    Left = 8
    Top = 136
    Width = 512
    Height = 512
  end
  object Image_Hue: TImage
    Left = 528
    Top = 136
    Width = 256
    Height = 256
    OnMouseMove = Image_HueMouseMove
  end
  object Image_Sat: TImage
    Left = 792
    Top = 136
    Width = 256
    Height = 256
    OnMouseMove = Image_HueMouseMove
  end
  object Image_Val: TImage
    Left = 1056
    Top = 136
    Width = 256
    Height = 256
    OnMouseMove = Image_HueMouseMove
  end
  object Image_Bin_Val: TImage
    Left = 1056
    Top = 400
    Width = 256
    Height = 256
  end
  object Label12: TLabel
    Left = 960
    Top = 16
    Width = 19
    Height = 24
    Caption = 'X:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label13: TLabel
    Left = 984
    Top = 16
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label14: TLabel
    Left = 960
    Top = 48
    Width = 17
    Height = 24
    Caption = 'Y:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label15: TLabel
    Left = 984
    Top = 48
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label16: TLabel
    Left = 1024
    Top = 80
    Width = 18
    Height = 24
    Caption = 'R:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label17: TLabel
    Left = 1048
    Top = 16
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label18: TLabel
    Left = 1024
    Top = 48
    Width = 19
    Height = 24
    Caption = 'G:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label19: TLabel
    Left = 1048
    Top = 48
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label20: TLabel
    Left = 1024
    Top = 16
    Width = 17
    Height = 24
    Caption = 'B:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label21: TLabel
    Left = 1048
    Top = 80
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Image_Bin_Hue: TImage
    Left = 528
    Top = 400
    Width = 256
    Height = 256
  end
  object Image_Bin_Sat: TImage
    Left = 792
    Top = 400
    Width = 256
    Height = 256
  end
  object Label10: TLabel
    Left = 600
    Top = 16
    Width = 52
    Height = 24
    Caption = 'Erode'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object Label11: TLabel
    Left = 824
    Top = 16
    Width = 9
    Height = 20
    Caption = '0'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object TrackBar1: TTrackBar
    Left = 64
    Top = 16
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 0
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar1Change
  end
  object TrackBar2: TTrackBar
    Left = 272
    Top = 16
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 1
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar2Change
  end
  object CheckBox1: TCheckBox
    Left = 480
    Top = 16
    Width = 97
    Height = 25
    Caption = 'In Range'
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 2
    OnClick = CheckBox1Click
  end
  object TrackBar3: TTrackBar
    Left = 64
    Top = 56
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 3
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar3Change
  end
  object TrackBar4: TTrackBar
    Left = 272
    Top = 56
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 4
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar4Change
  end
  object CheckBox2: TCheckBox
    Left = 480
    Top = 56
    Width = 97
    Height = 25
    Caption = 'In Range'
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 5
    OnClick = CheckBox1Click
  end
  object TrackBar5: TTrackBar
    Left = 64
    Top = 96
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 6
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar5Change
  end
  object TrackBar6: TTrackBar
    Left = 272
    Top = 96
    Width = 168
    Height = 33
    Max = 255
    Orientation = trHorizontal
    Frequency = 20
    Position = 64
    SelEnd = 0
    SelStart = 0
    TabOrder = 7
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar6Change
  end
  object CheckBox3: TCheckBox
    Left = 480
    Top = 96
    Width = 97
    Height = 25
    Caption = 'In Range'
    Checked = True
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    State = cbChecked
    TabOrder = 8
    OnClick = CheckBox1Click
  end
  object Button1: TButton
    Left = 1168
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Load Image'
    TabOrder = 9
  end
  object Button2: TButton
    Left = 1080
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Next'
    TabOrder = 10
  end
  object Button3: TButton
    Left = 1080
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Prev'
    TabOrder = 11
  end
  object Button4: TButton
    Left = 1168
    Top = 40
    Width = 75
    Height = 25
    Caption = 'Connect'
    TabOrder = 12
    OnClick = Button4Click
  end
  object Button5: TButton
    Left = 1168
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Send CMD'
    TabOrder = 13
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 1168
    Top = 104
    Width = 75
    Height = 25
    Caption = 'Draw Block'
    TabOrder = 14
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 1080
    Top = 72
    Width = 75
    Height = 25
    Caption = 'Select'
    TabOrder = 15
  end
  object TrackBar7: TTrackBar
    Left = 656
    Top = 16
    Width = 168
    Height = 33
    Orientation = trHorizontal
    Frequency = 1
    Position = 0
    SelEnd = 0
    SelStart = 0
    TabOrder = 16
    TickMarks = tmBottomRight
    TickStyle = tsAuto
    OnChange = TrackBar7Change
  end
  object IdTCPClient1: TIdTCPClient
    Port = 0
    Left = 16
    Top = 144
  end
  object OpenDialog1: TOpenDialog
    Left = 56
    Top = 144
  end
  object SaveDialog1: TSaveDialog
    Left = 96
    Top = 144
  end
  object Timer1: TTimer
    Interval = 50
    OnTimer = Timer1Timer
    Left = 136
    Top = 144
  end
end
