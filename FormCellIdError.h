//---------------------------------------------------------------------------

#ifndef FormCellIdErrorH
#define FormCellIdErrorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_CellIdError : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label_Title;
	TButton *btnSAVE;
	TButton *btnCANCEL;
	TLabel *Label_Msg1;
	TLabel *Label_Msg2;
	TLabel *Label_Msg3;
	TTimer *timerErrorOff;
	TTimer *Timer_BringToFront;
	void __fastcall Timer_BringToFrontTimer(TObject *Sender);
	void __fastcall timerErrorOffTimer(TObject *Sender);
	void __fastcall btnSAVEClick(TObject *Sender);
	void __fastcall btnCANCELClick(TObject *Sender);
private:	// User declarations

public:		// User declarations
	__fastcall TForm_CellIdError(TComponent* Owner);
    void __fastcall ChangeMessage(UnicodeString msg1, UnicodeString msg2, UnicodeString msg3);
    void __fastcall DisplayErrorMessage(int nStage);
    void __fastcall SaveErrorLog(AnsiString msg1, AnsiString msg2, AnsiString msg3);

    int stage;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_CellIdError *Form_CellIdError;
//---------------------------------------------------------------------------
#endif
