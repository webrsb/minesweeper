//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TForm *Form2;
bool MoveIn = false;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	int num_x = 9,
		num_y = 9,
		num_t = num_x * num_y;
	int img_h=Image1->Height,
		img_w=Image1->Width,
		img_t=Image1->Top,
		img_l=Image1->Left,
		img_padding=5;
	int num_h = num_x * num_y/2;
	imgs = new TImage*[num_t];
		for (int i=0 ; i<num_t ; ++i){
			imgs[i] = new TImage(NULL);
			imgs[i]->Parent  =Form1;
			imgs[i]->AutoSize= false;
			imgs[i]->Height  = 19; // 影像物件的高度
			imgs[i]->Width   = 18; // 影像物件的寬度
			imgs[i]->OnMouseMove = imgsMouseMove;
			imgs[i]->Stretch = True;
			imgs[i]->Visible = true;
			imgs[i]->Enabled = true;
			imgs[i]->Tag     = i;
			imgs[i]->Picture->LoadFromFile("pic\\0.bmp");  // 畫一下顏色表示已經在Form上
	  }
	   for (int i=0 ; i<num_t ; ++i){
         if(i%num_x==0){
			imgs[i]->Top  = img_t + i / num_x * (img_h + img_padding);
            imgs[i]->Left = img_l;
		 }else{
            imgs[i]->Top  = img_t + i / num_x * (img_h + img_padding);
            imgs[i]->Left = img_l + i % num_x * (img_w + img_padding);
		 }
	   }
}
//---------------------------------------------------------------------------



void __fastcall TForm1::N3Click(TObject *Sender)
{

   TForm* pChildForm = new TForm(Application);
   pChildForm->FormStyle = fsMDIChild;
   pChildForm->OnClose = Form2Close;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------



void __fastcall TForm1::Form2Close(TObject *Sender, TCloseAction &Action)
{
	Action=caFree;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseMove(TObject *Sender, TShiftState Shift, int X,
		  int Y)
{
  TImage *imgshow=(TImage*)Sender;
  int i=StrToInt(imgshow->Tag);

  imgshow->Picture->LoadFromFile("1.bmp");
 // ShowMessage(i);
}
//---------------------------------------------------------------------------



void __fastcall TForm1::imgsClick(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
  int i=imgshow->Tag;
  //ShowMessage(i);
  imgshow->Picture->LoadFromFile("1.bmp");
}
//---------------------------------------------------------------------------

