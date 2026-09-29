#ifndef OperationViewH
#define OperationViewH

#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "OperationViewState.h"

class TTotalForm;

// Owned by the stage form. Borrows DFM controls; owns only the refresh timer.
class TOperationView : public TComponent
{
    TTotalForm *stageForm;
    TTimer *refreshTimer;
    TPanel *tiles[TOperationViewState::Count];
    TLabel *tileLabels[TOperationViewState::Count];
    TPanel *pcModePanel, *plcModePanel;
    TLabel *currentTitle, *currentDetail, *elapsedLabel, *serialLabel;
    TMemo *logMemo;
    TCheckBox *followLog;
    TOperationViewState progress;
    TOperationCycleClock cycleClock;
    AnsiString lastLog, lastWaitKey, lastSignals[12];
    UnicodeString operationLogFile;
    bool logWriteFailed;
    bool signalsKnown, plcWasValid;
    int previousCloseRequest;
    void __fastcall TimerTick(TObject *Sender);
    void __fastcall OpenLogFile(TObject *Sender);
    void __fastcall FollowLogClick(TObject *Sender);
    void Refresh();
    void DrawTiles();
    void ObserveSignals(bool valid);
    void SetCurrent(AnsiString title, AnsiString detail, bool error);
    void FinishCycle();
    bool WriteOperationLog(const UnicodeString &line);
public:
    __fastcall TOperationView(TTotalForm *owner);
    void Append(AnsiString source, AnsiString message);
    void Command(TAutoInspectionCommand command);
    void FileSaved(bool saved);
    void MeasurementStarted();
    void Reset();
};
#endif
