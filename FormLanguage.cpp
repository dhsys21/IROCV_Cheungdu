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

}
//---------------------------------------------------------------------------
void __fastcall TForm_Language::LanguageChange(int LangIndex)
{
    TValueListEditor *vle;
    if(LangIndex == 0) vle = VLE_ENGLISH;
    else if(LangIndex == 1) vle = VLE_KOREAN;
    else if(LangIndex == 2) vle = VLE_CHINESE;

	//-------------------------------------------------------------------------
	// 				COMPONENT
	//-------------------------------------------------------------------------
	for(int i = 0; i < BaseForm->FormCnt; i++){
        BaseForm->nForm[i]->btnSaveConnConfig->Caption = vle->Values["SAVE"];
        BaseForm->nForm[i]->btnCloseConnConfig->Caption = vle->Values["CANCEL"];
        BaseForm->nForm[i]->btnConfig->Caption = vle->Values["CONFIG"];
        BaseForm->nForm[i]->btnManual->Caption = vle->Values["MANUAL"];
        BaseForm->nForm[i]->btnAuto->Caption = vle->Values["AUTO"];
        BaseForm->nForm[i]->btnReset->Caption = vle->Values["RESET"];
        BaseForm->nForm[i]->Panel6->Caption = vle->Values["TRAYID"];
        BaseForm->nForm[i]->Panel3->Caption = vle->Values["STATUS"];
        BaseForm->nForm[i]->Panel20->Caption = vle->Values["PROCESS"];
        BaseForm->nForm[i]->Panel9->Caption = vle->Values["CHANNEL"];
        BaseForm->nForm[i]->btnTrayOut->Caption = vle->Values["TRAYOUT"];
        BaseForm->nForm[i]->btnRemeasureInfo->Caption = vle->Values["REMEAINFO"];

        BaseForm->nForm[i]->btnConnectIROCV->Caption = vle->Values["CONNECT"];
        BaseForm->nForm[i]->btnDisConnectIROCV->Caption= vle->Values["DISCONNECT"];
        BaseForm->nForm[i]->btnConnectPLC->Caption = vle->Values["CONNECT"];
        BaseForm->nForm[i]->btnDisConnectPLC->Caption= vle->Values["DISCONNECT"];

        BaseForm->nForm[i]->cl_line->Caption = vle->Values["READY"];
        BaseForm->nForm[i]->cl_ir->Caption = vle->Values["IRCOMPLETE"];
        BaseForm->nForm[i]->cl_ocv->Caption = vle->Values["OCVCOMPLETE"];
        BaseForm->nForm[i]->cl_irocv->Caption = vle->Values["IROCV"];
        BaseForm->nForm[i]->pocv->Caption = vle->Values["OCVFAIL"];
        BaseForm->nForm[i]->cl_ce->Caption = vle->Values["IRFAIL"];
        BaseForm->nForm[i]->cl_avgover->Caption = vle->Values["AVGFAIL"];
        BaseForm->nForm[i]->cl_badir->Caption = vle->Values["FAIL"];
        BaseForm->nForm[i]->cl_badocv->Caption = vle->Values["OUTFLOW"];
        BaseForm->nForm[i]->cl_no->Caption = vle->Values["NOCELL"];

        BaseForm->nForm[i]->localCali->Caption = vle->Values["CALIBRATION"];
        BaseForm->nForm[i]->lblTrayInfo->Caption = vle->Values["TRAYINFO"];
        BaseForm->nForm[i]->lblProcessInfo->Caption = vle->Values["PROCESSINFO"];
    }

    MeasureInfoForm->btnProbeOpen->Caption = vle->Values["OPEN"];
    MeasureInfoForm->btnProbeClose->Caption = vle->Values["CLOSE"];
    MeasureInfoForm->btnAuto->Caption = vle->Values["START"];
    MeasureInfoForm->advMSAStart->Caption = vle->Values["START"];
	MeasureInfoForm->btnStop->Caption = vle->Values["STOP"];
    MeasureInfoForm->advMSAStop->Caption = vle->Values["STOP"];
    MeasureInfoForm->btnInit->Caption = vle->Values["INIT"];
    MeasureInfoForm->btnSave->Caption = vle->Values["SAVE"];
    MeasureInfoForm->grbChannelInfo->Caption = vle->Values["CHANNELINFO"];
    MeasureInfoForm->pnlChannel->Caption = vle->Values["CHANNEL"];
    MeasureInfoForm->pnlPosition->Caption = vle->Values["POSITION"];
    MeasureInfoForm->grbEachChannel->Caption = vle->Values["EACHCHANNEL"];
    MeasureInfoForm->grbProbeSetting->Caption = vle->Values["PROBESETTING"];
    MeasureInfoForm->btnProbeOpen->Caption = vle->Values["OPEN"];
    MeasureInfoForm->btnProbeClose->Caption = vle->Values["CLOSE"];

    Form_CellIdError->btnSAVE->Caption = vle->Values["SAVE"];
    Form_CellIdError->btnCANCEL->Caption = vle->Values["CANCEL"];

    //-------------------------------------------------------------------------
	// 				MESSAGE
	//-------------------------------------------------------------------------
    msgSaveConfig = vle->Values["msgSaveConfig"];
    msgInputPwd = vle->Values["msgInputPwd"];
    msgIncorrectPwd = vle->Values["msgIncorrectPwd"];
	msgRbt = vle->Values["msgRBT"];
    msgRst = vle->Values["msgRST"];
    msgTooManyNG = vle->Values["msgTooManyNG"];
    msgCellIdError1 = vle->Values["msgCellIdError1"];
    msgCellIdError2 = vle->Values["msgCellIdError2"];
    msgCellIdError3 = vle->Values["msgCellIdError3"];
    Form_CellIdError->ChangeMessage(msgCellIdError1, msgCellIdError2, msgCellIdError3);
}
//---------------------------------------------------------------------------
