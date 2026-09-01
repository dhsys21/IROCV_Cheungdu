//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormCalibration.h"
#include "RVMO_main.h"
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
	MakePanel(BaseForm->lblLineNo->Caption);
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

void __fastcall TCaliForm::MakePanel(AnsiString type)
{
	int nx, ny, nw, nh;

	if(type == "3" || type == "4")
	{
		nx = 4;
//		nx = 1300;
		ny = 600;
//		ny = 4;
//		nw = 37;
		nw = 30;
//		nh = 25;
		nh = 20;

		int cnt = 0;
		for(int index=399; index>=0;){
			pch[index] = new TPanel(this);
			SetOption(pch[index], nx, ny, nw, nh-1, index);
			pch[index]->Caption = pch[index]->Hint;
			pch[index]->Color = clSkyBlue;
			pch[index]->ParentBackground = false;

			nx = nx + nw + 1;
			pstandard[index] = new TEdit(this);
			pstandard[index]->Parent = pBase;
			pstandard[index]->Font->Size = 10;
			pstandard[index]->Left =  nx;
			pstandard[index]->Top = ny;
			pstandard[index]->Width = nw + 1;
			pstandard[index]->Height = nh + 5;
			pstandard[index]->Tag = index;


			ny = ny + nh;
			nx = pch[index]->Left;
			poffset[index] = new TPanel(this);
			SetOption(poffset[index], nx, ny, nw, nh, index);
			poffset[index]->Color = pnormal2->Color;
			poffset[index]->ParentBackground = false;
			poffset[index]->Caption = "0";
			poffset[index]->ParentBackground = false;

			nx = nx + nw + 1;
			pmeasure[index] = new TPanel(this);
			SetOption(pmeasure[index], nx, ny, nw, nh, index);
			pmeasure[index]->Color = pnormal2->Color;
			pmeasure[index]->ParentBackground = false;
			pmeasure[index]->Caption = "0.00";
			pmeasure[index]->ParentBackground = false;


			nx = nx + nw + 3;
//			nx = nx - nw - 3;
			ny = ny - nh;
//			ny = ny + nh;
			if(index % 2 == 0) nx += 2;
//			if(index % 2 == 0) nx -= 2;
			if(index % 20 == 0)
			{
				ny = ny - nh - nh  - 1;
//				ny = ny + nh + nh + 1;
				nx = 4;
//				nx = 1300;
				if( (index / 20) % 10 == 0) ny -= 3;
//				if( (index / 20) % 10 == 0) ny += 3;
			}
			index -= 1;
		}
	}
	else if(type == "6")
	{
		nx = 1200;
		ny = 600;
		nw = 30;
		nh = 20;

		int cnt = 0;
		for(int index=0; index<400;){
			pch[index] = new TPanel(this);
			SetOption(pch[index], nx, ny, nw, nh-1, index);
			pch[index]->Caption = pch[index]->Hint;
			pch[index]->Color = clSkyBlue;
			pch[index]->ParentBackground = false;

			nx = nx - nw - 1;
			pstandard[index] = new TEdit(this);
			pstandard[index]->Parent = pBase;
			pstandard[index]->Font->Size = 10;
			pstandard[index]->Left =  nx;
			pstandard[index]->Top = ny;
			pstandard[index]->Width = nw + 1;
			pstandard[index]->Height = nh + 5;
			pstandard[index]->Tag = index;


			ny = ny + nh;
			nx = pch[index]->Left;
			poffset[index] = new TPanel(this);
			SetOption(poffset[index], nx, ny, nw, nh, index);
			poffset[index]->Color = pnormal2->Color;
			poffset[index]->ParentBackground = false;
			poffset[index]->Caption = "0";
			poffset[index]->ParentBackground = false;

			nx = nx - nw - 1;
			pmeasure[index] = new TPanel(this);
			SetOption(pmeasure[index], nx, ny, nw, nh, index);
			pmeasure[index]->Color = pnormal2->Color;
			pmeasure[index]->ParentBackground = false;
			pmeasure[index]->Caption = "0.00";
			pmeasure[index]->ParentBackground = false;


			index += 1;
			nx = nx - nw - 3;
			ny = ny - nh;
			if(index % 2 == 0) nx -= 2;
			if(index % 20 == 0)
			{
				ny = ny - nh - nh  - 1;
				nx = 1200;
				if( (index / 20) % 4 == 0) ny -= 3;
			}
		}
	}
    else if(type == "1" || type == "2")
	{
		nx = 4;
		ny = 600;
		nw = 30;
		nh = 20;

		int cnt = 0;
		for(int index=0; index<400;){
			pch[index] = new TPanel(this);
			SetOption(pch[index], nx, ny, nw, nh-1, index);
			pch[index]->Caption = pch[index]->Hint;
			pch[index]->Color = clSkyBlue;
			pch[index]->ParentBackground = false;

			nx = nx + nw + 1;
			pstandard[index] = new TEdit(this);
			pstandard[index]->Parent = pBase;
			pstandard[index]->Font->Size = 10;
			pstandard[index]->Left =  nx;
			pstandard[index]->Top = ny;
			pstandard[index]->Width = nw + 1;
			pstandard[index]->Height = nh + 5;
			pstandard[index]->Tag = index;


			ny = ny + nh;
			nx = pch[index]->Left;
			poffset[index] = new TPanel(this);
			SetOption(poffset[index], nx, ny, nw, nh, index);
			poffset[index]->Color = pnormal2->Color;
			poffset[index]->ParentBackground = false;
			poffset[index]->Caption = "0";
			poffset[index]->ParentBackground = false;

			nx = nx + nw + 1;
			pmeasure[index] = new TPanel(this);
			SetOption(pmeasure[index], nx, ny, nw, nh, index);
			pmeasure[index]->Color = pnormal2->Color;
			pmeasure[index]->ParentBackground = false;
			pmeasure[index]->Caption = "0.00";
			pmeasure[index]->ParentBackground = false;


			index += 1;
			nx = nx + nw + 3;
			ny = ny - nh;
			if(index % 2 == 0) nx += 2;
			if(index % 20 == 0)
			{
				ny = ny - nh - nh  - 1;
				nx = 4;
				if( (index / 20) % 4 == 0) ny -= 3;
			}
		}
	}
    else if(type == "5")
	{
		nx = 1200;
		ny = 600;
		nw = 30;
		nh = 20;

		int cnt = 0;
		for(int index = 0; index < MAXCHANNEL;){
			pch[index] = new TPanel(this);
			SetOption(pch[index], nx, ny, nw, nh-1, index);
			pch[index]->Caption = pch[index]->Hint;
			pch[index]->Color = clSkyBlue;
			pch[index]->ParentBackground = false;

			nx = nx - nw - 1;
			pstandard[index] = new TEdit(this);
			pstandard[index]->Parent = pBase;
			pstandard[index]->Font->Size = 10;
			pstandard[index]->Left =  nx;
			pstandard[index]->Top = ny;
			pstandard[index]->Width = nw + 1;
			pstandard[index]->Height = nh + 5;
			pstandard[index]->Tag = index;


			ny = ny + nh;
			nx = pch[index]->Left;
			poffset[index] = new TPanel(this);
			SetOption(poffset[index], nx, ny, nw, nh, index);
			poffset[index]->Color = pnormal2->Color;
			poffset[index]->ParentBackground = false;
			poffset[index]->Caption = "0";
			poffset[index]->ParentBackground = false;

			nx = nx - nw - 1;
			pmeasure[index] = new TPanel(this);
			SetOption(pmeasure[index], nx, ny, nw, nh, index);
			pmeasure[index]->Color = pnormal2->Color;
			pmeasure[index]->ParentBackground = false;
			pmeasure[index]->Caption = "0.00";
			pmeasure[index]->ParentBackground = false;


			index += 1;
            nx = pch[index-1]->Left;
            ny = ny - 3 * nh - 1;
            //ny = ny - nh - nh  - 1;
			//nx = nx + nw + 3;
			//ny = ny - nh;
			//if(index % 2 == 0) nx += 2;
			if(index % 20 == 0)
			{
                nx = nx - 2 * nw - 3;
                ny = 600;
                //nx = nx + nw + 3;
				//nx = 4;
				//if( (index / 20) % 4 == 0) ny -= 3;
			}
		}
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
	pnl->Hint = IntToStr((index/20)+1) + "-" + IntToStr((index+20)%20 + 1);
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
	BaseForm->nForm[stage]->CmdForceStop();
}
//---------------------------------------------------------------------------

void __fastcall TCaliForm::btnAuto1Click(TObject *Sender)
{
	BaseForm->nForm[stage]->InitTrayStruct();
	for(int i = 0; i < MAXCHANNEL; i++)
	{
		poffset[i]->Caption = "-";
		pmeasure[i]->Caption = "-";
	}
	BaseForm->nForm[stage]->CmdAutoTest();
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
void __fastcall TCaliForm::WriteCaliboffset()
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
void __fastcall TCaliForm::ReadCaliboffset()
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
	WriteCaliboffset();
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
