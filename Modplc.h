//---------------------------------------------------------------------------

#ifndef ModPLCH
#define ModPLCH
#include "PlcAutoMode.h"
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <System.Win.ScktComp.hpp>
#include "Define.h"

#include <deque>

//---------------------------------------------------------------------------
//	디바이스 코드
//---------------------------------------------------------------------------
const int DEVCODE_M			=	0x90;		//	내부 릴레이
const int DEVCODE_L			=	0x92;	  	//	래치 릴레이
const int DEVCODE_D			=	0xA8;		//	데이터 레지스터
const int DEVCODE_W			=	0xB4;		//	링크 레지스터
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	Index 구분
//---------------------------------------------------------------------------
const int PLC_INDEX_INTERFACE[2]				=	{ 1, 2 };


const int PC_INDEX_INTERFACE					=		11;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	시작 번지
//---------------------------------------------------------------------------
const int PLC_D_INTERFACE_START_DEV_NUM	 			=	44000;
const int PLC_D_INTERFACE_LEN 						= 	100;

const int PLC_D_CELL_SERIAL_NUM                     =	{95000};
// PLC 공간은 실채널 수와 별개다. 256채널 사이트가 400채널 PLC 공간을 쓸 수도 있다.
const int PLC_D_CELL_SERIAL_CHANNEL_COUNT           =   400;
typedef char CheckSerialChannelCapacity[(MAXCHANNEL <= PLC_D_CELL_SERIAL_CHANNEL_COUNT) ? 1 : -1];
const int PLC_D_CELL_SERIAL_WORDS_PER_CHANNEL       =   10;
const int PLC_D_CELL_SERIAL_TRAYID_LEN              =   10;
const int PLC_D_CELL_SERIAL_LEN                     =   PLC_D_CELL_SERIAL_TRAYID_LEN
                                                        + (PLC_D_CELL_SERIAL_CHANNEL_COUNT
                                                        * PLC_D_CELL_SERIAL_WORDS_PER_CHANNEL);
const int PLC_D_CELL_SERIAL_READLEN                 =   820;
const int PLC_D_CELL_SERIAL_READCOUNT               =   (PLC_D_CELL_SERIAL_LEN
                                                        + PLC_D_CELL_SERIAL_READLEN - 1)
                                                        / PLC_D_CELL_SERIAL_READLEN;

const int PC_D_INTERFACE_START_DEV_NUM1				=	45000;
const int PC_D_INTERFACE_LEN1	 					= 	70;

const int PC_D_INTERFACE_IR							=	{45070};
const int PC_D_INTERFACE_IR_LEN						= 	800;

const int PC_D_INTERFACE_OCV						=	46000;
const int PC_D_INTERFACE_OCV_LEN 					= 	800;

const int PC_D_INTERFACE_IR_RESULT                  =   47000;
const int PC_D_INTERFACE_IR_RESULT_LEN              =	400;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
// 사용 채널이 PLC 예약 공간을 넘으면 컴파일 단계에서 발견한다.
typedef char CheckIrCapacity[(MAXCHANNEL * 2 <= PC_D_INTERFACE_IR_LEN) ? 1 : -1];
typedef char CheckOcvCapacity[(MAXCHANNEL * 2 <= PC_D_INTERFACE_OCV_LEN) ? 1 : -1];
typedef char CheckResultCapacity[(MAXCHANNEL <= PC_D_INTERFACE_IR_RESULT_LEN) ? 1 : -1];
//	PLC - PC Interface
//---------------------------------------------------------------------------
// PLC - IR/OCV
const int PLC_D_HEART_BEAT				   			=	0;
const int PLC_D_IROCV_AUTO_MANUAL	                =   1;
const int PLC_D_IROCV_ERROR    	  			        =   2;
const int PLC_D_IROCV_TRAY_IN   	  		        =   3;
const int PLC_D_IROCV_PROB_OPEN 	  		        =   4;
const int PLC_D_IROCV_PROB_CLOSE    	  	        =   5;
const int PLC_D_IROCV_COMPLETE	    	  	        =   8;

const int PLC_D_IROCV_TRAY_ID   	  		        =   10;

// TRAY INFO     256
const int PLC_D_IROCV_TRAY_CELL_DATA                = 	30;

// CELL SERIAL TRAY ID
const int PLC_D_IROCV_CELL_SERIAL_TRAYID            =   0;
const int PLC_D_IROCV_CELL_SERIAL                  	=   10;
//---------------------------------------------------------------------------
//	PLC - PC Interface
//---------------------------------------------------------------------------
// PC - IR/OCV
const int PC_D_HEART_BEAT			  				=	0;
const int PC_D_IROCV_STAGE_AUTO_READY     	    	=   1;
const int PC_D_IROCV_ERROR    	  			    	=   2;
const int PC_D_IROCV_TRAY_OUT    	  	   	    	=   3;
const int PC_D_IROCV_PROB_OPEN   	  		    	=   4;
const int PC_D_IROCV_PROB_CLOSE    	  	        	=   5;
const int PC_D_IROCV_MEASURING                   	=   6;
const int PC_D_IROCV_NG_ALARM		                =   7;
const int PC_D_IROCV_COMPLETE						=   8;
const int PC_D_IROCV_REMEASURE		                =   9;

const int PC_D_IROCV_NG_COUNT						=   10;
const int PC_D_IROCV_IR_MIN							=   11;
const int PC_D_IROCV_IR_MAX							=   13;
const int PC_D_IROCV_OCV_MIN						=   15;
const int PC_D_IROCV_OCV_MAX						=   17;

// OK/NG - D45030
const int PC_D_IROCV_MEASURE_OK_NG			   		=	30;

// NG CODE - D47000
const int PC_D_IROCV_RESULT_CODE                    =   0;

const int PC_D_IROCV_IR_VALUE                   	=   0;
const int PC_D_IROCV_OCV_VALUE                   	=   0;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	PLC
//---------------------------------------------------------------------------
typedef struct
{
	unsigned char SubHeader[2];			//	서브 헤더
	unsigned char NetNum;		 		//	네트워크 번호
	unsigned char PlcNum;	   			//	PLC 번호
	unsigned char ReqIONum[2];			//	IO 번호
	unsigned char ReqOfficeNum;	  		//	국 번호
	unsigned char ReqDataLen[2];		//  요구 데이터 길이(CPU 감시 타이머 ~ 디바이스 길이)
	unsigned char CpuTime[2];			//	CPU 감시 타이머
	unsigned char Command[2];			//	커맨드
	unsigned char SubCommand[2];		//	서브 커맨드 (0 = 비트-16단위, 워드-1단위 / 1 = 비트-1단위)
	unsigned char StartDevNum[3];		//	선두 디바이스
	unsigned char DevCode;  			//	디바이스 코드
	unsigned char DevLen[2];			//	디바이스 길이
} PLC_DATA;
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	PC
//---------------------------------------------------------------------------
typedef struct
{
	unsigned char SubHeader[2];					//	서브 헤더
	unsigned char NetNum;						//	네트워크 번호
	unsigned char PlcNum;	    				//	PLC 번호
	unsigned char ReqIONum[2];					//	IO 번호
	unsigned char ReqOfficeNum;	  				//	국 번호
	unsigned char ReqDataLen[2];				//  요구 데이터 길이(CPU 감시 타이머 ~ 디바이스 길이)
	unsigned char CpuTime[2];					//	CPU 감시 타이머
	unsigned char Command[2];					//	커맨드
	unsigned char SubCommand[2];				//	서브 커맨드
	unsigned char StartDevNum[3];				//	선두 디바이스
	unsigned char DevCode;  					//	디바이스 코드
	unsigned char DevLen[2];					//	디바이스 길이
} PC_DATA;
//---------------------------------------------------------------------------



//---------------------------------------------------------------------------
class TMod_PLC : public TDataModule
{
__published:	// IDE-managed Components
	TTimer *Timer_Read;
	TClientSocket *ClientSocket_PC;
	TTimer *Timer_PC_AutoConnect;
	TTimer *Timer_PC_WriteMsg;
	TClientSocket *ClientSocket_PLC;
	TTimer *Timer_PLC_AutoConnect;
	TTimer *Timer_PLC_WriteMsg;
	void __fastcall ClientSocket_PCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Timer_PC_AutoConnectTimer(TObject *Sender);
	void __fastcall Timer_PC_WriteMsgTimer(TObject *Sender);
	void __fastcall ClientSocket_PLCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PLCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Timer_PLC_WriteMsgTimer(TObject *Sender);
	void __fastcall Timer_PLC_AutoConnectTimer(TObject *Sender);

private:	// User declarations
    bool bClose;
//---------------------------------------------------------------------------
//	PLC
//---------------------------------------------------------------------------
	void __fastcall InitializePlcCommunication();
	void __fastcall PLC_DataChange(int subCommand, int address, int devCode, int devLen);
	void __fastcall ReadPlcInterfaceData();
    void __fastcall ReadPlcCellSerialChunk(int index, int wordsToRead);
    int __fastcall GetCellSerialReadWords(int index);
    void __fastcall ResetCellSerialRead();
    // [CELL SERIAL 공통] 일반 데이터 응답 후 요청/상시 모드에 따라 다음 읽기를 예약한다.
    void __fastcall PrepareCellSerialRead();
    // [CELL SERIAL 공통] 1회 분할 수신을 시작한다. 완료 버퍼는 마지막 조각까지 유지한다.
    void __fastcall BeginCellSerialRead();
    // [CELL SERIAL 공통] 조각 수신 후 전체 완료 시에만 공개 버퍼를 교체한다.
    void __fastcall CompleteCellSerialChunk();
    // [CELL SERIAL 공통] 설정은 재접속 후에도 유지하고, 다음 일반 응답부터 적용한다.
    bool cellSerialContinuousRead;
    // [CELL SERIAL 공통] 수신 중 임시 버퍼와 사용 가능한 완료 버퍼를 분리한다.
    unsigned char cellSerialReceiveData[PLC_D_CELL_SERIAL_LEN][2];

	PLC_DATA plc_Data;
	AnsiString plc_Read, plc_Read_Temp;
	bool plc_ReadFlag;
	int plc_ReadCount, plc_index;
	AnsiString plc_Interface;

//---------------------------------------------------------------------------
//	PC
//---------------------------------------------------------------------------
	void __fastcall InitializePcCommunication();
	void __fastcall PC_DataChange(int subCommand, int address, int devCode, int devLen);

	PC_DATA pc_Data;
	AnsiString pc_Read, pc_Read_Temp;
	bool pc_ReadFlag;
	int pc_ReadCount, pc_index;

//---------------------------------------------------------------------------
//	Tray Info
//---------------------------------------------------------------------------
	void __fastcall SaveTrayInfo(AnsiString trayID);
    AnsiString m_trayID;
	int m_slotNum, m_slotNumTemp;
public:		// User declarations
	__fastcall TMod_PLC(TComponent* Owner);

	void __fastcall Connect(AnsiString ip, int port1, int port2);
	void __fastcall Disconnect();

	void __fastcall SetData(unsigned char (*data)[2], int column, int num, bool flag);
	void __fastcall SetDouble(unsigned char (*data)[2], int column, double value);
	// 문자열 쓰기 확장용 API. 현재 호출이 없더라도 유지한다.
	void __fastcall SetString(unsigned char (*data)[2], int column, AnsiString msg);

	int __fastcall GetData(unsigned char (*data)[2], int column, int num);
	double __fastcall GetDouble(unsigned char (*data)[2], int column);
	AnsiString __fastcall GetString(unsigned char (*data)[2], int column, int count);

//---------------------------------------------------------------------------
// 수신 완료된 시리얼 버퍼 조회. 통신 요청은 StartCellSerialRead()가 담당한다.
    AnsiString __fastcall GetCellSerial(int plc_address, int index, int size);
    AnsiString __fastcall GetCellSerialTrayId(int plc_address, int size);
    double __fastcall GetCellSerialValue(int plc_address);
    void __fastcall StartCellSerialRead();
    // [CELL SERIAL 공통] false=명시 요청 때만, true=일반 데이터와 번갈아 상시 수신.
    void __fastcall SetCellSerialContinuousRead(bool enabled);
    bool __fastcall IsCellSerialReadComplete();
    bool __fastcall IsCellSerialReadActive();

    AnsiString __fastcall GetPlcValue(int plc_address, int size);
    double __fastcall GetPlcValue(int plc_address);
    // PLC 비트 읽기 확장용 API.
    int __fastcall GetPlcData(int plc_address, int bit_num);
    double __fastcall GetValue(int pc_address);
    void __fastcall SetValue(int pc_address, int value);
    void __fastcall SetResultCode(int pc_address, int value);
    int __fastcall GetResultCode(int pc_address, int index);
    void __fastcall SetSpecValue(int pc_address, int value);
    void __fastcall SetIrValue(int pc_address, int index, int value);
    void __fastcall SetOcvValue(int pc_address, int index, int value);
    int __fastcall GetIrValue(int pc_address, int index);
    int __fastcall GetOcvValue(int pc_address, int index);

    // PC 내부 전송 확인: 새 PLC 비트 없이 결과/IR/OCV 각 블록의 송신 여부를 추적한다.
    void __fastcall BeginResultTransmission();
    bool __fastcall WasResultTransmitted();
    bool __fastcall IsResultConnectionReady();
    bool __fastcall IsPlcAutoMode();
    TPlcAutoModeState plcAutoMode;
private:
    unsigned int resultSentParts;
public:
    //* PLC DATA
    int currentReadTask;
    int CellSerialIndex;
    bool CellSerialReadRequested;
    bool CellSerialReadActive;
    bool CellSerialReadComplete;
	unsigned char plc_Interface_Data[PLC_D_INTERFACE_LEN][2];
    unsigned char plc_Interface_Cell_Serial[PLC_D_CELL_SERIAL_LEN][2];
    //* PC DATA
    int currentWriteTask;
	unsigned char pc_Interface_Data[PC_D_INTERFACE_LEN1][2];
    unsigned char pc_Interface_Result_Code[PC_D_INTERFACE_IR_RESULT_LEN][2];
    unsigned char pc_Interface_Ir_Data[PC_D_INTERFACE_IR_LEN][2];
	unsigned char pc_Interface_Ocv_Data[PC_D_INTERFACE_OCV_LEN][2];
};
//---------------------------------------------------------------------------
extern PACKAGE TMod_PLC *Mod_PLC;
//---------------------------------------------------------------------------
#endif
