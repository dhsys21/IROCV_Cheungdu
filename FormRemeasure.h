//---------------------------------------------------------------------------

#ifndef FormRemeasureH
#define FormRemeasureH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Buttons.hpp>
#include <jpeg.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include "AdvSmoothButton.hpp"
//---------------------------------------------------------------------------


class TRemeasureForm : public TForm
{
__published:	// IDE-managed Components
	TSaveDialog *SaveDialog;
	TLabel *Label3;
	TGroupBox *GroupBox2;
	TPanel *Panel40;
	TPanel *pAccDate;
	TPanel *pstage;
	TPanel *pcolor1;
	TPanel *pcolor2;
	TPanel *pcolor4;
	TAdvSmoothButton *AccInitBtn;
	TPanel *Panel2;
	TPanel *cl_line;
	TPanel *pnormal2;
	TPanel *pnormal1;
	TPanel *Panel3;
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
	TPanel *Panel1;
	TLabel *Label1;
	TLabel *Label2;
	TPanel *Panel20;
	TPanel *pChannel;
	TPanel *Panel37;
	TPanel *pPos;
	TPanel *Panel39;
	TPanel *pNgTotalUse;
	TGroupBox *GroupBox1;
	TPanel *Panel44;
	TPanel *pnlTotalTray;
	TPanel *Panel36;
	TPanel *pnlFinalNg;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall FormHide(TObject *Sender);
	void __fastcall chInitdblClick(TObject *Sender);
	void __fastcall AccInitBtnClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall ChInfoMouseClick(TObject *Sender);
private:	// User declarations
	void __fastcall DrawChannelTitle(AnsiString type);
	void __fastcall MakePanel(AnsiString type);
	void __fastcall MakeUIPanel();
	void __fastcall SetOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
	void __fastcall SetUIOption(TPanel *pnl, int nx, int ny, int nw, int nh, int index);
	void __fastcall RefreshForm();

	TColor clLine, clLast, clSelect;
	int mode;


public:		// User declarations
	int *acc_remeasure;
	AnsiString *acc_init;

	int *acc_cnt;
    int *acc_totaluse;

    int *acc_totaltray;
    int *acc_finalng;

	TPanel *pre[400];
	TPanel *pch[400];
	TPanel *pUIx[20];
	TPanel *pUIy[20];
	int stage;

	__fastcall TRemeasureForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TRemeasureForm *RemeasureForm;
//---------------------------------------------------------------------------
#endif
