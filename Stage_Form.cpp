// [상태 화면] 진행 상태·오류·연결 이미지·PLC 표시등과 화면 전환.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

void __fastcall TTotalForm::ProcessError(AnsiString err1, AnsiString err2,AnsiString err3,AnsiString err4)
{
	if(GrpError->Visible == false){
		error1->Caption = err1 + " " + err2;
	//	error2->Caption = err2;
		error3->Caption = err3;
		error4->Caption = err4;
		ErrorTime->Caption = Now().FormatString("hh : nn : ss");
		WriteErrorLog();
		//ShowPanelGroup(GrpError);
	}
}


void __fastcall TTotalForm::DisplayProcess(AnsiString Status_Step, AnsiString msg, bool bError)
{
    // The current operation view still reads this message/error backing state.
    // Only the retired eight-panel color display has been removed.
    PLCStatus = msg;
    DisplayError(msg, bError);

	if(OldPLCStatus != PLCStatus) {
		OldPLCStatus = PLCStatus;
		WritePlcLog(Status_Step, PLCStatus);
		WriteCommLog(Status_Step, PLCStatus);
	}
}

void __fastcall TTotalForm::DisplayError(AnsiString msg, bool bError)
{
    Panel_State->Caption = msg;

	if(bError == true)
	{
        Panel_State->Color = clRed;
		Panel_State->Font->Color = clWhite;
	}
	else
	{
        Panel_State->Color = clWhite;
		Panel_State->Font->Color = clBlack;
    }
}

void __fastcall TTotalForm::RefreshStageStatusImage()
{
    // Connection state overrides only the image, not the production sequence.
    int imageStatus = nNoAnswer;
    if(Client->Active && Client->Socket->Connected)
    {
        imageStatus = stage.alarm_status;
        if(stage.arl == nLocal && imageStatus < nOpbox)
            imageStatus = nManual;
        else if(imageStatus == nNoAnswer)
        {
            if(autoInspection.GetStep() == STEP_WAIT_NG_ERROR ||
               autoInspection.GetStep() == STEP_ERROR_STOP)
                imageStatus = nEND;
            else if(autoInspection.IsMeasureStep())
                imageStatus = tray.ams && !tray.amf ? nRUN : nREADY;
            else if(autoInspection.GetStep() == STEP_WAIT_TRAY_OUT)
                imageStatus = nFinish;
            else
                imageStatus = autoInspection.GetStep() == STEP_WAIT_TRAY_IN ? nVacancy : nREADY;
        }
    }

    if(imageStatus >= nNoAnswer && imageStatus <= nEmergency)
        StatusImage->Picture = BaseForm->statusImage[imageStatus]->Picture;
}

void __fastcall TTotalForm::DisplayStatus(int status)
{
	AnsiString img_path;
	AnsiString err1, err2, err3, err4;
	err1 = "";
	err2 = "";
	err3 = "";
	err4 = "";

	if(GrpError->Visible == false){
		if ((stage.alarm_status < 20) && (status > 20))
			BaseForm->IncErrorCount();
		else if ((stage.alarm_status > 20) && (status < 20))
			BaseForm->DecErrorCount();
	}

	if(stage.arl == nAuto){
		stage.alarm_status = status;
	}
	else if (status < nOpbox){
		stage.alarm_status = nManual;
		RefreshStageStatusImage();
		return;
	}

	stage.alarm_status = status;

    RefreshStageStatusImage();

	if(GrpError->Visible){
		GrpError->BringToFront();
	}
	else if(stage.arl == nAuto || status >= 23)ShowPanelGroup(GrpMain);
}

void __fastcall TTotalForm::ResponseError(AnsiString param)
{
	int err_sort = param.SubString(1, 3).ToInt();
	AnsiString err;
	switch(err_sort){
		case 206:
			err = "IR Measurement Device error";
			break;
		default:
			break;
	}
}

void __fastcall TTotalForm::DisplayStageError(int err)
{
	AnsiString err1, err2, err3, err4;
//	bool ErrorMode = true;   // false : 알람모드 true: 에러모드
	switch(err){
		case BARCODE_ERROR:
			 err1 = "Barcode ERROR";
			 err2 = "";
			 err3 = "1.Check the status bar location";
			 err4 = "2.Inspection Start, click";
			 break;
		case RESET:
			if(GrpAlarm->Visible == true)ShowPanelGroup(OldGrp);
			return;
		case PROCESS_ERROR:
			 err1 = "IMS";
			 err2 = "PROCESS";
			 err3 = "1.Please check the process";
			 err4 = "";
			 break;
		case ACOUNT:	break;

		case nRunningError:
			 err1 = "RUNNING";
			 err2 = "";
			 err3 = "Lapse of Over 120 Seconds";
			 err4 = "Restart IR/OCV";
			break;
		case nReadyError:
			 err1 = "READY";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Restart IR/OCV";
			 break;
		case nRedEnd:
			 err1 = "TrayIn";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Restart IR/OCV";
			break;
		case nBlueEnd:
			 err1 = "END";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Please Tray Out Manually and Initialize IR/OCV";
			break;
		case nFinishError:
			 err1 = "FINISH";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Please Tray Out Manually and Initialize IR/OCV";
			break;
		case nDefaultError:
			err1 = "STAGE Status";
			err2 = "";
			err3 = "Lapse of Over 100 Seconds";
			err4 = "Check the status of STAGE";
			break;

	}
	stage.err = err;
	if(GrpError->Visible == false){
		error1->Caption = err1 +" " +  err2;
//		error2->Caption = err2;
		error3->Caption = err3;
		error4->Caption = err4;
		ErrorTime->Caption = Now().FormatString("hh : nn : ss");
		WriteErrorLog();
		//* 2023 06 14 설비가 멈췄을 경우 에러
        DisplayProcess(err1, err3, true);
		//Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 1);
		//ShowPanelGroup(GrpError);
	}
}


//---------------------------------------------------------------------------
// 상태 이미지·상태 지속 시간·PLC TRAY/PROBE 표시등을 갱신한다. 자동 검사 단계는 변경하지 않는다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 StatusTimerTimer. 설비 상태·알람·PLC 표시 갱신는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessStageStatus(TObject *Sender)
{
    // Keep PLC mode monitoring alive while the automatic inspection timer is disabled.
    UpdateAutoInspectionMode();
	RefreshStageStatusImage();
	if(stage.now_status != stage.alarm_status){
		stage.now_status = stage.alarm_status;
		stage.alarm_cnt = 0;
	}

	stage.alarm_cnt += 1;
    if(stage.alarm_cnt >= 1500) stage.alarm_cnt = 0;
	switch (stage.alarm_status){
		case nVacancy	:
			stage.alarm_cnt = 0;
			break;
		case nIN:
			if(stage.alarm_cnt > 100){
				DisplayStageError(nRedEnd);
				stage.alarm_cnt = 0;
			}
			break;
		case nREADY:
			if(stage.alarm_cnt > 100){
				DisplayStageError(nReadyError);
				stage.alarm_cnt = 0;
			}
			break;
		case nRUN:
			if(stage.alarm_cnt > 120){
				DisplayStageError(nRunningError);
				stage.alarm_cnt = 0;
			}
			break;
		case nEND:
			if(stage.alarm_cnt > 100){
				DisplayStageError(nBlueEnd);
				stage.alarm_cnt = 0;
			}
			break;
		case nReameasure:
			if( (stage.alarm_cnt > 300) && (stage.alarm_cnt < 400) ){
				stage.alarm_cnt = 500;
			}
			break;
		case nFinish:
            if(stage.alarm_cnt > 100){
				DisplayStageError(nFinishError);
				stage.alarm_cnt = 0;
			}
			break;
		case nOpbox:
		case nEmergency :
		case nManual:
            stage.alarm_cnt = 0;
		case nNoAnswer:
			stage.alarm_cnt = 0;
			break;
		default:
			break;
	}

    if(Mod_PLC->GetPlcValue(PLC_D_IROCV_TRAY_IN) == 1) DisplayPlcSignal(pnlTrayIn, true);
    else DisplayPlcSignal(pnlTrayIn, false);

    if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN) == 1) DisplayPlcSignal(pnlProbeOpen, true);
    else DisplayPlcSignal(pnlProbeOpen, false);

    if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE) == 1) DisplayPlcSignal(pnlProbeClose, true);
    else DisplayPlcSignal(pnlProbeClose, false);
    // 수동 대기 중에도 실행된다. 자동 표시와 경합하지 않도록 자동 타이머가 꺼진 경우만 갱신.
    if(!Timer_AutoInspection->Enabled && (bLocal || stage.arl == nLocal))
        CheckManualInspectionError();
}

//---------------------------------------------------------------------------
// 메인/재측정/오류 그룹을 전환하고 오류 화면 표시 개수를 갱신한다.
void __fastcall TTotalForm::ShowPanelGroup(TGroupBox *grp)
{
	if(grp->Visible == false){

/*		if(grp == GrpConfig){
			grp->Left = pMain->Left;
			grp->Top = pMain->Top;
			grp->Visible = true;
			grp->BringToFront();
			return;
		}
		else{
			grp->Left = GrpMain->Left;
			grp->Top = GrpMain->Top;
		}
*/
		grp->Left = GrpMain->Left;
		grp->Top = GrpMain->Top;

		if( (grp == GrpRemeasure) || (grp == GrpError) || (grp == GrpAlarm) ){
			if(grp->Visible == false)BaseForm->IncErrorCount();
			//Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_INTERFACE3_STATE_ERROR + (this->Tag * 100), 1);
		}
		//else Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_INTERFACE3_STATE_ERROR + (this->Tag * 100), 0);
		if( (CurrentGrp == GrpRemeasure) || (CurrentGrp == GrpError) || (CurrentGrp == GrpAlarm) ){
			BaseForm->DecErrorCount();
		}

        if(CurrentGrp != NULL){
            CurrentGrp->Visible = false;
        }
        // newGui replaces only the large main/local image. Alarm/error groups stay intact.
        grp->Visible = !(operationView && (grp == GrpMain || grp == GrpLocal));
        if(operationView && grp->Visible) grp->BringToFront();
        OldGrp = CurrentGrp;
        CurrentGrp = grp;
	}
}

//---------------------------------------------------------------------------
// PLC 입력 신호 ON/OFF를 표시등 색상으로 반영한다.
void __fastcall TTotalForm::DisplayPlcSignal(TAdvSmoothPanel *advPanel, bool bOn)
{
    if(bOn)
	{
		advPanel->Fill->Color = BaseForm->pon->Color;
		advPanel->Fill->ColorMirror = BaseForm->pon->Color;
		advPanel->Fill->ColorMirrorTo = BaseForm->pon->Color;
		advPanel->Fill->ColorTo = BaseForm->pon->Color;
	}else{
		advPanel->Fill->Color = BaseForm->poff->Color;
		advPanel->Fill->ColorMirror = BaseForm->poff->Color;
		advPanel->Fill->ColorMirrorTo = BaseForm->poff->Color;
		advPanel->Fill->ColorTo = BaseForm->poff->Color;
	}
}

//---------------------------------------------------------------------------
// 입력 암호를 확인한 뒤 설정 화면의 접근을 허용하거나 오류 문구를 표시한다.
void __fastcall TTotalForm::CheckPassword()
{
    UnicodeString msg = Form_Language->msgIncorrectPwd;
    if(PassEdit->Text == config.pwd){ //editPwd->Text){
        pnlConfig->Visible = true;
		pnlConfig->Left = 10;
		pnlConfig->Top = 50;

        editPwd->Text = config.pwd;
        PassEdit->Text = "";
        pPassword->Visible = false;
	}
	else{
		//MessageBox(Handle, L"Are you sure you’re spelling your password correctly?", L"ERROR", MB_OK|MB_ICONERROR);
        MessageBox(Handle, msg.c_str(), L"ERROR", MB_OK|MB_ICONERROR);
	}
}

//===========================================================================
// 자동/수동 오류 검사: 호출 시점과 반환값의 사용 방식은 각 운전 모드에서 유지한다.
//===========================================================================
// 자동 진행을 막는 통신/PLC/운전 모드 오류를 확인한다. true이면 현재 단계를 유지하고 대기한다.
bool __fastcall TTotalForm::CheckAutoInspectionError()
{
    DisplayError("");
    if(!Client->Active || !Client->Socket->Connected)
    {
        RefreshStageStatusImage();
        DisplayError("IR/OCV Connection Fail.");
        return true;
    }

    AnsiString error;
    if(!Mod_PLC->ClientSocket_PC->Active || !Mod_PLC->ClientSocket_PC->Socket->Connected ||
       !Mod_PLC->ClientSocket_PLC->Active || !Mod_PLC->ClientSocket_PLC->Socket->Connected)
        error = "PLC - PC Connection Fail.";
    else if(Mod_PLC->GetPlcValue(PLC_D_IROCV_ERROR))
        error = "PLC - Error!!";
    else if(bLocal && Mod_PLC->GetValue(PC_D_IROCV_STAGE_AUTO_READY) == 0)
        error = "IR/OCV is not in AutoMode";

    if(error.IsEmpty())
    {
        OldErrorCheckStatus = "";
        return false;
    }
    DisplayError(error, true);
    if(OldErrorCheckStatus != error)
    {
        OldErrorCheckStatus = error;
        WritePlcLog("CheckAutoInspectionError", error);
    }
    return true;
}
//---------------------------------------------------------------------------
// 수동에서는 자동검사 타이머가 멈추므로 상태 타이머에서 오류 표시만 갱신한다.
// 반환값은 표시 여부이며 수동 측정/PLC 출력을 정지시키는 인터록으로 사용하지 않는다.
bool __fastcall TTotalForm::CheckManualInspectionError()
{
    // 저장 실패/예외 정지의 원인 메시지를 수동 안내로 덮어쓰지 않는다.
    if(resultSaveStep == RESULT_ERROR || autoInspection.GetStep() == STEP_ERROR_STOP)
        return true;

    AnsiString error;
    if(!Client->Active || !Client->Socket || !Client->Socket->Connected)
        error = "IR/OCV Connection Fail.";
    else if(!Mod_PLC->ClientSocket_PC->Active || !Mod_PLC->ClientSocket_PC->Socket ||
            !Mod_PLC->ClientSocket_PC->Socket->Connected ||
            !Mod_PLC->ClientSocket_PLC->Active || !Mod_PLC->ClientSocket_PLC->Socket ||
            !Mod_PLC->ClientSocket_PLC->Socket->Connected)
        error = "PLC - PC Connection Fail.";
    else if(Mod_PLC->GetPlcValue(PLC_D_IROCV_ERROR) != 0)
        error = "PLC - Error!!";
    else if(bLocal || stage.arl == nLocal)
    {
        if(Mod_PLC->GetValue(PC_D_IROCV_STAGE_AUTO_READY) == 0)
            error = "IR/OCV is not in AutoMode";
    }

    // 연결 실패 → PLC 오류 → 수동 안내 순으로 표시해 중요한 오류가 가려지지 않는다.
    DisplayError(error, !error.IsEmpty());
    return !error.IsEmpty();
}
