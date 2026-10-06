#include <vcl.h>
#pragma hdrstop
#include "FormLanguage.h"
#include "RVMO_main.h"
#include <System.TypInfo.hpp>
#include <memory>

UnicodeString UiText(const UnicodeString &text)
{
    return Form_Language ? Form_Language->Translate(text) : text;
}

__fastcall TForm_Language::~TForm_Language()
{
    delete LangDict;
    delete English;
}

void __fastcall TForm_Language::ReadLanguage(const UnicodeString &language)
{
    CurrentLanguage = language;
    std::unique_ptr<TResourceStream> fallback(
        new TResourceStream((NativeUInt)HInstance, L"EN_DATA", RT_RCDATA));
    English->LoadFromStream(fallback.get(), TEncoding::UTF8);
    LangDict->Assign(English); // Same fallback/overlay method as India IR/OCV.
    if(language != L"EN")
    {
        std::unique_ptr<TStringList> selected(new TStringList());
        std::unique_ptr<TResourceStream> resource(
            new TResourceStream((NativeUInt)HInstance, language + L"_DATA", RT_RCDATA));
        selected->LoadFromStream(resource.get(), TEncoding::UTF8);
        for(int i = 0; i < selected->Count; ++i)
        {
            UnicodeString key = selected->Names[i];
            if(!key.IsEmpty()) LangDict->Values[key] = selected->ValueFromIndex[i];
        }
    }
    phrases.clear(); translatedText.clear(); displayCache.clear();
    for(int i = 0; i < English->Count; ++i)
    {
        UnicodeString key = English->Names[i];
        if(key.Pos(L"TEXT_") != 1) continue;
        UnicodeString source = English->ValueFromIndex[i];
        source = StringReplace(source, L"\\n", L"\r\n", TReplaceFlags() << rfReplaceAll);
        UnicodeString value = GetLangStr(key);
        translatedText[source] = value;
        if(source != value && !source.IsEmpty()) phrases.push_back(std::make_pair(source, value));
    }
}

UnicodeString __fastcall TForm_Language::GetLangStr(const UnicodeString &key)
{
    UnicodeString value = LangDict->Values[key];
    return StringReplace(value, L"\\n", L"\r\n", TReplaceFlags() << rfReplaceAll);
}

UnicodeString __fastcall TForm_Language::Translate(const UnicodeString &text)
{
    // Text keys are display-only: never translate protocol, CSV or saved logs.
    if(CurrentLanguage == L"EN") return text;
    std::map<UnicodeString, UnicodeString>::iterator found = translatedText.find(text);
    if(found != translatedText.end()) return found->second;
    found = displayCache.find(text);
    if(found != displayCache.end()) return found->second;
    // Dynamic displays compose a translated fixed phrase with numbers/units.
    UnicodeString result;
    for(int position = 1; position <= text.Length(); )
    {
        int best = -1, length = 0;
        for(unsigned int i = 0; i < phrases.size(); ++i)
        {
            const UnicodeString &phrase = phrases[i].first;
            if(phrase.Length() <= length) continue;
            if(text.SubString(position, phrase.Length()) != phrase) continue;
            const int after = position + phrase.Length();
            // Do not translate fragments embedded in machine signal identifiers.
            if(position > 1 && ((text[position - 1] >= L'A' && text[position - 1] <= L'Z') ||
                (text[position - 1] >= L'a' && text[position - 1] <= L'z') || text[position - 1] == L'_')) continue;
            if(after <= text.Length() && ((text[after] >= L'A' && text[after] <= L'Z') ||
                (text[after] >= L'a' && text[after] <= L'z') || text[after] == L'_')) continue;
            best = i; length = phrase.Length();
        }
        if(best >= 0) { result += phrases[best].second; position += length; }
        else { result += text[position]; ++position; }
    }
    if(displayCache.size() >= 2048) displayCache.clear();
    displayCache[text] = result;
    return result;
}

void __fastcall TForm_Language::LocalizeFormCaptions(TCustomForm *form)
{
    if(!form || form == this) return;
    UnicodeString rootKey = L"UI_" + UpperCase(form->ClassName()) + L"_CAPTION";
    if(English->IndexOfName(rootKey) >= 0) form->Caption = GetLangStr(rootKey);
    for(int i = 0; i < form->ComponentCount; ++i)
    {
        TComponent *component = form->Components[i];
        UnicodeString key = L"UI_" + UpperCase(form->ClassName()) + L"_" + UpperCase(component->Name);
        if(TListView *list = dynamic_cast<TListView*>(component))
            for(int column = 0; column < list->Columns->Count; ++column)
            {
                UnicodeString columnKey = key + L"_COL_" + IntToStr(column);
                if(English->IndexOfName(columnKey) >= 0) list->Columns->Items[column]->Caption = GetLangStr(columnKey);
            }
        // Only registered static captions are touched, never live channel data.
        if(English->IndexOfName(key) < 0) continue;
        TAdvSmoothPanel *smooth = dynamic_cast<TAdvSmoothPanel*>(component);
        if(smooth) smooth->Caption->Text = GetLangStr(key);
        else if(GetPropInfo(component, L"Caption")) SetStrProp(component, L"Caption", GetLangStr(key));
    }
}
