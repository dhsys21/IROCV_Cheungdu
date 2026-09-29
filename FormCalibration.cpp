//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCalibration.h"
#include "RVMO_main.h"
#include "ChannelLayout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothButton"
#pragma link "AdvSmoothToggleButton"
#pragma resource "*.dfm"
TCaliForm *CaliForm;
//---------------------------------------------------------------------------
__fastcall TCaliForm::TCaliForm(TComponent* Owner)
	: TForm(Owner)
{
	stage = -1;

	this->Left = 140;
	this->Top = 50;
}

void __fastcall TCaliForm::FormCreate(TObject *Sender)
{
	MakePanel();
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::FormShow(TObject *Sender)
{
	this->BringToFront();
//	for(int i = 0 ; i < 256 ; i++)
//	{
//		pmeasure[i]->Caption = FormatFloat("0,0", measure[i]);
//		pstandard[i]->Text = FormatFloat("0,0", standard[i]);
//	}

	OffsetEdit->Text = BaseForm->DefaultOffset[stage];
	LowOffsetEdit->Text = BaseForm->DefaultLowOffset[stage];
	OffsetEdit->Enabled = false;
}

void __fastcall TCaliForm::MakePanel()
{
    // 교정값도 동일 채널 인덱스를 사용한다. 셀 내부는 번호/기준값, 보정값/측정값의 2x2 구성.
    pBase->AutoSize = false;
    pBase->Width = btnInit->Left - pBase->Left - 8;
    pBase->Height = ClientHeight - pBase->Top - 8;
    for(int index = 0; index < MAXCHANNEL; ++index)
    {
        const ChannelLayout::Rect r = ChannelLayout::ForChannel(
            index, pBase->ClientWidth, pBase->ClientHeight, false);
        const int leftWidth = (r.width - 1) / 2;
        const int upperHeight = (r.height - 1) / 2;
        pch[index] = new TPanel(this);
        SetOption(pch[index], r.left, r.top, leftWidth, upperHeight, index);
        pch[index]->Caption = index + 1;
        pch[index]->ShowHint = true;
        pstandard[index] = new TEdit(this);
        pstandard[index]->Parent = pBase;
        pstandard[index]->AutoSize = false;
        pstandard[index]->Font->Size = 8;
        pstandard[index]->SetBounds(r.left + leftWidth + 1, r.top,
            r.width - leftWidth - 1, upperHeight);
        pstandard[index]->Tag = index;
        poffset[index] = new TPanel(this);
        SetOption(poffset[index], r.left, r.top + upperHeight + 1,
            leftWidth, r.height - upperHeight - 1, index);
        poffset[index]->Color = pnormal2->Color;
        poffset[index]->Caption = "0";
        pmeasure[index] = new TPanel(this);
        SetOption(pmeasure[index], r.left + leftWidth + 1, r.top + upperHeight + 1,
            r.width - leftWidth - 1, r.height - upperHeight - 1, index);
        pmeasure[index]->Color = pnormal2->Color;
        pmeasure[index]->Caption = "0.00";
    }
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index)
{
	pnl->Parent = pBase;
	pnl->Left =  nx;
	pnl->Top = ny;
	pnl->Width = nw;
	pnl->Height = nh;
	pnl->Alignment = taCenter;
	pnl->Font->Size = 8;
	pnl->Font->Color = clBlack;
	pnl->ParentBackground=false;
	pnl->Color = clSkyBlue;
//	pnl->OnDblClick = PanelIrDblClick;
	pnl->OnClick = PanelDblClick;
	pnl->BevelInner = bvNone;
	pnl->BevelKind = bkNone;
	pnl->BevelOuter = bvNone;
	pnl->Tag = index;
	pnl->Hint = "CH : " + IntToStr(index + 1) + " (" + IntToStr(ChannelLayout::RowNumber(index)) + "-" + IntToStr(ChannelLayout::ColumnNumber(index)) + ")";
	pnl->ShowHint = false;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TCaliForm::WriteCaliFile(bool Data)
{
	AnsiString str, FileName;
	int file_handle;

	if(SaveDialog->Execute() == false){
		return;
	}
	FileName = SaveDialog->FileName ;
	if(FileExists(FileName))DeleteFile(FileName);
	file_handle = FileCreate(FileName);
	FileSeek(file_handle, 0, 0);
	str = "Channel,STANDARD,MEASURE,OFFSET\r\n";
	FileWrite(file_handle, str.c_str(), str.Length());
	for(int i=0; i<MAXCHANNEL; ++i){
		str = IntToStr(i+1) + "," + pstandard[i]->Text + "," + pmeasure[i]->Caption + ","+ poffset[i]->Caption + "\r\n";
		FileWrite(file_handle, str.c_str(), str.Length());
	}
	FileClose(file_handle);
}
//---------------------------------------------------------------------------------------------------------------
void __fastcall TCaliForm::PanelDblClick(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;
	chEdit->Text = IntToStr(pnl->Tag+1);
	ManMeasureEdit->Text = pmeasure[pnl->Tag]->Caption;
	ManOffsetEdit->Text = poffset[pnl->Tag]->Caption;
	ManStandardEdit->Text = pstandard[pnl->Tag]->Text;
}
//------------------------------------------------------------------

void __fastcall TCaliForm::btnStopClick(TObject *Sender)
{
	BaseForm->nForm[stage]->FinishMeasurement();
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnAuto1Click(TObject *Sender)
{
	BaseForm->nForm[stage]->InitializeTrayData();
	for(int i = 0; i < MAXCHANNEL; i++)
	{
		poffset[i]->Caption = "-";
		pmeasure[i]->Caption = "-";
	}
	BaseForm->nForm[stage]->CmdStartMeasurement();
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::InsertMeasure(int pos, double value)
{
//	int index = pos-1;
//	pmeasure[index]->Caption = FormatFloat("0.00", value);
//	poffset[index]->Caption = FormatFloat("0.00", StrToFloat(pstandard[index]->Text) -  value);
}

void __fastcall TCaliForm::btnIrClick(TObject *Sender)
{
	int ch;
	ch = chEdit->Text.ToInt();
	pmeasure[ch-1]->Color = pnormal1->Color;

	BaseForm->nForm[stage]->CmdIRCell(FormatFloat("000", ch));
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::pstageClick(TObject *Sender)
{
	OffsetEdit->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnLoadClick(TObject *Sender)
{
	AnsiString str;
	TStringList *list = new TStringList;
	if(OpenDialog1->Execute()){
		list->LoadFromFile(OpenDialog1->FileName);
		try{
				for(int index=0; index<MAXCHANNEL; ++index){
					str = list->Strings[index+1];
					str.Delete(1, str.Pos(","));
					pstandard[index]->Text = str.SubString(1, str.Pos(",")-1);
					str.Delete(1, str.Pos(","));
					pmeasure[index]->Caption = str.SubString(1, str.Pos(",")-1);
					str.Delete(1, str.Pos(","));
					poffset[index]->Caption = str.Trim();
				}
			}
		catch(...){
			MessageBox(Handle, L"Is the wrong type of file.", L"", MB_OK|MB_ICONERROR);
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnSaveClick(TObject *Sender)
{
	WriteCaliFile(true);
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnInitClick(TObject *Sender)
{
	for(int pos = 0; pos <MAXCHANNEL; ++pos){
		CaliForm->pmeasure[pos]->Color = pnormal2->Color;
		CaliForm->pmeasure[pos]->ParentBackground=false;
		CaliForm->poffset[pos]->ParentBackground=false;
		CaliForm->poffset[pos]->Color = pnormal1->Color;
	}
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnStandardClick(TObject *Sender)
{
	TAdvSmoothToggleButton *btn;
	btn = (TAdvSmoothToggleButton*)Sender;

	int ch = chEdit->Text.ToInt()-1;

	switch(btn->Tag){
		case 1:
			pstandard[ch]->Text = ManStandardEdit->Text;
			break;
		case 2:
			pmeasure[ch]->Caption = ManMeasureEdit->Text;
			break;
		case 3:
			poffset[ch]->Caption = ManOffsetEdit->Text;
			break;

		default: break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::ConfigBtn1Click(TObject *Sender)
{
	try{
		BaseForm->DefaultOffset[stage] = OffsetEdit->Text.ToDouble();
		BaseForm->DefaultLowOffset[stage] = LowOffsetEdit->Text.ToDouble();
		BaseForm->WriteDefaultOffset();
	}
	catch(...){
		MessageBox(Handle, L"Please check the offset value.",L"", MB_OK|MB_ICONWARNING);
	}
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::WriteCalibrationOffsets()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "Caliboffset_" + IntToStr(this->stage) + ".cali";

	ini = new TIniFile(file);

	for(int index=0; index<MAXCHANNEL; ++index)
	{
		ini->WriteFloat("IR OFFSET", IntToStr(index+1), poffset[index]->Caption.ToDouble());
		ini->WriteFloat("STANDARD", IntToStr(index+1), pstandard[index]->Text.ToDouble());
        ini->WriteFloat("MEASURE", IntToStr(index+1), pmeasure[index]->Caption.ToDouble());
	}

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::ReadCalibrationOffsets()
{
	TIniFile *ini;
	ini = new TIniFile((AnsiString)BIN_PATH + "Caliboffset_" + IntToStr(this->stage) + ".cali");

	for(int index=0; index<MAXCHANNEL; ++index){
		poffset[index]->Caption = ini->ReadFloat("IR OFFSET", IntToStr(index+1), 0.0);
		pstandard[index]->Text = ini->ReadFloat("STANDARD", IntToStr(index+1), 0.0);
        pmeasure[index]->Caption = ini->ReadFloat("MEASURE", IntToStr(index+1), 0.0);
	}

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::btnApplyClick(TObject *Sender)
{
	for(int i = 0; i<MAXCHANNEL; i++)
	{
//		BaseForm->IR_Offset[i] = poffset[i]->Caption.ToDouble();
		BaseForm->nForm[stage]->stage.ir_offset[i] = poffset[i]->Caption.ToDouble();
	}
	WriteCalibrationOffsets();
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    this->stage = -1;
}
//---------------------------------------------------------------------------
void __fastcall TCaliForm::btnProbeCloseClick(TObject *Sender)
{
    Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
}
//---------------------------------------------------------------------------
