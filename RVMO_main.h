//---------------------------------------------------------------------------

#ifndef RVMO_mainH
#define RVMO_mainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "AdvSmoothButton.hpp"
#include "AdvSmoothPanel.hpp"
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Imaging.pngimage.hpp>


#include "DEFINE.h"
#include "FormTotal.h"
#include "FormPLCInterface.h"
#include "FormLanguage.h"
#include "FormNgCountError.h"
#include "Modplc.h"
#include "Mdfunc.h"
#include "FormError.h"
#include "FormCellIdError.h"
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Grids.hpp>
//---------------------------------------------------------------------------

class TBaseForm : public TForm
{
__published:	// IDE-managed Components
	TTimer *ClockTimer;
	TTimer *FileDeleteTimer;
	TAdvSmoothButton *AdvSmoothButton1;
	TPanel *pon;
	TPanel *poff;
	TPanel *Panel1;
	TImage *Image12;
	TLabel *Label1;
	TAdvSmoothButton *advPLCInterfaceShow;
	TAdvSmoothButton *btnInit;
	TAdvSmoothPanel *AdvSmoothPanel_PLC;
	TMemo *Memo1;
	TPanel *pPassword;
	TPanel *Panel61;
	TEdit *PassEdit;
	TAdvSmoothButton *cancelBtn2;
	TAdvSmoothButton *PasswordBtn;
	TLabel *lblLineNo;
	TImage *Image1;
	TImage *Image2;
	TImage *Image3;
	TImage *Image4;
	TImage *Image5;
	TImage *Image6;
	TImage *Image7;
	TImage *Image8;
	TImage *Image9;
	TImage *Image10;
	TImage *Image11;
	TPanel *pstepInfo1;
	TRadioButton *rbKorean;
	TRadioButton *rbEnglish;
	TGroupBox *GroupBox2;
	TButton *Button1;
	TButton *Button5;
	TButton *btnNgCountErr;
	TRadioButton *rbChinese;
	TAdvSmoothButton *btnViewLog;
	TAdvSmoothButton *btnViewData;
	TCheckBox *chkTest;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ClockTimerTimer(TObject *Sender);
	void __fastcall FileDeleteTimerTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall AdvSmoothButton1Click(TObject *Sender);
	void __fastcall advPLCInterfaceShowClick(TObject *Sender);
	void __fastcall btnInitClick(TObject *Sender);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall PasswordBtnClick(TObject *Sender);
	void __fastcall cancelBtn2Click(TObject *Sender);
	void __fastcall PassEditKeyPress(TObject *Sender, System::WideChar &Key);
	void __fastcall rbKoreanClick(TObject *Sender);
	void __fastcall pstepInfo1Click(TObject *Sender);
	void __fastcall btnNgCountErrClick(TObject *Sender);
	void __fastcall Label1Click(TObject *Sender);
	void __fastcall btnViewLogClick(TObject *Sender);
	void __fastcall btnViewDataClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button5Click(TObject *Sender);


private:	// User declarations

	int __fastcall GetStageIndex(AnsiString stage);

	AnsiString __fastcall GetTrayId(AnsiString str);
	void __fastcall DisplayCell(int index, AnsiString str);

	void __fastcall MakePanel();

	int DeleteDay;
	int DeleteIndex;
	bool __fastcall DeleteLogFile(AnsiString FileName);
	bool __fastcall DeleteLogFolder(AnsiString FolderName);

	void __fastcall WriteTrayLog(AnsiString msg);

	AnsiString m_sTrayID;
	int nSection, nStep;

    int nPLCDisconnectTime;

public:		// User declarations


	TTotalForm *nForm[1];
	double DefaultOffset[1];
	double DefaultLowOffset[1];

	int ErrorCount;
	void __fastcall IncErrorCount();
	void __fastcall DecErrorCount();
	void __fastcall ReadDefaultOffset();
	void __fastcall WriteDefaultOffset();
    void __fastcall OpenFolder(UnicodeString path);

    double __fastcall Round(double val, int num);
	int __fastcall StringToInt(UnicodeString str, int def);
	double __fastcall StringToDouble(UnicodeString str, double def);
    vector<int> __fastcall StringToVector(UnicodeString str);

	TDateTime rem_date;
	TImage *statusImage[13];

	int FormCnt;
	__fastcall TBaseForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TBaseForm *BaseForm;
//---------------------------------------------------------------------------
#endif
