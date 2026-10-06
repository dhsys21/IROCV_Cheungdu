// [설정·파일·로그] INI/채널 매핑, 결과 CSV, 누적 정보, 통신/PLC 로그.
// 전체 구조 및 오류 추적 위치: CODE_STRUCTURE.md

#include <vcl.h>
#pragma hdrstop

#include "FormTotal.h"
#include "RVMO_main.h"
#include "FormCalibration.h"

void __fastcall TTotalForm::WriteSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);
	// 0=재개폐 없음. 기존 REMEASURE 키를 유지하며 음수는 0으로 정규화한다.
    int probeCount = editProbeRemeasureCount->Text.ToIntDef(0);
    if(probeCount < 0) probeCount = 0;
    // 닫힘 상태의 재측정 허용 NG 개수: 이하 조건, 0=생략. 채널 수 범위로 제한.
    int maxNgCount = editClosedProbeRemeasureMaxNgCount->Text.ToIntDef(
        DEFAULT_CLOSED_PROBE_REMEASURE_MAX_NG_COUNT);
    if(maxNgCount < 0) maxNgCount = 0;
    if(maxNgCount > MAXCHANNEL) maxNgCount = MAXCHANNEL;
    ini->WriteInteger("MAIN", "CLOSED_PROBE_REMEASURE_MAX_NG_COUNT", maxNgCount);
    ini->WriteInteger("MAIN", "REMEASURE", probeCount);
    editClosedProbeRemeasureMaxNgCount->Text = maxNgCount;
    editProbeRemeasureCount->Text = probeCount;
    ini->DeleteKey("MAIN", "AUTO_CHECK");
    ini->DeleteKey("MAIN", "REM_BYPASS");
    ini->DeleteKey("MAIN", "USE_AVERAGE");
    ini->DeleteKey("MAIN", "IR_RANGE");
    ini->DeleteKey("MAIN", "OCV_RANGE");
    // [CELL SERIAL 공통] 미체크=TRAY IN 보관(기존), 체크=상시 수신/결과 직전 재확인.
    // 실제 적용은 ReadSystemInfo 및 다음 InitializeTrayData에서 한다. 현재 트레이 모드는 유지한다.
    ini->WriteBool("CELL_SERIAL", "CONTINUOUS_READ", chkCellSerialContinuousRead->Checked);

	ini->WriteString("IROCV_PLC", "IP", editPLCIPAddress->Text);
	ini->WriteString("IROCV_PLC", "PORT1", editPLCPortPC->Text);
	ini->WriteString("IROCV_PLC", "PORT2", editPLCPortPLC->Text);

	ini->WriteString("IROCV", "IP", editIROCVIPAddress->Text);
	ini->WriteString("IROCV", "PORT", editIROCVPort->Text);

    ini->WriteString("NG_ALARM_COUNT", "COUNT", editNgAlarmCount->Text);
	ini->WriteInteger("MAIN", "REMEASURE_ALARM_COUNT", editRemeasureAlarmCount->Text.ToIntDef(3));
	config.probeRemeasureCount = probeCount;
    config.closedProbeRemeasureMaxNgCount = maxNgCount;
	config.remeasure_alarm_cnt = editRemeasureAlarmCount->Text.ToIntDef(3);
    RemeasureForm->pcolor2->Caption = config.remeasure_alarm_cnt;

    ini->WriteString("CELLINFO", "MODELNAME", editModelName->Text);
    ini->WriteString("PASSWORD", "PWD", editPwd->Text);

    //* 측정속도
    AnsiString speedmode = "2";
    if(rbSpeedSlow->Checked) speedmode = "0";
    else if(rbSpeedMed->Checked) speedmode = "1";
    else if(rbSpeedFast->Checked) speedmode = "2";
    ini->WriteString("MAIN", "SPEED_MODE", speedmode);

	//* 2022 11 07

    // 화면 입력을 한 번만 해석한다. 파일/메모리/PLC가 같은 규격을 사용한다.
    config.ir_min = BaseForm->StringToDouble(irEdit1->Text, DEFAULT_IR_MIN);
    config.ir_max = BaseForm->StringToDouble(irEdit2->Text, DEFAULT_IR_MAX);
    config.ocv_min = BaseForm->StringToDouble(ocvEdit1->Text, DEFAULT_OCV_MIN);
    config.ocv_max = BaseForm->StringToDouble(ocvEdit2->Text, DEFAULT_OCV_MAX);
    ini->WriteFloat("MAIN", "IR1", config.ir_min);
    ini->WriteFloat("MAIN", "IR2", config.ir_max);
    ini->WriteFloat("MAIN", "OCV1", config.ocv_min);
    ini->WriteFloat("MAIN", "OCV2", config.ocv_max);

	delete ini;
}

void __fastcall TTotalForm::ReadSystemInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);
    // [CELL SERIAL 공통] 기존 INI에 키가 없으면 기존 TRAY IN 수신 방식으로 동작한다.
    config.cell_serial_continuous_read = ini->ReadBool("CELL_SERIAL", "CONTINUOUS_READ", false);
    chkCellSerialContinuousRead->Checked = config.cell_serial_continuous_read;
    if(autoInspection.GetStep() == STEP_WAIT_TRAY_IN && !IsWaitingForResultSave() && (!tray.ams || tray.amf))
        ApplyCellSerialReadMode();
    // 기존 파일에 새 키가 없으면 49개 이하를 유지. 0은 닫힘 재측정만 생략한다.
    config.closedProbeRemeasureMaxNgCount = ini->ReadInteger(
        "MAIN", "CLOSED_PROBE_REMEASURE_MAX_NG_COUNT", DEFAULT_CLOSED_PROBE_REMEASURE_MAX_NG_COUNT);
    if(config.closedProbeRemeasureMaxNgCount < 0) config.closedProbeRemeasureMaxNgCount = 0;
    if(config.closedProbeRemeasureMaxNgCount > MAXCHANNEL) config.closedProbeRemeasureMaxNgCount = MAXCHANNEL;
    // 기존 REMEASURE 키는 추가 재개폐 횟수 전용. 닫힘 NG 개수 설정과 혼용하지 않는다.
	config.probeRemeasureCount = ini->ReadInteger("MAIN", "REMEASURE", 0);
    if(config.probeRemeasureCount < 0) config.probeRemeasureCount = 0;
    // 이전 버전의 Auto Remeasure 미체크는 0회로 이관. 새 설정은 횟수 하나만 사용.
    if(ini->ValueExists("MAIN", "AUTO_CHECK") && !ini->ReadBool("MAIN", "AUTO_CHECK", false))
        config.probeRemeasureCount = 0;
    config.remeasure_alarm_cnt = ini->ReadInteger("MAIN", "REMEASURE_ALARM_COUNT", 5);

    //* 측정속도
    AnsiString speedmode = "2";
    speedmode = ini->ReadString("MAIN", "SPEED_MODE", "2");
    if(speedmode == "0") rbSpeedSlow->Checked = true;
    else if(speedmode == "1") rbSpeedMed->Checked = true;
    else if(speedmode == "2") rbSpeedFast->Checked = true;

    editNgAlarmCount->Text = ini->ReadString("NG_ALARM_COUNT", "COUNT", "20");

	config.ir_min = ini->ReadFloat("MAIN", "IR1", DEFAULT_IR_MIN);
	config.ir_max = ini->ReadFloat("MAIN", "IR2", DEFAULT_IR_MAX);

	irEdit1->Text = config.ir_min;
	irEdit2->Text = config.ir_max;

    pnlIRSpec->Caption = UiText("IR : " + FormatFloat("0.0", config.ir_min)  + " ~ " + FormatFloat("0.0", config.ir_max));

	config.ocv_min = ini->ReadFloat("MAIN", "OCV1", DEFAULT_OCV_MIN);
	config.ocv_max = ini->ReadFloat("MAIN", "OCV2", DEFAULT_OCV_MAX);

	ocvEdit1->Text = config.ocv_min;
	ocvEdit2->Text = config.ocv_max;

    pnlOCVSpec->Caption = UiText("OCV : " + FormatFloat("0.0", config.ocv_min) + " ~ " + FormatFloat("0.0", config.ocv_max));

	editPLCIPAddress->Text = ini->ReadString("IROCV_PLC", "IP", "17.91.80.220");
	editPLCPortPC->Text = ini->ReadString("IROCV_PLC", "PORT1", "5007");
	editPLCPortPLC->Text = ini->ReadString("IROCV_PLC", "PORT2", "5008");

    PLC_IPADDRESS = editPLCIPAddress->Text;
	PLC_PCPORT = editPLCPortPC->Text.ToIntDef(5007);
	PLC_PLCPORT = editPLCPortPLC->Text.ToIntDef(5008);

	editIROCVIPAddress->Text = ini->ReadString("IROCV", "IP", "192.168.250.202");
	editIROCVPort->Text = ini->ReadString("IROCV", "PORT", "45000");

    // IP/Port는 표시/메모리만 읽고, 저장/연결 버튼에서 실제 소켓에 적용한다.

	editModelName->Text = ini->ReadString("CELLINFO", "MODELNAME", "20PQ");
    editPwd->Text = ini->ReadString("PASSWORD", "PWD", "Eveml@123");
    config.pwd = editPwd->Text;
    editClosedProbeRemeasureMaxNgCount->Text = config.closedProbeRemeasureMaxNgCount;
	editProbeRemeasureCount->Text = config.probeRemeasureCount;
	editRemeasureAlarmCount->Text = config.remeasure_alarm_cnt;
	RemeasureForm->pcolor2->Caption = config.remeasure_alarm_cnt;

	delete ini;
}

void __fastcall TTotalForm::ReadCellInfo()
{
	TIniFile *ini;

	AnsiString file;
	file = (AnsiString)BIN_PATH + "SystemInfo_"+ IntToStr(this->Tag) + ".inf";

	ini = new TIniFile(file);

	tray.cell_model = ini->ReadString("CELL_INFO", "CELL_MODEL", "-");
	tray.lot_number = ini->ReadString("CELL_INFO", "LOT_NUMBER", "-");

	delete ini;
}

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

    UpdateRemeasureAlarm(nRemeasureAlarmCount);

	retest_info = "";
	acc_init = 	 ini->ReadString(title, "ACCMULATE_DAY", Now().FormatString("yyyy. m. d. hh:nn"));
	acc_cnt = ini->ReadInteger(title, "ACC_CNT", 0);

	delete ini;
}

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
	UpdateRemeasureAlarm(nRemeasureAlarmCount);

    ini->WriteInteger(title, "REMEASURE_ALARM_COUNT", editRemeasureAlarmCount->Text.ToIntDef(3));
	ini->WriteString(title, "ACCMULATE", retest_info);
    ini->WriteString(title, "TOTAL_USE", strTotalUse);
	ini->WriteString(title, "ACCMULATE_DAY", acc_init);
	ini->WriteInteger(title, "ACC_CNT", acc_cnt);

    ini->WriteInteger(title, "TOTAL_TRAY", acc_totaltray);
    ini->WriteInteger(title, "FINAL_NG", acc_finalng);


	delete ini;
}

void __fastcall TTotalForm::UpdateRemeasureAlarm(int remeasure_alarm_count)
{
	if(remeasure_alarm_count > 0) {
		Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_NG_ALARM, 1);
		btnRemeasureInfo->Color = clRed;
	}
	else{
        Mod_PLC->SetDouble(Mod_PLC->pc_Interface_Data,  PC_D_IROCV_NG_ALARM, 0);
		btnRemeasureInfo->Color = clWhite;
    }
}

void __fastcall TTotalForm::WriteCommLog(AnsiString Type, AnsiString Msg)
{
    AppendOperationLog(Type, Msg);
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

void __fastcall TTotalForm::WritePlcLog(AnsiString Type, AnsiString Msg)
{
    AppendOperationLog(Type, Msg);
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

bool __fastcall TTotalForm::WriteResultFile()
{
	int file_handle = -1;
    AnsiString filename;
    try
    {
	AnsiString dir;
	AnsiString cell, cell_id, ir, ocv, ch, ok_ng;

	dir = (AnsiString)DATA_PATH + Now().FormatString("yyyymmdd") + "\\";// + lblTitle->Caption + "\\";
	ForceDirectories((AnsiString)dir);
    if(resultFileName.IsEmpty())
        resultFileName = dir + editModelName->Text + "-" + tray.trayid + "-" + Now().FormatString("yymmddhhnn") + ".csv";
    filename = resultFileName + ".tmp";


	file_handle = FileCreate(filename);
	if(file_handle < 0) return false;

	AnsiString file;
	file = "Tray ID," + tray.trayid + "\n";
    file = file + "ARRIVE TIME," + m_dateTime.FormatString("yyyy/mm/dd hh:nn:ss") + "\r\n";
	file = file + "FINISH TIME," + Now().FormatString("yyyy/mm/dd hh:nn:ss") + "\r\n";
	file = file + "IR Min.," + FormatFloat("0.0", config.ir_min) + ",IR Max.," + FormatFloat("0.0", config.ir_max) + "\n";
		file = file + "OCV Min.," + FormatFloat("0.0", config.ocv_min) + ",OCV Max.," + FormatFloat("0.0", config.ocv_max) + "\n";
	file = file + "CH,CELL,CELL_ID,IR,OCV,RESULT\n";

	for(int i=0; i<MAXCHANNEL; ++i){
		ch = IntToStr(i+1);

		cell_id = tray.cell_serial[i];
		ir = FormatFloat("0.00", tray.after_value[i]);
		ocv = FormatFloat("0.0", tray.ocv_value[i]);

		if(tray.cell[i] == 1)
		{
			if(retest.cell[i] == 0) ok_ng = "OK";
			else if(retest.cell[i] == 2) ok_ng = "IR SPEC NG";

			else if(retest.cell[i] == 3) ok_ng = "OCV SPEC NG";

            else if(retest.cell[i] == 4) ok_ng = "Contact NG";

			cell = "O";
		}
		else if(tray.cell[i] == 0)
		{
			if((irValueReceived[i] && tray.measure_result[i] == GO) ||
               (ocvValueReceived[i] && tray.ocv_value[i] > 1500)) ok_ng = "NG(No Cell)";
			else ok_ng = "No Cell";

			cell = "X";
		}

		file = file + ch + "," + cell + "," + cell_id + ", " + ir + "," + ocv + "," + ok_ng +"\n";
	}
    const int written = FileWrite(file_handle, file.c_str(), file.Length());
    FileClose(file_handle);
    file_handle = -1;
    if(written != file.Length()) { DeleteFile(filename); return false; }
    // 완성된 임시 파일만 최종 경로로 교체. 재측정/재시도에서도 기존 결과를 먼저 지우지 않는다.
    if(!MoveFileExA(filename.c_str(), resultFileName.c_str(),
        MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH))
    { DeleteFile(filename); return false; }
    return true;
    }
    catch(...)
    {
        if(file_handle >= 0) FileClose(file_handle);
        if(!filename.IsEmpty()) DeleteFile(filename);
        return false;
    }
}

void __fastcall TTotalForm::WriteErrorLog(AnsiString title, AnsiString detail1, AnsiString detail2)
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

    // Keep diagnostic text independent of translated operator captions.
	str = Now().FormatString("yyyy-mm-dd hh:nn:ss ") + title + ", " + detail1 + ", " + detail2 + "\n";
	FileWrite(file_handle, str.c_str(), str.Length());

	FileClose(file_handle);
}

void __fastcall TTotalForm::ReadCalibrationOffsets()                         //20171202 개별보정을 위해 추가
{
	TIniFile *ini;
	ini = new TIniFile((AnsiString)BIN_PATH + "Caliboffset_" + IntToStr(this->Tag) + ".cali");

	for(int index=0; index<MAXCHANNEL; ++index){     							//20171202 개별보정을 위해 추가
		stage.ir_offset[index] = ini->ReadFloat("IR OFFSET", IntToStr(index+1), 0.0);
	}

	delete ini;
}

//---------------------------------------------------------------------------
// mapping.csv에서 장비↔화면 채널 매핑을 읽고, 파일이 없으면 기본 매핑을 만든다.
void __fastcall TTotalForm::ReadChannelMapping()
{
	AnsiString str, FileName;
	int file_handle;

	FileName = (AnsiString)BIN_PATH + "mapping.csv";

	TStringList *data;
	data = new TStringList;

	if (FileExists(FileName)) {

		data->LoadFromFile(FileName);

		for (int i = 1; i <= MAXCHANNEL; ++i) {
			str = data->Strings[i];
			str.Delete(1, str.Pos(",")); // 채널
			chMap[i] = str.ToInt();
			chReverseMap[str.ToInt()] = i;
		}
	}
	else {
		data->Add("변경전, 변경후");
		for (int i = 1; i <= MAXCHANNEL; ++i) {
			chMap[i] = i;
            chReverseMap[i] = i;
			data->Add(IntToStr(i) + "," + IntToStr(i));
		}
		data->SaveToFile(FileName);

	}
	delete data;
}
