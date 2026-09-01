#include "FormTotal.h"
#include "RVMO_main.h"

// 환경설정 파일 저장 / 읽기
void __fastcall TTotalForm::WriteSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);

	ini->WriteBool("MAIN", "AUTO_CHECK", RemeasureChk->Checked);
	ini->WriteInteger("MAIN", "REMEASURE", RemeasureEdit->Text.ToIntDef(0));
	ini->WriteBool("MAIN", "REM_BYPASS", chkRemBypass->Checked);

	ini->WriteString("IROCV_PLC", "IP", editPLCIPAddress->Text);
	ini->WriteString("IROCV_PLC", "PORT1", editPLCPortPC->Text);
	ini->WriteString("IROCV_PLC", "PORT2", editPLCPortPLC->Text);

	ini->WriteString("IROCV", "IP", editIROCVIPAddress->Text);
	ini->WriteString("IROCV", "PORT", editIROCVPort->Text);

    ini->WriteString("NG_ALARM_COUNT", "COUNT", editNgAlarmCount->Text);
	ini->WriteInteger("MAIN", "REMEASURE_ALARM_COUNT", editRemeasureAlarmCount->Text.ToIntDef(3));

	config.remeasure_use = RemeasureChk->Checked;
	config.remeasure_cnt = RemeasureEdit->Text.ToIntDef(1);
	config.remeasure_alarm_cnt = editRemeasureAlarmCount->Text.ToIntDef(3);
    RemeasureForm->pcolor2->Caption = config.remeasure_alarm_cnt;
	config.remeasure_bypass = chkRemBypass->Checked;

    ini->WriteString("CELLINFO", "MODELNAME", editModelName->Text);
    ini->WriteString("PASSWORD", "PWD", editPwd->Text);

    //* 측정속도
    AnsiString speedmode = "2";
    if(rbSpeedSlow->Checked) speedmode = "0";
    else if(rbSpeedMed->Checked) speedmode = "1";
    else if(rbSpeedFast->Checked) speedmode = "2";
    ini->WriteString("MAIN", "SPEED_MODE", speedmode);
	//* 최대/최소 대신에 평균값 +/- 범위로 변경
	//* 2022 11 07
	ini->WriteBool("MAIN", "USE_AVERAGE", chkUseAverage->Checked);
	ini->WriteFloat("MAIN", "IR_RANGE", BaseForm->StringToDouble(editIrRange->Text, 5));
	ini->WriteFloat("MAIN", "OCV_RANGE", BaseForm->StringToDouble(editOcvRange->Text, 1000));

	ini->WriteFloat("MAIN", "IR1", BaseForm->StringToDouble(irEdit1->Text, 12));
	ini->WriteFloat("MAIN", "IR2", BaseForm->StringToDouble(irEdit2->Text, 20));
	ini->WriteFloat("MAIN", "OCV1", BaseForm->StringToDouble(ocvEdit1->Text, 1000));
	ini->WriteFloat("MAIN", "OCV2", BaseForm->StringToDouble(ocvEdit2->Text, 3000));

	config.ir_range = BaseForm->StringToDouble(editIrRange->Text, 5);
	config.ocv_range = BaseForm->StringToDouble(editOcvRange->Text, 1000);

	config.ir_min = BaseForm->StringToDouble(irEdit1->Text, 12);
	config.ir_max = BaseForm->StringToDouble(irEdit2->Text, 5);
	config.ocv_min = BaseForm->StringToDouble(ocvEdit1->Text, 1000);
	config.ocv_max = BaseForm->StringToDouble(ocvEdit2->Text, 3000);

	delete ini;
}
//---------------------------------------------------------------------------
bool __fastcall TTotalForm::ReadSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);
	config.remeasure_use = ini->ReadBool("MAIN", "AUTO_CHECK", true);
	config.remeasure_cnt = ini->ReadInteger("MAIN", "REMEASURE", 1);
    config.remeasure_alarm_cnt = ini->ReadInteger("MAIN", "REMEASURE_ALARM_COUNT", 5);
	config.remeasure_bypass = 	ini->ReadBool("MAIN", "REM_BYPASS", false);

    //* 측정속도
    AnsiString speedmode = "2";
    speedmode = ini->ReadString("MAIN", "SPEED_MODE", "2");
    if(speedmode == "0") rbSpeedSlow->Checked = true;
    else if(speedmode == "1") rbSpeedMed->Checked = true;
    else if(speedmode == "2") rbSpeedFast->Checked = true;

    editNgAlarmCount->Text = ini->ReadString("NG_ALARM_COUNT", "COUNT", "20");
	//* IR SPEC (min/max 로 한번검사 + average +/-로 한번 더 검사)
	config.average_use = ini->ReadBool("MAIN", "USE_AVERAGE", true);
	config.ir_min = ini->ReadFloat("MAIN", "IR1", 10);
	config.ir_max = ini->ReadFloat("MAIN", "IR2", 40);
	config.ir_range = ini->ReadFloat("MAIN", "IR_RANGE", 5);

	irEdit1->Text = config.ir_min;
	irEdit2->Text = config.ir_max;
	editIrRange->Text = config.ir_range;

    pnlIRSpec->Caption = "IR : " + FormatFloat("0.0", config.ir_min)  + " ~ " + FormatFloat("0.0", config.ir_max);

	//* OCV SPEC (min/max 로 한번검사 + average +/-로 한번 더 검사)
	config.ocv_min = ini->ReadFloat("MAIN", "OCV1", 500);
	config.ocv_max = ini->ReadFloat("MAIN", "OCV2", 3000);
	config.ocv_range = ini->ReadFloat("MAIN", "OCV_RANGE", 1000);

	ocvEdit1->Text = config.ocv_min;
	ocvEdit2->Text = config.ocv_max;
	editOcvRange->Text = config.ocv_range;

    pnlOCVSpec->Caption = "OCV : " + FormatFloat("0.0", config.ocv_min) + " ~ " + FormatFloat("0.0", config.ocv_max);

	//VisibleSpec(config.ir_average_use);

	editPLCIPAddress->Text = ini->ReadString("IROCV_PLC", "IP", "17.91.80.220");
	editPLCPortPC->Text = ini->ReadString("IROCV_PLC", "PORT1", "5007");
	editPLCPortPLC->Text = ini->ReadString("IROCV_PLC", "PORT2", "5008");

    PLC_IPADDRESS = editPLCIPAddress->Text;
	PLC_PCPORT = editPLCPortPC->Text.ToIntDef(5007);
	PLC_PLCPORT = editPLCPortPLC->Text.ToIntDef(5008);

	editIROCVIPAddress->Text = ini->ReadString("IROCV", "IP", "192.168.250.202");
	editIROCVPort->Text = ini->ReadString("IROCV", "PORT", "45000");

	Client->Host = editIROCVIPAddress->Text;
    Client->Port = editIROCVPort->Text.ToIntDef(45000);

	editModelName->Text = ini->ReadString("CELLINFO", "MODELNAME", "20PQ");
    editPwd->Text = ini->ReadString("PASSWORD", "PWD", "Eveml@123");
    config.pwd = editPwd->Text;

	chkUseAverage->Checked = config.average_use;
	RemeasureChk->Checked = config.remeasure_use;
	RemeasureEdit->Text = config.remeasure_cnt;
	editRemeasureAlarmCount->Text = config.remeasure_alarm_cnt;
	RemeasureForm->pcolor2->Caption = config.remeasure_alarm_cnt;
	chkRemBypass->Checked = config.remeasure_bypass;

	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::VisibleSpec(bool bUseAverage)
{
	if(bUseAverage){
		grpIrSpec->Visible = true;
		grpOcvSpec->Visible = false;
		grpIrAvg->Visible = true;
		grpOcvAvg->Visible = true;
	}
	else{
		grpIrSpec->Visible = true;
		grpOcvSpec->Visible = true;
		grpIrAvg->Visible = false;
		grpOcvAvg->Visible = false;
	}
}
//---------------------------------------------------------------------------
bool __fastcall TTotalForm::ReadCellInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);

	tray.cell_model = ini->ReadString("CELL_INFO", "CELL_MODEL", "-");
	tray.lot_number = ini->ReadString("CELL_INFO", "LOT_NUMBER", "-");

	delete ini;
}
//---------------------------------------------------------------------------
bool __fastcall TTotalForm::LoadTrayInfo(AnsiString trayID)
{
	AnsiString filename;
	filename = (UnicodeString)TRAY_PATH2 + trayID + ".Tray";
    WritePLCLog("Read CELL SERIAL Filename", filename);
	if(FileExists(filename)){
		TIniFile *ini;

		ini = new TIniFile(filename);
		for(int i = 0; i < MAXCHANNEL; i++)
		{
			tray.cell_serial[i] = ini->ReadString(i + 1, "CELL_SERIAL", "-");
		}

		delete ini;
	}
	else return false;

	return true;
}
//---------------------------------------------------------------------------
// 재측정 정보 읽고 쓰기
void __fastcall TTotalForm::ReadRemeasureInfo()
{
	TIniFile *ini;

	ini = new TIniFile((AnsiString)BIN_PATH + "RemeasureInfo.inf");

	AnsiString retest_info, strTotalUse;
	AnsiString title = "REMEASURE" + IntToStr(this->Tag);

	int pos = 0, posTotalNg = 0;
	retest_info = ini->ReadString(title, "ACCMULATE", "-1");
    strTotalUse = ini->ReadString(title, "TOTAL_USE", "-1");
	int nRemeasureAlarmCount = 0;
	config.remeasure_alarm_cnt = ini->ReadInteger(title, "REMEASURE_ALARM_COUNT", 5);
    editRemeasureAlarmCount->Text = config.remeasure_alarm_cnt;
	RemeasureForm->pcolor2->Caption = config.remeasure_alarm_cnt;

    acc_totaltray = ini->ReadInteger(title, "TOTAL_TRAY", 0);
    acc_finalng = ini->ReadInteger(title, "FINAL_NG", 0);

    //* 총 누적불량
	if(retest_info == "-1"){	// 파일이 존재하지 않으면
		for(int index=0; index<MAXCHANNEL; ++index){
			acc_remeasure[index] = 0; 	// 모두 0으로
		}
	}
	else{
		for(int index=0; index<MAXCHANNEL; ++index){
			pos = retest_info.Pos("_");
			acc_remeasure[index] = retest_info.SubString(1,pos-1).ToIntDef(0);
			if(acc_remeasure[index] >= config.remeasure_alarm_cnt)
				nRemeasureAlarmCount++;
			retest_info.Delete(1, pos);
		}
	}

    //* 총 측정 횟수
	if(strTotalUse == "-1"){	// 파일이 존재하지 않으면
		for(int index = 0; index < MAXCHANNEL; ++index)
			acc_totaluse[index] = 0; 	// 모두 0으로
	} else{
		for(int index = 0; index < MAXCHANNEL; ++index){
			posTotalNg = strTotalUse.Pos("_");
			acc_totaluse[index] = strTotalUse.SubString(1, posTotalNg - 1).ToIntDef(0);
			strTotalUse.Delete(1, posTotalNg);
		}
	}

    RemeasureAlarm(nRemeasureAlarmCount);

	retest_info = "";
	acc_init = 	 ini->ReadString(title, "ACCMULATE_DAY", Now().FormatString("yyyy. m. d. hh:nn"));
	acc_cnt = ini->ReadInteger(title, "ACC_CNT", 0);

	delete ini;
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::WriteRemeasureInfo()	// Tray가 Vacancy 상태일때 기록
{
	TIniFile *ini;

	ini = new TIniFile((AnsiString)BIN_PATH + "RemeasureInfo.inf");

	AnsiString retest_info = "", strTotalUse = "";
	AnsiString title = "REMEASURE" + IntToStr(this->Tag);
	retest_info = "";
	int nRemeasureAlarmCount = 0;

	retest_info = "";
	for(int index=0; index<MAXCHANNEL; ++index){
		retest_info =  retest_info + acc_remeasure[index] + "_";
        strTotalUse = strTotalUse + acc_totaluse[index] + "_";
		if(acc_remeasure[index] >= config.remeasure_alarm_cnt)
			nRemeasureAlarmCount++;
	}
	RemeasureAlarm(nRemeasureAlarmCount);

    ini->WriteInteger(title, "REMEASURE_ALARM_COUNT", editRemeasureAlarmCount->Text.ToIntDef(3));
	ini->WriteString(title, "ACCMULATE", retest_info);
    ini->WriteString(title, "TOTAL_USE", strTotalUse);
	ini->WriteString(title, "ACCMULATE_DAY", acc_init);
	ini->WriteInteger(title, "ACC_CNT", acc_cnt);

    ini->WriteInteger(title, "TOTAL_TRAY", acc_totaltray);
    ini->WriteInteger(title, "FINAL_NG", acc_finalng);


	delete ini;
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::RemeasureAlarm(int remeasure_alarm_count)
{
	if(remeasure_alarm_count > 0) {
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_NG_ALARM, 1);
		btnRemeasureInfo->Color = clRed;
		lblRemeasureAlarmCheck->Visible = true;
	}
	else{
        Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_NG_ALARM, 0);
		btnRemeasureInfo->Color = clWhite;
		lblRemeasureAlarmCheck->Visible = false;
    }
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::WriteCommLog(AnsiString Type, AnsiString Msg)
{
	AnsiString str, dir;
	int file_handle;

	dir = (AnsiString)LOG_PATH + Now().FormatString("yyyymmdd") + "\\";
	ForceDirectories((AnsiString)dir);

	str = dir + "STAGE" + FormatFloat("000", this->Tag+1) + "_" + Now().FormatString("yymmdd-hh") + ".log";

	if(FileExists(str))
		file_handle = FileOpen(str, fmOpenWrite);
	else{
		file_handle = FileCreate(str);
	}

	FileSeek(file_handle, 0, 2);

	str = Now().FormatString("yyyy-mm-dd hh:nn:ss ") +Type +  "\t" + Msg + "\n";
	FileWrite(file_handle, str.c_str(), str.Length());

	FileClose(file_handle);
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::WritePLCLog(AnsiString Type, AnsiString Msg)
{
	AnsiString str, dir;
	int file_handle;

	dir = (AnsiString)LOG_PATH + Now().FormatString("yyyymmdd") + "\\";
	ForceDirectories((AnsiString)dir);

	str = dir + "STAGE" + FormatFloat("000", this->Tag+1) + "_PLC_" + Now().FormatString("yymmdd-hh") + ".log";

	if(FileExists(str))
		file_handle = FileOpen(str, fmOpenWrite);
	else{
		file_handle = FileCreate(str);
	}

	FileSeek(file_handle, 0, 2);

	str = Now().FormatString("yyyy-mm-dd hh:nn:ss ") +Type +  "\t" + Msg + "\n";
	FileWrite(file_handle, str.c_str(), str.Length());

	FileClose(file_handle);
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::WriteTrayInfo()
{
	int file_handle;
	AnsiString filename;
	AnsiString dir;
	AnsiString ok_ng;

	dir = (AnsiString)DATA_PATH + Now().FormatString("yyyymmdd") + "\\";// + lblTitle->Caption + "\\";
	ForceDirectories((AnsiString)dir);

	filename =  dir + tray.trayid +  "-" + Now().FormatString("yymmddhhnnss") + "-TRAYINFO.csv";

	if(FileExists(filename)){
		DeleteFile(filename);
	}

	file_handle = FileCreate(filename);
	FileSeek(file_handle, 0, 0);

	AnsiString file;
//	file = "TRAY ID," + tray.trayid + "\r\n";
//	file += "CH,OK/NG\r\n";
	file = "CELL 유무 (1 : OK/ 0 : NG)\r\n";
	for(int i = 0; i < MAXCHANNEL; ++i)
	{
		if(tray.cell[i] == 1) ok_ng = "1";
		else ok_ng = "0";
		file = file + IntToStr(i+1) + "," + ok_ng + "\r\n";
	}

	FileWrite(file_handle, file.c_str(), file.Length());
	FileClose(file_handle);
}

//---------------------------------------------------------------------------
void __fastcall TTotalForm::WriteResultFile()
{
	int file_handle;
	AnsiString filename, dupFileName;
	AnsiString dir;
	AnsiString cell, cell_id, ir, ocv, ch, ok_ng;

	dir = (AnsiString)DATA_PATH + Now().FormatString("yyyymmdd") + "\\";// + lblTitle->Caption + "\\";
	ForceDirectories((AnsiString)dir);

	//filename =  dir + editModelName->Text + "-" + tray.trayid +  "-" + Now().FormatString("yymmddhhnnss") + ".csv";
    filename =  dir + editModelName->Text + "-" + tray.trayid +  "-" + Now().FormatString("yymmddhhnn") + ".csv";

	if(FileExists(filename)){
		DeleteFile(filename);
	}

	file_handle = FileCreate(filename);
	FileSeek(file_handle, 0, 0);

	AnsiString file;
	file = "Tray ID," + tray.trayid + "\n";
    file = file + "ARRIVE TIME," + m_dateTime.FormatString("yyyy/mm/dd hh:nn:ss") + "\r\n";
	file = file + "FINISH TIME," + Now().FormatString("yyyy/mm/dd hh:nn:ss") + "\r\n";
	file = file + "IR Min.," + FormatFloat("0.0", config.ir_min) + ",IR Max.," + FormatFloat("0.0", config.ir_max) + "\n";
	if(config.average_use == true)
		file = file + "OCV Min., 100, OCV Max.,4200\n";
	else
		file = file + "OCV Min.," + FormatFloat("0.0", config.ocv_min) + ",OCV Max.," + FormatFloat("0.0", config.ocv_max) + "\n";
	file = file + "IR Avg.," + tray.ir_avg + ",IR Range," + config.ir_range + ",IR Sigma," + tray.ir_sigma + "\r\n";
	file = file + "OCV Avg.," + tray.ocv_avg + ",OCV Range," + config.ocv_range + ",OCV Sigma," + tray.ocv_sigma + "\r\n";
	file = file + "CH,CELL,CELL_ID,IR,OCV,RESULT\n";

	for(int i=0; i<MAXCHANNEL; ++i){
		ch = IntToStr(i+1);

		cell_id = tray.cell_serial[i];
        //cell_id = m_sCell_Serial[i];
		ir = FormatFloat("0.00", tray.after_value[i]);
		ocv = FormatFloat("0.0", tray.ocv_value[i]);

		if(tray.cell[i] == 1)
		{
			if(retest.cell[i] == 0) ok_ng = "OK";
			else if(retest.cell[i] == 2) ok_ng = "IR SPEC NG";
            else if(retest.cell[i] == 5) ok_ng = "IR Avg. NG";
			else if(retest.cell[i] == 3) ok_ng = "OCV SPEC NG";
            else if(retest.cell[i] == 6) ok_ng = "OCV Avg. NG";
            else if(retest.cell[i] == 4) ok_ng = "Contact NG";

			cell = "O";
		}
		else if(tray.cell[i] == 0)
		{
			if(panel[i]->Color == clCellError) ok_ng = "NG(No Cell)";
			else ok_ng = "No Cell";

			cell = "X";
		}

		file = file + ch + "," + cell + "," + cell_id + ", " + ir + "," + ocv + "," + ok_ng +"\n";
	}
	FileWrite(file_handle, file.c_str(), file.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::WriteOKNG()
{
	int file_handle;
	AnsiString filename;
	AnsiString dir;
	AnsiString ok_ng;

	dir = (AnsiString)DATA_PATH + Now().FormatString("yyyymmdd") + "\\";// + lblTitle->Caption + "\\";
	ForceDirectories((AnsiString)dir);

	filename =  dir + tray.trayid +  "-" + Now().FormatString("yymmddhhnnss") + "-OKNG.csv";

	if(FileExists(filename)){
		DeleteFile(filename);
	}

	file_handle = FileCreate(filename);
	FileSeek(file_handle, 0, 0);

	AnsiString file;
	file = "TRAY ID," + tray.trayid + "\r\n";
	file += "CH,OK/NG\r\n";

	for(int i = 0; i < MAXCHANNEL; ++i)
	{
		if((tray.cell[i] == 1) && retest.cell[i] == '0') ok_ng = "OK";
		else ok_ng = "NG";
		file = file + IntToStr(i+1) + "," + ok_ng + "\r\n";
	}

	FileWrite(file_handle, file.c_str(), file.Length());
	FileClose(file_handle);
}
//---------------------------------------------------------------------------

void __fastcall TTotalForm::ErrorLog()
{
	AnsiString str, dir;
	int file_handle;

	dir = (AnsiString)LOG_PATH + Now().FormatString("yyyymmdd") + "\\";
	ForceDirectories((AnsiString)dir);

	str = dir + "ERROR" + FormatFloat("000", this->Tag+1) + "_" + Now().FormatString("yymmdd-hh") + ".log";

	if(FileExists(str))
		file_handle = FileOpen(str, fmOpenWrite);
	else{
		file_handle = FileCreate(str);
	}

	FileSeek(file_handle, 0, 2);

	str = Now().FormatString("yyyy-mm-dd hh:nn:ss ") + error1->Caption + ", " + error3->Caption + ", " + error4->Caption + "\n";
	FileWrite(file_handle, str.c_str(), str.Length());

	FileClose(file_handle);
}
//---------------------------------------------------------------------------
// 재측정 정보 읽고 쓰기
void __fastcall TTotalForm::ReadPreChargerOKNG(AnsiString trayid)
{
	AnsiString dir = "C:\\PreCharge\\Data\\";// + lblTitle->Caption + "\\";
	AnsiString filename = dir + tray.trayid + "-OKNG.csv";
	AnsiString str;
	int file_handle, file_len;
	char *txt;

	if(FileExists(filename))
		file_handle = FileOpen(filename, fmOpenRead);

	file_len = FileSeek(file_handle, 0, 2);
	FileSeek(file_handle, 0, 0);

	txt = new char[file_len+1];
	FileRead(file_handle, txt, file_len);
	FileClose(file_handle);

	// ir ocv value processing
	str = txt;
	delete []txt;

	AnsiString tempStr, tempStr1;

	str.Delete(1, str.Pos("\n"));  										// 첫째줄 tray id 삭제

	for(int chCount = 0; chCount < MAXCHANNEL; chCount++){
		tempStr1 = str.SubString(1, str.Pos("\n"));
		str.Delete(1, tempStr1.Pos("\n"));                              // 읽은 줄 변수(tempStr1)에 넣고 삭제
		tempStr1.Delete(1, tempStr1.Pos(","));       					// 채널 번호 삭제

		tempStr = tempStr1.SubString(1, tempStr1.Pos("\n") - 1);       // OK/NG 값 - tempStr
		precharger_okng[chCount] = tempStr.ToInt();
	}
}
//---------------------------------------------------------------------------
void __fastcall TTotalForm::ReadCaliboffset()                         //20171202 개별보정을 위해 추가
{
	TIniFile *ini;
	ini = new TIniFile((AnsiString)BIN_PATH + "Caliboffset_" + IntToStr(this->Tag) + ".cali");

	for(int index=0; index<MAXCHANNEL; ++index){     							//20171202 개별보정을 위해 추가
		stage.ir_offset[index] = ini->ReadFloat("IR OFFSET", IntToStr(index+1), 0.0);
	}

	delete ini;
}
//---------------------------------------------------------------------------
