#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"
#pragma link "wininet.lib"
void __fastcall TTotalForm::CmdStart()
{
	MakeData(1, "STA");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdBattHeight(int height)
{
	// 자동검사 2. 높이 전송 (송신)
	if(sensor._SafetySensing_1 == true){
		ProcessError("STAGE", "ERROR","Abnormal position tray", "Normal sensor was detected");
	}else{
		MakeData(1, "SIZ", "01");
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdAutoTest()
{
    for(int i = 0; i < MAXCHANNEL; i++)
	{
		tray.ir_flag[i] = false;
		tray.ocv_flag[i] = false;
	}

	tray.ir_avgAll = 0;
	tray.ir_avgAll_count = 0;

	tray.ocv_avgAll = 0;
    tray.ocv_avgAll_count = 0;

	// 자동검사 4. 검사시작
	MakeData(3, "AMS");
}
//---------------------------------------------------------------------------
// For PLC
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdForceStop_Original()
{
	// 자동검사 7. 검사종료	- Probe 해제 및 Tray 검사 대기
	MakeData(1, "STP");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdForceStop()
{
	// 검사종료	- Probe 해제 및 Tray 검사 대기
    MakeData(1, "STP");
    Panel_State->Caption = " IR/OCV Complete ... ";

	Mod_PLC->SetValue(PC_D_IROCV_PROB_OPEN, 1);
	WritePLCLog("CmdForceStop", "IROCV PROBE OPEN = 1");

    BadInfomation();
    WritePLCLog("CmdForceStop", "Write BadInfomation");
    Sleep(50);
    WriteResultCode();
    WritePLCLog("CmdForceStop", "Write ResultCode");
    ReadCellInfo();

    Sleep(50);
    WriteIROCVValue();
    WritePLCLog("CmdForceStop", "Write IR, OCV Value");
    // Load Cell Serial
    LoadTrayInfo(tray.trayid);
    // Write Result File
    WriteResultFile();
    Mod_PLC->SetValue(PC_D_IROCV_COMPLETE, 1);
    WritePLCLog("CmdForceStop", "PC_D_IROCV_COMPLETE = 1");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdTrayOut()
{
    Mod_PLC->SetValue(PC_D_IROCV_CELL_SERIAL_COMP, 0);
    Mod_PLC->SetValue(PC_D_IROCV_CELL_SERIAL_START, 0);

    if(NgCount == tray.cell_count || NgCount > editNgAlarmCount->Text.ToIntDef(10)){
        Form_Error->DisplayErrorMessage("IR/OCV NG ERROR",
										"There is too many ng cells. Please check it.",
										"Select [Tray Out] or [Restart]");
		Form_Error->Tag = this->Tag;
        DisplayStatus(nEND);
	}
	else{
        Mod_PLC->SetValue(PC_D_IROCV_TRAY_OUT, 1);
        DisplayStatus(nFinish);
        WritePLCLog("CmdTrayOut", "IROCV TRAY OUT = 1");
		Panel_State->Caption = " IROCV Tray Out ... ";
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdTrayOut_Original()
{
	BadInfomation();
	WriteIROCVValue();
    LoadTrayInfo(tray.trayid);
	WriteResultFile();
//	WriteResultFile_MES2();
//    WriteResultFile_MES();
//	WriteOKNG();

//	DeleteFile((AnsiString)DATA_PATH + tray.trayid + ".Tray");

	// 자동검사 9(끝). 트레이 방출
	MakeData(1,"FIN");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdVersion()
{
	MakeData(1, "IDN");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdEmergencyStop()
{
	MakeData(1, "EMS");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdReset()
{
	MakeData(1, "RST");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdIRCell(AnsiString pos)
{
    int value = pos.ToInt();
	value = chReverseMap[value];
	pos = FormatFloat("000", value);
	MakeData(2, "IR*", pos);
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdOCVCell(AnsiString pos)
{
    int value = pos.ToInt();
	value = chReverseMap[value];
	pos = FormatFloat("000", value);
	MakeData(2, "OCV", pos);
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdGetSensorInfo()
{
	MakeData(0,"SEN");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdSpeedSet(int mode)
{
    MakeData(1, "IRT", mode);
}
//---------------------------------------------------------------------------
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
        nSection = STEP_WAIT;
		nStep = 0;
		if(Timer_AutoInspection->Enabled == true)
			Timer_AutoInspection->Enabled = false;
	}
	else{    //* Auto
        Mod_PLC->SetValue(PC_D_IROCV_STAGE_AUTO_READY, 1);
		SendData("MAN", "X");
		this->InitTrayStruct();

        DisplayStatus(nVacancy);
        nSection = STEP_WAIT;
		nStep = 0;
		if(Timer_AutoInspection->Enabled == false)
			Timer_AutoInspection->Enabled = true;

        if(MeasureInfoForm->msaTimer->Enabled == true)
            MeasureInfoForm->msaTimer->Enabled = false;
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdRestart()
{
	MakeData(1, "REM");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::StageClearAlarm()
{
	MakeData(1, "CLR");
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::CmdDeviceInfo()
{
	MakeData(3, "DEV", "1");
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
void __fastcall TTotalForm::ResponseAutoTestFinish()
{
//*
//    if(config.average_use == true) SetRemeasureList();
//	else SetRemeasureList2();

	if(bLocal == true){
		CmdForceStop();
        DisplayProcess(sFinish, "AutoInspection_Measure", " AMF - Measure finished ... ");
		WriteCommLog("IR/OCV STOP", "AMF - ResponseautoTestfinish()");
	}
	else
	{
//		SendData("AMF");    //kedison
		SendData("SEN");
//		CmdForceStop();
    	//* 마련 EVE는 Average(SetRemeasureList2())를 사용하지 않음.
		if(config.average_use == true) SetRemeasureList();
		else SetRemeasureList();
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  				IR / OCV 데이타 처리 관련
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TTotalForm::ProcessIr(AnsiString param)
{
	AnsiString msg_ir, msg_ocv, result;
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Pos(",") - pos - 2).ToInt();

	if(count > 10) value = 0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 0 || value > 900)result = "CE";
	else result = "GO";

    int index = channel - 1;

	if(CaliForm->stage != this->Tag)
	{
		InsertIrValue(channel, value, result); //일반계측
	}
	else
	{
        TColor clr;
		if(result == "GO")
		{
			clr = clIrCheck;
			CaliForm->pmeasure[index]->Caption = FormatFloat("0.000", value);
			CaliForm->poffset[index]->Caption = FormatFloat("0.00", StrToFloat(CaliForm->pstandard[index]->Text) -  value);
		}
		else
			clr = clMeasureFail;
			value = 0;
	}

	if(tray.rem_mode == 1){
		send.tx_mode = 200;
		this->RemeasureExcute();
	}

}//---------------------------------------------------------------------------
void __fastcall TTotalForm::InsertIrValue(int pos, float value, AnsiString result)
{
	int index = pos-1;

	bool cell = false;

	if(tray.cell[index] == 1)cell = true;
	tray.measure_result[index] = GetReslut(result);


	if(cell)   // 셀이 있을때
	{
        tray.orginal_value[index] = value;
		tray.after_value[index] = tray.orginal_value[index] + BaseForm->DefaultOffset[this->Tag];
		tray.after_value[index] = tray.after_value[index] + stage.ir_offset[index];    //개별보정

		if(tray.measure_result[index] == GO)
		{
			if(tray.after_value[index] >= config.ir_min && tray.after_value[index] <= config.ir_max)
			{
				SetProcessColor(index, IrCheck);

                tray.ir_avgAll_count++;
				tray.ir_avgAll += tray.after_value[index];
                tray.ir_flag[index] = true;
			}
			else
			{
				SetProcessColor(index, MeasureFail, result);
            }
		}
		else
		{
			tray.orginal_value[index] = 999;
			tray.after_value[index] = 999;
			SetProcessColor(index, MeasureFail, result);
		}

	}
	else{     // 셀이 없을때
		if(tray.measure_result[index] == GO)
		{
			WriteCommLog("ETC", "OUTFLOW");
			SetProcessColor(index, CellError);
		}

		tray.orginal_value[index] = 0;
		tray.after_value[index] = 0;
	}
}
//---------------------------------------------------------------------------
int __fastcall TTotalForm::GetReslut(AnsiString result)
{
	if(result == "GO") return GO;
	if(result == "HI") return HI;
	if(result == "LO") return LO;
	if(result == "OV") return OV;
	if(result == "UN") return UN;
	if(result == "CE") return CE;
	if(result == "NA") return NA;
	if(result == "NO") return NO;
	else return 100;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::ProcessOcv(AnsiString param)
{
	int channel = 0;
	channel = chMap[param.SubString(1, 3).ToInt()];

	param.Delete(1,3);
	int pos = param.Pos("E");

	float value = (float)param.SubString(1, pos-1).ToDouble() * 1000;
	int count = param.SubString(pos + 2, param.Length()).ToInt();

	if(count > 10) value = 0.0;
	else
	{
		if(param.SubString(pos + 1, 1) == "+")
		{
			for(int i = 0; i < count; i++) {
				value *= 10.0;
			}
		}
		else if(param.SubString(pos + 1, 1) == "-")
		{
			for(int i = 0; i < count; i++) {
				value /= 10.0;
			}
		}
	}

	if(value <= 10 || value > 7000) value = 0.0;

	int index;

	index = channel -1;
	InsertOcvValue(channel, value);


//	SetProcessColor(index, OcvCheck);

//	if(tray.ocv_value[index] >= config.ocv_min && tray.ocv_value[index] <= config.ocv_max){
//		SetProcessColor(index, OcvCheck);
//	}else{
//        SetProcessColor(index, BadOcv);
//    }
//	SetProcessColor(index, OcvCheck);

	if(tray.rem_mode == 1){
		send.tx_mode = 200;
		this->RemeasureExcute();
	}
}

//---------------------------------------------------------------------------
void __fastcall TTotalForm::InsertOcvValue(int pos, float value)
{
	// 자동검사 5.2 검사 결과 수신 - OCV
	int index = pos-1;
	bool cell = false;

	if(tray.cell[index] == 1)cell = true;

	if(cell)
	{
		tray.ocv_value[index] = value;

//		if(config.average_use == true && tray.ocv_value[index] >= 100 && tray.ocv_value[index] <= 4200)
//		{
//            SetProcessColor(index, OcvCheck);
//
//			tray.ocv_avgAll_count++;
//			tray.ocv_avgAll += tray.ocv_value[index];
//			tray.ocv_flag[index] = true;
//		}
//		else if(config.average_use == false && tray.ocv_value[index] >= config.ocv_min && tray.ocv_value[index] <= config.ocv_max)
//		{
//			SetProcessColor(index, OcvCheck);
//
//			tray.ocv_avgAll_count++;
//			tray.ocv_avgAll += tray.ocv_value[index];
//			tray.ocv_flag[index] = true;
//		}
//		else
//		{
//			SetProcessColor(index, BadOcv);
//		}
        if(tray.ocv_value[index] >= config.ocv_min && tray.ocv_value[index] <= config.ocv_max)
		{
			SetProcessColor(index, OcvCheck);

			tray.ocv_avgAll_count++;
			tray.ocv_avgAll += tray.ocv_value[index];
			tray.ocv_flag[index] = true;
		}
		else
		{
			SetProcessColor(index, BadOcv);
		}
	}
	else
	{
		if(value > 1500)
		{
			WriteCommLog("ETC", "OUTFLOW");
			SetProcessColor(index, CellError);
		}
//		tray.ocv_value[index] = 0;
        tray.ocv_value[index] = value;
	}
}
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
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
//---------------------------------------------------------------------------
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


