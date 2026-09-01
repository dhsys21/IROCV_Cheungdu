//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Error *Form_Error;
//---------------------------------------------------------------------------
__fastcall TForm_Error::TForm_Error(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Error::DisplayErrorMessage(AnsiString title, AnsiString msg1, AnsiString msg2)
{
	if(!this->Visible)
	{
		Timer_BringToFront->Enabled = true;

		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 1);

		Label_Title->Caption = title;
		Label_Msg1->Caption = msg1;
		Label_Msg2->Caption = msg2;

		int width = 0;
		if(Label_Title->Width > width) width = Label_Title->Width;
		if(Label_Msg1->Width > width) width = Label_Msg1->Width;
		if(Label_Msg2->Width > width) width = Label_Msg2->Width;

		this->Width = width + 60;

		Label_Title->Left = (this->Width / 2) - (Label_Title->Width / 2);
		//Button_OK->Left = (this->Width / 2) - (Button_OK->Width / 2);
        btnTrayOut->Left = (this->Width / 2) - 150;
		btnRestart->Left = (this->Width / 2) + 50;

		SaveErrorLog(title, msg1, msg2);

		this->Position = poMainFormCenter;
		this->BringToFront();
		this->Show();
		this->Left = this->Left - BaseForm->Left;
	}
	else this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Error::Button_OKClick(TObject *Sender)
{
	Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 0);

	Timer_BringToFront->Enabled = false;
	this->Close();
}
//---------------------------------------------------------------------------





//---------------------------------------------------------------------------
void __fastcall TForm_Error::SaveErrorLog(AnsiString title, AnsiString msg1, AnsiString msg2)
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








void __fastcall TForm_Error::Timer_BringToFrontTimer(TObject *Sender)
{
	this->BringToFront();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Error::btnTrayOutClick(TObject *Sender)
{
	Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 0);
	Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_TRAY_OUT, 1);
	BaseForm->nForm[this->Tag]->WritePLCLog("TRAY OUT", "NG TRAY OUT");
	timerErrorOff->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TForm_Error::btnRestartClick(TObject *Sender)
{
	Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 0);
	BaseForm->nForm[this->Tag]->Initialization();
	BaseForm->nForm[this->Tag]->WritePLCLog("RESTART", "NG TRAY RESTART");
	timerErrorOff->Enabled = true;
	//this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Error::timerErrorOffTimer(TObject *Sender)
{
	if(Mod_PLC->GetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR) == 1)
	{
		Label_Msg2->Caption = "Please check PLC whether PC ERROR is 0 ...";
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_ERROR, 0);
	}
	else
	{
        Timer_BringToFront->Enabled = false;
		timerErrorOff->Enabled = false;
        this->Close();
    }
}
//---------------------------------------------------------------------------

