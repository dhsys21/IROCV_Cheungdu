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
#include "AutoInspectionSequence.h"
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

class TOperationView;

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
	TTimer *Timer_AutoInspection;
    TTimer *Timer_ResultSave;
    TGroupBox *grpCellSerialReadMode;
    TCheckBox *chkCellSerialContinuousRead;
    TLabel *lblCellSerialReadMode;
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
	TAdvSmoothButton *btnReset;
	TAdvSmoothButton *btnAuto;
	TAdvSmoothButton *btnManual;
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
	TPanel *Panel15;
	TEdit *editNgAlarmCount;
    TEdit *editProbeRemeasureCount;
    TLabel *lblProbeRemeasureCount;
    TEdit *editClosedProbeRemeasureMaxNgCount;
    TLabel *lblClosedProbeRemeasureMaxNgCount;
    TLabel *lblRemeasureSettingsHelp;
	TAdvSmoothButton *btnMeasureInfo;
	TPanel *pBase;
	TPanel *Panel1;
	TPanel *cl_line;
	TPanel *cl_ir;
	TPanel *cl_ocv;
	TPanel *cl_irocv;
	TPanel *pocv;
	TPanel *cl_badir;
	TPanel *cl_badocv;
	TPanel *cl_no;
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
    TPanel *pnlLegacyDisplay;
    TGroupBox *grpOperationProcess;
    TGroupBox *grpOperationCurrent;
    TGroupBox *grpOperationLog;
    TPanel *pnlOperationPcMode;
    TPanel *pnlOperationPlcMode;
    TLabel *lblOperationSerial;
    TLabel *lblOperationTitle;
    TLabel *lblOperationDetail;
    TLabel *lblOperationElapsed;
    TMemo *memoOperationLog;
    TButton *btnOperationLogFile;
    TPanel *pOpReady;
    TLabel *lblOpReady;
    TPanel *pOpTrayIn;
    TLabel *lblOpTrayIn;
    TPanel *pOpTrayId;
    TLabel *lblOpTrayId;
    TPanel *pOpCellData;
    TLabel *lblOpCellData;
    TPanel *pOpCloseRequest;
    TLabel *lblOpCloseRequest;
    TPanel *pOpCloseConfirmed;
    TLabel *lblOpCloseConfirmed;
    TPanel *pOpMeasure;
    TLabel *lblOpMeasure;
    TPanel *pOpFileSave;
    TLabel *lblOpFileSave;
    TPanel *pOpResultTransmit;
    TLabel *lblOpResultTransmit;
    TPanel *pOpComplete;
    TLabel *lblOpComplete;
    TPanel *pOpOpenRequest;
    TLabel *lblOpOpenRequest;
    TPanel *pOpOpenConfirmed;
    TLabel *lblOpOpenConfirmed;
    TPanel *pOpOutRequest;
    TLabel *lblOpOutRequest;
    TPanel *pOpOutConfirmed;
    TLabel *lblOpOutConfirmed;
    // IDE 관리 영역: 컴포넌트 선언은 위에, 이벤트 함수 선언은 아래에 모은다.
    // 이벤트 선언 뒤에 컴포넌트를 추가하면 폼 디자이너가 해석하지 못할 수 있다.
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
	void __fastcall RemeasureBtnClick(TObject *Sender);
	void __fastcall AlarmConfirmBtnClick(TObject *Sender);
	void __fastcall btnAutoClick(TObject *Sender);
	void __fastcall btnTrayOutClick(TObject *Sender);
	void __fastcall BadListDrawItem(TCustomListView *Sender, TListItem *Item,
          TRect &Rect, TOwnerDrawState drawState);
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
    void __fastcall Timer_ResultSaveTimer(TObject *Sender);
	void __fastcall btnConfigClick(TObject *Sender);
	void __fastcall localCaliClick(TObject *Sender);
	void __fastcall btnCloseConnConfigClick(TObject *Sender);
	void __fastcall btnConnectPLCClick(TObject *Sender);
	void __fastcall btnDisConnectPLCClick(TObject *Sender);
	void __fastcall Timer_PLCConnectTimer(TObject *Sender);
	void __fastcall btnConnectIROCVClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall btnDisConnectIROCVClick(TObject *Sender);
	void __fastcall PasswordBtnClick(TObject *Sender);
	void __fastcall cancelBtn2Click(TObject *Sender);
	void __fastcall PassEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall rbSpeedFastClick(TObject *Sender);
	void __fastcall GroupBox8DblClick(TObject *Sender);

private:
    // newGui is an observer only; production decisions stay in Stage_* / sequence.
    friend class TOperationView;
    friend class TOperationCommandLogScope;
    TOperationView *operationView;
    void __fastcall CreateOperationView();
    void __fastcall ResetOperationView();
    void __fastcall RecordOperationCommand(TAutoInspectionCommand command);
    void __fastcall RecordOperationFileSave(bool saved);
    void __fastcall RecordOperationMeasurementStart();
    void __fastcall AppendOperationLog(AnsiString type, AnsiString message);
    // 디자이너 이벤트 정의는 반드시 FormTotal.cpp에 둔다. 아래는 역할별 파일의 실제 처리 함수.
    // Stage_AutoInspection.cpp: 자동측정 타이머 처리. Timer_AutoInspectionTimer에서 한 번 호출한다.
    void __fastcall ProcessAutoInspection(TObject *Sender);
    // Stage_Measurement.cpp: 시리얼 수신·결과 저장·PLC 완료 대기. Timer_ResultSaveTimer에서 한 번 호출한다.
    void __fastcall ProcessResultSave(TObject *Sender);
    // Stage_Form.cpp: 설비 상태·알람·PLC 표시 갱신. StatusTimerTimer에서 한 번 호출한다.
    void __fastcall ProcessStageStatus(TObject *Sender);
    // Stage_comm.cpp: 측정장비 연결 완료. ClientConnect에서 한 번 호출한다.
    void __fastcall ProcessEquipmentConnected(TObject *Sender, TCustomWinSocket *Socket);
    // Stage_comm.cpp: 측정장비 연결 진행. ClientConnecting에서 한 번 호출한다.
    void __fastcall ProcessEquipmentConnecting(TObject *Sender, TCustomWinSocket *Socket);
    // Stage_comm.cpp: 측정장비 소켓 오류. ClientError에서 한 번 호출한다.
    void __fastcall ProcessEquipmentSocketError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent, int &ErrorCode);
    // Stage_comm.cpp: 측정장비 연결 해제. ClientDisconnect에서 한 번 호출한다.
    void __fastcall ProcessEquipmentDisconnected(TObject *Sender, TCustomWinSocket *Socket);
    // Stage_comm.cpp: 측정장비 재접속. ReContactTimerTimer에서 한 번 호출한다.
    void __fastcall ProcessEquipmentReconnect(TObject *Sender);
    // Stage_comm.cpp: 측정장비 수신 프레임 분리. ClientRead에서 한 번 호출한다.
    void __fastcall ProcessEquipmentSocketRead(TObject *Sender, TCustomWinSocket *Socket);
    // Stage_comm.cpp: 측정장비 수신 큐 처리. rxTimerTimer에서 한 번 호출한다.
    void __fastcall ProcessEquipmentReceiveQueue(TObject *Sender);
    // Stage_comm.cpp: 측정장비 송신 큐 처리. SendTimerTimer에서 한 번 호출한다.
    void __fastcall ProcessEquipmentSendQueue(TObject *Sender);
    // [CELL SERIAL 공통] 트레이 초기화 시 확정한 모드. 검사 도중 설정 저장으로 바꾸지 않는다.
    bool cellSerialContinuousReadForTray;
    // Stage_Measurement.cpp: 자동/수동 공통 결과 마감. 상태에 따라 시리얼/PLC 타이머를 진행한다.
    TResultSaveStep resultSaveStep; // 파일/시리얼/PLC 완료 대기를 한 상태로 관리.
    DWORD resultSaveStartTime; // 현재 비동기 대기 시작 시각(ms).
    AnsiString resultFileName; // 같은 트레이 재측정은 같은 파일을 덮어쓴다.
    bool trayResultCounted; // 생산 트레이 수는 한 번만 집계한다.
    int countedFinalIrNg; // 재측정으로 바뀐 최종 IR/접촉 NG 누계를 보정한다.
    // [CELL SERIAL 공통] 저장 설정을 다음 트레이/대기 상태에 적용한다.
    void __fastcall ApplyCellSerialReadMode();
    // [CELL SERIAL 공통] 결과 저장용 새 전체 수신을 요청하고 전용 타이머로 완료를 기다린다.
    void __fastcall StartResultCellSerialRead();
    // 초기화/강제 배출 시 모든 지연 저장·완료 신호를 취소한다.
    void __fastcall CancelResultSave();
    // 상시 읽기 결과 검사: 개수 불일치/타임아웃은 로그만 기록하고 오류창 없이 저장.
    void __fastcall CompleteResultCellSerialRead();
    // NG/PLC 버퍼/파일 작성. 수동 또는 상시 읽기 타임아웃은 true로 호출해 ID 없이 저장.
    // 실제 COMPLETE는 Timer_ResultSave에서 지연 출력한다.
    void __fastcall WriteMeasurementResults(bool saveWithoutCellSerial = false);
    // 측정값만으로 현재 셀 판정. 이전 색상/이전 불량의 영향을 받지 않는다.
    int __fastcall JudgeCellResult(int index);
    // 불량 셀마다 IR/OCV 두 항목의 요청을 준비한다. 최종 판정값은 변경하지 않는다.
    void __fastcall PrepareRemeasureItems();
    // ===== 데이터: 기존 접근 범위 유지 =====
    // 현재 표시 중인 화면 그룹.
    TGroupBox *CurrentGrp;
    // 오류창을 닫을 때 복귀할 이전 화면 그룹.
    TGroupBox *OldGrp;
    // 현재 자동 검사 단계/설정: 외부 폼에서는 직접 변경하지 않는다.
    TAutoInspectionSequence autoInspection;
    // 자동측정 처리 함수 실행 중 여부. 설비의 전체 측정 기간을 뜻하지 않는다.
    bool isAutoInspectionProcessing;
    // 현재 단계에서 읽은 트레이 ID.
    AnsiString autoInspectionTrayId;
    // 장비 수신 문자열 큐.
    queue<string> rxq;
    // 장비 송신 프레임 구성 버퍼.
    vector<unsigned char> TxVector;
    // 현재 연결된 장비 소켓.
    TCustomWinSocket *sock;
    // 프레임 경계에 걸친 미처리 수신 문자열.
    AnsiString remainMsg;
    TColor clNoCell;
    TColor clBadIr;
    TColor clCellError;
    TColor clLine;
    TColor clIrCheck;
    TColor clOcvCheck;
    TColor clBothCheck;
    TColor clMeasureFail;
    // 시작 화면 안내 번호 표시. 트레이 투입/측정 시작 이후에는 미수신 항목을 공란으로 유지한다.
    bool showStartupChannelNumbers;
    // IR 실제 수신 여부: 수신한 채널만 측정값 표시.
    bool irValueReceived[MAXCHANNEL];
    // OCV 실제 수신 여부: IR과 별도로 수신한 채널만 측정값 표시.
    bool ocvValueReceived[MAXCHANNEL];
    // NG 오류창 기준 개수: 존재 셀의 IR/OCV/접촉 불량만 집계.
    int measurementNgCount;

    // 장비 수신 메시지와 C++ 처리 함수 연결
    BEGIN_MESSAGE_MAP
    MESSAGE_HANDLER(COMM_RECEIVE,		TMessage, ProcessEquipmentMessage)
    END_MESSAGE_MAP(TForm)

    // ===== Stage_AutoInspection.cpp =====
    // 메인 화면 수동 배출: 재측정 목록 정리, 강제 배출, PROBE CLOSE=0 / OPEN=1 / COMPLETE=1.
    void __fastcall ProcessManualTrayOut();
    // 자동측정 대기 설정 읽기: 기존 200ms 타이머 호출 횟수 단위를 유지한다.
    TAutoInspectionSetting __fastcall GetAutoInspectionSetting();
    // PLC 신호·운전 옵션·검사 수량을 읽는다. 시리얼은 전체 수신 완료 후 버퍼에서 읽는다.
    TAutoInspectionData __fastcall ReadAutoInspectionData();
    // 단계 판단에서 반환한 명령을 한 번 실행한다. 실제 PLC 출력·측정 시작·오류창은 이곳에서 처리한다.
    void __fastcall RunAutoInspectionCommand(TAutoInspectionCommand command,
        const TAutoInspectionData &data);
    // 단계가 바뀔 때 이전/다음 단계와 전환 이유를 PLC 로그에 기록한다.
    void __fastcall WriteAutoStepLog(TAutoInspectionStep previous, AnsiString reason);
    // 자동측정 단계와 NG 개수를 초기화한다. PLC 출력과 트레이 데이터 초기화는 InitializeInspection에서 한다.
    void __fastcall ResetAutoInspection();
    void __fastcall UpdateAutoInspectionMode();
    bool __fastcall IsAutoInspectionBlocked();
    void __fastcall ResetAutoInspectionForPlcMode();
    bool autoInspectionBlockedByPlc;
    unsigned long lastPlcAutoResetVersion;
    // 운전 모드에 따라 PLC AUTO READY 신호 설정: 자동=1, 수동=0. 값이 바뀔 때만 기록한다.
    void __fastcall SetAutoReadySignalToPLC();
    // PLC CELL DATA 25워드의 비트맵으로 400셀 유무와 개수를 읽는다. Cycle 모드는 전 채널 사용.
    void __fastcall ReadAutoCellData();
    // CELL SERIAL 4,010워드 분할 수신 시작. 별도 START/COMPLETE 핸드셰이크는 사용하지 않는다.
    void __fastcall StartAutoCellSerialRead();
    // PLC 프로브 열림 확인 후 PC의 PROBE OPEN 요청을 0으로 해제한다.
    void __fastcall ClearProbeOpenSignalToPLC();
    // 현재 단계의 화면 문구와 MEASURING 신호를 갱신한다. 프로브/배출 동작을 새로 시작하지 않는다.
    void __fastcall DisplayAutoInspectionStep();
    // 예외 발생 단계와 원인을 기록하고 PC 자동 진행을 정지한다. 설비 비상정지 명령은 아니다.
    void __fastcall StopAutoInspectionOnError(AnsiString message);
    // 결과 처리 함수 종료를 시퀀스에 알린다. 이후 PLC 프로브 열림을 확인해야 자동 배출한다.
    void __fastcall SetAutoMeasurementComplete();
    // 재측정 가능 단계인지 확인하고 이전 측정 완료/프로브 열림 요청을 초기화한다.
    bool __fastcall PrepareAutoRemeasure();

    // ===== Stage_Measurement.cpp =====
    // 전체 재측정 요청: 트레이 ID를 유지하고 데이터 초기화·CELL DATA 재읽기 후 프로브 닫힘을 기다린다.
    void __fastcall StartFullRemeasure();
    // 선택 재측정 요청: 기존 불량 목록을 사용하고 프로브 닫힘 확인 후 채널별 재측정을 시작한다.
    void __fastcall StartSelectedRemeasure();
    // IR 응답 문자열을 값/채널로 해석하고 일반 측정 또는 교정 화면에 전달한다.
    void __fastcall ProcessIr(AnsiString param);
    // 채널 IR 수신 처리: 보정·판정·수신 표시를 갱신한다. 화면은 수신 여부와 현재 측정값으로 갱신한다.
    void __fastcall InsertIrValue(int pos, float value, AnsiString result);
    // OCV 응답 문자열을 값/채널로 해석하고 채널 판정 및 필요 시 다음 재측정을 진행한다.
    void __fastcall ProcessOcv(AnsiString param);
    // 채널 OCV 수신 처리: 규격 판정·화면을 갱신한다.
    void __fastcall InsertOcvValue(int pos, float value);
    // 장비의 GO/HI/LO/CE 등 판정 문자를 기존 내부 결과 코드로 변환한다.
    int __fastcall GetResult(AnsiString result);

    // ===== Stage_TrayData.cpp =====
    // 수신 버퍼의 400셀 시리얼을 복사하고 비어 있지 않은 개수를 반환한다. 완료 판정은 호출부에서 한다.
    int __fastcall ReadCellSerial();
    // 트레이 ID의 .Tray 파일에서 셀 시리얼을 복원한다. 파일이 없으면 false.
    bool __fastcall LoadTrayInfo(AnsiString trayID);
    // 현재 트레이의 400셀 시리얼을 .Tray 파일에 저장한다.
    void __fastcall SaveTrayInfo(AnsiString trayID);
    // 배출 완료한 트레이의 임시 .Tray 파일을 삭제한다.
    void __fastcall DeleteTrayInfo(AnsiString trayID);

    // ===== Stage_CellDisplay.cpp =====
    // 설비 배치 타입에 맞춰 메인 화면의 400채널 패널을 생성한다.
    void __fastcall MakePanel();
    // 셀 유무/판정 색상 갱신. 시작 안내 번호/트레이 투입 후 공란/각각 수신한 실제 값을 표시한다.
    void __fastcall UpdateCellDisplay(int index);
    // 수신 표시 초기화. 프로그램 시작은 번호, 트레이 투입/측정 이후는 공란.
    void __fastcall InitializeCellDisplay();

    // ===== Stage_comm.cpp =====
    // 장비 응답 분기: AMS/AMF/IR/OCV/센서 상태 등을 해당 처리 함수로 전달한다.
    void __fastcall ProcessEquipmentMessage(TMessage& Msg);
    void __fastcall SendData(AnsiString Cmd, AnsiString Param="");
    void __fastcall MakeData(int tx_mode, AnsiString cmd="", AnsiString param="");
    int __fastcall ParseEquipmentMessage(AnsiString msg, AnsiString &param);
    // 장비의 로컬 재측정 요청을 처리하고 기존 불량 개수에 따라 재측정 모드를 정한다.
    void __fastcall ProcessOpBoxRemeasureRequest(bool frm = false);
    // 센서 입력 응답을 저장하고 장비 상태 변경을 감지한다.
    void __fastcall ProcessSensorInput(AnsiString param);
    // 장비 센서 출력 응답을 센서 출력 버퍼에 저장한다.
    void __fastcall ProcessSensorOutput(AnsiString param);
    int __fastcall SensorState(AnsiString cmd);
    // 장비 상태 코드 변경에 따른 기존 화면/명령 처리를 수행한다.
    void __fastcall EquipStatus(int cmd);
    // 최초 센서 응답의 운전 상태를 초기 화면에 반영한다.
    void __fastcall InitEquipStatus(int cmd);
    // 예약된 Auto/Remote/Local 운전 모드를 적용한다.
    void __fastcall ModChange();

    // ===== Stage_Form.cpp =====
    // 메인/재측정/오류 그룹을 전환하고 오류 화면 표시 개수를 갱신한다.
    void __fastcall ShowPanelGroup(TGroupBox *grp);
    void __fastcall RefreshStageStatusImage();
    void __fastcall DisplayProcess(AnsiString Status_Step, AnsiString msg, bool bError = false);
    void __fastcall DisplayError(AnsiString msg, bool bError = false);
    // Stage_Form.cpp: 자동은 true일 때 진행 보류, 수동은 오류 표시만 수행한다.
    bool __fastcall CheckAutoInspectionError();
    bool __fastcall CheckManualInspectionError();
    void __fastcall ResponseError(AnsiString param);

    // ===== Stage_log.cpp =====
    void __fastcall WriteSystemInfo();
    void __fastcall ReadSystemInfo();
    bool __fastcall ValidateConnectionSettings(bool equipment, bool plc);
    void __fastcall ApplyConnectionSettings(bool equipment, bool plc);
    void __fastcall ReadCellInfo();
    bool __fastcall WriteResultFile(); // 파일 쓰기 1회. 실패 시 false, 재시도 정책은 호출부.
    void __fastcall WriteErrorLog();
    void __fastcall ReadCalibrationOffsets();

public:
    // ===== 데이터: 기존 접근 범위 유지 =====
    AnsiString PLC_IPADDRESS;
    int PLC_PCPORT;
    int PLC_PLCPORT;
    STAGE_INFO stage;
    CONFIG config;
    TRAY_INFO tray;
    TPanel *panel[MAXCHANNEL];
    TPanel *pdev[8];
    int acc_remeasure[MAXCHANNEL];
    int acc_totaluse[MAXCHANNEL];
    int chMap[MAXCHANNEL + 1];
    int chReverseMap[MAXCHANNEL + 1];
    int acc_totaltray;
    int acc_finalng;
    int acc_cnt;
    AnsiString acc_init;
    // 현재 트레이 검사 시작 시각.
    TDateTime m_dateTime;
    TExtInput  sensor;
    TExtOutput  sensor_out;
    SEND_DATA send;
    queue<string> q_cmd;
    queue<string> q_param;
    // 현재 트레이의 재측정 대상/진행 정보.
    REMEASURE retest;
    int senCnt;
    AnsiString OldSenCmd;
    AnsiString OldPLCStatus, PLCStatus, OldErrorCheckStatus;
    // 수동 측정 운전 여부.
    bool bLocal;

    // ===== FormTotal.cpp =====
    __fastcall TTotalForm(TComponent* Owner);

    // ===== Stage_AutoInspection.cpp =====
    // 자동 검사 전체 초기화: PLC 출력 → 트레이 데이터 → 단계 순서로 초기화한다.
    void __fastcall InitializeInspection();
    // 자동 배출 판단: Auto/프로브 열림/결과 완료를 확인하고 NG 조건에 따라 오류 대기 또는 배출한다.
    void __fastcall ProcessAutoTrayOut();
    // 수동 또는 운영자가 승인한 배출: NG를 다시 검사하지 않고 TRAY OUT을 요청한다.
    void __fastcall ForceTrayOut();
    // NG 오류창 Restart: PLC·트레이·자동 단계를 초기화하고 TRAY IN부터 다시 검사한다.
    void __fastcall RestartAutoInspection();
    // 시리얼 오류창 SAVE: 현재 데이터를 저장하고 프로브 닫힘 확인 단계로 진행한다.
    void __fastcall AcceptCellSerialData();
    // 시리얼 오류창 CANCEL: 대기 횟수를 초기화하고 4,010워드를 처음부터 다시 수신한다.
    void __fastcall RetryCellSerialRead();

    // ===== Stage_Measurement.cpp =====
    // 수동 측정 초기화: 내부 값은 0, 화면은 수신 전까지 공란.
    void __fastcall ResetMeasurementData();
    // 전체 측정 시작: 표시·수신 플래그를 초기화하고 AMS 명령을 예약한다.
    void __fastcall CmdStartMeasurement();
    // 결과 마감: STP/프로브 열림 요청 → NG·결과 코드·값·파일 작성 → COMPLETE → 자동 단계 완료 통지.
    void __fastcall FinishMeasurement();
    // [CELL SERIAL 공통] 수동/MSA 반복 측정도 이전 결과 저장 대기가 끝난 뒤 다음 측정을 시작한다.
    bool IsWaitingForResultSave() const {
        return resultSaveStep == RESULT_WAIT_SERIAL ||
               resultSaveStep == RESULT_WRITE_FILE || resultSaveStep == RESULT_WAIT_PLC_SEND;
    }
    // AMF 수신 후 처리: 운전 모드에 따라 결과 마감 또는 기존 자동 개별 재측정을 수행한다.
    void __fastcall ProcessMeasurementCompleteResponse();
    // 재측정 목록의 다음 IR/OCV를 요청한다. 더 없으면 최종 판정과 결과 마감을 수행한다.
    void __fastcall ExecuteRemeasure();
    // 전체 측정 후 재측정 대상 집계. SiteConfig.h의 개수 조건에 따라 개별 재측정 또는 결과 마감한다.
    void __fastcall SetRemeasureList();
    // 개별 재측정 후 최종 불량 목록을 다시 집계한다. 측정 명령은 보내지 않는다.
    void __fastcall SetRemeasureListAfter();

    // ===== Stage_PlcData.cpp =====
    // PC→PLC 검사 출력과 결과 버퍼 초기화. 기존 주소·초기값·출력 순서를 유지한다.
    void __fastcall InitializePlcData();
    // 최종 판정으로 PLC NG 비트/코드/수량을 함께 작성. measurementNgCount는 실제 셀의 불량만 센다.
    void __fastcall UpdatePlcResults();
    // IR/OCV 값을 PLC 결과 버퍼에 쓴다. 인자 없는 함수는 측정값, int 인자는 초기화 값이다.
    void __fastcall WriteIROCVValue();
    // IR/OCV 값을 PLC 결과 버퍼에 쓴다. 인자 없는 함수는 측정값, int 인자는 초기화 값이다.
    void __fastcall WriteIROCVValue(int initValue);
    // 현재 IR/OCV 규격 상·하한을 기존 배율로 PLC 설정 버퍼에 기록한다.
    void __fastcall WritePlcSpecifications();

    // ===== Stage_TrayData.cpp =====
    // 새 트레이 초기화: 시리얼 모드 확정/지연 저장 취소, 데이터와 수신 표시 초기화.
    void __fastcall InitializeTrayData();

    // ===== Stage_CellDisplay.cpp =====
    // 측정정보 창 재표시. 수신값과 미수신 공란(프로그램 시작 전에는 안내 번호)을 유지한다.
    void __fastcall InitializeMeasureForm();
    // CELL DATA의 셀 유무를 채널 화면에 반영한다. 측정값 수신 여부는 변경하지 않는다.
    void __fastcall DisplayTrayInfo();

    // ===== Stage_comm.cpp =====
    void __fastcall CmdReset();
    void __fastcall CmdIRCell(AnsiString pos);
    void __fastcall CmdOCVCell(AnsiString pos);
    void __fastcall CmdBattHeight(int height = 1);
    void __fastcall CmdSetManualMode(bool Set);
    void __fastcall CmdSetSpeed(int mode);
    void __fastcall CmdStart();

    // ===== Stage_Form.cpp =====
    void __fastcall DisplayStatus(int status);
    void __fastcall DisplayStageError(int err);
    void __fastcall ProcessError(AnsiString err1, AnsiString err2,AnsiString err3,AnsiString err4);
    // PLC 입력 신호 ON/OFF를 표시등 색상으로 반영한다.
    void __fastcall DisplayPlcSignal(TAdvSmoothPanel *advPanel, bool bOn);
    // 입력 암호를 확인한 뒤 설정 화면의 접근을 허용하거나 오류 문구를 표시한다.
    void __fastcall CheckPassword();

    // ===== Stage_log.cpp =====
    // mapping.csv에서 장비↔화면 채널 매핑을 읽고, 파일이 없으면 기본 매핑을 만든다.
    void __fastcall ReadChannelMapping();
    void __fastcall ReadRemeasureInfo();
    void __fastcall WriteRemeasureInfo();
    void __fastcall UpdateRemeasureAlarm(int remeasure_alarm_count);
    void __fastcall WriteCommLog(AnsiString Type, AnsiString Msg);
    void __fastcall WritePlcLog(AnsiString Type, AnsiString Msg);

};
//---------------------------------------------------------------------------
extern PACKAGE TTotalForm *TotalForm;
//---------------------------------------------------------------------------
#endif
