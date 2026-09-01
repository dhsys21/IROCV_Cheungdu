//---------------------------------------------------------------------------

#ifndef FormLanguageH
#define FormLanguageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.ValEdit.hpp>
//---------------------------------------------------------------------------
class TForm_Language : public TForm
{
__published:	// IDE-managed Components
	TValueListEditor *VLE_KOREAN;
	TValueListEditor *VLE_ENGLISH;
	TStringGrid *sGridLanguage;
	TValueListEditor *VLE_CHINESE;
private:	// User declarations
    void __fastcall SetLanguage();
public:		// User declarations
	__fastcall TForm_Language(TComponent* Owner);
    UnicodeString __fastcall GetTranslation(AnsiString name, int LangIndex);
    void __fastcall LanguageChange(int LangIndex);

    //* Message º¯¼ö
	UnicodeString msgRst;
    UnicodeString msgRbt;
    UnicodeString msgTooManyNG;
    UnicodeString msgCellIdError1, msgCellIdError2, msgCellIdError3;
    UnicodeString msgSaveConfig, msgInputPwd, msgIncorrectPwd;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Language *Form_Language;
//---------------------------------------------------------------------------
#endif
