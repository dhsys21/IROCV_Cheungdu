//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Language *Form_Language;
//---------------------------------------------------------------------------
__fastcall TForm_Language::TForm_Language(TComponent* Owner)
	: TForm(Owner)
{
    LangDict = new TStringList();
    English = new TStringList();
    ReadLanguage(L"EN");
}
//---------------------------------------------------------------------------
void __fastcall TForm_Language::LanguageChange(int LangIndex)
{
    // Preserve persisted EN=0 / KO=1 / ZH=2 selection indices.
    ReadLanguage(LangIndex == 1 ? L"KO" : LangIndex == 2 ? L"ZH" : L"EN");

	//-------------------------------------------------------------------------
	// 				COMPONENT
	//-------------------------------------------------------------------------
	for(int i = 0; i < BaseForm->FormCnt; i++){
        BaseForm->nForm[i]->btnSaveConnConfig->Caption = GetLangStr(L"SAVE");
        BaseForm->nForm[i]->btnCloseConnConfig->Caption = GetLangStr(L"CANCEL");
        BaseForm->nForm[i]->btnConfig->Caption = GetLangStr(L"CONFIG");
        BaseForm->nForm[i]->btnManual->Caption = GetLangStr(L"MANUAL");
        BaseForm->nForm[i]->btnAuto->Caption = GetLangStr(L"AUTO");
        BaseForm->nForm[i]->btnReset->Caption = GetLangStr(L"RESET");
        BaseForm->nForm[i]->Panel6->Caption = GetLangStr(L"TRAYID");
        BaseForm->nForm[i]->Panel3->Caption = GetLangStr(L"STATUS");
        BaseForm->nForm[i]->Panel20->Caption = GetLangStr(L"PROCESS");
        BaseForm->nForm[i]->Panel9->Caption = GetLangStr(L"CHANNEL");
        BaseForm->nForm[i]->btnTrayOut->Caption = GetLangStr(L"TRAYOUT");
        BaseForm->nForm[i]->btnRemeasureInfo->Caption = GetLangStr(L"REMEAINFO");

        BaseForm->nForm[i]->btnConnectIROCV->Caption = GetLangStr(L"CONNECT");
        BaseForm->nForm[i]->btnDisConnectIROCV->Caption= GetLangStr(L"DISCONNECT");
        BaseForm->nForm[i]->btnConnectPLC->Caption = GetLangStr(L"CONNECT");
        BaseForm->nForm[i]->btnDisConnectPLC->Caption= GetLangStr(L"DISCONNECT");

        BaseForm->nForm[i]->cl_line->Caption = GetLangStr(L"READY");
        BaseForm->nForm[i]->cl_ir->Caption = GetLangStr(L"IRCOMPLETE");
        BaseForm->nForm[i]->cl_ocv->Caption = GetLangStr(L"OCVCOMPLETE");
        BaseForm->nForm[i]->cl_irocv->Caption = GetLangStr(L"IROCV");
        BaseForm->nForm[i]->pocv->Caption = GetLangStr(L"OCVFAIL");
        BaseForm->nForm[i]->cl_ce->Caption = GetLangStr(L"IRFAIL");
        BaseForm->nForm[i]->cl_badir->Caption = GetLangStr(L"FAIL");
        BaseForm->nForm[i]->cl_badocv->Caption = GetLangStr(L"OUTFLOW");
        BaseForm->nForm[i]->cl_no->Caption = GetLangStr(L"NOCELL");

        BaseForm->nForm[i]->localCali->Caption = GetLangStr(L"CALIBRATION");
        BaseForm->nForm[i]->lblTrayInfo->Caption = GetLangStr(L"TRAYINFO");
    }

    MeasureInfoForm->btnProbeOpen->Caption = GetLangStr(L"OPEN");
    MeasureInfoForm->btnProbeClose->Caption = GetLangStr(L"CLOSE");
    MeasureInfoForm->btnAuto->Caption = GetLangStr(L"START");
    MeasureInfoForm->advMSAStart->Caption = GetLangStr(L"START");
	MeasureInfoForm->btnStop->Caption = GetLangStr(L"STOP");
    MeasureInfoForm->advMSAStop->Caption = GetLangStr(L"STOP");
    MeasureInfoForm->btnInit->Caption = GetLangStr(L"INIT");
    MeasureInfoForm->btnSave->Caption = GetLangStr(L"SAVE");
    MeasureInfoForm->grbChannelInfo->Caption = GetLangStr(L"CHANNELINFO");
    MeasureInfoForm->pnlChannel->Caption = GetLangStr(L"CHANNEL");
    MeasureInfoForm->pnlPosition->Caption = GetLangStr(L"POSITION");
    MeasureInfoForm->grbEachChannel->Caption = GetLangStr(L"EACHCHANNEL");
    MeasureInfoForm->grbProbeSetting->Caption = GetLangStr(L"PROBESETTING");
    MeasureInfoForm->btnProbeOpen->Caption = GetLangStr(L"OPEN");
    MeasureInfoForm->btnProbeClose->Caption = GetLangStr(L"CLOSE");

    Form_CellIdError->btnSAVE->Caption = GetLangStr(L"SAVE");
    Form_CellIdError->btnCANCEL->Caption = GetLangStr(L"CANCEL");

    //-------------------------------------------------------------------------
	// 				MESSAGE
	//-------------------------------------------------------------------------
    msgSaveConfig = GetLangStr(L"msgSaveConfig");
    msgInputPwd = GetLangStr(L"msgInputPwd");
    msgIncorrectPwd = GetLangStr(L"msgIncorrectPwd");
	msgRbt = GetLangStr(L"msgRBT");
    msgRst = GetLangStr(L"msgRST");
    msgTooManyNG = GetLangStr(L"msgTooManyNG");
    msgCellIdError1 = GetLangStr(L"msgCellIdError1");
    msgCellIdError2 = GetLangStr(L"msgCellIdError2");
    msgCellIdError3 = GetLangStr(L"msgCellIdError3");
    Form_CellIdError->ChangeMessage(msgCellIdError1, msgCellIdError2, msgCellIdError3);
    // Static designer captions on every open form use the same dictionary.
    for(int i = 0; i < Screen->FormCount; ++i) LocalizeFormCaptions(Screen->Forms[i]);
}
//---------------------------------------------------------------------------
