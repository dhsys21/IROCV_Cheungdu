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

		// PLC 오류 출력은 검사 처리에서 담당한다. 이 함수는 화면만 표시한다.

		Label_Title->Caption = UiText(title);
		Label_Msg1->Caption = UiText(UnicodeString(msg1));
		Label_Msg2->Caption = UiText(UnicodeString(msg2));

        // 크기/글꼴/줄바꿈/버튼 위치는 DFM에서 함께 관리한다.

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
	Label_Msg1->Caption = UiText(UnicodeString(msg1));
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
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[stage]->ForceTrayOut();
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::btnOKClick(TObject *Sender)
{
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[stage]->RestartAutoInspection();
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::Timer_BringToFrontTimer(TObject *Sender)
{
    this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_NgCountError::timerErrorOffTimer(TObject *Sender)
{
    // 이전 창의 닫기 타이머가 새 검사 오류를 해제하지 않도록 화면만 정리한다.
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
}
//---------------------------------------------------------------------------
