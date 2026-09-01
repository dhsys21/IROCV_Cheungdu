//---------------------------------------------------------------------------

#ifndef FormMeasureInfoH
#define FormMeasureInfoH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include "AdvSmoothButton.hpp"
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <vector>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <jpeg.hpp>
#include "AdvSmoothButton.hpp"
#include <VclTee.TeeGDIPlus.hpp>
//---------------------------------------------------------------------------
using namespace std;

typedef struct{
	int *cell;
    int *measure_result;
	float *orginal_value;
	float *after_value;
	float *ocv_value;
    int arl;
}DISPLAY_INF0;


class TMeasureInfoForm : public TForm
{
__published:	// IDE-managed Components
	TSaveDialog *SaveDialog;
	TPanel *Panel2;
	TPanel *clir;
	TPanel *clocv;
	TGroupBox *grbChannelInfo;
	TPanel *pnlChannel;
	TPanel *pch;
	TPanel *pnlPosition;
	TPanel *ppos;
	TPanel *pLocal;
	TGroupBox *grbEachChannel;
	TEdit *chEdit;
	TGroupBox *GroupBox3;
	TGroupBox *grbProbeSetting;
	TPanel *pstage;
	TPanel *cl_line;
	TChart *OcvChart;
	TLineSeries *LineSeries1;
	TPanel *pnormal2;
	TPanel *pnormal1;
	TChart *IrChart;
	TLineSeries *Series1;
	TAdvSmoothButton *btnInit;
	TAdvSmoothButton *btnProbeOpen;
	TAdvSmoothButton *btnProbeClose;
	TAdvSmoothButton *btnAuto;
	TAdvSmoothButton *btnStop;
	TAdvSmoothButton *btnOcv;
	TAdvSmoothButton *btnIr;
	TCheckBox *chkGraph;
	TGroupBox *GroupBox2;
	TAdvSmoothButton *advMSAStart;
	TAdvSmoothButton *advMSAStop;
	TLabel *Label1;
	TEdit *Edit1;
	TTimer *msaTimer;
	TTimer *probetimer;
	TAdvSmoothButton *btnSave;
	TGroupBox *grpRemeasure;
	TAdvSmoothButton *advBtnRemeasure;
	TAdvSmoothButton *advRemeasureTrayOut;
	TPanel *Panel19;
	TPanel *Panel21;
	TPanel *Panel22;
	TPanel *Panel23;
	TPanel *Panel24;
	TPanel *Panel25;
	TPanel *Panel26;
	TPanel *Panel27;
	TPanel *Panel28;
	TPanel *Panel29;
	TPanel *Panel30;
	TPanel *Panel31;
	TPanel *Panel32;
	TPanel *Panel33;
	TPanel *Panel34;
	TPanel *Panel35;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel6;
	TPanel *Panel7;
	TPanel *Panel8;
	TPanel *Panel9;
	TPanel *Panel10;
	TPanel *Panel11;
	TPanel *Panel12;
	TPanel *Panel13;
	TPanel *Panel14;
	TPanel *Panel15;
	TPanel *Panel16;
	TPanel *Panel17;
	TPanel *Panel18;
	TLabel *MSA_COUNT_CHECK;
	TImage *Image1;
	TLineSeries *Series2;
	TLineSeries *Series3;
	TLineSeries *Series4;
	TLineSeries *Series5;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btnSaveClick(TObject *Sender);
	void __fastcall btnIrClick(TObject *Sender);
	void __fastcall btnOcvClick(TObject *Sender);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall btnAutoClick(TObject *Sender);
	void __fastcall btnStopClick(TObject *Sender);
	void __fastcall btnProbeClick(TObject *Sender);
	void __fastcall PanelDblClickk(TObject *Sender);
	void __fastcall ChInfoMouseEnter(TObject *Sender);
	void __fastcall ChInfoMouseLeave(TObject *Sender);
	void __fastcall chkGraphClick(TObject *Sender);
	void __fastcall btnChartRefreshClick(TObject *Sender);
	void __fastcall Panel19Click(TObject *Sender);
	void __fastcall Panel35Click(TObject *Sender);
	void __fastcall msaTimerTimer(TObject *Sender);
	void __fastcall advMSAStartClick(TObject *Sender);
	void __fastcall advMSAStopClick(TObject *Sender);
	void __fastcall probetimerTimer(TObject *Sender);
	void __fastcall advBtnRemeasureClick(TObject *Sender);
	void __fastcall advRemeasureTrayOutClick(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);

private:	// User declarations
	void __fastcall MakePanel(AnsiString type);
	void __fastcall MakeUIPanel(AnsiString type);
	void __fastcall SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
	void __fastcall SetUIOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
//	void __fastcall MakePanel();
//	void __fastcall SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
	void __fastcall WriteResultFile(AnsiString fn, int msaIndex);
	void __fastcall WriteResultFile2(AnsiString fn, int msaIndex, int nTotalCount);
    void __fastcall MakeReportFile(AnsiString fn_data, AnsiString fn_report, int nTotalCount);
public:		// User declarations
	TPanel *pir[400];
	TPanel *pocv[400];
    TPanel *pUIx[20];
	TPanel *pUIy[20];
    int stage;
	DISPLAY_INF0 display;
	int nStep;
	int msaCount;
    AnsiString msaFN, msaReportFN;
	void __fastcall InitStruct();
	void __fastcall DisplayIrValue(int index, TColor clr, AnsiString caption);
	void __fastcall DisplayIrValue(int index, AnsiString caption);
	void __fastcall DisplayOcvValue(int index, TColor clr, AnsiString caption );
    void __fastcall initChart(int ir_min, int ir_max, int ocv_min, int ocv_max);
	__fastcall TMeasureInfoForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMeasureInfoForm *MeasureInfoForm;
//---------------------------------------------------------------------------
#endif
