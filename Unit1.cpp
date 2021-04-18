//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <stdio.h>
#include <time.h>
#include <stdexcept>

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
TImage **imgs;
int **Data;
int num_t;  //地雷總數
int first_click,TotalMines,TotalMines_D,num_x,num_y,remainder,gametime,RL_click;
int *num;   //地雷陣列
int nnn[8],nnn3[8];
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}

//---------------------------------------------------------------------------
void TForm1::Start()
{
	Panel2->Visible = false;
	CreateImgs(num_x,num_y);
	first_click = true;//第一次點擊
	RL_click = false;
	//0索引編號 1地雷位置 2是否插旗 3是否按開
	Data = new int*[num_t];
	for(int i=0; i<num_t; i++){
		Data[i] = new int[4];
		Data[i][0] = i;
		Data[i][1] = 0;
		Data[i][2] = 0;
		Data[i][3] = 0;
	}
	int P_height = Panel1->Height,
		P_width = Panel1->Width,
		P_top = Panel1->Top,
		P_left = Panel1->Left,
		L_h = 5;
	int w = P_left*3 + P_width -15;
	int h = P_top*2 + P_height + Label1->Height+40;
	if(w <=242){
	   Form1->Width = 243;
	}else{
		Form1->Width = w;
	}
	if(h <= 219){
	   Form1->Height = 220;
	}else{
		Form1->Height= h;
	}
	Label1->Top = P_top*2 + P_height + L_h - 20;
	Label2->Top = P_top*2 + P_height + L_h - 20;
	Label3->Top = P_top*2 + P_height + L_h - 20;
	Label4->Top = P_top*2 + P_height + L_h - 20;

}
//---------------------------------------------------------------------------
void TForm1::Clear()
{
	Panel1->AutoSize =false;
	first_click = true;
	Timer1->Enabled = false;
	gametime = 0;//遊戲時間初使化
	Label4->Caption = gametime;
	if(imgs != NULL)    //清除圖片
	{
		for(int i=num_t-1;i>=0;i--){
			delete imgs[i];
		}
		imgs = NULL;
	}
	if(num != NULL){    // 刪除資料
		delete []num;
	}
	if(Data != NULL)    //刪除資料
	{
		for(int i=num_t-1;i>=0;i--)
		  delete Data[i];
		Data = NULL;
	}
	for(int i=0;i<8;i++){
		nnn3[i] = -1;
		nnn[i] = -1;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseEnter(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
	ImageList1->GetBitmap(1,imgshow->Picture->Bitmap);
	imgshow->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseLeave(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
	ImageList1->GetBitmap(0,imgshow->Picture->Bitmap);
	imgshow->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseEnter_flag(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
	ImageList1->GetBitmap(5,imgshow->Picture->Bitmap);
	imgshow->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseLeave_flag(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
	ImageList1->GetBitmap(4,imgshow->Picture->Bitmap);
	imgshow->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imgsMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	int j=0;
	while(nnn3[j]!=-1 && j < 8){
		if(Data[nnn3[j]][3] == 0 && Data[nnn3[j]][2]==0)
		ImageList1->GetBitmap(0,imgs[nnn3[j]]->Picture->Bitmap);
		imgs[nnn3[j]]->Refresh();
		j++;
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::imgsMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y)
{
	TImage *imgshow=(TImage*)Sender;
	int NO = imgshow->Tag;
	if (Shift == TShiftState() << ssLeft << ssRight){
		RL_click = true;
		TImage *imgshow=(TImage*)Sender;
		int NO = imgshow->Tag;
		MinesFound(NO);
		for(int i=0;i<8;i++)
		nnn3[i] = nnn[i];
		for(int i=0;nnn[i]!=-1 && i < 8;i++){
			if(Data[nnn[i]][3] == 0 && Data[nnn[i]][2]==0)
			ImageList1->GetBitmap(2,imgs[nnn[i]]->Picture->Bitmap);
			imgs[nnn[i]]->Refresh();
		}
	}else if(Button==mbLeft){
		if(Data[NO][2] == 1){
			imgs[NO]->OnClick = imgsClick_flag;
			ImageList1->GetBitmap(4,imgshow->Picture->Bitmap);
			imgshow->Refresh();
		}else if(Data[NO][2] == 0){
			ImageList1->GetBitmap(2,imgshow->Picture->Bitmap);
			imgshow->Refresh();
		}
	}else if(Button==mbRight){
		if(Data[NO][2] == 0){
			Data[NO][2] = 1;
			ImageList1->GetBitmap(5,imgshow->Picture->Bitmap);
			imgshow->Refresh();
			imgs[NO]->OnMouseLeave = imgsMouseLeave_flag;
			imgs[NO]->OnMouseEnter = imgsMouseEnter_flag;
			imgs[NO]->OnClick = imgsClick;
			TotalMines_D --;
			Label3->Caption = IntToStr(TotalMines_D);
		}else if(Data[NO][2] == 1){
			Data[NO][2] = 0;
			ImageList1->GetBitmap(1,imgshow->Picture->Bitmap);
			imgshow->Refresh();
			imgs[NO]->OnMouseLeave = imgsMouseLeave;
			imgs[NO]->OnMouseEnter = imgsMouseEnter;
			TotalMines_D ++;
			Label3->Caption = IntToStr(TotalMines_D);
			imgs[NO]->OnClick = imgsClick;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsMouseDown_Empty(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y){
	if (Shift == TShiftState() << ssLeft << ssRight){  //同時按掃雷
		RL_click = true;
		TImage *imgshow=(TImage*)Sender;
		int NO = imgshow->Tag;
		MinesFound(NO);
		for(int i=0;i<8;i++)
		nnn3[i] = nnn[i];
		for(int i=0;nnn[i]!=-1 && i < 8;i++){
			if(Data[nnn[i]][3] == 0 && Data[nnn[i]][2]==0)
			ImageList1->GetBitmap(2,imgs[nnn[i]]->Picture->Bitmap);
			imgs[nnn[i]]->Refresh();
		}
	}

}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsClick_Empty(TObject *Sender){
if(RL_click == true){
	TImage *imgshow=(TImage*)Sender;
	int NO = imgshow->Tag;
	int Mines;
	Mines = MinesFound(NO); //檢查按下四週之地雷
	int nnn2[8] = nnn;
	int j = 0;
	bool flag = true;
	bool gameover = false;
	int flag_num = 0;
	while(nnn2[j]!=-1 && j < 8){
		if(Data[nnn2[j]][2] == 1){
			flag_num ++;
		}
		j++;
	}
	j=0;
	while(nnn2[j]!=-1 && j < 8){
		if(Data[nnn2[j]][1] == 0 && Data[nnn2[j]][2] ==1 && Mines == flag_num){    //沒地雷有插旗
			for(int i=0;i<TotalMines;i++){                  //地雷數剛好等於旗子數時
				Data[num[i]][3] = 1;
				if(Data[num[i]][2] == 1 && Data[num[i]][1] == 1){
				ImageList1->GetBitmap(9,imgs[num[i]]->Picture->Bitmap);
				imgs[num[i]]->Refresh();
				}else{
				ImageList1->GetBitmap(6,imgs[num[i]]->Picture->Bitmap);
				imgs[num[i]]->Refresh();
				}
				imgs[num[i]]->OnMouseEnter = NULL;
				imgs[num[i]]->OnMouseLeave = NULL;
			}
			ImageList1->GetBitmap(8,imgs[nnn2[j]]->Picture->Bitmap);
			imgs[nnn2[j]]->Refresh();       	//錯誤之旗子
			imgs[nnn2[j]]->OnMouseEnter = NULL;
			imgs[nnn2[j]]->OnMouseLeave = NULL;
			for(int i=0;i<num_t;i++){
				imgs[i]->OnMouseDown = NULL;
				imgs[i]->OnClick = NULL;
			}
			gameover = true;
		}else if(Data[nnn2[j]][1] == 1 && Data[nnn2[j]][2] ==0){  //有地雷沒插旗
			flag = false;
		}
		j++;
	}
	if(flag == true){   //有地雷，全都有插旗
		for(int i=0;nnn2[i]!=-1 && i < 8;i++){
			if(Data[nnn2[i]][1] == 0)
			MinesCheck(nnn2[i],1);
		}
	}
	if(gameover == true){
		Gameover(1);
	}
	RL_click = false;
}
}
//開始按
void __fastcall TForm1::imgsClick(TObject *Sender){
	TImage *imgshow=(TImage*)Sender;
	int NO = imgshow->Tag;
if(RL_click == false){
	ImageList1->GetBitmap(3,imgshow->Picture->Bitmap);
	imgshow->Refresh();
	imgshow->OnMouseEnter = NULL;
	imgshow->OnMouseLeave = NULL;
	imgshow->OnMouseDown = imgsMouseDown_Empty;
	imgshow->OnClick = imgsClick_Empty;
	//第一次點擊建立亂數
	//0索引編號 1地雷位置 2插旗子 3是否按開
	if(first_click == true){
		num = new int[num_t];
		bool flag;
		int x = 0,randa;
		while(x<TotalMines){
			do{
				randa = rand() % (num_t);//0~num_t
				num[x] = randa;
				flag = true;
				if(NO == randa)
					flag = false;
				for(int i=0;i<x;i++){
					if(num[i] == randa){
						flag = false;
					}
				}
			}while(!flag);
		Data[num[x]][1] = 1;
		x++;
		}
		first_click = false;
		Timer1->Enabled = true;//開始計時
	}
	MinesCheck(NO,0);
	}else{
		if(Data[NO][2] == 1){
			ImageList1->GetBitmap(5,imgshow->Picture->Bitmap);
			imgshow->Refresh();
		}else{
			ImageList1->GetBitmap(1,imgshow->Picture->Bitmap);
			imgshow->Refresh();
		}
	}
	RL_click = false;
}
//---------------------------------------------------------------------------
int TForm1::MinesCheck(int NO,int Mode){   //檢查該點是否有地雷，和顯示數字
	if(Data[NO][1] == 1 && Mode == 0){
		Data[NO][3] = 1;
		for(int i=0;i<TotalMines;i++){
			Data[num[i]][3] = 1;
			if(Data[num[i]][1] == 1 && Data[num[i]][2] == 1){
				ImageList1->GetBitmap(9,imgs[num[i]]->Picture->Bitmap);
				imgs[num[i]]->Refresh();
			}else if(Data[num[i]][1] == 1){
				ImageList1->GetBitmap(6,imgs[num[i]]->Picture->Bitmap);
				imgs[num[i]]->Refresh();
			}
			imgs[num[i]]->OnMouseEnter = NULL;
			imgs[num[i]]->OnMouseLeave = NULL;
		}
		for(int i=0;i<num_t;i++){
			imgs[i]->OnMouseDown = NULL;
			imgs[i]->OnClick = NULL;
		}
		ImageList1->GetBitmap(7,imgs[NO]->Picture->Bitmap);
		imgs[NO]->Refresh();
		Gameover(0);
	}else if(NO>=0 && NO < num_t && Data[NO][3] == 0 && Data[NO][2] == 0){
	Data[NO][3] = 1;
	int Mines = MinesFound(NO);
		//模式1擴展
		if(Mode == 1){
			ImageList1->GetBitmap(3,imgs[NO]->Picture->Bitmap);
			imgs[NO]->Refresh();
			imgs[NO]->OnMouseEnter = NULL;
			imgs[NO]->OnMouseLeave = NULL;
			imgs[NO]->OnMouseDown = imgsMouseDown_Empty;
			imgs[NO]->OnClick = imgsClick_Empty;
		//模式0顯示數字
		}
		if(Mines != 0){
		imgs[NO]->Canvas->Brush->Style=bsClear;
		imgs[NO]->Canvas->Font->Color=ImgsColor(Mines);
		imgs[NO]->Canvas->Font->Size=14;
		imgs[NO]->Canvas->TextOut(3.2, -4.0, Mines);
		}else{
			Spread(NO);
		}
		remainder --;
		WinCheck();
		return Mines;
	}
	return -1;
//已點擊
}
//---------------------------------------------------------------------------
int TForm1::MinesFound(int NO){
	int NO_x,NO_y;      //轉x,y座標
		NO_x = NO%num_x;
		NO_y = NO/num_x;
	int iarr[] = {-1,-1,-1,-1,-1,-1,-1,-1};
	for(int i=0;i<8;i++)    //檢查邊線
		iarr[i] = -1;
	if(NO_x == num_x-1 && NO_y == 0){//右上
		iarr[0]=3;iarr[1]=5;iarr[2]=6;
	}else if(NO_x == num_x-1 && NO_y == num_y-1){   //右下
		iarr[0]=0;iarr[1]=1;iarr[2]=3;
	}else if(NO_x == 0 && NO_y == num_y-1){   //左下
		iarr[0]=1;iarr[1]=2;iarr[2]=4;
	}else if(NO_x == 0 && NO_y == 0){   //左上
		iarr[0]=4;iarr[1]=6;iarr[2]=7;
	}else if(NO_x == num_x-1){  //右排
		iarr[0]=0;iarr[1]=1;iarr[2]=3;iarr[3]=5;iarr[4]=6;
	}else if(NO_y == num_y-1){   //下排
		iarr[0]=0;iarr[1]=1;iarr[2]=2;iarr[3]=3;iarr[4]=4;
	}else if(NO_x == 0){   //左排
		iarr[0]=1;iarr[1]=2;iarr[2]=4;iarr[3]=6;iarr[4]=7;
	}else if(NO_y == 0){  //上排
		iarr[0]=3;iarr[1]=4;iarr[2]=5;iarr[3]=6;iarr[4]=7;
	}else{               //中間
		iarr[0]=0;iarr[1]=1;iarr[2]=2;iarr[3]=3;iarr[4]=4;iarr[5]=5;iarr[6]=6;iarr[7]=7;
	}
	for(int i=0;i<8;i++)
		nnn[i] = -1;
	for(int i=0;i<8;i++){
		if(iarr[i] == -1)
		break;
		switch(iarr[i]){
			case 0:
			nnn[i] = NO - num_x -1;
			break;
			case 1:
			nnn[i] = NO - num_x;
			break;
			case 2:
			nnn[i] = NO - num_x +1;
			break;
			case 3:
			nnn[i] = NO -1;
			break;
			case 4:
			nnn[i] = NO +1;
			break;
			case 5:
			nnn[i] = NO + num_x -1;
			break;
			case 6:
			nnn[i] = NO + num_x;
			break;
			case 7:
			nnn[i] = NO + num_x +1;
			break;
		}
	}
	int j = 0;
	int Mines = 0;  //地雷總數
	while(nnn[j]!=-1 && j < 8){
		if(Data[nnn[j]][1] == 1)
			Mines ++;
		j++;
	}
	return Mines;
}
//---------------------------------------------------------------------------
void TForm1::WinCheck(){
	if(remainder == 0){
		Label3->Caption = ("0");
		Timer1->Enabled =false;
		for(int i=0;i<TotalMines;i++){
			Data[num[i]][3] = 1;
			ImageList1->GetBitmap(9,imgs[num[i]]->Picture->Bitmap);
			imgs[num[i]]->Refresh();
			imgs[num[i]]->OnMouseEnter = NULL;
			imgs[num[i]]->OnMouseLeave = NULL;
		}
		ShowMessage("勝利");
		for(int i=0;i<num_t;i++){
			imgs[i]->OnMouseDown = NULL;
			imgs[i]->OnClick = NULL;
		}
	}
}
//---------------------------------------------------------------------------
void TForm1::Gameover(int mode){
	Timer1->Enabled =false;
	if(mode == 0){
		ShowMessage("你踩到地雷了！");
	}else if(mode == 1){
		ShowMessage("你的旗子插錯了！");
	}
	for(int i=0;i<num_t;i++){
		imgs[i]->OnMouseDown = NULL;
		imgs[i]->OnClick = NULL;
	}
}
//---------------------------------------------------------------------------
void TForm1::Spread(int NO){
	int NO_x,NO_y;      //轉x,y座標
	NO_x = NO%num_x;
	NO_y = NO/num_x;
	int iarr[] = {-1,-1,-1,-1,-1,-1,-1,-1};
	for(int i=0;i<8;i++)    //檢查邊線
		iarr[i] = -1;
	if(NO_x == num_x-1 && NO_y == 0){//右上
		iarr[0]=3;iarr[1]=5;iarr[2]=6;
	}else if(NO_x == num_x-1 && NO_y == num_y-1){   //右下
		iarr[0]=0;iarr[1]=1;iarr[2]=3;
	}else if(NO_x == 0 && NO_y == num_y-1){   //左下
		iarr[0]=1;iarr[1]=2;iarr[2]=4;
	}else if(NO_x == 0 && NO_y == 0){   //左上
		iarr[0]=4;iarr[1]=6;iarr[2]=7;
	}else if(NO_x == num_x-1){  //右排
		iarr[0]=0;iarr[1]=1;iarr[2]=3;iarr[3]=5;iarr[4]=6;
	}else if(NO_y == num_y-1){   //下排
		iarr[0]=0;iarr[1]=1;iarr[2]=2;iarr[3]=3;iarr[4]=4;
	}else if(NO_x == 0){   //左排
		iarr[0]=1;iarr[1]=2;iarr[2]=4;iarr[3]=6;iarr[4]=7;
	}else if(NO_y == 0){  //上排
		iarr[0]=3;iarr[1]=4;iarr[2]=5;iarr[3]=6;iarr[4]=7;
	}else{               //中間
		iarr[0]=0;iarr[1]=1;iarr[2]=2;iarr[3]=3;iarr[4]=4;iarr[5]=5;iarr[6]=6;iarr[7]=7;
	}
	for(int i=0;i<8;i++){
		if(iarr[i] == -1)
		break;
		switch(iarr[i]){
			case 0:
			MinesCheck(NO - num_x -1,1);
			break;
			case 1:
			MinesCheck(NO - num_x,1);
			break;
			case 2:
			MinesCheck(NO - num_x +1,1);
			break;
			case 3:
			MinesCheck(NO -1,true);
			break;
			case 4:
			MinesCheck(NO +1,true);
			break;
			case 5:
			MinesCheck(NO + num_x -1,1);
			break;
			case 6:
			MinesCheck( NO + num_x,1);
			break;
			case 7:
			MinesCheck(NO + num_x +1,1);
			break;
		}
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::imgsClick_flag(TObject *Sender)
{
	TImage *imgshow=(TImage*)Sender;
	ImageList1->GetBitmap(5,imgshow->Picture->Bitmap);
	imgshow->Refresh();
}
//---------------------------------------------------------------------------

void TForm1::CreateImgs(int num_x,int num_y)
{
	Panel1->AutoSize = false;
	num_t = num_x * num_y; //地雷總數
	remainder = num_t - TotalMines;//剩餘格數
	TotalMines_D = TotalMines;
	int img_h=Image1->Height,
		img_w=Image1->Width,
		img_t=Image1->Top,
		img_l=Image1->Left,
		img_padding=1;  //間距
	imgs = new TImage *[num_t];
	//列外處理
	try{
	for (int i=0 ; i<num_t ; ++i){
		imgs[i] = new TImage(this); //增加新圖片
		imgs[i]->Parent  =Panel1;
		imgs[i]->AutoSize= false;
		imgs[i]->Height  = img_h; // 影像物件的高度
		imgs[i]->Width   = img_w; // 影像物件的寬度
		imgs[i]->OnMouseEnter = imgsMouseEnter;
		imgs[i]->OnMouseLeave = imgsMouseLeave;
		imgs[i]->OnMouseDown  = imgsMouseDown;
		imgs[i]->OnMouseUp  = imgsMouseUp;
		imgs[i]->OnClick = imgsClick;
		imgs[i]->Stretch = true;
		imgs[i]->Transparent =false;
		imgs[i]->Picture->Bitmap->TransparentColor = clWhite;
		imgs[i]->Visible = false;
		imgs[i]->Enabled = true;
		imgs[i]->Tag     = i;
		ImageList1->GetBitmap(0,imgs[i]->Picture->Bitmap);
		imgs[i]->Refresh();
	}
	for (int i=0 ; i<num_t ; ++i){
		if(i%num_x==0){
			imgs[i]->Top  = img_t + i / num_x * (img_h + img_padding);
			imgs[i]->Left = img_l;
		}else{
			imgs[i]->Top  = img_t + i / num_x * (img_h + img_padding);
			imgs[i]->Left = img_l + i % num_x * (img_w + img_padding);
		}
		imgs[i]->Visible = true;
	}
	}
		catch(...){
		ShowMessage("系統無法負荷");
		N99101Click(NULL);

	}
	Panel1->AutoSize = true;
}
//---------------------------------------------------------------------------
TColor TForm1::ImgsColor(int amount){//數字顏色
	TColor Color;
	switch(amount)
	{
		case 1: Color=TColor(RGB(62,79,189));  break;
		case 2: Color=clGreen;         break;
		case 3: Color=clRed;           break;
		case 4: Color=clBlue;          break;
		case 5: Color=clMaroon;        break;
		case 6: Color=clTeal;          break;
		case 7: Color=clGray;          break;
		case 8: Color=clBlack;         break;
		default : Color=clWhite;       break;
	}
	return Color;
}
void __fastcall TForm1::N99101Click(TObject *Sender)
{
	Clear();
	num_x = 9;num_y = 9; TotalMines = 10;
	Label3->Caption = IntToStr(TotalMines);
	Start();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1616401Click(TObject *Sender)
{
	Clear();
	num_x = 16;num_y = 16; TotalMines = 40;
	Label3->Caption = IntToStr(TotalMines);
	Start();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N1630991Click(TObject *Sender)
{
	Clear();
	num_x = 30;num_y = 16; TotalMines = 99;
	Label3->Caption = IntToStr(TotalMines);
	Start();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	time_t t;
	srand((unsigned) time(&t)); // 以時間當種子


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
	if(gametime < 999){
		gametime ++;
		Label4->Caption = IntToStr(gametime);
	}else{
        Timer1->Enabled = false;
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N2Click(TObject *Sender)
{
  Close();
}

//---------------------------------------------------------------------------





void __fastcall TForm1::Button1Click(TObject *Sender)
{
	int x = StrToInt(Edit2->Text);
	int y = StrToInt(Edit1->Text);
	int TM = StrToInt(Edit3->Text);
	if(TM < 1){
		 ShowMessage("總地雷必須大於0");
	}else if(x <=1 ||y <=1){
		ShowMessage("至少要2×2以上");
	}else if(TM >= x * y ){
		ShowMessage("地雷數過多");
	}else{
		Clear();
		num_x = x;
		num_y = y;
        TotalMines = TM;
		Label3->Caption = IntToStr(TotalMines);
		Start();
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
	Panel2->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::N3Click(TObject *Sender)
{
	Panel2->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
N99101Click(Sender);
}
//---------------------------------------------------------------------------







