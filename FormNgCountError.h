//---------------------------------------------------------------------------

#ifndef FormNgCountErrorH
#define FormNgCountErrorH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TForm_NgCountError : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label_Title;
	TLabel *Label_Msg1;
	TLabel *Label_Msg2;
	TButton *btnOK;
	TButton *btnTrayOut;
	TTimer *Timer_BringToFront;
	TTimer *timerErrorOff;
    void __fastcall btnTrayOutClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
	void __fastcall Timer_BringToFrontTimer(TObject *Sender);
	void __fastcall timerErrorOffTimer(TObject *Sender);
private:	// User declarations
    void __fastcall SaveErrorLog(AnsiString title, AnsiString msg1, AnsiString msg2);
public:		// User declarations
	__fastcall TForm_NgCountError(TComponent* Owner);
    int stage;
	void __fastcall DisplayErrorMessage(AnsiString title, WideString msg1, WideString msg2, int stageno);
    void __fastcall DisplayErrorMessage(WideString msg1, WideString btn_trayout, WideString btn_restart);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_NgCountError *Form_NgCountError;
//---------------------------------------------------------------------------
#endif
