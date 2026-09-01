//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_NgCountError *Form_NgCountError;
//---------------------------------------------------------------------------
__fastcall TForm_NgCountError::TForm_NgCountError(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::DisplayErrorMessage(AnsiString title, WideString msg1, WideString msg2, int nStage)
{
    stage = nStage;
	if(!this->Visible)
	{
		Timer_BringToFront->Enabled = true;

		Mod_PLC->SetValue(PC_D_IROCV_ERROR, 1);

		Label_Title->Caption = title;
		Label_Msg1->Caption = msg1;
		Label_Msg2->Caption = msg2;

		int width = 0;
		if(Label_Title->Width > width) width = Label_Title->Width;
		if(Label_Msg1->Width > width) width = Label_Msg1->Width;
		if(Label_Msg2->Width > width) width = Label_Msg2->Width;

		this->Width = width + 60;

		Label_Title->Left = (this->Width / 2) - (Label_Title->Width / 2);
		btnTrayOut->Left = (this->Width / 2) - 150;
		btnOK->Left = (this->Width / 2) + 50;

		SaveErrorLog(title, msg1, msg2);

		this->Position = poMainFormCenter;
		this->BringToFront();
		this->Show();
	}
	else this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::DisplayErrorMessage(WideString msg1, WideString btn_trayout, WideString btn_restart)
{
	Label_Msg1->Caption = msg1;
	btnTrayOut->Caption = btn_trayout;
    btnOK->Caption = btn_restart;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::SaveErrorLog(AnsiString title, AnsiString msg1, AnsiString msg2)
{
    AnsiString str, dir;
	int file_handle;

	dir = (AnsiString)LOG_PATH + Now().FormatString("yyyymmdd") + "\\";
	ForceDirectories((AnsiString)dir);

	str = dir + "ERROR_" + Now().FormatString("yymmdd-hh") + ".log";

	if(FileExists(str))
		file_handle = FileOpen(str, fmOpenWrite);
	else{
		file_handle = FileCreate(str);
	}

	FileSeek(file_handle, 0, 2);

	str = Now().FormatString("yyyy-mm-dd hh:nn:ss> ") + title + " : " + msg1 + ", " + msg2 + "\r\n";
	FileWrite(file_handle, str.c_str(), str.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::btnTrayOutClick(TObject *Sender)
{
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
	Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 1);
	BaseForm->nForm[stage]->WritePLCLog("TRAY OUT", "NG TRAY OUT");
	timerErrorOff->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::btnOKClick(TObject *Sender)
{
    Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);
    Mod_PLC->SetValue(PC_D_IROCV_REMEASURE, 1);
	BaseForm->nForm[stage]->Initialization();
	BaseForm->nForm[stage]->WritePLCLog("RESTART", "NG TRAY RESTART");
    BaseForm->nForm[stage]->CmdForceStop_Original();
	timerErrorOff->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::Timer_BringToFrontTimer(TObject *Sender)
{
    this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::timerErrorOffTimer(TObject *Sender)
{
    if(Mod_PLC->GetPlcValue(PC_D_IROCV_ERROR) == 1)
	{
		Label_Msg2->Caption = "Please check PLC whether PC ERROR is 0 ...";
		Mod_PLC->SetValue(PC_D_IROCV_ERROR, 0);
	}
	else
	{
        Timer_BringToFront->Enabled = false;
		timerErrorOff->Enabled = false;
        this->Close();
    }
}
//---------------------------------------------------------------------------