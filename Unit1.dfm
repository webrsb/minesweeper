object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 597
  ClientWidth = 675
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIForm
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poDesktopCenter
  Visible = True
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object Image1: TImage
    Left = 56
    Top = 32
    Width = 17
    Height = 17
  end
  object MainMenu1: TMainMenu
    Left = 720
    Top = 8
    object N1: TMenuItem
      Caption = #36938#25138
      object N2: TMenuItem
        Caption = #26032#36938#25138
      end
      object N3: TMenuItem
        Caption = #36984#38917
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #38626#38283
      end
    end
  end
end
