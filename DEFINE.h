#ifndef RVMO_define
#define RVMO_define


#define APP_PATH					"D:\\IROCV_EVE\\"
#define BIN_PATH			  		APP_PATH"Bin\\"
#define MSA_PATH			  		APP_PATH"Msa\\"
#define DATA_PATH					APP_PATH"Data\\"
#define LOG_PATH                    APP_PATH"Log\\"
#define TRAY_PATH                   APP_PATH"Tray\\"
#define NG_PATH                     APP_PATH"NGPP\\"

//---------------------------------------------------------------------------
//	Cell Serial 읽기
//---------------------------------------------------------------------------
const int nSTANDARD  	=   1;
const int nCELLSERIAL   =   2;

//---------------------------------------------------------------------------
//	Write PC Data
//---------------------------------------------------------------------------
const int nPCDATA		=   1;
const int nIR			=   2;
const int nOCV			=   3;

//---------------------------------------------------------------------------
//	STEP 정보
//---------------------------------------------------------------------------
#define STEP_WAIT					0
#define STEP_MEASURE				1
#define STEP_FINISH					2
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
//	Channel 갯수
//---------------------------------------------------------------------------
#include "SiteConfig.h"

const int SEND = 1;
const int RECEIVE = 2;
const int ETC = 3;

const char nAuto 	= 0;
const char nRemote 	= 1;
const char nLocal 	= 2;

const char nAllRetest 	= 3;
const char nCellRetest 	= 4;
const char nCalibration = 5;

const char nNoAnswer	= 0;
const char nIdle		= 1;
const char nVacancy		= 2;
const char nIN			= 3;
const char nREADY		= 4;
const char nRUN			= 5;
const char nEND			= 6;
const char nFinish 		= 7;
const char nManual		= 8;
const char nOpbox		= 9; 	// IMS 프로토콜 외 별도 생성
const char nEmergency 	= 10;


const char nBusy		= 11;
const char nReameasure 	= 12;

const char nRedEnd 		= 20;
const char nBlueEnd 	= 21;

const int nRunningError = 28;
const int nReadyError 	= 30;
const int nFinishError  = 32;
const int nDefaultError = 40;

// Process Status
const int sReady   		= 0;
const int sTrayIn  		= 1;
const int sBarcode 		= 2;
const int sProbeDown 	= 3;
const int sMeasure      = 4;
const int sFinish       = 5;
const int sProbeOpen    = 6;
const int sTrayOut      = 7;

#define		COMM_RECEIVE	WM_USER + 1003


const int IDN = 1;

const int SIZ = 2;		// 검사 관련 명령어
const int AMS = 3;
const int IR =  4;
const int OCV = 5;
const int AMF = 6;
const int STP = 7;
const int FIN = 8;
const int SLO = 9;
const int FST = 10;
const int BCR = 11;
const int DEV = 13;


const int SAV = 20;     // 수동 조작
const int LOD = 21;

const int SEN = 40;
const int EMS = 41;
const int ERR = 42;
const int ARV = 43;
const int STB = 44;
const int MAN = 45;
const int LOC = 46;
const int EMP = 47;
const int BYP = 48;
const int RDY = 49;
const int DOR = 50;
const int BZY = 51;
const int STA = 53;

const int LRM = 60;
const int REC = 61;
const int RST = 62;		// 비상정지 해제
const int REM = 63;
const int CLR = 64;
const int GSC = 65;
const int IDL = 66;
const int FRM = 67;
const int sOUT = 68;
const int HOM = 69;

const int GO = 71;
const int HI = 72;
const int LO = 73;
const int OV = 74;
const int UN = 75;
const int CE = 76;
const int NA = 77;
const int NO = 78;
//const int CE = 79; /// value error

// IMS 보고 메세지
const int RESET = 0;
const int EMERGENCY = 1;
const int PROBE_ERROR = 4;
const int RESTART = 5;
const int PROCESS_ERROR = 7;
const int AIR_ERROR = 14;
const int NO_ANSWER = 17;
const int ACOUNT = 24;
const int GPIB_ERROR = 50;
const int BARCODE_ERROR = 51;
// STAGE 정의 메세지
const int OPBOX = 101;



typedef struct{
    bool ams;
    bool amf;
	AnsiString trayid;
	int cell[MAXCHANNEL];
	AnsiString cell_type;
	AnsiString lotid;
	AnsiString cell_serial[MAXCHANNEL];
	int cell_count;
	int rem_mode;
	float original_value[MAXCHANNEL];
	float after_value[MAXCHANNEL];
	float ocv_value[MAXCHANNEL];
	float Cali_value[MAXCHANNEL];
	int measure_result[MAXCHANNEL];
	bool first;
	AnsiString precharger[MAXCHANNEL];
	AnsiString precharge_volt[MAXCHANNEL];
	AnsiString arrive;
    AnsiString finish;
	AnsiString cell_model;
	AnsiString lot_number;
}TRAY_INFO;

typedef struct{
	int arl_reserve;
	int arl;
	bool init;
	int err;
	int alarm_status;
	int alarm_cnt;
	int now_status;
	double ir_offset[MAXCHANNEL];
}STAGE_INFO;

typedef struct{
	bool re_excute;
	int cnt_error;
	int cell[MAXCHANNEL];
	// 최종 판정(cell)과 다음 재측정 항목을 분리한다: 비트 1=IR, 2=OCV.
    int pendingItems[MAXCHANNEL];
    int waitingChannel; // 응답 대기 채널. -1이면 요청 없음.
    int waitingItem; // 1=IR, 2=OCV.
	int re_index;
}REMEASURE;

typedef struct{
	bool recontact;
	double ir_min;
	double ir_max;
	double ocv_min;
	double ocv_max;
    int closedProbeRemeasureMaxNgCount; // 닫힘 유지 재측정: NG 1~설정값 이하, 0=생략.
	int probeRemeasureCount; // 프로브 재개폐 추가 횟수. 0=사용 안 함, 최초 측정 제외.
    int remeasure_alarm_cnt;
    // [CELL SERIAL 공통] false=TRAY IN 수신 보관, true=상시 수신 후 결과 저장 직전 재확인.
    bool cell_serial_continuous_read;
    AnsiString pwd;
}CONFIG;

#endif
