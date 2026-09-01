//---------------------------------------------------------------------------

#ifndef ModPLCAsciiH
#define ModPLCAsciiH
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
const int PLC_INDEX_INTERFACE[1]				= { 1 };
const int PC_INDEX_INTERFACE					=		11;
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	시작 번지(통합)
//---------------------------------------------------------------------------
const int PLC_D_INTERFACE_START_DEV_NUM	 			=	{40000};
const int PLC_D_INTERFACE_LEN	 					= 	100;
//----------------------------------------------------------------------------

const int PC_D_INTERFACE_START_DEV_NUM				=	{41000};
const int PC_D_INTERFACE_LEN  						= 	60;

const int PC_D_INTERFACE_VOLTAGE					=	{41070};
const int PC_D_INTERFACE_VOLTAGE_LEN				= 	800;

const int PC_D_INTERFACE_CURRENT					=	{42000};
const int PC_D_INTERFACE_CURRENT_LEN				= 	800;
//----------------------------------------------------------------------------


//---------------------------------------------------------------------------
//	PLC - PC Interface
//---------------------------------------------------------------------------
const int PLC_D_HEART_BEAT				   			=	0;
const int PLC_D_AUTO_MANUAL			   				=	1;
const int PLC_D_PRE_ERROR		   	  				=	2;
const int PLC_D_PRE_TRAY_IN	    	  		        =   3;
const int PLC_D_PRE_PROB_OPEN   	  		        =   4;
const int PLC_D_PRE_PROB_CLOSE 		   	  	        =   5;
const int PLC_D_PRE_COMPLETE 		   	  	        =   8;

const int PLC_D_PRE_TRAY_ID    	  			        =   10;

// TRAY INFO
const int PLC_D_PRE_TRAY_CELL_DATA				   	=	30;
//---------------------------------------------------------------------------
//	PC - PLC Interface
//---------------------------------------------------------------------------
const int PC_D_HEART_BEAT			  				=	0;
const int PC_D_PRE_STAGE_AUTO_READY     	        =   1;
const int PC_D_PRE_ERROR						   	=	2;
const int PC_D_PRE_TRAY_OUT    	  		        	=   3;
const int PC_D_PRE_PROB_OPEN   	  		        	=   4;
const int PC_D_PRE_PROB_CLOSE    	  	        	=   5;
const int PC_D_PRE_CHARGING                      	=   6;
const int PC_D_PRE_NG_ALARM                         =   7;
const int PC_D_PRE_COMPLETE                         =   8;
const int PC_D_PRE_REMEASURE                        =   9;

const int PC_D_PRE_NG_COUNT                      	=   10;
const int PC_D_PRE_CURRENT_MIN                      =   11;
const int PC_D_PRE_CHARGE_VOLTAGE                   =   13;
const int PC_D_PRE_CHARGE_CURRENT                   =   15;
const int PC_D_PRE_CHARGE_TIME                      =   17;

// OK/NG - D41030
const int PC_D_PRE_MEASURE_OK_NG			   		=	30;
// D41070
const int PC_D_PRE_VOLTAGE_VALUE                    =   0;
// D42000
const int PC_D_PRE_CURRENT_VALUE                    =   0;
//---------------------------------------------------------------------------

class TMod_PLCAscii : public TDataModule
{
__published:	// IDE-managed Components
	TTimer *Timer_Read;
	TClientSocket *ClientSocket_PC;
	TClientSocket *ClientSocket_PLC;
	TTimer *Timer_PC_AutoConnect;
	TTimer *Timer_PC_WriteMsg;
	TTimer *Timer_PLC_WriteMsg;
	TTimer *Timer_PLC_AutoConnect;
	void __fastcall ClientSocket_PCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCConnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCDisconnect(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientSocket_PLCError(TObject *Sender, TCustomWinSocket *Socket,
          TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ClientSocket_PLCRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall Timer_PC_AutoConnectTimer(TObject *Sender);
	void __fastcall Timer_PLC_AutoConnectTimer(TObject *Sender);
	void __fastcall Timer_PC_WriteMsgTimer(TObject *Sender);
	void __fastcall Timer_PLC_WriteMsgTimer(TObject *Sender);

private:	// User declarations
    bool bClose;
    //---------------------------------------------------------------------------
    //	PLC
    //---------------------------------------------------------------------------
	void __fastcall PLC_Initialization();
	void __fastcall PLC_DataChange(int subCommand, int address, int devCode, int devLen);
	void __fastcall PLC_Recv_Interface(int nTag);
    AnsiString __fastcall BuildAsciiReadCommand(int address, int devCode, int devLen);

	bool plc_ReadFlag;
	int plc_ReadCount, plc_index;
	AnsiString plc_Interface;

    //---------------------------------------------------------------------------
    //	PC
    //---------------------------------------------------------------------------
	void __fastcall PC_Initialization();
	void __fastcall PC_DataChange(int subCommand, int address, int devCode, int devLen);
    AnsiString __fastcall BuildAsciiWriteCommand(int address, int devCode, int devLen, unsigned char (*data)[2]);

	bool pc_ReadFlag;
	int pc_ReadCount, pc_index;
public:		// User declarations
	__fastcall TMod_PLCAscii(TComponent* Owner);
    void __fastcall Connect(AnsiString ip, int port1, int port2);
	void __fastcall DisConnect();

	void __fastcall SetData(unsigned char (*data)[2], int column, int num, bool flag);
	void __fastcall SetDouble(unsigned char (*data)[2], int column, double value);
	void __fastcall SetString(unsigned char (*data)[2], int column, AnsiString msg);

	int __fastcall GetData(unsigned char (*data)[2], int column, int num);
	double __fastcall GetDouble(unsigned char (*data)[2], int column);
	AnsiString __fastcall GetString(unsigned char (*data)[2], int column, int count);
//---------------------------------------------------------------------------
//  실제호출함수
    AnsiString __fastcall GetPlcValue(int plc_address, int size);
    double __fastcall GetPlcValue(int plc_address);
    int __fastcall GetPlcData(int plc_address, int bit_num);
    void __fastcall SetValue(int pc_address, int value);
    void __fastcall SetVoltValue(int pc_address, int index, int value);
    void __fastcall SetCurrValue(int pc_address, int index, int value);
    int __fastcall GetVoltValue(int pc_address, int index);
    int __fastcall GetCurrValue(int pc_address, int index);

	bool PLC_Write_Result; //voltage, current 값은 필요 시에만 쓰기를 한다.
	unsigned char plc_Interface_Data[PLC_D_INTERFACE_LEN][2];
	unsigned char pc_Interface_Data[PC_D_INTERFACE_LEN][2];
    unsigned char pc_Interface_Volt_Data[PC_D_INTERFACE_VOLTAGE_LEN][2];
	unsigned char pc_Interface_Curr_Data[PC_D_INTERFACE_CURRENT_LEN][2];
};
//---------------------------------------------------------------------------
extern PACKAGE TMod_PLCAscii *Mod_PLCAscii;
//---------------------------------------------------------------------------
#endif
