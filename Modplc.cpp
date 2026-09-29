//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RVMO_main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TMod_PLC *Mod_PLC;
//---------------------------------------------------------------------------
__fastcall TMod_PLC::TMod_PLC(TComponent* Owner)
	: TDataModule(Owner)
{
    // PLC
	plc_Data.SubHeader[0] = 0x50;
	plc_Data.SubHeader[1] = 0x00;
	plc_Data.NetNum = 0x03;
	plc_Data.PlcNum = 0x03;
	plc_Data.ReqIONum[0] = 0xff;
	plc_Data.ReqIONum[1] = 0x03;
	plc_Data.ReqOfficeNum = 0x00;
	plc_Data.ReqDataLen[0] = 0x0c;
	plc_Data.ReqDataLen[1] = 0x00;
	plc_Data.CpuTime[0] = 0x10;
	plc_Data.CpuTime[1] = 0x00;
	plc_Data.Command[0] = 0x01;
	plc_Data.Command[1] = 0x04;

	plc_index = PLC_INDEX_INTERFACE[0];

	// PC
	pc_Data.SubHeader[0] = 0x50;
	pc_Data.SubHeader[1] = 0x00;
	pc_Data.NetNum = 0x03;
	pc_Data.PlcNum = 0x03;
	pc_Data.ReqIONum[0] = 0xff;
	pc_Data.ReqIONum[1] = 0x03;
	pc_Data.ReqOfficeNum = 0x00;

	pc_Data.CpuTime[0] = 0x10;
	pc_Data.CpuTime[1] = 0x00;
	pc_Data.Command[0] = 0x01;
	pc_Data.Command[1] = 0x14;

	pc_index = PC_INDEX_INTERFACE;
	plc_Interface = "";
	bClose = false;

	//* PLC Data Init
	memset(plc_Interface_Data, 0, sizeof(unsigned char) * PLC_D_INTERFACE_LEN * 2);
    memset(plc_Interface_Cell_Serial, 0, sizeof(unsigned char) * PLC_D_CELL_SERIAL_LEN * 2);
    //* PC Data Init
	memset(pc_Interface_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_LEN1 * 2);
    memset(pc_Interface_Ir_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_IR_LEN * 2);
	memset(pc_Interface_Ocv_Data, 0, sizeof(unsigned char) * PC_D_INTERFACE_OCV_LEN * 2);
    resultSentParts = 0;
    cellSerialContinuousRead = false; // [CELL SERIAL 공통] 기존 TRAY IN 수신이 기본값.
    ResetCellSerialRead();
    currentWriteTask = nPCDATA;
}
//---------------------------------------------------------------------------
//	접속 & 해제
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::Connect(AnsiString ip, int port1, int port2)
{
    // 사용 중인 소켓의 주소/포트는 변경할 수 없다. 주소 변경 시 두 경로를 먼저 닫는다.
    const bool changed = ClientSocket_PLC->Address != ip || ClientSocket_PLC->Port != port1 ||
        ClientSocket_PC->Address != ip || ClientSocket_PC->Port != port2;
    if(changed) Disconnect();
    bClose = false;
    if(!ClientSocket_PLC->Active)
    {
        ClientSocket_PLC->Host = "";
        ClientSocket_PLC->Address = ip;
        ClientSocket_PLC->Port = port1;
        Timer_PLC_AutoConnectTimer(this);
    }
    if(!ClientSocket_PC->Active)
    {
        ClientSocket_PC->Host = "";
        ClientSocket_PC->Address = ip;
        ClientSocket_PC->Port = port2;
        Timer_PC_AutoConnectTimer(this);
    }
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::Disconnect()
{
    plcAutoMode.Invalidate();
    // bClose는 두 소켓의 Disconnect 이벤트 이후에도 유지한다. Connect에서만 해제한다.
    bClose = true;
    Timer_PLC_AutoConnect->Enabled = false;
    Timer_PC_AutoConnect->Enabled = false;
    Timer_PLC_WriteMsg->Enabled = false;
    Timer_PC_WriteMsg->Enabled = false;
    ClientSocket_PLC->Close();
    ClientSocket_PC->Close();
    ResetCellSerialRead();
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::InitializePlcCommunication()
{
    plcAutoMode.Invalidate();
	plc_Read = "";
	plc_ReadCount = 0;
	plc_ReadFlag = true;
    ResetCellSerialRead();

	Timer_PLC_WriteMsg->Enabled = true;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::ResetCellSerialRead()
{
    CellSerialIndex = 0;
    currentReadTask = nSTANDARD;
    CellSerialReadRequested = false;
    CellSerialReadActive = false;
    CellSerialReadComplete = false;
    memset(cellSerialReceiveData, 0, sizeof(cellSerialReceiveData));
    memset(plc_Interface_Cell_Serial, 0,
        sizeof(unsigned char) * PLC_D_CELL_SERIAL_LEN * 2);
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::StartCellSerialRead()
{
    // [CELL SERIAL 공통] 지금 요청한 이후의 완전한 1회 수신만 완료로 인정한다.
    // 이미 진행 중인 이전 회차는 다음 응답에서 버리고 처음부터 다시 읽는다.
    CellSerialReadComplete = false;
    CellSerialReadRequested = true;
    memset(plc_Interface_Cell_Serial, 0, sizeof(plc_Interface_Cell_Serial));
}
//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 통신 중인 조각은 건드리지 않고 다음 읽기 예약부터 모드를 적용한다.
void __fastcall TMod_PLC::SetCellSerialContinuousRead(bool enabled)
{
    cellSerialContinuousRead = enabled;
}
//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 수신용 버퍼만 지운다. 상시 수신 중 완료 버퍼는 계속 조회할 수 있다.
void __fastcall TMod_PLC::BeginCellSerialRead()
{
    memset(cellSerialReceiveData, 0, sizeof(cellSerialReceiveData));
    CellSerialIndex = 0;
    CellSerialReadRequested = false;
    CellSerialReadActive = true;
    currentReadTask = nCELLSERIAL;
}
//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 일반 데이터는 상시 모드에서도 매 조각 사이에 읽어 PLC 신호 갱신을 유지한다.
void __fastcall TMod_PLC::PrepareCellSerialRead()
{
    if(CellSerialReadRequested || (cellSerialContinuousRead && !CellSerialReadActive))
        BeginCellSerialRead();
    else
        currentReadTask = CellSerialReadActive ? nCELLSERIAL : nSTANDARD;
}
//---------------------------------------------------------------------------
// [CELL SERIAL 공통] 820×4+730=4,010워드가 모두 모인 뒤에만 결과/화면용 버퍼를 교체한다.
void __fastcall TMod_PLC::CompleteCellSerialChunk()
{
    if(CellSerialReadRequested)
    {
        BeginCellSerialRead();
        if(cellSerialContinuousRead) currentReadTask = nSTANDARD;
        return;
    }
    ++CellSerialIndex;
    if(CellSerialIndex >= PLC_D_CELL_SERIAL_READCOUNT)
    {
        memcpy(plc_Interface_Cell_Serial, cellSerialReceiveData, sizeof(plc_Interface_Cell_Serial));
        CellSerialIndex = 0;
        CellSerialReadActive = false;
        CellSerialReadComplete = true;
        currentReadTask = nSTANDARD;
    }
    else
        currentReadTask = cellSerialContinuousRead ? nSTANDARD : nCELLSERIAL;
}
//---------------------------------------------------------------------------
bool __fastcall TMod_PLC::IsCellSerialReadComplete()
{
    return CellSerialReadComplete;
}
//---------------------------------------------------------------------------
bool __fastcall TMod_PLC::IsCellSerialReadActive()
{
    return CellSerialReadRequested || CellSerialReadActive;
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC::GetCellSerialReadWords(int index)
{
    int remaining = PLC_D_CELL_SERIAL_LEN - (index * PLC_D_CELL_SERIAL_READLEN);
    if(remaining <= 0) return 0;
    if(remaining > PLC_D_CELL_SERIAL_READLEN) return PLC_D_CELL_SERIAL_READLEN;
    return remaining;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::InitializePcCommunication()
{
    resultSentParts = 0; // 재접속 후 이전 전송 표식을 사용하지 않는다.
	pc_Read = "";
	pc_ReadFlag = true;
	pc_ReadCount = 0;

	Timer_PC_WriteMsg->Enabled = true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//  Client Socket PC
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::ClientSocket_PCConnect(TObject *Sender, TCustomWinSocket *Socket)

{
    InitializePcCommunication();
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PCDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
    plcAutoMode.Invalidate();
    Timer_PC_WriteMsg->Enabled = false;
    Timer_PC_AutoConnect->Enabled = !bClose;
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
    plcAutoMode.Invalidate();
    ErrorCode = 0;
	Socket->Close();
    Timer_PC_AutoConnect->Enabled = !bClose;
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PCRead(TObject *Sender, TCustomWinSocket *Socket)

{
	int length = Socket->ReceiveLength();
	pc_Read_Temp = Socket->ReceiveText();

	for(int i = 0; i < length; i++)
		pc_Read += IntToHex((unsigned char)pc_Read_Temp[i + 1], 2);

	while(!pc_Read.IsEmpty() && (pc_Read.Length() >= 22) && (pc_Read.Pos("D000")))
	{
		int index = pc_Read.Pos("D000");

		if(index == 1)
		{
			if(pc_Read.SubString(19, 4) == "0000")	//	무조껀 읽어야 함, 그래서 생략
			{
				pc_ReadFlag = true;
				pc_ReadCount = 0;
			}
			pc_Read = "";
			break;
		}
		else pc_Read.Delete(1, index - 1);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::Timer_PC_WriteMsgTimer(TObject *Sender)
{
    if(ClientSocket_PC->Active)
	{
		if(pc_ReadFlag)
		{
			if(pc_index == PC_INDEX_INTERFACE)
			{
                switch(currentWriteTask)
                {
                    case nPCDATA:
                    {
                        //* Heart Beat
                        if(BaseForm->nForm[0]->Client->Active)
                        {
                            bool flag = GetData(pc_Interface_Data, PC_D_HEART_BEAT, 0);
                            SetDouble(pc_Interface_Data, PC_D_HEART_BEAT, (int)!flag);
                        }

                        //* write ir, ocv 완료
                        if(GetPlcValue(PLC_D_IROCV_COMPLETE) == 1)
                            SetValue(PC_D_IROCV_COMPLETE, 0);

                        //* General Data, Result Data, Min/Max Data, IR Data
                        PC_DataChange(0, PC_D_INTERFACE_START_DEV_NUM1, DEVCODE_D, PC_D_INTERFACE_LEN1);
                        ClientSocket_PC->Socket->SendBuf(&pc_Data, sizeof(pc_Data));        // should comment for emulator
                        ClientSocket_PC->Socket->SendBuf(&pc_Interface_Data, sizeof(pc_Interface_Data));

                        Sleep(30);
                        PC_DataChange(0, PC_D_INTERFACE_IR_RESULT, DEVCODE_D, PC_D_INTERFACE_IR_RESULT_LEN);
                        const int headerBytes = ClientSocket_PC->Socket->SendBuf(&pc_Data, sizeof(pc_Data));
                        const int dataBytes = ClientSocket_PC->Socket->SendBuf(&pc_Interface_Result_Code, sizeof(pc_Interface_Result_Code));
                        if(headerBytes == static_cast<int>(sizeof(pc_Data)) && dataBytes == static_cast<int>(sizeof(pc_Interface_Result_Code)))
                            resultSentParts |= 1;

                        currentWriteTask = nIR;
                        break;
                    }
                    case nIR:
                    {
                        PC_DataChange(0, PC_D_INTERFACE_IR, DEVCODE_D, PC_D_INTERFACE_IR_LEN);
                        const int headerBytes = ClientSocket_PC->Socket->SendBuf(&pc_Data, sizeof(pc_Data));
                        const int dataBytes = ClientSocket_PC->Socket->SendBuf(&pc_Interface_Ir_Data, sizeof(pc_Interface_Ir_Data));
                        if(headerBytes == static_cast<int>(sizeof(pc_Data)) && dataBytes == static_cast<int>(sizeof(pc_Interface_Ir_Data)))
                            resultSentParts |= 2;

                        currentWriteTask = nOCV;
                        break;
                    }
                    case nOCV:
                    {
                        PC_DataChange(0, PC_D_INTERFACE_OCV, DEVCODE_D, PC_D_INTERFACE_OCV_LEN);
                        const int headerBytes = ClientSocket_PC->Socket->SendBuf(&pc_Data, sizeof(pc_Data));
                        const int dataBytes = ClientSocket_PC->Socket->SendBuf(&pc_Interface_Ocv_Data, sizeof(pc_Interface_Ocv_Data));
                        if(headerBytes == static_cast<int>(sizeof(pc_Data)) && dataBytes == static_cast<int>(sizeof(pc_Interface_Ocv_Data)))
                            resultSentParts |= 4;

                        currentWriteTask = nPCDATA;
                        break;
                    }
                }
				pc_ReadFlag = false;
			}
		}
		else if(pc_ReadCount > 10)
		{		//	3초동안 응답확인
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
void __fastcall TMod_PLC::Timer_PC_AutoConnectTimer(TObject *Sender)
{
    Timer_PC_AutoConnect->Enabled = false;
    if(bClose || ClientSocket_PC->Active) return;
    try
    {
        ClientSocket_PC->Active = true;
    }
    catch(...)
    {
        Timer_PC_AutoConnect->Enabled = !bClose;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	데이터 변경
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::PC_DataChange(int subCommand, int address, int devCode, int devLen)
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
//---------------------------------------------------------------------------
//  Client Socket PLC
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PLCConnect(TObject *Sender, TCustomWinSocket *Socket)

{
    InitializePlcCommunication();
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PLCDisconnect(TObject *Sender, TCustomWinSocket *Socket)
{
    plcAutoMode.Invalidate();
    Timer_PLC_WriteMsg->Enabled = false;
    ResetCellSerialRead();
    Timer_PLC_AutoConnect->Enabled = !bClose;
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PLCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode)
{
    plcAutoMode.Invalidate();
    ErrorCode = 0;
	ResetCellSerialRead();
	Socket->Close();
    Timer_PLC_AutoConnect->Enabled = !bClose;
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::ClientSocket_PLCRead(TObject *Sender, TCustomWinSocket *Socket)

{
    bool responseComplete = false; // [CELL SERIAL 공통] TCP 일부 수신에서는 다음 요청을 보내지 않는다.
    int length = Socket->ReceiveLength();
	plc_Read_Temp = Socket->ReceiveText();

	for(int i = 0; i < length; i++)
		plc_Read += IntToHex((unsigned char)plc_Read_Temp[i + 1], 2);
   //	TotalForm->Memo1->Lines->Add(plc_Read);
	while(!plc_Read.IsEmpty() && (plc_Read.Length() >= 22) && (plc_Read.Pos("D000")))
	{
		int index = plc_Read.Pos("D000");

		if(index != 1) plc_Read.Delete(1, index - 1);		//	헤더 위치 인지 확인
		if(plc_Read.Length() < 22) break;

		if(plc_Read.SubString(19, 4) == "0000")		// 종료 코드 확인(에러)
		{
			// [CELL SERIAL 공통] MC 길이는 바이트, plc_Read는 HEX 문자열(바이트당 2글자).
            // TCP에서 조각나 도착한 응답을 전체 응답으로 오인하지 않는다.
			int length = 18 + 2 * (StrToInt("0x" + plc_Read.SubString(15, 2))
						+ (StrToInt("0x" + plc_Read.SubString(17, 2)) * 256));

			if(plc_Read.Length() >= length)
			{
                const int expectedWords = currentReadTask == nCELLSERIAL
                    ? GetCellSerialReadWords(CellSerialIndex) : PLC_D_INTERFACE_LEN;
                if(length < 22 + expectedWords * 4)
                {
                    plcAutoMode.Invalidate();
                    // 잘못된 길이는 완료로 게시하지 않고 일반 데이터부터 재동기화한다.
                    ResetCellSerialRead();
                    StartCellSerialRead();
                    plc_Read = "";
                    responseComplete = true;
                    break;
                }
            	switch(currentReadTask)
                {
                    case nSTANDARD:
                        ReadPlcInterfaceData();
                        plcAutoMode.Observe(GetPlcValue(PLC_D_IROCV_AUTO_MANUAL) == PLC_AUTO_MODE_VALUE);
                        PrepareCellSerialRead();
                        break;
                    case nCELLSERIAL:
                        ReadPlcCellSerialChunk(CellSerialIndex, GetCellSerialReadWords(CellSerialIndex));
                        CompleteCellSerialChunk();
                        break;
                }
//				if(plc_index == PLC_INDEX_INTERFACE) ReadPlcInterfaceData();
//				else plc_index = PLC_INDEX_INTERFACE;
			}
			else break;
		}
		else
        {
            // [CELL SERIAL 공통] PLC 오류 응답의 이전 완료값을 최종 결과에 사용하지 않는다.
            plcAutoMode.Invalidate();
            ResetCellSerialRead();
            StartCellSerialRead();
        }
		plc_Read = "";
		responseComplete = true;
		break;
	}

	if(!responseComplete) return;
	plc_ReadCount = 0;
	plc_ReadFlag = true;
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::Timer_PLC_WriteMsgTimer(TObject *Sender)
{
    int startAddress;
    if(ClientSocket_PLC->Active)
	{
		if(plc_ReadFlag)
		{
            switch(currentReadTask)
            {
                case nSTANDARD:
                    PLC_DataChange(0, PLC_D_INTERFACE_START_DEV_NUM, DEVCODE_D, PLC_D_INTERFACE_LEN);
                    break;
                case nCELLSERIAL:
                    startAddress = PLC_D_CELL_SERIAL_NUM + (CellSerialIndex * PLC_D_CELL_SERIAL_READLEN);
                    PLC_DataChange(0, startAddress, DEVCODE_D,
                        GetCellSerialReadWords(CellSerialIndex));
                    break;
                default:
                	break;
            }
            ClientSocket_PLC->Socket->SendBuf(&plc_Data, sizeof(plc_Data));

//			if(plc_index == PLC_INDEX_INTERFACE)
//				PLC_DataChange(0, PLC_D_INTERFACE_START_DEV_NUM, DEVCODE_D, PLC_D_INTERFACE_LEN);
//			ClientSocket_PLC->Socket->SendBuf(&plc_Data, sizeof(plc_Data));

			plc_ReadFlag = false;
            plc_ReadCount = 0;
		}
		else if(plc_ReadCount > 10)		//	3초동안 응답확인
			ClientSocket_PLC->Close();

		plc_ReadCount++;
	}
	else ClientSocket_PLC->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMod_PLC::Timer_PLC_AutoConnectTimer(TObject *Sender)
{
    Timer_PLC_AutoConnect->Enabled = false;
    if(bClose || ClientSocket_PLC->Active) return;
    try
    {
        ClientSocket_PLC->Active = true;
    }
    catch(...)
    {
        Timer_PLC_AutoConnect->Enabled = !bClose;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	데이터 변경
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::PLC_DataChange(int subCommand, int address, int devCode, int devLen)
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
void __fastcall TMod_PLC::ReadPlcInterfaceData()
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
void __fastcall TMod_PLC::ReadPlcCellSerialChunk(int index, int wordsToRead)
{
    int num = 0;

    for(int i = 0; i < wordsToRead; i++)
    {
        int destIndex = i + (index * PLC_D_CELL_SERIAL_READLEN);
        if(destIndex >= PLC_D_CELL_SERIAL_LEN) break;

        cellSerialReceiveData[destIndex][0] = StrToInt("0x" + plc_Read.SubString(23 + num, 2));
        cellSerialReceiveData[destIndex][1] = StrToInt("0x" + plc_Read.SubString(23 + num + 2, 2));
        num += 4;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//	데이터 쓰기 & 읽기
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetData(unsigned char (*data)[2], int column, int num, bool flag)
{
	int num1 = num / 8;
	int num2 = num % 8;

	if(flag) data[column][num1] |= (1 << num2);
	else data[column][num1] &= ~(1 << num2);
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetDouble(unsigned char (*data)[2], int column, double value)
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
void __fastcall TMod_PLC::SetString(unsigned char (*data)[2], int column, AnsiString msg)
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
int __fastcall TMod_PLC::GetData(unsigned char (*data)[2], int column, int num)
{
	bool value = false;
	int num1 = num / 8;
	int num2 = num % 8;

	value = data[column][num1] & (1 << num2);

	return value;
}
//---------------------------------------------------------------------------
double __fastcall TMod_PLC::GetDouble(unsigned char (*data)[2], int column)
{
	double value = -1;

	value = (data[column][1] * 256) + data[column][0];

	return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC::GetString(unsigned char (*data)[2], int column, int count)
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
double __fastcall TMod_PLC::GetPlcValue(int plc_address)
{
    double value = GetDouble(plc_Interface_Data, plc_address);
    return value;
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC::GetPlcData(int plc_address, int bit_num)
{
    int value = GetData(plc_Interface_Data, plc_address, bit_num);
    return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC::GetPlcValue(int plc_address, int size)
{
    AnsiString value = GetString(plc_Interface_Data, plc_address, size);
    return value;
}
//---------------------------------------------------------------------------
double __fastcall TMod_PLC::GetValue(int pc_address)
{
    double value = GetDouble(pc_Interface_Data, pc_address);
    return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC::GetCellSerial(int plc_address, int index, int size)
{
    AnsiString value = GetString(plc_Interface_Cell_Serial, plc_address + index * 10, size);
    return value;
}
//---------------------------------------------------------------------------
AnsiString __fastcall TMod_PLC::GetCellSerialTrayId(int plc_address, int size)
{
    AnsiString value = GetString(plc_Interface_Cell_Serial, plc_address, size);
    return value;
}
//---------------------------------------------------------------------------
double __fastcall TMod_PLC::GetCellSerialValue(int plc_address)
{
    double value = GetDouble(plc_Interface_Cell_Serial, plc_address);
    return value;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetValue(int pc_address, int value)
{
    SetDouble(pc_Interface_Data,  pc_address, value);
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetResultCode(int pc_address, int value)
{
    SetDouble(pc_Interface_Result_Code, pc_address, value);
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC::GetResultCode(int pc_address, int index)
{
    int lowWord = GetDouble(pc_Interface_Result_Code, pc_address + index);
    return lowWord;
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetSpecValue(int pc_address, int value)
{
	SetDouble(pc_Interface_Data, pc_address, static_cast<int16_t>(value));
	SetDouble(pc_Interface_Data, pc_address + 1, static_cast<int16_t>(value >> 16));
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetIrValue(int pc_address, int index, int value)
{
	SetDouble(pc_Interface_Ir_Data, pc_address + (index * 2), static_cast<int16_t>(value));
	SetDouble(pc_Interface_Ir_Data, pc_address + (index * 2) + 1, static_cast<int16_t>(value >> 16));
}
//---------------------------------------------------------------------------
void __fastcall TMod_PLC::SetOcvValue(int pc_address, int index, int value)
{
    SetDouble(pc_Interface_Ocv_Data, pc_address + (index * 2), static_cast<int16_t>(value));
	SetDouble(pc_Interface_Ocv_Data, pc_address + (index * 2) + 1, static_cast<int16_t>(value >> 16));
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC::GetIrValue(int pc_address, int index)
{
    int lowWord = GetDouble(pc_Interface_Ir_Data, pc_address + (index * 2));
    int highWord = GetDouble(pc_Interface_Ir_Data, pc_address + (index * 2) + 1);
    return (highWord << 16) | lowWord;
}
//---------------------------------------------------------------------------
int __fastcall TMod_PLC::GetOcvValue(int pc_address, int index)
{
    int lowWord = GetDouble(pc_Interface_Ocv_Data, pc_address + (index * 2));
    int highWord = GetDouble(pc_Interface_Ocv_Data, pc_address + (index * 2) + 1);
    return (highWord << 16) | lowWord;
}
//---------------------------------------------------------------------------
// PLC 명령어
//---------------------------------------------------------------------------






//---------------------------------------------------------------------------
// 최종 버퍼 준비 직후 호출. 이후 세 블록이 각각 실제 송신된 경우만 완료 지연을 끝낸다.
// TCP 송신 확인이며 PLC 내부 반영 ACK를 의미하지 않는다.
void __fastcall TMod_PLC::BeginResultTransmission() { resultSentParts = 0; }
bool __fastcall TMod_PLC::WasResultTransmitted() { return resultSentParts == 7; }
bool __fastcall TMod_PLC::IsResultConnectionReady()
{
    return ClientSocket_PC->Active && ClientSocket_PC->Socket->Connected &&
           ClientSocket_PLC->Active && ClientSocket_PLC->Socket->Connected &&
           GetPlcValue(PLC_D_IROCV_ERROR) == 0;
}

// The PC AUTO READY output is not the PLC mode input. Require fresh reception after reconnect.
bool __fastcall TMod_PLC::IsPlcAutoMode()
{
    return plcAutoMode.IsAutomatic() &&
        ClientSocket_PC->Active && ClientSocket_PC->Socket && ClientSocket_PC->Socket->Connected &&
        ClientSocket_PLC->Active && ClientSocket_PLC->Socket && ClientSocket_PLC->Socket->Connected;
}
