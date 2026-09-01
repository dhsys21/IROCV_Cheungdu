#include "FormTotal.h"
#include "RVMO_main.h"


void __fastcall TTotalForm::ShowAlarm(AnsiString err1, AnsiString err2, AnsiString err3 , AnsiString err4)
{
	if(GrpAlarm->Visible == false){
		modAlarm1->Caption = err1 + " " + err2;
	//	modAlarm2->Caption = err2;
		modAlarm3->Caption = err3;
		modAlarm4->Caption = err4;
		AlarmTime->Caption = Now().FormatString("hh : nn : ss");
		VisibleBox(GrpAlarm);
	}
}
// 알람 보이기
void __fastcall TTotalForm::ProcessError(AnsiString err1, AnsiString err2,AnsiString err3,AnsiString err4)
{
	if(GrpError->Visible == false){
		error1->Caption = err1 + " " + err2;
	//	error2->Caption = err2;
		error3->Caption = err3;
		error4->Caption = err4;
		ErrorTime->Caption = Now().FormatString("hh : nn : ss");
		ErrorLog();
		//VisibleBox(GrpError);
	}
}
//---------------------------------------------------------------------------

// 전지 정보 표시
void __fastcall TTotalForm::DisplayTrayInfo()
{
	
	for(int i=0; i<MAXCHANNEL; ++i){
		if(tray.cell[i] == 1){
			SetProcessColor(i, Line);
		}
		else{
			SetProcessColor(i, NoCell);
		}
	}
}
//---------------------------------------------------------------------------
// 전지 색상 표현
void __fastcall TTotalForm::SetProcessColor(int index, int clr, AnsiString result)
{
	TColor basic;

	TColor irColor = cl_line->Color;
	TColor ocvColor = cl_line->Color;


	int draw = 0;	// 1: ir, 2:ocv, 3:둘다
	AnsiString sir, socv;
	basic = panel[index]->Color;

	sir = "";
	socv = "";

	if(tray.cell[index] == 1){

		if(tray.orginal_value[index] == 0)
			sir = "-";
		else
			sir = FormatFloat("0.00", tray.after_value[index]);
		if(tray.ocv_value[index] == 0)
			socv = "-";
		else
			socv = FormatFloat("0.0", tray.ocv_value[index]);

		switch(clr){
			case Line:
				basic = clLine;
				break;
			case BadIr:
				basic = clBadIr;
				irColor = clBadIr;
				break;
			case AverageOver:
				basic = clAverageOver;
                irColor = clAverageOver;
                break;
			case BadOcv:
				if(basic == clMeasureFail)
				{
					irColor = clMeasureFail;
				}
				else
				{
					basic = pocv->Color;
					ocvColor = pocv->Color;
                }
				break;
			case IrCheck:
				if(basic != clMeasureFail){
					if(basic == clOcvCheck)basic = clBothCheck;
					else basic = clIrCheck;
				}else{
					basic = clIrCheck;
				}
				break;
			case OcvCheck:
				if(basic == clMeasureFail){
					irColor = clMeasureFail;
				}else{
					if(basic == clIrCheck)basic = clBothCheck;
					else basic = clOcvCheck;
				}
				break;
			case MeasureFail:
				basic = clMeasureFail;
				irColor = clMeasureFail;
				break;
		}
	}
	else{
		sir = "NO";
		socv = "CELL";

		if(clr == CellError){
			WriteCommLog("ETC", "CellError");
			basic = clCellError;
		}else{
			if(basic == clLine)basic = clNoCell;
		}
		irColor = basic;
		ocvColor = basic;
	}

	panel[index]->Color = basic;

	if(MeasureInfoForm->stage == this->Tag){
		MeasureInfoForm->DisplayIrValue(index, irColor, sir);
		MeasureInfoForm->DisplayOcvValue(index, ocvColor, socv);
	}

}
//---------------------------------------------------------------------------
// 컬러 인덱스
int __fastcall TTotalForm::GetColorIndex(TColor clr)
{
	if(clr == clNoCell)		return 1;
	if(clr == clBadIr )		return 2;
	if(clr == clCellError )	return 3;
	if(clr == clLine )		return 4;
	if(clr == clIrCheck )	return 5;
	if(clr == clOcvCheck )	return 6;
	if(clr == clBothCheck)	return 7;
	if(clr==clMeasureFail)	return 8;
	if(clr == pocv->Color) 	return 9;
	return 100;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::DisplayProcess(int status, AnsiString Status_Step, AnsiString msg, bool bError)
{
	for(int i = 0; i < 8; i++)
		pProcess[i]->Color = clSilver;

	PLCStatus = msg;
	pProcess[status]->Color = p0->Color;
	Panel_State->Caption = PLCStatus;

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

	if(OldPLCStatus != PLCStatus) {
		OldPLCStatus = PLCStatus;
		WritePLCLog(Status_Step, PLCStatus);
		WriteCommLog(Status_Step, PLCStatus);
	}
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
// 메인화면 검사 진행 표시
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
		return;
	}

	stage.alarm_status = status;

    if(status >=0 && status <=12){
		StatusImage->Picture = BaseForm->statusImage[status]->Picture;
	}

	if(GrpError->Visible){
		GrpError->BringToFront();
	}
	else if(stage.arl == nAuto || status >= 23)VisibleBox(GrpMain);
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

void __fastcall TTotalForm::ErrorMsg(int err)
{
	AnsiString err1, err2, err3, err4;
    int nstatus = 0;
//	bool ErrorMode = true;   // false : 알람모드 true: 에러모드
	switch(err){
		case BARCODE_ERROR:
			 err1 = "Barcode ERROR";
			 err2 = "";
			 err3 = "1.Check the status bar location";
			 err4 = "2.Inspection Start, click";
			 break;
		case RESET:
			if(GrpAlarm->Visible == true)VisibleBox(OldGrp);
			return;
		case PROCESS_ERROR:
			 err1 = "IMS";
			 err2 = "PROCESS";
			 err3 = "1.Please check the process";
			 err4 = "";
			 break;
		case ACOUNT:	break;

		case nRunningError:
			nstatus = sMeasure;
			 err1 = "RUNNING";
			 err2 = "";
			 err3 = "Lapse of Over 120 Seconds";
			 err4 = "Restart IR/OCV";
			break;
		case nReadyError:
			nstatus = sReady;
			 err1 = "READY";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Restart IR/OCV";
			 break;
		case nRedEnd:
            nstatus = sTrayIn;
			 err1 = "TrayIn";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Restart IR/OCV";
			break;
		case nBlueEnd:
			nstatus = sFinish;
			 err1 = "END";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Please Tray Out Manually and Initialize IR/OCV";
			break;
		case nFinishError:
			nstatus = sTrayOut;
			 err1 = "FINISH";
			 err2 = "";
			 err3 = "Lapse of Over 100 Seconds";
			 err4 = "Please Tray Out Manually and Initialize IR/OCV";
			break;
		case nDefaultError:
			nstatus = 0;
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
		ErrorLog();
		//* 2023 06 14 설비가 멈췄을 경우 에러
        DisplayProcess(nstatus, err1, err3, true);
		//Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_ERROR, 1);
		//VisibleBox(GrpError);
	}
}

