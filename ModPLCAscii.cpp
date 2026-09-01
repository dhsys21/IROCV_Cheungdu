//---------------------------------------------------------------------------


#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma classgroup "Vcl.Controls.TControl"
#pragma resource "*.dfm"
TMod_PLC *Mod_PLC;
//---------------------------------------------------------------------------
__fastcall TMod_PLCAscii::TMod_PLCAscii(TComponent* Owner)
	: TDataModule(Owner)
{
    //* PLC Data Init
	memset(plc_Interface_Data, 0, sizeof(unsigned char) * PLC_D_INTERFACE_LEN * 2);
	//* PC Data Init
	memset(pc_Interface_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_LEN * 2);
    memset(pc_Interface_Volt_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_VOLTAGE_LEN * 2);
	memset(pc_Interface_Curr_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_CURRENT_LEN * 2);

	PLC_Write_Result = false; //voltage, current 값은 필요 시에만 쓰기를 한다.
}
//---------------------------------------------------------------------------
//	접속 & 해제
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::Connect(AnsiString ip, int port1, int port2)
{
	try
	{
		bClose = false;

		ClientSocket_PLC->Address = ip;
		ClientSocket_PLC->Port = port1;
		ClientSocket_PLC->Open();

		ClientSocket_PC->Address = ip;
		ClientSocket_PC->Port = port2;
		ClientSocket_PC->Open();
	}
	catch(...)
	{
		ShowMessage("PLC -> PC : 통신 설정 실패.");
	}
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::DisConnect()
{
	bClose = true;
	Timer_PLC_WriteMsg->Enabled = false;
	Timer_PC_WriteMsg->Enabled = false;
	ClientSocket_PLC->Close();
	ClientSocket_PC->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLCAscii::PLC_Initialization()
{
	plc_Read = "";
	plc_ReadCount = 0;
	plc_ReadFlag = true;

	Timer_PLC_WriteMsg->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::PC_Initialization()
{
	pc_Read = "";
	pc_ReadFlag = true;
	pc_ReadCount = 0;

	Timer_PC_WriteMsg->Enabled = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// PC 영역 접속및 데이터 읽어오기 시작
void __fastcall TMod_PLCAscii::ClientSocket_PCConnect(TObject *Sender, TCustomWinSocket *Socket)
{
    PC_Initialization();
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PCDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
    if(bClose) bClose = false;
	else Timer_PC_AutoConnect->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
    ErrorCode = 0;
	Socket->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PCRead(TObject *Sender, TCustomWinSocket *Socket)
{
    if (Socket->ReceiveLength() <= 0) return;
	pc_Read += Socket->ReceiveText();

	while(pc_Read.Pos("D000"))
	{
		int index = pc_Read.Pos("D000");
		if (index > 1) pc_Read.Delete(1, index - 1); // 헤더 앞 불필요 데이터 제거

		// 쓰기 응답은 데이터부 없이 헤더만 옴 (22자리)
		if (pc_Read.Length() >= 22)
		{
			// 정상 종료 코드("0000") 확인
			if(pc_Read.SubString(19, 4) == "0000")
			{
				pc_ReadFlag = true;
				pc_ReadCount = 0;
			}
			pc_Read.Delete(1, 22); // 처리된 응답 패킷 제거
		}
		else
		{
			break; // 패킷이 완전히 수신되지 않음
		}
	}
}
// PC 영역 접속및 데이터 읽어오기 끝
//---------------------------------------------------------------------------
// PLC 영역 접속및 데이터 읽어오기 시작
void __fastcall TMod_PLCAscii::ClientSocket_PLCConnect(TObject *Sender, TCustomWinSocket *Socket)
{
    PLC_Initialization();
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PLCDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
    if(bClose) bClose = false;
	else Timer_PLC_AutoConnect->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PLCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
    ErrorCode = 0;
	Socket->Close();
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::ClientSocket_PLCRead(TObject *Sender, TCustomWinSocket *Socket)
{
    if (Socket->ReceiveLength() <= 0) return;
	plc_Read += Socket->ReceiveText();
    BaseForm->Memo1->Lines->Add(plc_Read);

	// 응답 프레임 시작("D000") 위치 확인
	int startPos = plc_Read.Pos("D000");
	if (startPos == 0) return; // 아직 헤더가 없음
	if (startPos > 1) plc_Read.Delete(1, startPos - 1); // 헤더 앞의 불필요한 데이터 삭제

	// 응답 프레임 길이 확인
	// 헤더(18) + 종료코드(4) = 22자리 최소 길이
	if (plc_Read.Length() < 22) return;

	// 정상 종료 코드("0000") 확인
	if (plc_Read.SubString(19, 4) == "0000")
	{
		// 응답 데이터 길이 (ASCII 문자 개수)
		int dataLen = StrToInt("0x" + plc_Read.SubString(15, 4));
		int totalLen = 22 + dataLen;

		if (plc_Read.Length() >= totalLen)
		{
			AnsiString data_part = plc_Read.SubString(23, dataLen);

			// 데이터 파싱 및 저장
			int num = 1;
			for(int i = 0; i < PLC_D_INTERFACE_LEN; i++)
			{
				if (num + 3 <= data_part.Length())
				{
					// 4글자(1워드)씩 잘라서 16진수 변환 후 버퍼에 저장
					AnsiString word_hex = data_part.SubString(num, 4);
					int word_val = StrToInt("0x" + word_hex);
					plc_Interface_Data[i][0] = word_val & 0xFF; // LSB
					plc_Interface_Data[i][1] = (word_val >> 8) & 0xFF; // MSB
					num += 4;
				} else break;
			}

			plc_Read.Delete(1, totalLen); // 처리된 패킷 삭제
		}
	}
	else // 에러 응답 수신
	{
		plc_Read = ""; // 버퍼 비우기
	}

	plc_ReadFlag = true;
	plc_ReadCount = 0;
}
// PLC 영역 접속및 데이터 읽어오기 끝
//---------------------------------------------------------------------------
// PLC 접속 타이머 시작
void __fastcall TMod_PLCAscii::Timer_PC_AutoConnectTimer(TObject *Sender)
{
    ClientSocket_PC->Active = true;
	Timer_PC_AutoConnect->Enabled = false;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::Timer_PLC_AutoConnectTimer(TObject *Sender)
{
    ClientSocket_PLC->Active = true;
	Timer_PLC_AutoConnect->Enabled = false;
}
// PLC 접속 타이머 끝
//---------------------------------------------------------------------------
// PC 영역 데이터 요청 및 쓰기
AnsiString __fastcall TMod_PLCAscii::BuildAsciiReadCommand(int address, int devCode, int devLen)
{
	AnsiString command;
	// 서브헤더, PC번호, 요구대상 네트워크/국번호, IO번호 등
	command = "5000"; // 요청 프레임
	command += "00";  // 네트워크 번호
	command += "FF";  // PLC 번호
	command += "03FF"; // 요구대상 I/O 번호
	command += "00";   // 요구대상 국번호

	// 요구 데이터 길이 (CPU 감시타이머부터 끝까지의 문자열 길이)
	// 길이: 4(타이머) + 4(커맨드) + 4(서브커맨드) + 2(디바이스코드) + 6(시작주소) + 4(디바이스점수) = 24
	command += "0018"; // 24를 16진수 문자열로 표현

	// CPU 감시 타이머
	command += "0010"; // 250ms * 16 = 4000ms

	// 커맨드 (워드 단위 일괄 읽기)
	command += "0401"; //

	// 서브커맨드 (워드)
	command += "0000";

	// 디바이스 코드 및 시작 주소
	command += "D*"; // 데이터 레지스터(D)를 16비트 워드로 지정
	command += AnsiString().sprintf("%06d", address); // 시작 주소 6자리

	// 디바이스 점수 (읽을 워드 개수)
	command += AnsiString().sprintf("%04X", devLen); // 길이를 16진수 4자리로

	return command;
}
void __fastcall TMod_PLCAscii::Timer_PC_WriteMsgTimer(TObject *Sender)
{
    TTimer *tmr;
	tmr = (TTimer*)Sender;
	if(ClientSocket_PC->Active)
	{
		if(pc_ReadFlag)
		{
			//* Heart Beat
			if(BaseForm->nForm[0]->Client->Active)
			{
				bool flag = GetData(pc_Interface_Data, PC_D_HEART_BEAT, 0);
				SetDouble(pc_Interface_Data, PC_D_HEART_BEAT, (int)!flag);
			}

			//* General Data (41000 번지 영역) 쓰기
			AnsiString cmd_general = BuildAsciiWriteCommand(PC_D_INTERFACE_START_DEV_NUM, DEVCODE_D, PC_D_INTERFACE_LEN, pc_Interface_Data);
			ClientSocket_PC->Socket->SendText(cmd_general);
			Sleep(100); // PLC 처리 시간 대기

			//* Voltage, Current Data 쓰기
			if(PLC_Write_Result == true && GetPlcValue(PLC_D_PRE_COMPLETE) == 0){
				// Voltage Data (41070 번지 영역)
				AnsiString cmd_volt = BuildAsciiWriteCommand(PC_D_INTERFACE_VOLTAGE, DEVCODE_D, PC_D_INTERFACE_VOLTAGE_LEN, pc_Interface_Volt_Data);
				ClientSocket_PC->Socket->SendText(cmd_volt);
				Sleep(100);

				// Current Data (42000 번지 영역)
				AnsiString cmd_curr = BuildAsciiWriteCommand(PC_D_INTERFACE_CURRENT, DEVCODE_D, PC_D_INTERFACE_CURRENT_LEN, pc_Interface_Curr_Data);
				ClientSocket_PC->Socket->SendText(cmd_curr);
			}
			else if(GetPlcValue(PLC_D_PRE_COMPLETE) == 1){
				PLC_Write_Result = false;
				SetValue(PC_D_PRE_COMPLETE, 0);
			}

			pc_ReadFlag = false;
			pc_ReadCount = 0;
		}
		else if(pc_ReadCount > 10)
		{
			ClientSocket_PC->Close();
		}
		pc_ReadCount++;
	}
	else
	{
		ClientSocket_PC->Close();
	}
}
//---------------------------------------------------------------------------
// PLC 영역 데이터 요청
// ASCII 쓰기 명령 생성
AnsiString __fastcall TMod_PLCAscii::BuildAsciiWriteCommand(int address, int devCode, int devLen, unsigned char (*data)[2])
{
	AnsiString command;
	// 서브헤더, PC번호, 요구대상 네트워크/국번호, IO번호 등
	command = "5000"; // 요청 프레임
	command += "00";  // 네트워크 번호
	command += "FF";  // PLC 번호
	command += "03FF"; // 요구대상 I/O 번호
	command += "00";   // 요구대상 국번호

	// 요구 데이터 길이 (CPU 감시타이머 ~ 끝까지 길이)
	// 기본 길이 24 + 데이터 길이 (워드당 4글자)
	int dataLength = 24 + (devLen * 4);
	command += AnsiString().sprintf("%04X", dataLength);

	// CPU 감시 타이머
	command += "0010"; //

	// 커맨드 (워드 단위 일괄 쓰기)
	command += "1401"; //

	// 서브커맨드 (워드)
	command += "0000";

	// 디바이스 코드 및 시작 주소
	command += "D*";
	command += AnsiString().sprintf("%06d", address);

	// 디바이스 점수 (쓸 워드 개수)
	command += AnsiString().sprintf("%04X", devLen);

	// 쓸 데이터
	for (int i = 0; i < devLen; i++)
	{
		// PLC는 Little Endian이므로 저위바이트(LSB) 먼저
		command += AnsiString().sprintf("%02X%02X", data[i][1], data[i][0]); // MSB, LSB 순서로 전송
	}

	return command;
}
void __fastcall TMod_PLCAscii::Timer_PLC_WriteMsgTimer(TObject *Sender)
{
    if(ClientSocket_PLC->Active)
	{
		if(plc_ReadFlag)
		{
			// ASCII 읽기 명령 생성
			AnsiString command = BuildAsciiReadCommand(PLC_D_INTERFACE_START_DEV_NUM, DEVCODE_D, PLC_D_INTERFACE_LEN);

			// ASCII 명령 전송
			ClientSocket_PLC->Socket->SendText(command);
			plc_ReadFlag = false;
			plc_ReadCount = 0;
		}
		else if(plc_ReadCount > 10) // 3초동안 응답 확인
		{
			ClientSocket_PLC->Close();
		}
		plc_ReadCount++;
	}
	else
	{
		ClientSocket_PLC->Close();
	}
}
//---------------------------------------------------------------------------
//	PC 영역 변경 (PLC에 변경된 Header 쓰기)
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::PC_DataChange(int subCommand, int address, int devCode, int devLen)
{
	pc_Data.SubCommand[0] = subCommand;
	pc_Data.SubCommand[1] = 0x00;

	pc_Data.ReqDataLen[0] = (0x0c + (devLen * 2)) % 256;
	pc_Data.ReqDataLen[1] = (0x0c + (devLen * 2)) / 256;;

	pc_Data.StartDevNum[0] = address % 256;
	pc_Data.StartDevNum[1] = (address / 256) % 256;
	pc_Data.StartDevNum[2] = address / (256 * 256);
	pc_Data.DevCode = devCode;

	pc_Data.DevLen[0] = devLen % 256;
	pc_Data.DevLen[1] = devLen / 256;
}
//---------------------------------------------------------------------------
//	PLC 영역 변경 (PLC에 변경된 Header 쓰기)
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::PLC_DataChange(int subCommand, int address, int devCode, int devLen)
{
	plc_Data.SubCommand[0] = subCommand;
	plc_Data.SubCommand[1] = 0x00;

	plc_Data.StartDevNum[0] = address % 256;
	plc_Data.StartDevNum[1] = (address / 256) % 256;
	plc_Data.StartDevNum[2] = address / (256 * 256);

	plc_Data.DevCode = devCode;

	plc_Data.DevLen[0] = devLen % 256;
	plc_Data.DevLen[1] = devLen / 256;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLCAscii::PLC_Recv_Interface(int nTag)
{
	int num = 0;
	plc_Interface = plc_Read.SubString(23, PLC_D_INTERFACE_LEN);

	for(int i = 0; i < PLC_D_INTERFACE_LEN; i++)
	{
		plc_Interface_Data[i][0] = StrToInt("0x" + plc_Read.SubString(23 + num, 2));
		plc_Interface_Data[i][1] = StrToInt("0x" + plc_Read.SubString(23 + num + 2, 2));
		num += 4;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	데이터 쓰기 & 읽기
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetData(unsigned char (*data)[2], int column, int num, bool flag)
{
	int num1 = num / 8;
	int num2 = num % 8;

	if(flag) data[column][num1] |= (1 << num2);
	else data[column][num1] &= ~(1 << num2);
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetDouble(unsigned char (*data)[2], int column, double value)
{
//	int temp = value;
//
//	data[column][1] = temp / 256;
//	data[column][0] = temp % 256;
    short temp = static_cast<short>(value); // signed 16-bit 정수로 형변환

    data[column][0] = temp & 0xFF;         // LSB (저장 순서에 따라 다름)
    data[column][1] = (temp >> 8) & 0xFF;  // MSB
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetString(unsigned char (*data)[2], int column, AnsiString msg)
{
	if(msg.Length() % 2) msg += (char)0x0;

	int num = 0;
	for(int i = 0; i < msg.Length() / 2; i++)
	{
		data[column + i][0] = msg[1 + num];
		data[column + i][1] = msg[2 + num];
		num += 2;
	}
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC2::GetData(unsigned char (*data)[2], int column, int num)
{
	bool value = false;
	int num1 = num / 8;
	int num2 = num % 8;

	value = data[column][num1] & (1 << num2);

	return value;
}
//---------------------------------------------------------------------------
double __fastcall TMod_PLC2::GetDouble(unsigned char (*data)[2], int column)
{
	double value = -1;

	value = (data[column][1] * 256) + data[column][0];

	return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC2::GetString(unsigned char (*data)[2], int column, int count)
{
	AnsiString m_GetStringValue = "";
	for(int i = 0; i < count; i++)
	{
		m_GetStringValue += (char)data[column + i][0];
		m_GetStringValue += (char)data[column + i][1];
	}

	return m_GetStringValue.Trim();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	데이터 쓰기 & 읽기
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// PLC 명령어
//---------------------------------------------------------------------------
double __fastcall TMod_PLC2::GetPlcValue(int plc_address)
{
    double value = GetDouble(plc_Interface_Data, plc_address);
    return value;
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC2::GetPlcData(int plc_address, int bit_num)
{
    int value = GetData(plc_Interface_Data, plc_address, bit_num);
    return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC2::GetPlcValue(int plc_address, int size)
{
    AnsiString value = GetString(plc_Interface_Data, plc_address, size);
    return value;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetValue(int pc_address, int value)
{
    SetDouble(pc_Interface_Data,  pc_address, value);
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetVoltValue(int pc_address, int index, int value)
{
	SetDouble(pc_Interface_Volt_Data, pc_address + (index * 2), static_cast<int16_t>(value));
	SetDouble(pc_Interface_Volt_Data, pc_address + (index * 2) + 1, static_cast<int16_t>(value >> 16));
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC2::SetCurrValue(int pc_address, int index, int value)
{
    SetDouble(pc_Interface_Curr_Data, pc_address + (index * 2), static_cast<int16_t>(value));
	SetDouble(pc_Interface_Curr_Data, pc_address + (index * 2) + 1, static_cast<int16_t>(value >> 16));
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC2::GetVoltValue(int pc_address, int index)
{
    int lowWord = GetDouble(pc_Interface_Volt_Data, pc_address + (index * 2));
    int highWord = GetDouble(pc_Interface_Volt_Data, pc_address + (index * 2) + 1);
    return (highWord << 16) | lowWord;
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC2::GetCurrValue(int pc_address, int index)
{
    int lowWord = GetDouble(pc_Interface_Curr_Data, pc_address + (index * 2));
    int highWord = GetDouble(pc_Interface_Curr_Data, pc_address + (index * 2) + 1);
    return (highWord << 16) | lowWord;
}
//---------------------------------------------------------------------------
// PLC 명령어
//---------------------------------------------------------------------------
