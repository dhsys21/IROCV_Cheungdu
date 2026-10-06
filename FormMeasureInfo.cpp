//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "FormMeasureInfo.h"
#include "RVMO_main.h"
#include "ChannelLayout.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "AdvSmoothButton"
#pragma link "AdvSmoothButton"
#pragma resource "*.dfm"
TMeasureInfoForm *MeasureInfoForm;
//---------------------------------------------------------------------------
__fastcall TMeasureInfoForm::TMeasureInfoForm(TComponent* Owner)
	: TForm(Owner)
{

	this->Parent = BaseForm;
	stage = 0;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TMeasureInfoForm::FormShow(TObject *Sender)
{
//	this->btnInitClick(this);
	this->BringToFront();
	pLocal->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMeasureInfoForm::InitializeDisplayData()
{
	memset(&display, 0, sizeof(display));
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::FormCreate(TObject *Sender)
{
	MakeUIPanel();
	MakePanel();

	InitializeChart(10, 40, 1600, 4200);

//	this->ScaleBy(75,100);
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::MakePanel()
{
    // 한 채널의 두 표시창은 같은 셀 안에 위/아래로 배치한다.
    for(int index = 0; index < MAXCHANNEL; ++index)
    {
        const ChannelLayout::Rect r = ChannelLayout::ForChannel(
            index, Panel2->ClientWidth, Panel2->ClientHeight, true);
        const int upperHeight = (r.height - 1) / 2;
        pir[index] = new TPanel(this);
        pocv[index] = new TPanel(this);
        SetOption(pir[index], r.left, r.top, r.width, upperHeight, index);
        SetOption(pocv[index], r.left, r.top + upperHeight + 1,
            r.width, r.height - upperHeight - 1, index);
        pocv[index]->Caption = IntToStr(ChannelLayout::RowNumber(index)) + "-" +
            IntToStr(ChannelLayout::ColumnNumber(index));
        pocv[index]->Color = pnormal2->Color;
        pir[index]->ParentBackground = false;
        pocv[index]->ParentBackground = false;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::MakeUIPanel()
{
    // DFM에 남은 16채널 기준 제목은 숨기고, 실제 행/열 수로 축 제목을 생성한다.
    for(int i = 0; i < Panel2->ControlCount; ++i)
        Panel2->Controls[i]->Visible = false;
    Panel2->Caption = "";
    const int width = Panel2->ClientWidth;
    const int height = Panel2->ClientHeight;
    // 배열 번호=안내 번호-1. 제목 위치와 채널 위치는 동일한 시작 모서리를 사용한다.
    for(int column = 0; column < CELL_COLUMN_COUNT; ++column)
    {
        const ChannelLayout::Rect r = ChannelLayout::ColumnTitle(column, width, height);
        pUIx[column] = new TPanel(this);
        SetUIOption(pUIx[column], r.left, r.top, r.width, r.height, column);
        pUIx[column]->Caption = column + 1;
    }
    for(int row = 0; row < CELL_ROW_COUNT; ++row)
    {
        const ChannelLayout::Rect r = ChannelLayout::RowTitle(row, width, height);
        pUIy[row] = new TPanel(this);
        SetUIOption(pUIy[row], r.left, r.top, r.width, r.height, row);
        pUIy[row]->Caption = row + 1;
    }
    // 측정값/보조값 범례도 두 안내 축이 만나는 모서리로 이동한다.
    const ChannelLayout::Rect corner = ChannelLayout::AxisCorner(width, height);
    const int legendHeight = (corner.height - 1) / 2;
    clir->SetBounds(corner.left, corner.top, corner.width, legendHeight);
    clocv->SetBounds(corner.left, corner.top + legendHeight + 1,
        corner.width, corner.height - legendHeight - 1);
    clir->Visible = true;
    clocv->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index)
{
	pnl->Parent = Panel2;
	pnl->Left =  nx;
	pnl->Top = ny;
	pnl->Width = nw;
	pnl->Height = nh;
	pnl->Alignment = taCenter;
	pnl->Font->Size = 8;
	pnl->Font->Color = clBlack;
	pnl->Font->Style = Font->Style << fsBold;
	pnl->Color = pnormal1->Color;
	pnl->ParentBackground = false;
	pnl->OnDblClick = PanelDblClickk;
	pnl->OnMouseEnter = ChInfoMouseEnter;
	pnl->OnMouseLeave = ChInfoMouseLeave;

	pnl->BevelInner = bvNone;
	pnl->BevelKind = bkNone;
	pnl->BevelOuter = bvNone;
	pnl->Tag = index;
//	pnl->Hint = "채널 : " + IntToStr(index+1) + "(" + IntToStr((index%16)+1) + "-" + IntToStr((index+16)/16)+ ")";
	pnl->Hint = "CH : " + IntToStr(index + 1) + " (" + IntToStr(ChannelLayout::RowNumber(index)) + "-" + IntToStr(ChannelLayout::ColumnNumber(index)) + ")";
	pnl->ShowHint = true;
	pnl->Caption = index+1;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::SetUIOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index)
{
	pnl->Parent = Panel2;
	pnl->ParentBackground = false;
	pnl->Left = nx;
	pnl->Top = ny;
	pnl->Width = nw;
	pnl->Height = nh;
	pnl->Alignment = taCenter;
	pnl->Color = Panel35->Color;
	pnl->Caption = index+1;
	pnl->ShowCaption = true;
	pnl->Font->Size = 12;
	pnl->Font->Color = clBlack;
	pnl->Font->Style = Font->Style << fsBold;

	pnl->BevelInner = bvNone;
	pnl->BevelKind = bkNone;
	pnl->BevelOuter = bvRaised;
	pnl->BevelWidth =1;
	pnl->BiDiMode = bdLeftToRight;
	pnl->BorderStyle = bsNone;
	pnl->BorderWidth = 0;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::DisplayIrValue(int index, TColor clr, AnsiString caption, bool measured)
{
	if(index < 0 || index >= MAXCHANNEL) return;
	pir[index]->Caption = caption;

    // 채널번호를 IR 측정값으로 그래프에 넣지 않는다. 차트도 0-based index.
    if(index < IrChart->Series[0]->Count())
        IrChart->Series[0]->YValue[index] = measured ? BaseForm->StringToDouble(caption, 0) : 0;

	if(clr == cl_line->Color)pir[index]->Color = pnormal1->Color;
	else pir[index]->Color = clr;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::DisplayIrValue(int index, AnsiString caption)
{
	pir[index]->Caption = caption;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::DisplayOcvValue(int index, TColor clr, AnsiString caption, bool measured)
{
    if(index < 0 || index >= MAXCHANNEL) return;
    pocv[index]->Caption = caption;

    if(index < OcvChart->Series[0]->Count())
        OcvChart->Series[0]->YValue[index] = measured ? BaseForm->StringToDouble(caption, 0) : 0;

	if(clr == cl_line->Color)pocv[index]->Color = pnormal2->Color;
	else pocv[index]->Color = clr;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnSaveClick(TObject *Sender)
{
	AnsiString str, FileName;
	int file_handle;

	if(SaveDialog->Execute()){
		FileName = SaveDialog->FileName;
		if(FileExists(FileName)){
			if(MessageBox(Handle, UiText(L"Would you like to overwrite files?").c_str(), UiText(L"SAVE").c_str(), MB_YESNO|MB_ICONQUESTION) == ID_NO){
				return;
			}
			else{
				DeleteFile(FileName);
			}
		}
		file_handle = FileCreate(FileName);
        FileSeek(file_handle, 0, 0);
		str = "No,IR,OCV\n";
		for(int i=0; i<MAXCHANNEL; ++i){
			str = str + IntToStr(i+1) + "," ;
			str = str + FormatFloat("0.00", display.after_value[i]) + ",";
			str = str + FormatFloat("0.0", display.ocv_value[i]) + "\n";
		}
		FileWrite(file_handle, str.c_str(), str.Length());
		FileClose(file_handle);
		}
		else return;



}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnIrClick(TObject *Sender)
{
	int ch;
	ch = chEdit->Text.ToInt();
	pir[ch-1]->Color = pnormal1->Color;

	BaseForm->nForm[stage]->CmdIRCell(FormatFloat("000", ch));
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnOcvClick(TObject *Sender)
{
	int ch;
	ch = chEdit->Text.ToInt();
	pocv[ch-1]->Color = pnormal2->Color;
	BaseForm->nForm[stage]->CmdOCVCell(FormatFloat("000", ch));
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnInitClick(TObject *Sender)
{
	BaseForm->nForm[stage]->ResetMeasurementData();
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnStartManualInspectionClick(TObject *Sender)
{
	BaseForm->nForm[stage]->InitializeTrayData();
	//BaseForm->nForm[stage]->CmdDeviceInfo();
	BaseForm->nForm[stage]->CmdStartMeasurement();
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnStopClick(TObject *Sender)
{
	BaseForm->nForm[stage]->FinishMeasurement();
    Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data, PC_D_IROCV_PROB_CLOSE, 0);
	BaseForm->nForm[stage]->WriteCommLog("IR/OCV STOP", "MANUAL STOP");
	probetimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::btnProbeClick(TObject *Sender)
{
	Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
	Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
    probetimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMeasureInfoForm::PanelDblClickk(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;
	chEdit->Text = IntToStr(pnl->Tag+1);
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::ChInfoMouseEnter(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;
	int index;
	index = pnl->Tag;
	pch->Caption = index + 1;
//	ppos->Caption = UiText(IntToStr((index%16)+1) + "-" + IntToStr((index+16)/16));
	ppos->Caption = IntToStr(ChannelLayout::RowNumber(index)) + "-" + IntToStr(ChannelLayout::ColumnNumber(index));
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::ChInfoMouseLeave(TObject *Sender)
{
	pch->Caption = "";
	ppos->Caption = "";
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::chkGraphClick(TObject *Sender)
{
	if(chkGraph->Checked){
		IrChart->Visible = true;
		OcvChart->Visible = true;
		IrChart->BringToFront();
		OcvChart->BringToFront();
	}
	else{
		IrChart->Visible = false;
		OcvChart->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TMeasureInfoForm::btnChartRefreshClick(TObject *Sender)
{
	IrChart->Series[0]->Clear();
	OcvChart->Series[0]->Clear();
	for(int i = 0; i < MAXCHANNEL; ++i){
		IrChart->Series[0]->AddXY(i+1, display.after_value[i]);
		OcvChart->Series[0]->AddXY(i+1, display.ocv_value[i]);
	}
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::Panel19Click(TObject *Sender)
{
	for(int i = 0; i < MAXCHANNEL; ++i){
		pir[i]->Caption = IntToStr(i+1);
		pocv[i]->Caption = IntToStr(ChannelLayout::RowNumber(i)) + "-" + IntToStr(ChannelLayout::ColumnNumber(i));
	}
}


void __fastcall TMeasureInfoForm::Panel35Click(TObject *Sender)
{
	pLocal->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::msaTimerTimer(TObject *Sender)
{
    // [CELL SERIAL 공통] PROBE OPEN이 먼저 와도 최종 시리얼/결과 저장 완료 전에는 다음 회차로 가지 않는다.
    if(BaseForm->nForm[stage]->IsWaitingForResultSave()) return;
	switch(nStep)
	{
		case 0:
			if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN))
			{
                Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
				Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
				BaseForm->nForm[stage]->ResetMeasurementData();
				nStep = 1;
			}
			break;
		case 1:
			if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE)){
				Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
				BaseForm->nForm[stage]->CmdStartMeasurement();     // ams -> amf -> if cell-error (< 10) then auto-remeasure
				nStep = 2;
			}
			else
			{
				Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 1);
			}
			break;
		case 2:
			if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN))
			{
				Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);

				WriteResultFile2(msaFN, msaCount, Edit1->Text.ToIntDef(3));
				//WriteResultFile(msaFN, msaCount);
				msaCount++;
				MSA_COUNT_CHECK->Caption = IntToStr(msaCount+1)+"/"+ Edit1->Text;

				if(msaCount >= Edit1->Text.ToInt())
				{
					BaseForm->nForm[stage]->FinishMeasurement();
                    MakeReportFile(msaFN, msaReportFN, msaCount);
					BaseForm->nForm[stage]->WriteCommLog("IR/OCV STOP", "MSA COMPLETE");
					msaTimer->Enabled = false;

					ShowMessage(UiText("MSA COMPLETE"));
					MSA_COUNT_CHECK->Caption = "";
				}else
				{
					BaseForm->nForm[stage]->FinishMeasurement();
					BaseForm->nForm[stage]->WriteCommLog("IR/OCV STOP", "MSA Nth-TIME STOP");
					nStep = 0;
				}
			}
			break;
		default:
			break;
	}
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::advMSAStartClick(TObject *Sender)
{
	nStep = 0;
	msaCount = 0;
//	msaFN = Now().FormatString("yymmddhhnnss");
//	BaseForm->nForm[stage]->InitializeInspection();
	MSA_COUNT_CHECK->Caption = UiText("1/"+ Edit1->Text);
	//msaTimer->Enabled = true;

    // msa 저장 파일 설정
	AnsiString dir;
	dir = (AnsiString)MSA_PATH + Now().FormatString("yyyymmdd") + "\\" + pstage->Caption + "\\";
	ForceDirectories((AnsiString)dir);
	msaFN = dir + Now().FormatString("yymmddhhnnss") + ".csv";
	msaReportFN = dir + Now().FormatString("yymmddhhnnss") + "_report.csv";

	BaseForm->nForm[stage]->InitializeInspection();
	msaTimer->Enabled = true;
}
//---------------------------------------------------------------------------

void __fastcall TMeasureInfoForm::advMSAStopClick(TObject *Sender)
{
	BaseForm->nForm[stage]->FinishMeasurement();
	BaseForm->nForm[stage]->WriteCommLog("IR/OCV STOP", "MSA TIMER STOP BUTTON");
	msaTimer->Enabled = false;

    probetimer->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::WriteResultFile(AnsiString fn, int msaIndex)
{
	int file_handle;
	AnsiString filename;
	AnsiString dir;
	AnsiString ir, ocv, ch, serial;

	dir = (AnsiString)MSA_PATH + Now().FormatString("yyyymmdd") + "\\" + pstage->Caption + "\\";
	ForceDirectories((AnsiString)dir);

	//filename =  dir + fn + "_" + IntToStr(msaIndex + 1) + ".csv";
    filename = fn;
	if(FileExists(filename)){
		DeleteFile(filename);
	}

	file_handle = FileCreate(filename);
	FileSeek(file_handle, 0, 0);

	AnsiString file;

	file += "CH,IR,OCV\n";


	for(int i=0; i<MAXCHANNEL; ++i){
		ch = IntToStr(i+1) + ",";
		ir = FormatFloat("0.00", BaseForm->nForm[stage]->tray.after_value[i]);
		ocv = FormatFloat("0.00", BaseForm->nForm[stage]->tray.ocv_value[i]);
		file = file + ch + ir + "," + ocv  + "\n";
	}
	FileWrite(file_handle, file.c_str(), file.Length());
	FileClose(file_handle);
}
void __fastcall TMeasureInfoForm::WriteResultFile2(AnsiString fn, int msaIndex, int nTotalCount)
{
	int file_handle;
	AnsiString filename, str;
	AnsiString dir;
	AnsiString ir, ocv, repeat, serial;

	dir = (AnsiString)MSA_PATH + Now().FormatString("yyyymmdd") + "\\" + pstage->Caption + "\\";
	ForceDirectories((AnsiString)dir);

	//filename =  dir + fn + ".csv";
	filename = fn;

	if(FileExists(filename)) file_handle = FileOpen(filename, fmOpenWrite);
	else
	{
		file_handle = FileCreate(filename);
		str = "REPEAT COUNT";
		for(int i = 0; i < MAXCHANNEL; i++)
			str += ",IR_" + IntToStr(i + 1);
		for(int i = 0; i < MAXCHANNEL; i++)
			str += ",OCV_" + IntToStr(i + 1);
		str += "\n";
	}
	FileSeek(file_handle, 0, 2);

	str += "REPEAT_" + IntToStr(msaIndex + 1);
	for(int i = 0; i < MAXCHANNEL; ++i)
		ir += "," + FormatFloat("0.00", BaseForm->nForm[stage]->tray.after_value[i]);
	for(int i = 0; i < MAXCHANNEL; ++i)
		ocv += "," + FormatFloat("0.0", BaseForm->nForm[stage]->tray.ocv_value[i]);
    str = str + ir + ocv + "\n";
	FileWrite(file_handle, str.c_str(), str.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::MakeReportFile(AnsiString fn_data, AnsiString fn_report, int nTotalCount)
{
	int file_handle;
	AnsiString filename, str;
	AnsiString dir;
	AnsiString ir, ocv, repeat, serial;
	AnsiString irValues[100][MAXCHANNEL], ocvValues[100][MAXCHANNEL];
	double irSum, ocvSum, irMin[MAXCHANNEL], irMax[MAXCHANNEL], ocvMin[MAXCHANNEL], ocvMax[MAXCHANNEL];
	AnsiString tempvalue;

	int nRepeat = 0;
	//* 파일 읽기
	//* 한줄
	TStringList *sList_line = new TStringList;
	//* IR, OCV 값  읽기
	TStringList *sList_value = new TStringList;
	sList_line->LoadFromFile(fn_data);
	for(int i = 1; i < sList_line->Count; i++){
		sList_value->Delimiter=',';
		sList_value->DelimitedText = sList_line->Strings[i].Trim();

		for(int nIndex = 1; nIndex < MAXCHANNEL + 1; nIndex++){
			if(sList_value->Strings[nIndex].Trim() == "") tempvalue = "0";
			else tempvalue = sList_value->Strings[nIndex].Trim();
//			irValues[nRepeat][nIndex - 1] = sList_value->Strings[nIndex].Trim();
			irValues[nRepeat][nIndex - 1] = tempvalue;
		}
		for(int nIndex = MAXCHANNEL + 1; nIndex < MAXCHANNEL * 2 + 1; nIndex++){
			if(sList_value->Strings[nIndex].Trim() == "") tempvalue = "0";
			else tempvalue = sList_value->Strings[nIndex].Trim();
//			ocvValues[nRepeat][nIndex - 257] = sList_value->Strings[nIndex].Trim();
			ocvValues[nRepeat][nIndex - (MAXCHANNEL + 1)] = tempvalue;
		}
		nRepeat++;
	}

	//* IR min/max, IR dev,
	ir = "Channel";
	for(int i = 0; i < nTotalCount; i++){
		ir += ",IR_" + IntToStr(i + 1);
	}

	for(int i = 0; i < nTotalCount; i++){
		ir += ",IR_Delta_" + IntToStr(i + 1);
	}

	ir += ",IR_MIN,IR_MAX,IR_MAX - IR_MIN\n";

	for(int i = 0; i < MAXCHANNEL; i++){
		ir += IntToStr(i + 1);
		//* min/max
		for(int j = 0; j < nTotalCount; j++){
			ir += "," + irValues[j][i];
			if(j == 0){
				irMin[i] = StrToFloat(irValues[j][i]);
				irMax[i] = StrToFloat(irValues[j][i]);
			}else{
				if(irMin[i] > StrToFloat(irValues[j][i])) irMin[i] = StrToFloat(irValues[j][i]);
                if(irMax[i] < StrToFloat(irValues[j][i])) irMax[i] = StrToFloat(irValues[j][i]);
			}
		}
		//* delta
        for(int j = 0; j < nTotalCount; j++){
			ir += "," + FormatFloat("0.00", StrToFloat(irValues[j][i]) - StrToFloat(irValues[0][i])) ;
		}
		ir += "," + FormatFloat("0.00", irMin[i]) + "," + FormatFloat("0.00", irMax[i]) + "," + FormatFloat("0.00", irMax[i]-irMin[i]) + "\n";
	}

	//* OCV min/max, OCV dev 계산
	ocv = "Channel";
	for(int i = 0; i < nTotalCount; i++){
		ocv += ",OCV_" + IntToStr(i + 1);
	}
	for(int i = 0; i < nTotalCount; i++){
		ocv += ",OCV_Delta_" + IntToStr(i + 1);
	}

	ocv += ",OCV_MIN,OCV_MAX,OCV_MAX - OCV_MIN\n";

	for(int i = 0; i < MAXCHANNEL; i++){
		ocv += IntToStr(i + 1);
		//* min/max
		for(int j = 0; j < nTotalCount; j++){
			ocv += "," + ocvValues[j][i];
			if(j == 0){
				ocvMin[i] = StrToFloat(ocvValues[j][i]);
				ocvMax[i] = StrToFloat(ocvValues[j][i]);
			}else{
				if(ocvMin[i] > StrToFloat(ocvValues[j][i])) ocvMin[i] = StrToFloat(ocvValues[j][i]);
				if(ocvMax[i] < StrToFloat(ocvValues[j][i])) ocvMax[i] = StrToFloat(ocvValues[j][i]);
			}
		}
		//* delta
		for(int j = 0; j < nTotalCount; j++){
			ocv += "," + FormatFloat("0.00", StrToFloat(ocvValues[j][i]) - StrToFloat(ocvValues[0][i])) ;
		}
		ocv += "," + FormatFloat("0.00", ocvMin[i]) + "," + FormatFloat("0.00", ocvMax[i]) + "," + FormatFloat("0.00", ocvMax[i]-ocvMin[i]) + "\n";
	}


	//* 파일 쓰기
	//fn_report = ExtractFileName(fn_data) + "_report.csv";
	if(FileExists(fn_report)){
		DeleteFile(fn_report);
	}

	file_handle = FileCreate(fn_report);
	FileSeek(file_handle, 0, 0);

	str = ir + "\n" + ocv;

	FileWrite(file_handle, str.c_str(), str.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::probetimerTimer(TObject *Sender)
{
	if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_CLOSE)){
		Mod_PLC->SetValue(PC_D_IROCV_PROB_CLOSE, 0);
		probetimer->Enabled = false;
	}

	if(Mod_PLC->GetPlcValue(PLC_D_IROCV_PROB_OPEN)){
		Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 0);
        probetimer->Enabled = false;
	}

}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::advBtnRemeasureClick(TObject *Sender)
{
	BaseForm->nForm[0]->RemeasureAllBtnClick(this);
	this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::advRemeasureTrayOutClick(TObject *Sender)
{
	// tray_out on
	BaseForm->nForm[0]->ForceTrayOut();
	this->Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// CHART
//---------------------------------------------------------------------------
void __fastcall TMeasureInfoForm::InitializeChart(int ir_min, int ir_max, int ocv_min, int ocv_max)
{
    for(int i=0; i<3; ++i){
		IrChart->Series[i]->Clear();
		OcvChart->Series[i]->Clear();
	}

	for(int i = 0; i < MAXCHANNEL; ++i){
		IrChart->Series[0]->AddXY(i + 1, 0);
		OcvChart->Series[0]->AddXY(i + 1, 0);
	}

	IrChart->LeftAxis->Maximum = ir_max + 5;
	IrChart->LeftAxis->Minimum = ir_min - 5;

	OcvChart->LeftAxis->Maximum = ocv_max + 200;
	OcvChart->LeftAxis->Minimum = ocv_min - 200;

	IrChart->Series[1]->AddXY(1, ir_max);
	IrChart->Series[1]->AddXY(MAXCHANNEL, ir_max);
	OcvChart->Series[1]->AddXY(1, ocv_max);
	OcvChart->Series[1]->AddXY(MAXCHANNEL, ocv_max);

	IrChart->Series[2]->AddXY(1, ir_min);
	IrChart->Series[2]->AddXY(MAXCHANNEL, ir_min);
	OcvChart->Series[2]->AddXY(1, ocv_min);
	OcvChart->Series[2]->AddXY(MAXCHANNEL, ocv_min);
}
//---------------------------------------------------------------------------
