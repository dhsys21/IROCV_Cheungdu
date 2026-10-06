//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormRemeasure.h"
#include "RVMO_main.h"
#include "ChannelLayout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothButton"
#pragma resource "*.dfm"
TRemeasureForm *RemeasureForm;
//---------------------------------------------------------------------------

__fastcall TRemeasureForm::TRemeasureForm(TComponent* Owner)
	: TForm(Owner)
{
	stage = -1;
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::RefreshForm()
{

	for(int i=0; i<MAXCHANNEL; ++i){
		pre[i]->Caption = IntToStr(acc_remeasure[i]);
		if(acc_remeasure[i] < pcolor2->Caption.ToIntDef(3)){
			pre[i]->Color = pcolor1->Color;
			pre[i]->ParentBackground = false;
		}
		else{
			pre[i]->Color = pcolor2->Color;
			pre[i]->ParentBackground = false;
		}
//		if(acc_remeasure[i] >= 10){
//			pre[i]->Color = pcolor4->Color;  // 마지막 측정  채널
//			pre[i]->ParentBackground = false;
//		}
	}
	//pAccCnt->Caption = IntToStr(*acc_cnt);
	pAccDate->Caption = *acc_init;

    pnlTotalTray->Caption = *acc_totaltray;
    pnlFinalNg->Caption = *acc_finalng;

}
//---------------------------------------------------------------------------

void __fastcall TRemeasureForm::FormCreate(TObject *Sender)
{
	MakeUIPanel();
	MakePanel();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::MakePanel()
{
    // 한 채널의 두 표시창은 같은 셀 안에 위/아래로 배치한다.
    for(int index = 0; index < MAXCHANNEL; ++index)
    {
        const ChannelLayout::Rect r = ChannelLayout::ForChannel(
            index, Panel2->ClientWidth, Panel2->ClientHeight, true);
        const int upperHeight = (r.height - 1) / 2;
        pch[index] = new TPanel(this);
        pre[index] = new TPanel(this);
        SetOption(pch[index], r.left, r.top, r.width, upperHeight, index);
        SetOption(pre[index], r.left, r.top + upperHeight + 1,
            r.width, r.height - upperHeight - 1, index);
        pch[index]->Caption = index + 1;
        pch[index]->Font->Color = clWhite;
        pch[index]->Color = clSkyBlue;
        pre[index]->Color = pcolor1->Color;
        pch[index]->ParentBackground = false;
        pre[index]->ParentBackground = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::MakeUIPanel()
{
    // DFM에 남은 16채널 기준 제목은 숨기고, 실제 행/열 수로 축 제목을 생성한다.
    for(int i = 0; i < Panel2->ControlCount; ++i)
        Panel2->Controls[i]->Visible = false;
    Panel2->Caption = "";
    const int width = Panel2->ClientWidth;
    const int height = Panel2->ClientHeight;
    // 배열 번호=안내 번호-1. 제목 위치와 채널 위치는 동일한 시작 모서리를 사용한다.
    for(int column = 0; column < CELL_COLUMN_COUNT; ++column)
    {
        const ChannelLayout::Rect r = ChannelLayout::ColumnTitle(column, width, height);
        pUIx[column] = new TPanel(this);
        SetUIOption(pUIx[column], r.left, r.top, r.width, r.height, column);
        pUIx[column]->Caption = column + 1;
    }
    for(int row = 0; row < CELL_ROW_COUNT; ++row)
    {
        const ChannelLayout::Rect r = ChannelLayout::RowTitle(row, width, height);
        pUIy[row] = new TPanel(this);
        SetUIOption(pUIy[row], r.left, r.top, r.width, r.height, row);
        pUIy[row]->Caption = row + 1;
    }
    const ChannelLayout::Rect corner = ChannelLayout::AxisCorner(width, height);
    Panel1->SetBounds(corner.left, corner.top, corner.width, corner.height);
    Panel1->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index)
{
	pnl->Parent = Panel2;
	pnl->Left =  nx;
	pnl->Top = ny;
	pnl->Width = nw;
	pnl->Height = nh;
	pnl->Alignment = taCenter;
	pnl->Font->Size = 10;
	pnl->Font->Color = clBlack;
	pnl->Font->Style = Font->Style << fsBold;

	pnl->BevelInner = bvNone;
	pnl->BevelKind = bkNone;
	pnl->BevelOuter = bvNone;
	pnl->Tag = index; // index + 16
	pnl->Hint = "CH : " + IntToStr(index + 1) + " (" + IntToStr(ChannelLayout::RowNumber(index)) + "-" + IntToStr(ChannelLayout::ColumnNumber(index)) + ")";
    pnl->OnClick = ChInfoMouseClick;
//    pnl->OnMouseLeave = ChInfoMouseLeave;

	pnl->ShowHint = true;
	pnl->OnDblClick = chInitdblClick;
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::SetUIOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index)
{
	pnl->Parent = Panel2;
    pnl->ParentBackground = false;
	pnl->Left = nx;
	pnl->Top = ny;
	pnl->Width = nw;
	pnl->Height = nh;
	pnl->Alignment = taCenter;
	pnl->Color = Panel35->Color;
	pnl->Caption = index+1;
    pnl->ShowCaption = true;
	pnl->Font->Size = 12;
	pnl->Font->Color = clBlack;
	pnl->Font->Style = Font->Style << fsBold;

	pnl->BevelInner = bvNone;
	pnl->BevelKind = bkNone;
	pnl->BevelOuter = bvRaised;
	pnl->BevelWidth =1;
	pnl->BiDiMode = bdLeftToRight;
	pnl->BorderStyle = bsNone;
	pnl->BorderWidth = 0;
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::FormShow(TObject *Sender)
{
	this->Left = 650;
	this->Top = 120;
	this->BringToFront();
	this->RefreshForm();

    BaseForm->nForm[stage]->WriteRemeasureInfo();
    BaseForm->nForm[stage]->ReadRemeasureInfo();
}
//---------------------------------------------------------------------------


void __fastcall TRemeasureForm::FormHide(TObject *Sender)
{
	stage = -1;	
}
//---------------------------------------------------------------------------


void __fastcall TRemeasureForm::chInitdblClick(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;
	int ch = pnl->Tag;
	int nRemeasureAlarmCount = 0;
	UnicodeString str;
	str = "Do you want to initialize the channel " + IntToStr(ch+1) +" record??";
   if(MessageBox(Handle, str.c_str(), L"", MB_YESNO|MB_ICONQUESTION) == ID_YES){
		acc_remeasure[ch] = 0;
        acc_totaluse[ch] = 0;

		for(int index=0; index<MAXCHANNEL; ++index){
			if(acc_remeasure[index] >= pcolor2->Caption.ToIntDef(3))
				nRemeasureAlarmCount++;
		}
		BaseForm->nForm[stage]->UpdateRemeasureAlarm(nRemeasureAlarmCount);
		this->RefreshForm();
	}
}
//---------------------------------------------------------------------------

void __fastcall TRemeasureForm::AccInitBtnClick(TObject *Sender)
{
	if(MessageBox(Handle, L"Do you want to initialize all channel record?", L"", MB_YESNO|MB_ICONQUESTION) == ID_YES){
		for(int i=0; i<MAXCHANNEL; ++i){
        	acc_remeasure[i] = 0;
            acc_totaluse[i] = 0;
        }
		BaseForm->nForm[stage]->UpdateRemeasureAlarm(0);
		pAccDate->Caption = UiText(Now().FormatString("yyyy. m. d. hh:nn"));
		//pAccCnt->Caption = 0;
		*acc_cnt = 0;
		*acc_init = pAccDate->Caption;

        *acc_totaltray = 0;
        *acc_finalng = 0;
		this->RefreshForm();
	}

}
//---------------------------------------------------------------------------

void __fastcall TRemeasureForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    BaseForm->nForm[stage]->WriteRemeasureInfo();
}
//---------------------------------------------------------------------------
void __fastcall TRemeasureForm::ChInfoMouseClick(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;
	int index;
	index = pnl->Tag;
	pChannel->Caption = index + 1;
    pPos->Caption = UiText(IntToStr(ChannelLayout::RowNumber(index)) + "-" + IntToStr(ChannelLayout::ColumnNumber(index)));
    pNgTotalUse->Caption = UiText(IntToStr(acc_remeasure[index]) + " / " + IntToStr(acc_totaluse[index]));
}
//---------------------------------------------------------------------------
