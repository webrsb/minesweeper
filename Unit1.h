//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ImgList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TMenuItem *N1;
	TMenuItem *N99101;
	TMenuItem *N1616401;
	TMenuItem *N1630991;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label1;
	TLabel *Label4;
	TTimer *Timer1;
	TPanel *Panel1;
	TImage *Image1;
	TMenuItem *N2;
	TMenuItem *N3;
	TPanel *Panel2;
	TLabel *Label5;
	TLabel *Label6;
	TLabel *Label7;
	TLabel *Label8;
	TEdit *Edit1;
	TEdit *Edit2;
	TButton *Button1;
	TButton *Button2;
	TEdit *Edit3;
	TImageList *ImageList1;
	TLabel *Label10;
	TEdit *Edit4;
	TLabel *Label11;
	TLabel *Label12;
	TLabel *Label13;
	TLabel *Label14;
	TLabel *Label9;
	TLabel *Label15;
	TLabel *Label16;
	void __fastcall imgsMouseEnter(TObject *Sender);
	void __fastcall imgsMouseLeave(TObject *Sender);
	void __fastcall imgsMouseEnter_flag(TObject *Sender);
	void __fastcall imgsMouseLeave_flag(TObject *Sender);
	void __fastcall imgsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall imgsMouseDown_Empty(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall imgsClick(TObject *Sender);
	void __fastcall imgsClick_flag(TObject *Sender);
	void __fastcall N99101Click(TObject *Sender);
	void __fastcall N1616401Click(TObject *Sender);
	void __fastcall N1630991Click(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall imgsClick_Empty(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall N2Click(TObject *Sender);
	void __fastcall imgsMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall N3Click(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Edit3KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Edit4KeyUp(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall FormClick(TObject *Sender);
	void __fastcall Edit4Enter(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void CreateImgs(int,int);
	void Start();
	int MinesCheck(int,int);
	int MinesFound(int);
	void Spread(int);
	TColor ImgsColor(int);
	void Clear();
	void WinCheck();
	void Gameover(int);
	void GetPersent();
};

//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif

