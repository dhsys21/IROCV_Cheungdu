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

		// PLC 오류 출력은 검사 처리에서 담당한다. 이 함수는 화면만 표시한다.

		Label_Title->Caption = title;
		Label_Msg1->Caption = msg1;
		Label_Msg2->Caption = msg2;

        // 크기/글꼴/줄바꿈/버튼 위치는 DFM에서 함께 관리한다.

		SaveErrorLog(title, msg1, msg2);

		this->Position = poMainFormCenter;
		this->BringToFront();
		this->Show();
        // 메인 창 중앙 위치를 유지한다.
	}
	else this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Error::Button_OKClick(TObject *Sender)
{
	// 창 닫기는 오류 해제가 아니다. 배출/재시작 선택은 검사 처리로 전달한다.

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
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[this->Tag]->ForceTrayOut();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Error::btnRestartClick(TObject *Sender)
{
    // Close this dialog now; a delayed close timer must not clear a new alarm.
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[this->Tag]->RestartAutoInspection();
}
//---------------------------------------------------------------------------
void __fastcall TForm_Error::timerErrorOffTimer(TObject *Sender)
{
    // 이전 창의 닫기 타이머가 새 검사 오류를 해제하지 않도록 화면만 정리한다.
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
}
//---------------------------------------------------------------------------
