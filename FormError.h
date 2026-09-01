//---------------------------------------------------------------------------

#ifndef FormErrorH
#define FormErrorH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_Error : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label_Title;
	TLabel *Label_Msg1;
	TLabel *Label_Msg2;
	TButton *Button_OK;
	TTimer *Timer_BringToFront;
	TTimer *timerErrorOff;
	TButton *btnTrayOut;
	TButton *btnRestart;
	void __fastcall Button_OKClick(TObject *Sender);
	void __fastcall Timer_BringToFrontTimer(TObject *Sender);
	void __fastcall btnTrayOutClick(TObject *Sender);
	void __fastcall btnRestartClick(TObject *Sender);
	void __fastcall timerErrorOffTimer(TObject *Sender);
private:	// User declarations
	void __fastcall SaveErrorLog(AnsiString title, AnsiString msg1, AnsiString msg2);
public:		// User declarations
	__fastcall TForm_Error(TComponent* Owner);

	void __fastcall DisplayErrorMessage(AnsiString title, AnsiString msg1, AnsiString msg2);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Error *Form_Error;
//---------------------------------------------------------------------------
#endif
