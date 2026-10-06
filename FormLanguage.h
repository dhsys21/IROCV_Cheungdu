//---------------------------------------------------------------------------

#ifndef FormLanguageH
#define FormLanguageH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <map>
#include <vector>
//---------------------------------------------------------------------------
class TForm_Language : public TForm
{
__published:	// IDE-managed Components
private:	// User declarations
    TStringList *LangDict, *English;
    std::vector<std::pair<UnicodeString, UnicodeString> > phrases;
    std::map<UnicodeString, UnicodeString> translatedText, displayCache;
    void __fastcall LocalizeFormCaptions(TCustomForm *form);
public:		// User declarations
	__fastcall TForm_Language(TComponent* Owner);
    __fastcall ~TForm_Language();
    UnicodeString CurrentLanguage;
    void __fastcall ReadLanguage(const UnicodeString &language);
    UnicodeString __fastcall GetLangStr(const UnicodeString &key);
    UnicodeString __fastcall Translate(const UnicodeString &text);
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
UnicodeString UiText(const UnicodeString &text);
//---------------------------------------------------------------------------
#endif
