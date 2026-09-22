// [폼 진입점] 생성/표시/닫기, 버튼·입력 이벤트. 검사 처리 구현은 역할별 Stage_*.cpp를 참고한다.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

#pragma package(smart_init)
#pragma link "AdvSmoothButton"
#pragma link "AdvSmoothPanel"
#pragma resource "*.dfm"

TTotalForm *TotalForm;

//===========================================================================
// 폼 생성 / 시작 / 종료
//===========================================================================
__fastcall TTotalForm::TTotalForm(TComponent* Owner)
	: TForm(Owner)
{
	senCnt = 0;
	CurrentGrp = GrpMain;
	sock = NULL;

	clNoCell = cl_no->Color;
	clBadIr = cl_badir->Color;
	clCellError = cl_badocv->Color;
	clLine = cl_line->Color;
	clIrCheck = cl_ir->Color;
	clOcvCheck = cl_ocv->Color;
	clBothCheck = cl_irocv->Color;
	clMeasureFail = cl_ce->Color;

	//BaseImage->AutoSize = true;

//	LocalRemeasure = false;
	MakePanel(BaseForm->lblLineNo->Caption);
//	this->ScaleBy(60,100);
    isAutoInspectionProcessing = false;
    config.cell_serial_continuous_read = false;
    cellSerialContinuousReadForTray = false;
    resultSaveStep = RESULT_IDLE;
    resultSaveStartTime = 0;
    trayResultCounted = false;
    countedFinalIrNg = 0;
    config.probeRemeasureCount = 0;
    config.closedProbeRemeasureMaxNgCount = DEFAULT_CLOSED_PROBE_REMEASURE_MAX_NG_COUNT;
    tray.ams = false; // 설정을 처음 읽을 때 진행 중인 측정으로 오인하지 않게 한다.
    measNgCount = 0;
    showStartupChannelNumbers = true;
    memset(irValueReceived, 0, sizeof(irValueReceived));
    memset(ocvValueReceived, 0, sizeof(ocvValueReceived));

    pProcess[0] = pReady;
	pProcess[1] = pTrayIn;
	pProcess[2] = pBarcode;
	pProcess[3] = pProbeDown;
	pProcess[4] = pMeasure;
	pProcess[5] = pFinish;
	pProcess[6] = pProbeOpen;
	pProcess[7] = pTrayOut;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::FormShow(TObject *Sender)
{
	pdev[0] = pdev1;
	pdev[0]->ParentBackground = false;
	pdev[1] = pdev2;
	pdev[1]->ParentBackground = false;
	pdev[2] = pdev3;
	pdev[2]->ParentBackground = false;
	pdev[3] = pdev4;
	pdev[3]->ParentBackground = false;
	pdev[4] = pdev5;
	pdev[4]->ParentBackground = false;
	pdev[5] = pdev6;
	pdev[5]->ParentBackground = false;
	pdev[6] = pdev7;
	pdev[6]->ParentBackground = false;
	pdev[7] = pdev8;
	pdev[7]->ParentBackground = false;

	ReadRemeasureInfo();

	stage.init = true;
	bLocal = false;

	ReadSystemInfo();
	ReadchannelMapping();


	Timer_PLCConnect->Enabled = true;
	btnConnectIROCVClick(this);
	config.recontact = true;

	pback->Width = 620;
	this->Width = pback->Width + 10;
	this->Height = pback->Height;

    pnlConfig->Width = 600;
    pnlConfig->Height = 644; // [CELL SERIAL 공통] 수신 방식 설정 영역 포함.

	this->ReadCaliboffset();                      //20171202 개별보정을 위해 추가

	OldPLCStatus = "";
	PLCStatus = "";
	OldErrorCheckStatus = "";

    Initialization();
	btnMeasureInfoClick(this);

    //* 임시
    acc_finalng = 0;
    acc_totaltray = 0;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    CancelResultSave();
	WriteRemeasureInfo();
}
//---------------------------------------------------------------------------

//===========================================================================
// 설정 및 측정 화면 버튼
//===========================================================================
void __fastcall TTotalForm::btnSaveConfigClick(TObject *Sender)
{
    UnicodeString msg = Form_Language->msgSaveConfig;
    if(MessageBox(Handle, msg.c_str(), L"SAVE", MB_YESNO|MB_ICONQUESTION) == ID_YES){
	//if(MessageBox(Handle, L"Are you sure you want to save?", L"SAVE", MB_YESNO|MB_ICONQUESTION) == ID_YES){
		WriteSystemInfo();
		WriteRemeasureInfo();
        ReadSystemInfo();
		pnlConfig->Visible = false;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnRemeasureInfoClick(TObject *Sender)
{
	RemeasureForm->stage            = this->Tag;
	RemeasureForm->acc_remeasure 	= acc_remeasure;
    RemeasureForm->acc_totaluse     = acc_totaluse;
	RemeasureForm->acc_init 		= &acc_init;
	RemeasureForm->acc_cnt			= &acc_cnt;
    RemeasureForm->acc_totaltray    = &acc_totaltray;
    RemeasureForm->acc_finalng      = &acc_finalng;

	RemeasureForm->pstage->Caption	= lblTitle->Caption;
    RemeasureForm->Left = 200;
    RemeasureForm->Top = 70;
	RemeasureForm->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::localTestClick(TObject *Sender)
{
	MeasureInfoForm->display.arl = nLocal;
	InitMeasureForm();
	MeasureInfoForm->pLocal->Visible = true;
	bLocal = true;
}
//---------------------------------------------------------------------------

//===========================================================================
// 재측정 / 배출 버튼: 실제 처리는 Stage_Measurement / Stage_AutoInspection
//===========================================================================
void __fastcall TTotalForm::RemeasureAllBtnClick(TObject *Sender)
{
    StartFullRemeasure();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::RemeasureBtnClick(TObject *Sender)
{
    StartSelectedRemeasure();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::TrayOutBtnClick(TObject *Sender)
{
    ForceTrayOut();
    VisibleBox(GrpMain);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::AlarmConfirmBtnClick(TObject *Sender)
{
	MainBtnClick(Sender);

}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnTrayOutClick(TObject *Sender)
{
	if(MessageBox(Handle, L"Are you sure you want to eject the tray?", L"", MB_YESNO|MB_ICONQUESTION) == ID_YES){
        ManualTrayOut();
	}
}
//---------------------------------------------------------------------------

//===========================================================================
// 목록 그리기 / 트레이 ID 입력
//===========================================================================
void __fastcall TTotalForm::BadListDrawItem(TCustomListView *Sender,
	  TListItem *Item, TRect &Rect, TOwnerDrawState drawState)
{
	if(Item->Selected ) {
		BadList->Canvas->Brush->Color = clYellow;
	}
	else {
		BadList->Canvas->Brush->Color = clWindow;
	}
	BadList->Canvas->FillRect(Rect);

	BadList->Canvas->Font->Size = 8;
	BadList->Canvas->TextOut(Rect.Left + 5,Rect.Top,Item->Caption);
	int width = 0;
	for(int i=0; i<Item->SubItems->Count; i++) {
		if(i == 0){
			BadList->Canvas->Font->Color = clRed;
			BadList->Canvas->Font->Style = Font->Style << fsBold;

		}
		else{
			BadList->Canvas->Font->Color = clBlack;
		}

		width += BadList->Columns->Items[i]->Width;
		BadList->Canvas->TextOut(Rect.Left + width + 5,Rect.Top,Item->SubItems->Strings[i]);
	}

}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::pTrayidDblClick(TObject *Sender)
{
	editTrayId->BringToFront();
	editTrayId->Text = "";
	editTrayId->Visible = true;
	editTrayId->SetFocus();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::editTrayIdKeyDown(TObject *Sender, WORD &Key,
		TShiftState Shift)
{
//	UnicodeString str;
//	if(Key == VK_RETURN){
//		str = "[" + editTrayId->Text + "]" + " Are you sure you want inspection?";
//		if(MessageBox(Handle, str.c_str(), L"", MB_YESNO|MB_ICONQUESTION) == ID_YES){
//			send.tx_mode = 0;
//			plc_Barcode();
//			if(LoadTrayInfo(editTrayId->Text))
//			{
//				CmdBattHeight();
//			}
//			else ProcessError("Tray Information", "Error", "The tray information file does not exist.", "Check the barcode ID and file information.");
//		}
//		editTrayId->Visible = false;
//	}
//	if(Key == VK_ESCAPE){
//		editTrayId->Visible = false;
//	}
}
//---------------------------------------------------------------------------

//===========================================================================
// 장비 초기화 / 채널 마우스 표시 / 운전 모드
//===========================================================================
void __fastcall TTotalForm::btnResetClick(TObject *Sender)
{
	if(MessageBox(Handle, L"Are you sure you want to reset?", L"RESET", MB_YESNO|MB_ICONQUESTION) == ID_YES){
		this->CmdReset();
		send.time_out = 0;
		OldSenCmd = "NONE";
	}
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::ChInfoMouseEnter(TObject *Sender)
{
	TPanel *pnl;
	pnl = (TPanel*)Sender;

	pPos->Caption = pnl->Hint;
	pIrValue->Caption = FormatFloat("0.00",tray.after_value[pnl->Tag]);
	pOcvValue->Caption = FormatFloat("0.0",tray.ocv_value[pnl->Tag]);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::ChInfoMouseLeave(TObject *Sender)
{

	pPos->Caption = "";
	pIrValue->Caption = "";
	pOcvValue->Caption = "";

}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::MainBtnClick(TObject *Sender)
{
	switch(stage.arl){
		case nAuto:
			VisibleBox(GrpMain);
			break;
		case nLocal:
			VisibleBox(GrpLocal);
			break;
	}
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::chkBypassMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
	if(chkBypass->Checked && Button == mbLeft){
		if(MessageBox(Handle, L"Do yoy want change BYPASS mode?", L"BYPASS", MB_YESNO|MB_ICONQUESTION) == ID_NO){
			chkBypass->Checked = false;
		}
	}
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnManualClick(TObject *Sender)
{
	stage.arl_reserve = nLocal;
	stage.arl = nLocal;
//    Timer_AutoInspection->Enabled = false;
	this->CmdManualMod(true);
	VisibleBox(GrpLocal);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnAutoClick(TObject *Sender)
{
	stage.arl_reserve = nAuto;
	stage.arl = nAuto;
	bLocal = false;
//    Timer_AutoInspection->Enabled = false;
    MeasureInfoForm->pLocal->Visible = false;
	this->CmdManualMod(false);
	VisibleBox(GrpMain);
}
//---------------------------------------------------------------------------

//===========================================================================
// 화면 열기 / 암호 / 교정
//===========================================================================
void __fastcall TTotalForm::btnMeasureInfoClick(TObject *Sender)
{
    MeasureInfoForm->Left = 640;
    MeasureInfoForm->Top = 85;
    // 수신한 값은 유지하고, 미수신 항목은 채널/위치 번호를 표시한다.
    InitMeasureForm();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnConfigClick(TObject *Sender)
{
    UnicodeString msg = Form_Language->msgInputPwd;
    if (MessageDlg(msg, mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel,1) == mrOk){
//    if (MessageDlg("Plese enter the password!", mtConfirmation, TMsgDlgButtons() << mbOK << mbCancel,1) == mrOk){
		pPassword->Visible = !pPassword->Visible;
        pPassword->BringToFront();
        pPassword->Left = 309;
        pPassword->Top = 48;
	}
//	pnlConfig->Visible = !pnlConfig->Visible;
//	pnlConfig->Left = 10;
//	pnlConfig->Top = 50;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::PasswordBtnClick(TObject *Sender)
{
    CheckPassword();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::PassEditKeyPress(TObject *Sender, System::WideChar &Key)
{
    if(Key == '\r'){
        CheckPassword();

        Key = 0;
    }
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::cancelBtn2Click(TObject *Sender)
{
    pnlConfig->Visible = false;
}
//---------------------------------------------------------------------------


void __fastcall TTotalForm::localCaliClick(TObject *Sender)
{
	CaliForm->stage = this->Tag;
	CaliForm->pstage->Caption = lblTitle->Caption;
	CaliForm->Visible = true;
    CaliForm->WindowState = wsNormal;
	CaliForm->BringToFront();

    CaliForm->ReadCaliboffset();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnCloseConnConfigClick(TObject *Sender)
{
    chkCellSerialContinuousRead->Checked = config.cell_serial_continuous_read;
	pnlConfig->Visible = false;
}
//---------------------------------------------------------------------------

//===========================================================================
// PLC / 측정장비 연결 버튼
//===========================================================================
void __fastcall TTotalForm::btnConnectPLCClick(TObject *Sender)
{
    WriteSystemInfo();
    ReadSystemInfo();
	Mod_PLC->Connect(PLC_IPADDRESS, PLC_PLCPORT, PLC_PCPORT);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnDisConnectPLCClick(TObject *Sender)
{
    Mod_PLC->DisConnect();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::Timer_PLCConnectTimer(TObject *Sender)
{
    if(Mod_PLC->ClientSocket_PC->Active == false && Mod_PLC->ClientSocket_PLC->Active == false)
		Mod_PLC->Connect(PLC_IPADDRESS, PLC_PLCPORT, PLC_PCPORT);
    Timer_PLCConnect->Enabled = false;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnConnectIROCVClick(TObject *Sender)
{
    if(Client->Active == false){
		config.recontact = true;
		this->ReContactTimerTimer(ReContactTimer);
	}
	else{
			Client->Active = false;
			config.recontact = true;
			this->ReContactTimerTimer(ReContactTimer);
	}
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::btnDisConnectIROCVClick(TObject *Sender)
{
    Client->Active = false;
    config.recontact = true;
    this->ReContactTimerTimer(ReContactTimer);
}
//---------------------------------------------------------------------------

//===========================================================================
// 기존 시험용 UI / 속도 / 대기 시간 표시
//===========================================================================
void __fastcall TTotalForm::Button1Click(TObject *Sender)
{
	SetRemeasureList();
    CmdTrayOut();
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::pReadyClick(TObject *Sender)
{
    // 오류창 표시 시험: 실제 검사 상태나 PLC 오류 출력은 변경하지 않는다.
    Form_Error->Tag = this->Tag;
    Form_Error->DisplayErrorMessage("IR/OCV NG ERROR",
										"There is too many ng cells. Please check it.",
										"Select [Tray Out] or [Restart]");
}
//---------------------------------------------------------------------------



void __fastcall TTotalForm::rbSpeedFastClick(TObject *Sender)
{
    TRadioButton *rb = (TRadioButton*)Sender;
    CmdSpeedSet(rb->Tag);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::GroupBox8DblClick(TObject *Sender)
{
    editMaxDelayTime->Visible = !editMaxDelayTime->Visible;
}
//---------------------------------------------------------------------------

// 디자이너 이벤트 진입점: DFM에 연결된 함수는 이 폼 파일에 유지한다.
// 실제 처리만 Stage_*.cpp로 분리해 이벤트 이동과 역할별 코드 정리를 함께 유지한다.
// 자동측정 타이머 처리: Stage_AutoInspection.cpp의 ProcessAutoInspection를 확인한다.
void __fastcall TTotalForm::Timer_AutoInspectionTimer(TObject *Sender)
{
    ProcessAutoInspection(Sender);
}
//---------------------------------------------------------------------------

// 시리얼 수신·결과 저장·PLC 완료 대기: Stage_Measurement.cpp의 ProcessResultSave를 확인한다.
void __fastcall TTotalForm::Timer_ResultSaveTimer(TObject *Sender)
{
    ProcessResultSave(Sender);
}
//---------------------------------------------------------------------------

// 설비 상태·알람·PLC 표시 갱신: Stage_Form.cpp의 ProcessStageStatus를 확인한다.
void __fastcall TTotalForm::StatusTimerTimer(TObject *Sender)
{
    ProcessStageStatus(Sender);
}
//---------------------------------------------------------------------------

// 측정장비 연결 완료: Stage_comm.cpp의 ProcessEquipmentConnected를 확인한다.
void __fastcall TTotalForm::ClientConnect(TObject *Sender,
	  TCustomWinSocket *Socket)
{
    ProcessEquipmentConnected(Sender, Socket);
}
//---------------------------------------------------------------------------

// 측정장비 연결 진행: Stage_comm.cpp의 ProcessEquipmentConnecting를 확인한다.
void __fastcall TTotalForm::ClientConnecting(TObject *Sender,
	  TCustomWinSocket *Socket)
{
    ProcessEquipmentConnecting(Sender, Socket);
}
//---------------------------------------------------------------------------

// 측정장비 소켓 오류: Stage_comm.cpp의 ProcessEquipmentSocketError를 확인한다.
void __fastcall TTotalForm::ClientError(TObject *Sender,
	  TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
    ProcessEquipmentSocketError(Sender, Socket, ErrorEvent, ErrorCode);
}
//---------------------------------------------------------------------------

// 측정장비 연결 해제: Stage_comm.cpp의 ProcessEquipmentDisconnected를 확인한다.
void __fastcall TTotalForm::ClientDisconnect(TObject *Sender,
	  TCustomWinSocket *Socket)
{
    ProcessEquipmentDisconnected(Sender, Socket);
}
//---------------------------------------------------------------------------

// 측정장비 재접속: Stage_comm.cpp의 ProcessEquipmentReconnect를 확인한다.
void __fastcall TTotalForm::ReContactTimerTimer(TObject *Sender)
{
    ProcessEquipmentReconnect(Sender);
}
//---------------------------------------------------------------------------

// 측정장비 수신 프레임 분리: Stage_comm.cpp의 ProcessEquipmentSocketRead를 확인한다.
void __fastcall TTotalForm::ClientRead(TObject *Sender,
	  TCustomWinSocket *Socket)
{
    ProcessEquipmentSocketRead(Sender, Socket);
}
//---------------------------------------------------------------------------

// 측정장비 수신 큐 처리: Stage_comm.cpp의 ProcessEquipmentReceiveQueue를 확인한다.
void __fastcall TTotalForm::rxTimerTimer(TObject *Sender)
{
    ProcessEquipmentReceiveQueue(Sender);
}
//---------------------------------------------------------------------------

// 측정장비 송신 큐 처리: Stage_comm.cpp의 ProcessEquipmentSendQueue를 확인한다.
void __fastcall TTotalForm::SendTimerTimer(TObject *Sender)
{
    ProcessEquipmentSendQueue(Sender);
}
//---------------------------------------------------------------------------
