// [장비 통신] 소켓 연결, 수신 큐, 프레임 해석, 명령 송신, 응답 분기와 운전 모드.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"
#pragma link "wininet.lib"

void __fastcall TTotalForm::CmdStart()
{
	MakeData(1, "STA");
}

void __fastcall TTotalForm::CmdBattHeight(int height)
{
	// 자동검사 2. 높이 전송 (송신)
	if(sensor._SafetySensing_1 == true){
		ProcessError("STAGE", "ERROR","Abnormal position tray", "Normal sensor was detected");
	}else{
		MakeData(1, "SIZ", "01");
	}
}

void __fastcall TTotalForm::CmdReset()
{
	MakeData(1, "RST");
}

void __fastcall TTotalForm::CmdIRCell(AnsiString pos)
{
    int value = pos.ToInt();
	value = chReverseMap[value];
	pos = FormatFloat("000", value);
	MakeData(2, "IR*", pos);
}

void __fastcall TTotalForm::CmdOCVCell(AnsiString pos)
{
    int value = pos.ToInt();
	value = chReverseMap[value];
	pos = FormatFloat("000", value);
	MakeData(2, "OCV", pos);
}

void __fastcall TTotalForm::CmdSpeedSet(int mode)
{
    MakeData(1, "IRT", mode);
}

void __fastcall TTotalForm::CmdManualMod(bool Set)
{
    //* 속도 변경 IRT0->slow IRT1->medium IRT2->fast
    if(rbSpeedSlow->Checked) CmdSpeedSet(0);
    else if(rbSpeedMed->Checked) CmdSpeedSet(1);
    else if(rbSpeedFast->Checked) CmdSpeedSet(2);

    PLCInitialization();
	if(Set){ //* Manual
        Mod_PLC->SetValue(PC_D_IROCV_STAGE_AUTO_READY, 0);
		SendData("MAN", "O");
		this->InitTrayStruct();

		DisplayStatus(nManual);
        ResetAutoInspection();
		if(Timer_AutoInspection->Enabled == true)
			Timer_AutoInspection->Enabled = false;
	}
	else{    //* Auto
        Mod_PLC->SetValue(PC_D_IROCV_STAGE_AUTO_READY, 1);
		SendData("MAN", "X");
		this->InitTrayStruct();

        DisplayStatus(nVacancy);
        ResetAutoInspection();
		if(Timer_AutoInspection->Enabled == false)
			Timer_AutoInspection->Enabled = true;

        if(MeasureInfoForm->msaTimer->Enabled == true)
            MeasureInfoForm->msaTimer->Enabled = false;
	}
}

int __fastcall TTotalForm::SensorState(AnsiString cmd)
{
/*
	if(cmd == "MAN"){
		if(MeasureInfoForm->pLocal->Visible == false){
			MeasureInfoForm->pLocal->Visible = true;
		}
		return MAN;
	}else{
		if(MeasureInfoForm->pLocal->Visible){
			MeasureInfoForm->pLocal->Visible = false;
		}
	}
*/
	if(cmd == "EMS")return EMS;
	if(cmd == "ERR")return ERR;
	if(cmd == "ARV")return ARV;
	if(cmd == "STB")return STB;
	if(cmd == "LOC")return LOC;
	if(cmd == "EMP")return EMP;
	if(cmd == "BYP")return BYP;
	if(cmd == "RDY")return RDY;
	if(cmd == "DOR")return DOR;
	if(cmd == "RST")return RST;
	if(cmd == "BZY")return BZY;
	if(cmd == "IDL")return IDL;
    if(cmd == "HOM")return HOM;
	return -3;
}

int __fastcall TTotalForm::DataCheck(AnsiString msg, AnsiString &param)
{
	// 1. stx, etx 확인
	// 2. CMD + PARAM 분리
	// 3. CHECKSUM 확인
	// 4. 재전송 및 응답 확인


	unsigned char stx, etx;
	AnsiString cmd;
	AnsiString check_sum;
	unsigned char sum = 0;

	int data_len = msg.Length();
	int param_len = data_len - 7;

	stx = msg[1];
	etx = msg[data_len];
	cmd = msg.SubString(2,3);
	if(param_len > 0){
		param = msg.SubString(5, param_len);
	}
	check_sum = msg.SubString(data_len-2,2);

	for(int i=2; i<data_len - 2; ++i){
		sum = msg[i] + sum;
	}
	if(stx != 0x02 || etx != 0x03)return -1;
	if(check_sum != IntToHex(sum, 2))return -2;

	// PC 전송에 대한 검사장치 응답 메세지

	if(cmd == "AMS")return AMS;
	if(cmd == "AMF")return AMF;
	if(cmd == "IR*")return IR;
	if(cmd == "OCV")return OCV;

	if(cmd == "IDN")return IDN;
	if(cmd == "SIZ")return SIZ;


	if(cmd == "STP")return STP;
	if(cmd == "FIN")return FIN;

	if(cmd == "MAN")return MAN;


	if(cmd == "SEN")return SEN;
	if(cmd == "OUT")return sOUT;
	if(cmd == "BCR")return BCR;

	if(cmd == "EMS")return EMS;
	if(cmd == "RST")return RST;
	if(cmd == "REM")return REM;
	if(cmd == "ERR")return ERR;
	if(cmd == "CLR")return CLR;
	if(cmd == "REC")return REC;
	if(cmd == "LRM")return LRM;
	if(cmd == "FRM")return FRM;
	if(cmd == "STA")return STA;
	if(cmd == "DEV")return DEV;
	return -3;
}

void __fastcall TTotalForm::SendData(AnsiString Cmd, AnsiString Param)
{
	if(sock != NULL){
		TxVector.clear();
		TxVector.push_back(0x02);

		unsigned char CheckSum =0;
		TxVector.push_back(Cmd[1]);
		TxVector.push_back(Cmd[2]);
		TxVector.push_back(Cmd[3]);

		if(!Param.IsEmpty()){
			for(int i=1; i<Param.Length()+1; ++i){
				TxVector.push_back(Param[i]);
			}
		}
		for(unsigned int i=1; i<TxVector.size(); ++i){
			CheckSum += TxVector[i];
		}

		AnsiString msg;

		for(unsigned int i=0; i<TxVector.size(); i++){
			msg = msg + (char)TxVector[i];
		}
		msg = msg + IntToHex(CheckSum,2) + (char)3;
		// 로그 남기기
		WriteCommLog("TX", msg);
		sock->SendText(msg);
		//sock->sen
	}
}

void __fastcall TTotalForm::MakeData(int tx_mode, AnsiString cmd, AnsiString param)
{
	if(tx_mode < 0){
		q_cmd.push(cmd.c_str());
		q_param.push(param.c_str());
	}else{
		send.cmd = cmd;
		send.param = param;
		send.tx_mode = tx_mode;
	}
}

//---------------------------------------------------------------------------
// 장비 소켓 연결 완료: 송신 상태와 화면을 초기화하고 현재 모드 정보를 적용한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ClientConnect. 측정장비 연결 완료는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentConnected(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	pConInfo->Font->Color = clrConInfo->Color;
	pConInfo->Caption = "IR/OCV is connected";
	sock = Socket;

	send.tx_mode = 0;  	// 초기화
	send.time_out = 0;
	send.re_send = 0;


	if(stage.arl == nLocal){
		this->CmdManualMod(true);
	}
	OldSenCmd = "NONE";
	SendTimer->Enabled = true;
	RefreshStageStatusImage();
}

//---------------------------------------------------------------------------
// 장비 소켓 연결 중 표시를 갱신한다. 연결 완료로 간주하지 않는다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ClientConnecting. 측정장비 연결 진행는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentConnecting(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	pConInfo->Font->Color = clRed;
	pConInfo->Caption = "Connection...";
	RefreshStageStatusImage();
}

//---------------------------------------------------------------------------
// 장비 소켓 오류 처리: 연결을 닫고 미연결 이미지를 갱신한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ClientError. 측정장비 소켓 오류는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentSocketError(TObject *Sender,
	  TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode)
{
	AnsiString str;
	str = "Connection failed";
	pConInfo->Caption = str;
	ErrorCode = 0;
	Socket->Close();
	RefreshStageStatusImage();
}

//---------------------------------------------------------------------------
// 장비 연결 해제 처리: 연결 표시를 바꾸며 자동 검사 단계 자체는 보존한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ClientDisconnect. 측정장비 연결 해제는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentDisconnected(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	pConInfo->Font->Color = clRed;
	pConInfo->Caption = "Connection failed.";
	ReContactTimer->Enabled = true;
	sock = NULL;
	RefreshStageStatusImage();
}

//---------------------------------------------------------------------------
// 설정된 재접속 조건에 따라 장비 소켓 연결을 다시 요청한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ReContactTimerTimer. 측정장비 재접속는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentReconnect(TObject *Sender)
{
		ReContactTimer->Enabled = false;
		if(config.recontact == true)
			Client->Active = true;
}

//---------------------------------------------------------------------------
// 장비 소켓에서 받은 문자열을 수신 큐에 넣는다. 명령별 처리는 OnReceiveStage에서 한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 ClientRead. 측정장비 수신 프레임 분리는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentSocketRead(TObject *Sender,
	  TCustomWinSocket *Socket)
{
	AnsiString msg;
	AnsiString queue_msg;

	msg = Socket->ReceiveText();
	int stx =  msg.Pos((char)0x02);
	int etx = msg.Pos((char)0x03);

	if(etx > 0){
		while(etx > 0){
			if(stx == 1)queue_msg = msg.SubString(1, etx);
			else queue_msg = remainMsg + msg.SubString(1, etx);
			rxq.push(queue_msg.c_str());
			msg.Delete(1, etx);

			stx =  msg.Pos((char)0x02);
			etx =  msg.Pos((char)0x03);

			if(etx > 0)remainMsg = "";
			else remainMsg = msg;
		}
	}else{
		remainMsg = msg;
	}
}

//---------------------------------------------------------------------------
// 수신 큐를 읽어 COMM_RECEIVE 메시지로 전달한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 rxTimerTimer. 측정장비 수신 큐 처리는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentReceiveQueue(TObject *Sender)
{
	AnsiString RxStr;
	bool flag;

	if(rxq.empty() == false){	// 데이터가 있으면 처리
			RxStr = rxq.front().data();
			rxq.pop();
			SendMessage(BaseForm->nForm[Tag]->Handle, COMM_RECEIVE, 0, (LPARAM)&RxStr);
	}

}

//---------------------------------------------------------------------------
// 예약된 장비 명령의 송신·재전송을 처리한다. 자동 검사 진행 타이머와 구분한다.
// 디자이너 이벤트 진입점은 FormTotal.cpp의 SendTimerTimer. 측정장비 송신 큐 처리는 이 파일에서 유지한다.
void __fastcall TTotalForm::ProcessEquipmentSendQueue(TObject *Sender)
{
	if(q_cmd.empty() == false){
		SendTimer->Interval = 700;
		SendData(q_cmd.front().data(), q_param.front().data());
		q_cmd.pop();
		q_param.pop();
	}else{
		senCnt += 1;

		switch(send.tx_mode){
			case 0: // 일반 상태, 타임아웃 처리
				SendTimer->Interval = 10;
				if(senCnt < 32 && senCnt > 30){
					SendData("OUT");
				}else if(senCnt > 60) {
					senCnt = 0;
					SendData("SEN");
				}
				break;
			case 1: // 특정 메세지 전송
				SendTimer->Interval = 500;
				SendData(send.cmd, send.param);
				break;
			case 2:	// 응답일 경우
				SendTimer->Interval = 100;
				SendData(send.cmd, send.param);
				send.tx_mode = 0;
				break;
			case 3:	// 전송 후 다른 명령어 대기
                SendTimer->Interval = 300;
				SendData(send.cmd, send.param);
				send.tx_mode = 100;
			case 200:
				return;
			default:
				break;
		}
		send.time_out += 1;	// 재전송 횟수 및 타이머 시간 체크
		// 타임아웃 시간 설정 할것.
		if(send.time_out == 300){
			//this->DisplayStatus(nNoAnswer);
		}
	}
}

//---------------------------------------------------------------------------
// 장비 응답 분기: AMS/AMF/IR/OCV/센서 상태 등을 해당 처리 함수로 전달한다.
void __fastcall TTotalForm::OnReceiveStage(TMessage& Msg)
{
	AnsiString *msg, param;
	int cmd = 0;
	msg = (AnsiString*)Msg.LParam;
	int nvalue = 0;

//	if((stage.err == NO_ANSWER) && (GrpError->Visible)){
//		this->VisibleBox(OldGrp);
//	}

	try{

		if(msg->Trim().IsEmpty()){
			return;
		}
		WriteCommLog("RX", *msg);
		cmd = DataCheck(*msg, param); 	// cmd , check sum 확인

		send.time_out = 0;

        //if(!ims->m_bStart) return;      // 수정

		switch(cmd){
			case STA:
				send.tx_mode = 0;
				 break;
			case DEV:
				if(param.Pos(",1,") > 0)pdev1->Color = clBothCheck;
				else pdev1->Color = clSilver;
				if(param.Pos(",2,") > 0)pdev2->Color = clBothCheck;
				else pdev2->Color = clSilver;
				if(param.Pos(",3,") > 0)pdev3->Color = clBothCheck;
				else pdev3->Color = clSilver;
				if(param.Pos(",4,") > 0)pdev4->Color = clBothCheck;
				else pdev4->Color = clSilver;
				if(param.Pos(",11,") > 0)pdev5->Color = clBothCheck;
				else pdev5->Color = clSilver;
				if(param.Pos(",12,") > 0)pdev6->Color = clBothCheck;
				else pdev6->Color = clSilver;
				if(param.Pos(",13,") > 0)pdev7->Color = clBothCheck;
				else pdev7->Color = clSilver;
				if(param.Pos(",14,") > 0)pdev8->Color = clBothCheck;
				else pdev8->Color = clSilver;

				for(int i=0; i<8; ++i){
					if(pdev[i]->Color == clBothCheck)nvalue += 1;
				}

				if(nvalue < 2)ProcessError("MEASUREMENT", "ERROR","Measurement error", "");
				else{
					CmdAutoTest();
				}
				break;
			case BCR:
				if( (param.Pos("?") == 0) && (param != "NOREAD") ){ 	// 바코드 읽기 성공
					//pTrayid->Caption = param;
					editTrayId->Text = param;
					send.tx_mode = 0;
				}
				else{
					if(send.re_send < 2){
						send.re_send += 1;
						send.tx_mode = 3;
					}
					else{
						send.tx_mode = 0;
						send.re_send = 0;
						ErrorMsg(BARCODE_ERROR);
					}
				}
				break;
			case IDN:        // 버전
				pConInfo->Caption = param;
				send.tx_mode = 0;
				break;
			case RST:
				send.tx_mode = 0;
				ErrorMsg(RESET);
                Initialization(); // 2017 09 04 herald
				//SendData("STA");
				break;        // 모든 에러 해제
			case SIZ:
				send.tx_mode = 0;
				DisplayStatus(nREADY);
				break;        // BATT 사이즈 정보
			case AMS:
				pb->Position = 0;
				send.tx_mode = 200;
				tray.ams = true;
                tray.amf = false;
				DisplayStatus(nRUN);
				break;
			case AMF:        // 검사종료 알림
                if(tray.amf) break; // Ignore a duplicate completion for this measurement.
				send.tx_mode = 0;
				tray.ams = false;
				tray.amf = true;

				ResponseAutoTestFinish();
				break;
			case IR:        // IR 셀 검사
				if(pb->Position < pb->Max)pb->Position += 1;
				ProcessIr(param);	// 읽기 , 색깔 변화
				break;
			case OCV:        // OCV 셀 검사
				ProcessOcv(param);
				break;
			case STP:        // 강제 검사 종료
				send.tx_mode = 0;
				DisplayStatus(nEND);
				break;
			case FIN:       // 트레이 방출
				//this->DisplayStatus(nFinish);
				ModChange();
				send.tx_mode = 0;
				break;
			// 검사장치 송신에 대한 PC응답 메세지 처리
			case MAN: send.tx_mode = 0; break;
			case REM: send.tx_mode = 0; break;
			case EMS: send.tx_mode = 0; break;
			case SEN:        // 센서정보
				SensorInputProcess(param);
				break;
			case sOUT:
				SensorOutputProcess(param);
				break;
			case ERR:        // 검사장치 에러 발생
				ResponseError(param);
				OldSenCmd = "NONE";
				send.tx_mode = 0;
				break;
			case CLR:
				SendData("CLR");
				OldSenCmd = "NONE";
				VisibleBox(OldGrp);
				break;       // 에러 해제 통보
			case REC: send.tx_mode = 0; break;
			case LRM:
				send.tx_mode = 0;
				StageLocalRemeasure();
				break;
			default:
				this->WriteCommLog("ERR", "Undefined Command");
				send.tx_mode = 0;
				break;
		}
	}catch(...){
		this->WriteCommLog("ERR", "Except Error : " + *msg);
	}
}

//---------------------------------------------------------------------------
// 장비의 로컬 재측정 요청을 처리하고 기존 불량 개수에 따라 재측정 모드를 정한다.
void __fastcall TTotalForm::StageLocalRemeasure(bool frm)
{
	// OP 박스 재측정 요청시
	SendData("LRM");

	if(GrpRemeasure->Visible == true){
		VisibleBox(GrpMain);

        // OP 박스 요청의 전체/선택 기준. Config의 닫힘 유지 재측정 제한과는 별개.
		if(retest.cnt_error > PROBE_REMEASURE_ALL_CELL_NG_THRESHOLD){
			retest.re_excute = false;	// 전체 재측정
		}
		else{
			retest.re_excute = true;	// 불량 재측정
		}
		CmdBattHeight();
	}
}

//---------------------------------------------------------------------------
// 예약된 Auto/Remote/Local 운전 모드를 적용한다.
void __fastcall TTotalForm::ModChange()
{
	if(stage.arl != stage.arl_reserve){
		stage.arl = stage.arl_reserve;
		switch(stage.arl){
			case nAuto:
				this->CmdManualMod(false);
				VisibleBox(GrpMain);
				break;
			case nRemote:
				this->CmdManualMod(false);
				break;
			case nLocal:
				this->CmdManualMod(true);
				stage.alarm_status = nManual;
				break;
		}
	}
}

//---------------------------------------------------------------------------
// 센서 입력 응답을 저장하고 장비 상태 변경을 감지한다.
void __fastcall TTotalForm::SensorInputProcess(AnsiString param)
{
	AnsiString cmd;
	cmd = param.SubString(1,3);
	param.Delete(1,3);

	unsigned char *ptrInput;


	ptrInput = (unsigned char *)&sensor;


	while(param.IsEmpty() == false){
		*ptrInput = (unsigned char)StrToInt("0x" + param.SubString(1,2));
		ptrInput++;
		param.Delete(1,2).Trim();
	}
	//DisplaySensorInfo();

	if(stage.init == true){
		lblStatus->Caption = cmd;
		InitEquipStatus(SensorState(cmd));
		OldSenCmd = cmd;
		stage.init = false;
	}
	else if(cmd != OldSenCmd){
		lblStatus->Caption = cmd;
		EquipStatus(SensorState(cmd));
		OldSenCmd = cmd;
	}
}

//---------------------------------------------------------------------------
// 장비 센서 출력 응답을 센서 출력 버퍼에 저장한다.
void __fastcall TTotalForm::SensorOutputProcess(AnsiString param)
{
	unsigned char *ptrOutput;

	ptrOutput = (unsigned char *)&sensor_out;


	while(param.IsEmpty() == false){
		*ptrOutput = (unsigned char)StrToInt("0x" + param.SubString(1,2));
		ptrOutput++;
		param.Delete(1,2).Trim();
	}
	//DisplaySensorInfo();
}

//---------------------------------------------------------------------------
// 장비 상태 코드 변경에 따른 기존 화면/명령 처리를 수행한다.
void __fastcall TTotalForm::EquipStatus(int cmd)
{
	switch(cmd)
	{
		case HOM:
//			DisplayStatus(nVacancy);
//			VisibleBox(GrpMain);
			break;

		case MAN:
//			if(GrpLocal->Visible == false){
//				stage.arl = nLocal;
//				VisibleBox(GrpLocal);
//			}
//			DisplayStatus(nManual);
//			InitMeasureForm();
			break;
		case EMS:
			//DisplayStatus(nEmergency);
			VisibleBox(GrpMain);
			break;
		case LOC:
			//DisplayStatus(nOpbox);
			VisibleBox(GrpMain);
			break;
		case EMP:
			//DisplayStatus(nVacancy);
			break;
		case RST:
			CmdStart();
			OldSenCmd = "NONE";
			break;
		case IDL:
//			if( OldSenCmd != "ARV"){
//				CmdStart();
//			}
//			else{
//				DisplayStatus(nIdle);
//			}
			break;
		case BZY:
			break;
	}
}

//---------------------------------------------------------------------------
// 최초 센서 응답의 운전 상태를 초기 화면에 반영한다.
void __fastcall TTotalForm::InitEquipStatus(int cmd)
{

	switch(cmd)
	{
		case RDY:
			//this->FinishMeasurement();
			//this->DisplayStatus(nIN);
			//ProcessError("Tray In", "",  "Please select the following actions : ", "Inspection start or  eject tray");
			break;
		case ARV:
		case STB:
			//this->DisplayStatus(nIN);
			//ProcessError("Tray In", "",  "Please select the following actions : ", "Inspection start or  eject tray");
			break;
		case MAN:
			stage.alarm_status = nManual;
			stage.arl = nLocal;
			VisibleBox(GrpLocal);
			DisplayStatus(nManual);
			break;
		case BZY:
			//ProcessError("STAGE", "BUSY", "On stage is a work in progress", "");
			break;
		default:
			EquipStatus(cmd);
			break;
	}
}
