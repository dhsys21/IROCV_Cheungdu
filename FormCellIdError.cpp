//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_CellIdError *Form_CellIdError;
//---------------------------------------------------------------------------
__fastcall TForm_CellIdError::TForm_CellIdError(TComponent* Owner)
	: TForm(Owner)
{
    stage = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::ChangeMessage(UnicodeString msg1, UnicodeString msg2, UnicodeString msg3)
{
	Label_Msg1->Caption = msg1;
    Label_Msg2->Caption = msg2;
    Label_Msg3->Caption = msg3;
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::DisplayErrorMessage(int nStage)
{
    stage = nStage;
	if(!this->Visible)
	{
		Timer_BringToFront->Enabled = true;
        // PLC 오류 출력은 검사 처리에서 담당한다. 이 함수는 화면만 표시한다.
		SaveErrorLog(Label_Msg1->Caption, Label_Msg2->Caption, Label_Msg3->Caption);

		this->Position = poMainFormCenter;
		this->BringToFront();
		this->Show();
        // 메인 창 중앙 위치를 유지한다. 좌표를 다시 빼서 화면 밖으로 밀리지 않게 한다.
	}
	else this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::Timer_BringToFrontTimer(TObject *Sender)
{
    this->BringToFront();
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::timerErrorOffTimer(TObject *Sender)
{
    // 이전 창의 닫기 타이머에서는 PLC 오류를 해제하지 않는다.
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::SaveErrorLog(AnsiString msg1, AnsiString msg2, AnsiString msg3)
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

	str = Now().FormatString("yyyy-mm-dd hh:nn:ss> ") + msg1 + " " + msg2 + " " + msg3 + "\r\n";
	FileWrite(file_handle, str.c_str(), str.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------
void __fastcall TForm_CellIdError::btnSAVEClick(TObject *Sender)
{
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[stage]->AcceptCellSerialData();
}
//---------------------------------------------------------------------------

void __fastcall TForm_CellIdError::btnCANCELClick(TObject *Sender)
{
    Timer_BringToFront->Enabled = false;
    timerErrorOff->Enabled = false;
    Close();
    BaseForm->nForm[stage]->RetryCellSerialRead();
}
//---------------------------------------------------------------------------

