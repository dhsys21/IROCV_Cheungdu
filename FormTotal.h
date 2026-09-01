//---------------------------------------------------------------------------

#ifndef FormTotalH
#define FormTotalH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <IniFiles.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <jpeg.hpp>

//---------------------------------------------------------------------------
#include "define.h"
#include "FormMeasureInfo.h"
#include "FormRemeasure.h"
#include <Menus.hpp>
#include "AdvSmoothButton.hpp"
#include <Graphics.hpp>
#include "AdvSmoothPanel.hpp"
#include <System.Win.ScktComp.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <queue>
#include <string>
#include <vector>


const int NoCell = 1;
const int BadIr = 2;
const int CellError = 3;
const int Line = 4;
const int IrCheck = 5;
const int OcvCheck = 6;
const int BothCheck = 7;
const int MeasureFail = 8;
const int BadOcv = 9;
const int AverageOver = 10;

using namespace std;


typedef struct{
	AnsiString cmd;
	AnsiString param;
	int tx_mode;
	int time_out;
	int re_send;
}SEND_DATA;

typedef struct ExtInput
{
	// Board 1
	// (uint8_t *)&Input
	uint8_t OP_17: 1;					// 1-I17						
	uint8_t OP_Remeasure: 1;				// 1-I18
	uint8_t OP_AutoSw: 1;					// 1-I19
	uint8_t OP_ManualSw: 1;  				// 1-I20
	uint8_t OP_ResetSw: 1;					// 1-I21
	uint8_t OP_StartSw: 1;					// 1-I22
	uint8_t OP_EMSSw: 1;		    		// 1-I23
	uint8_t OP_24: 1;					// 1-I24
	
	uint8_t OP_9: 1;				// 1-I9
	uint8_t OP_10: 1;				// 1-I10
	uint8_t OP_11: 1;				// 1-I11
	uint8_t OP_12: 1;				// 1-I12
	uint8_t OP_13: 1;				// 1-I13
	uint8_t OP_14: 1;				// 1-I14
	uint8_t OP_15: 1;				// 1-I15
	uint8_t OP_16: 1;						// 1-116

	uint8_t OP_ProbeUpUp: 1;				// 1-I1
	uint8_t OP_ProbeUpDn: 1;				// 1-I2
	uint8_t OP_ProbeDnUp: 1;				// 1-I3
	uint8_t OP_ProbeDnDn: 1;				// 1-I4
	uint8_t OP_CenteringUp: 1; 				// 1-I5 
	uint8_t OP_CenteringDn: 1;				// 1-I6 
	uint8_t OP_TrayForward: 1;				// 1-I7
	uint8_t OP_TrayBackward: 1;				// 1-I8
	
	// board2
	uint8_t IN2_17: 1;						// 2-I17
	uint8_t IN2_18: 1;		  				// 2-I18	
	uint8_t IN2_19: 1;				// 2-I19
	uint8_t IN2_20: 1;				// 2-I20
	uint8_t IN2_21: 1;						// 2-I21
	uint8_t IN2_22: 1;						// 2-I22
	uint8_t IN2_23: 1; 						// 2-I23
	uint8_t IN2_24: 1;						// 2-I24
	
	
	uint8_t _TraySensing: 1;				// 2-I09
	uint8_t Interface_InOK: 1;						// 2-I10
	uint8_t _SafetySensing_1: 1;  					// 2-I11
	uint8_t _Air: 1;						// 2-I12
	uint8_t CenteringUp: 1;						// 2-I13
	uint8_t CenteringDn: 1;      				// 2-I14
	uint8_t IN2_15: 1;						// 2-I15
	uint8_t IN2_16: 1;						// 2-I16
	
	uint8_t ProbeUpUp: 1;				// 2-I1
	uint8_t ProbeUpDn: 1;				// 2-I2
	uint8_t ProbeDnUp: 1;				// 2-I3
	uint8_t ProbeDnDn: 1;				// 2-I4
	uint8_t IN2_5: 1; 		// 2-I5 
	uint8_t IN2_6: 1;					// 2-I6 
	uint8_t TrayForward: 1;				// 2-I7
	uint8_t TrayBackward: 1;				// 2-I8	
	
} TExtInput;

typedef struct ExtOutput		// Bit Field 이용
{
	uint8_t OUT1_9: 1;				// 1-09
	uint8_t OUT1_10: 1;				// 1-10
	uint8_t OUT1_11: 1;				// 1-11
	uint8_t OUT1_12: 1;				// 1-12
	uint8_t OUT1_13: 1;				// 1-13
	uint8_t OUT1_14: 1;				// 1-14
	uint8_t OUT1_15: 1;				// 1-15
	uint8_t OUT1_16: 1;				// 1-16
		
	uint8_t ErrorLamp: 1;		    // 1-O1
	uint8_t StartLamp: 1;  			// 1-O2
	uint8_t StopLamp: 1;			// 1-O3
	uint8_t OUT1_4: 1;				// 1-O4
	uint8_t ResetLamp: 1;			// 1-O5
	uint8_t OUT1_6: 1;				// 1-O6
	uint8_t OUT1_7: 1;				// 1-O7
	uint8_t OUT1_8: 1;				// 1-O8	



	uint8_t OUT2_9: 1;			// 2-09
	uint8_t OUT2_10: 1;			// 2-10
	uint8_t OUT2_11: 1;			// 2-11
	uint8_t Standby: 1;				// 2-12
	uint8_t OUT2_13: 1;			// 2-13
	uint8_t OUT2_14: 1;			// 2-14
	uint8_t OUT2_15: 1;		// 2-15
	uint8_t Finish: 1;				// 2-16
		
	uint8_t ProbeUpDn: 1;		    // 2-O1
	uint8_t ProbeDnUp: 1;  			// 2-O2
	uint8_t CenteringUp: 1;			// 2-O3
	uint8_t OUT2_4: 1;				// 2-O4
	uint8_t TrayForward: 1;			// 2-O5
	uint8_t OUT2_6: 1;			// 2-O6
	uint8_t OUT2_7: 1;			// 2-O7
	uint8_t OUT2_8: 1;				// 2-O8	
} TExtOutput;

class TTotalForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GrpMain;
	TClientSocket *Client;
	TTimer *ReContactTimer;
	TTimer *SendTimer;
	TGroupBox *GrpAlarm;
	TImage *Image3;
	TLabel *modAlarm1;
	TLabel *modAlarm3;
	TLabel *modAlarm4;
	TTimer *StatusTimer;
	TLabel *AlarmTime;
	TGroupBox *GrpRemeasure;
	TGroupBox *GrpError;
	TLabel *error1;
	TLabel *error3;
	TLabel *error4;
	TLabel *ErrorTime;
	TPanel *pWork;
	TTimer *rxTimer;
	TImage *Image2;
	TLabel *lblRemeasureTime;
	TListView *BadList;
	TAdvSmoothButton *AlarmConfirmBtn;
	TAdvSmoothButton *RemeasureAllBtn;
	TAdvSmoothButton *RemeasureBtn;
	TAdvSmoothButton *TrayOutBtn;
	TAdvSmoothPanel *pback;
	TPanel *pConInfo;
	TLabel *lblStatus;
	TLabel *lblTitle;
	TGroupBox *GrpLocal;
	TImage *Image5;
	TAdvSmoothButton *localTest;
	TTimer *Timer_AutoInspection;
	TAdvSmoothButton *localCali;
	TAdvSmoothButton *btnConfig;
	TGroupBox *GroupBox3;
	TPanel *pdev1;
	TPanel *pdev2;
	TPanel *pdev3;
	TPanel *pdev4;
	TPanel *pdev5;
	TPanel *pdev6;
	TPanel *pdev7;
	TPanel *pdev8;
	TPanel *clrConInfo;
	TPanel *pon;
	TPanel *poff;
	TAdvSmoothPanel *pnlConfig;
	TLabel *Label5;
	TGroupBox *GroupBox4;
	TEdit *editIROCVIPAddress;
	TPanel *Panel23;
	TPanel *Panel24;
	TEdit *editIROCVPort;
	TAdvSmoothButton *btnConnectIROCV;
	TGroupBox *GroupBox5;
	TEdit *editPLCIPAddress;
	TPanel *Panel25;
	TPanel *Panel26;
	TEdit *editPLCPortPC;
	TAdvSmoothButton *btnConnectPLC;
	TAdvSmoothButton *btnDisConnectPLC;
	TPanel *pnlportplc;
	TEdit *editPLCPortPLC;
	TAdvSmoothButton *btnCloseConnConfig;
	TAdvSmoothButton *btnSaveConnConfig;
	TImage *StatusImage;
	TGroupBox *GroupBox7;
	TPanel *Panel20;
	TProgressBar *pb;
	TPanel *Panel9;
	TPanel *pPos;
	TPanel *Panel31;
	TPanel *pIrValue;
	TPanel *Panel63;
	TPanel *pOcvValue;
	TPanel *flowChart;
	TLabel *lblProcessInfo;
	TPanel *pReady;
	TPanel *pTrayIn;
	TPanel *pBarcode;
	TPanel *pMeasure;
	TPanel *pFinish;
	TPanel *pProbeOpen;
	TPanel *pTrayOut;
	TPanel *pProbeDown;
	TAdvSmoothButton *btnReset;
	TAdvSmoothButton *btnAuto;
	TAdvSmoothButton *btnManual;
	TLabel *lblRemeasureAlarmCheck;
	TAdvSmoothButton *btnTrayOut;
	TPanel *Panel16;
	TLabel *lblTrayInfo;
	TCheckBox *chkCycle;
	TCheckBox *chkBypass;
	TPanel *Panel6;
	TPanel *Panel3;
	TPanel *Panel_State;
	TPanel *pTrayid;
	TEdit *editTrayId;
	TAdvSmoothButton *btnRemeasureInfo;
	TGroupBox *GroupBox2;
	TPanel *pnormal2;
	TPanel *pnormal1;
	TAdvSmoothPanel *AdvSmoothPanel1;
	TLabel *Label9;
	TAdvSmoothButton *AdvSmoothButton4;
	TAdvSmoothButton *AdvSmoothButton5;
	TPanel *Panel17;
	TEdit *editCellModel;
	TPanel *Panel18;
	TEdit *editLotNumber;
	TPanel *p0;
	TTimer *Timer_PLCConnect;
	TButton *Button1;
	TGroupBox *GroupBox1;
	TPanel *Panel4;
	TGroupBox *grpIrSpec;
	TLabel *Label1;
	TLabel *Label3;
	TEdit *irEdit1;
	TPanel *Panel5;
	TEdit *irEdit2;
	TGroupBox *grpOcvSpec;
	TLabel *Label2;
	TLabel *Label4;
	TEdit *ocvEdit1;
	TPanel *Panel8;
	TEdit *ocvEdit2;
	TPanel *Panel7;
	TCheckBox *RemeasureChk;
	TCheckBox *chkRemBypass;
	TPanel *Panel15;
	TEdit *editNgAlarmCount;
	TEdit *RemeasureEdit;
	TAdvSmoothButton *btnMeasureInfo;
	TPanel *pBase;
	TPanel *Panel1;
	TPanel *cl_line;
	TPanel *cl_ir;
	TPanel *cl_ocv;
	TPanel *cl_irocv;
	TPanel *pocv;
	TPanel *cl_avgover;
	TPanel *cl_badir;
	TPanel *cl_badocv;
	TPanel *cl_no;
	TGroupBox *grpIrAvg;
	TLabel *Label6;
	TLabel *Label10;
	TEdit *editIrAvg;
	TEdit *editIrRange;
	TGroupBox *grpOcvAvg;
	TLabel *Label11;
	TLabel *Label12;
	TEdit *editOcvAvg;
	TEdit *editOcvRange;
	TCheckBox *chkUseAverage;
	TPanel *cl_ce;
	TTimer *TrayDownTimer;
	TTimer *TrayUpTimer;
	TPanel *pnlIRSpec;
	TPanel *pnlOCVSpec;
	TAdvSmoothPanel *pnlTrayIn;
	TAdvSmoothPanel *pnlTrayOut;
	TAdvSmoothPanel *pnlProbeOpen;
	TAdvSmoothPanel *pnlProbeClose;
	TPanel *Panel2;
	TEdit *editRemeasureAlarmCount;
	TAdvSmoothButton *btnDisConnectIROCV;
	TGroupBox *GroupBox6;
	TEdit *editModelName;
	TCheckBox *chkCellIdBypass;
	TPanel *pPassword;
	TPanel *Panel61;
	TEdit *PassEdit;
	TAdvSmoothButton *cancelBtn2;
	TAdvSmoothButton *PasswordBtn;
	TGroupBox *GroupBox8;
	TEdit *editPwd;
	TRadioGroup *RadioGroup1;
	TRadioButton *rbSpeedMed;
	TRadioButton *rbSpeedFast;
	TRadioButton *rbSpeedSlow;
	TEdit *editMaxDelayTime;
	void __fastcall ClientConnect(TObject *Sender,
		  TCustomWinSocket *Socket);
	void __fastcall ClientDisconnect(TObject *Sender,
		  TCustomWinSocket *Socket);
	void __fastcall ClientConnecting(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall ClientError(TObject *Sender, TCustomWinSocket *Socket,
		  TErrorEvent ErrorEvent, int &ErrorCode);
	void __fastcall ReContactTimerTimer(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall btnSaveConfigClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall SendTimerTimer(TObject *Sender);
	void __fastcall ClientRead(TObject *Sender, TCustomWinSocket *Socket);
	void __fastcall btnRemeasureInfoClick(TObject *Sender);
	void __fastcall RemeasureAllBtnClick(TObject *Sender);
	//void __fastcall BitmapBtn5Click(TObject *Sender);
	void __fastcall RemeasureBtnClick(TObject *Sender);
	void __fastcall localTestClick(TObject *Sender);
	void __fastcall AlarmConfirmBtnClick(TObject *Sender);
	void __fastcall btnAutoClick(TObject *Sender);
	void __fastcall btnTrayOutClick(TObject *Sender);
	void __fastcall BadListDrawItem(TCustomListView *Sender, TListItem *Item,
          TRect &Rect, TOwnerDrawState State);
	void __fastcall StatusTimerTimer(TObject *Sender);
	void __fastcall pTrayidDblClick(TObject *Sender);
	void __fastcall editTrayIdKeyDown(TObject *Sender, WORD &Key,
		  TShiftState Shift);
	void __fastcall btnResetClick(TObject *Sender);
	void __fastcall ChInfoMouseEnter(TObject *Sender);
	void __fastcall ChInfoMouseLeave(TObject *Sender);
	void __fastcall rxTimerTimer(TObject *Sender);
	void __fastcall MainBtnClick(TObject *Sender);
	void __fastcall chkBypassMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y);
	void __fastcall btnManualClick(TObject *Sender);
	void __fastcall btnMeasureInfoClick(TObject *Sender);
	void __fastcall TrayOutBtnClick(TObject *Sender);
	void __fastcall Timer_AutoInspectionTimer(TObject *Sender);
	void __fastcall btnConfigClick(TObject *Sender);
	void __fastcall btnPLCConnectClick(TObject *Sender);
	void __fastcall btnPLCDisconnectClick(TObject *Sender);
	void __fastcall localCaliClick(TObject *Sender);
	void __fastcall btnCloseConnConfigClick(TObject *Sender);
	void __fastcall btnConnectPLCClick(TObject *Sender);
	void __fastcall btnDisConnectPLCClick(TObject *Sender);
	void __fastcall Timer_PLCConnectTimer(TObject *Sender);
	void __fastcall btnConnectIROCVClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall pReadyClick(TObject *Sender);
	void __fastcall chkUseAverageClick(TObject *Sender);
	void __fastcall btnDisConnectIROCVClick(TObject *Sender);
	void __fastcall lblTitleDblClick(TObject *Sender);
	void __fastcall PasswordBtnClick(TObject *Sender);
	void __fastcall cancelBtn2Click(TObject *Sender);
	void __fastcall PassEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall rbSpeedFastClick(TObject *Sender);
	void __fastcall GroupBox8DblClick(TObject *Sender);

private:	// User declarations
//------------ 폼 관련 -------------------//
    AnsiString Old_batch;

	TGroupBox *CurrentGrp;
	TGroupBox *OldGrp;
	void __fastcall VisibleBox(TGroupBox *grp);
	bool bconfig;

	void __fastcall MakePanel(AnsiString type);
	bool __fastcall ErrorCheck();
	//void __fastcall DisplayStatus(int status);
    void __fastcall DisplayProcess(int status, AnsiString Status_Step, AnsiString msg, bool bError = false);
    void __fastcall DisplayError(AnsiString msg, bool bError = false);
	//void __fastcall DisplaySensorInfo();
	void __fastcall SetProcessColor(int index, int clr, AnsiString result ="");
	int __fastcall GetColorIndex(TColor clr);

	// 로그 파일 관련 생성
	void __fastcall WriteSystemInfo();
	bool __fastcall ReadSystemInfo();
	bool __fastcall ReadCellInfo();
	void __fastcall WriteResultFile();
	void __fastcall WriteResultFile_MES();
	void __fastcall WriteResultFile_MES2(); //210318
	void __fastcall WriteOKNG();
	void __fastcall ErrorLog();
	void __fastcall ReadCaliboffset();           //20171202 개별보정을 위해 추가
	double __fastcall GetSigma(float values[], bool flag[], double avg, int count);

	BEGIN_MESSAGE_MAP
		MESSAGE_HANDLER(COMM_RECEIVE,		TMessage, OnReceiveStage)
	END_MESSAGE_MAP(TForm)
	//------------ IMS 관련 -------------------//
	//------------ STAGE 통신 관련 -------------------//
	queue<string> rxq;		// 수신 큐
	vector<unsigned char> TxVector;		// 전송 데이터 만들기
	TCustomWinSocket *sock;	// STAGE에 전송을 위한 소켓
	AnsiString remainMsg;

	void __fastcall OnReceiveStage(TMessage& Msg);		// 데이터 수신시 발생
	// 데이터 전송
	void __fastcall SendData(AnsiString Cmd, AnsiString Param="");
	// 전송 방식 결정 - 한번, 반복,,,
	void __fastcall MakeData(int tx_mode, AnsiString cmd="", AnsiString param="");
	int __fastcall DataCheck(AnsiString msg, AnsiString &param);

	void __fastcall ResponseError(AnsiString param);
	void __fastcall StageLocalRemeasure(bool frm = false);
	void __fastcall StageClearAlarm();
	void __fastcall StageReady();

	void __fastcall SensorInputProcess(AnsiString param);
	void __fastcall SensorOutputProcess(AnsiString param);
	int __fastcall SensorState(AnsiString cmd);
	void __fastcall EquipStatus(int cmd);
	void __fastcall InitEquipStatus(int cmd);

	void __fastcall ProcessIr(AnsiString param);
	void __fastcall InsertIrValue(int pos, float value, AnsiString result);
	void __fastcall ProcessOcv(AnsiString param);
	void __fastcall InsertOcvValue(int pos, float value);
	int __fastcall GetReslut(AnsiString result);

    TColor clAverageOver;
	TColor clNoCell;
	TColor clBadIr;
	TColor clCellError;
	TColor clLine;
	TColor clSelect;
	TColor clIrCheck;
	TColor clOcvCheck;
	TColor clBothCheck;
	TColor clMeasureFail;
	TColor clNo;
	TColor clYes;

	void __fastcall InitCellDisplay();
	void __fastcall ModChange();

    TPanel *pProcess[8];
    int NgCount;
    //* CELL SERIAL
    int nReadCellCountTime;
    int nReadCellSerialCount;
    AnsiString m_sTrayID, m_sCell_Serial[MAXCHANNEL];
    bool m_bReadCellSerial;
    int nCellSerialStep;
    void __fastcall InitCellSerial();
    void __fastcall ReadCellSerial2();
    bool __fastcall CheckTrayInfo(AnsiString trayID);
    bool __fastcall LoadTrayInfo(AnsiString trayID);
    void __fastcall SaveTrayInfo(AnsiString trayID);
    void __fastcall DeleteTrayInfo(AnsiString trayID);
    void __fastcall WriteTrayLog(AnsiString msg);
public:		// User declarations

	void __fastcall InitMeasureForm();
	void __fastcall InitMeasureFormRemeasure();
	void __fastcall InitTrayStruct();
	void __fastcall Initialization();
	void __fastcall PLCInitialization();
	void __fastcall DisplayStatus(int status);

	void __fastcall AutoInspection_Wait();
	void __fastcall AutoInspection_Measure();
	void __fastcall AutoInspection_Finish();
	void __fastcall ResultReportToPLC();

	void __fastcall OnInit();	// 초기화 요청
	void __fastcall CmdVersion();
	void __fastcall CmdEmergencyStop();
	void __fastcall CmdReset();
	void __fastcall CmdIRCell(AnsiString pos);
	void __fastcall CmdOCVCell(AnsiString pos);
	void __fastcall CmdAutoTest();
	void __fastcall CmdBattHeight(int height = 1);
	void __fastcall CmdGetSensorInfo();
	void __fastcall CmdTrayOut();
	void __fastcall CmdTrayOut_Original();
	void __fastcall CmdForceStop();
    void __fastcall CmdForceStop_Original();

	void __fastcall CmdTestMode();
	void __fastcall CmdManualMod(bool Set);
    void __fastcall CmdSpeedSet(int mode);
	void __fastcall CmdRestart();

	void __fastcall plc_Barcode();
	void __fastcall CmdStart();
	void __fastcall CmdDeviceInfo();
	void __fastcall ResponseAutoTestFinish();
	void __fastcall ReadchannelMapping();

    //* CELL SERIAL STEP
    void __fastcall ChangeCellSerialStep(int nstep);

//---------------------------------------------------------------------------
// PLC
	AnsiString PLC_IPADDRESS;
	int PLC_PCPORT;
	int PLC_PLCPORT;

	STAGE_INFO stage;
	CONFIG config;					// 환경 설정
	TRAY_INFO tray;

	TPanel *panel[400];
	TPanel *pdev[8];

	int acc_remeasure[400];
    int acc_totaluse[400];
	int remeasure_info[400];
	int precharger_okng[400];
	int chMap[401];
	int chReverseMap[401];

    //* 임시
    int acc_totaltray;
    int acc_finalng;

	int acc_cnt;
	AnsiString acc_init;
    TDateTime m_dateTime;

    int start_delay_time;
    int max_delay_time;

	int nSection, nStep, nStepCount;
	bool m_bAuto;
    bool mAuto;
	//------------ STAGE 통신 관련 -------------------//

	TExtInput  sensor;				//  센서
	TExtOutput  sensor_out;				//  센서

	SEND_DATA send;				// 전송 데이터
	queue<string> q_cmd;
	queue<string> q_param;
	queue<int> q_txMode;

	REMEASURE retest;
	void __fastcall RemeasureExcute();
	void __fastcall ReadRemeasureInfo();
	void __fastcall WriteRemeasureInfo();
	int senCnt;

	AnsiString OldSenCmd;
	AnsiString OldPLCStatus, PLCStatus, OldErrorCheckStatus, ErrorCheckStatus, OldIROCVStage, IROCVStage;

	void __fastcall ErrorMsg(int err);
	void __fastcall ProcessError(AnsiString err1, AnsiString err2,AnsiString err3,AnsiString err4);
	void __fastcall ShowAlarm(AnsiString err1, AnsiString err2, AnsiString err3 , AnsiString err4);

    void __fastcall RemeasureAlarm(int remeasure_alarm_count);
	void __fastcall WriteCommLog(AnsiString Type, AnsiString Msg);
    void __fastcall WritePLCLog(AnsiString Type, AnsiString Msg);
	void __fastcall ReadPreChargerOKNG(AnsiString trayid);

	int remLimit;
    void __fastcall VisibleSpec(bool bUseAverage);
	void __fastcall SetRemeasureList();
    void __fastcall SetRemeasureListAfter();
	void __fastcall SetRemeasureList2();
	void __fastcall AddRemeasureList();
	void __fastcall ViewRemeasureList();
    void __fastcall WriteTrayInfo();
	void __fastcall SetTrayID(AnsiString str_id);
	void __fastcall BadInfomation();
    void __fastcall WriteResultCode();
	void __fastcall WriteIROCVValue();
    void __fastcall WriteIROCVValue(int initValue);
	void __fastcall WriteIRMINMAX();

	void __fastcall DisplayTrayInfo();
    void __fastcall ShowPLCSignal(TAdvSmoothPanel *advPanel, bool bOn);
    void __fastcall CheckPassword();

	__fastcall TTotalForm(TComponent* Owner);
	bool bLocal, n_bMeasureStart;
};
//---------------------------------------------------------------------------
extern PACKAGE TTotalForm *TotalForm;
//---------------------------------------------------------------------------
#endif
