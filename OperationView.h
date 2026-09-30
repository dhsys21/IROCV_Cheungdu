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
    friend class TOperationCommandLogScope;
    TTotalForm *stageForm;
    TTimer *refreshTimer;
    TPanel *tiles[TOperationViewState::Count];
    TLabel *tileLabels[TOperationViewState::Count];
    TPanel *pcModePanel, *plcModePanel;
    TLabel *currentTitle, *currentDetail, *elapsedLabel, *serialLabel;
    TMemo *logMemo;
    TOperationViewState progress;
    TOperationTimeline timeline;
    TOperationCycleClock cycleClock;
    AnsiString lastLog, lastWaitKey, lastSignals[12];
    UnicodeString operationLogFile;
    bool logWriteFailed;
    bool signalsKnown, plcWasValid;
    int previousCloseRequest;
    int commandLogTile;
    void __fastcall TimerTick(TObject *Sender);
    void __fastcall OpenLogFile(TObject *Sender);
    void Refresh();
    void DrawTiles();
    int CurrentProcessTile();
    int SynchronizeTimeline();
    void BeginCommand(TAutoInspectionCommand command);
    void BeginRemeasureTimeline();
    void ObserveSignals(bool valid);
    void SetCurrent(AnsiString title, AnsiString detail, bool error);
    void FinishCycle();
    bool WriteOperationLog(const UnicodeString &line);
public:
    __fastcall TOperationView(TTotalForm *owner);
    void Append(AnsiString source, AnsiString message, int processTile = -1);
    void Command(TAutoInspectionCommand command);
    void FileSaved(bool saved);
    void MeasurementStarted();
    void Reset();
};

// Logs written inside a command retain that command's phase even though the
// automatic sequence has already advanced its step. Restore on exceptions too.
class TOperationCommandLogScope
{
    TOperationView *view;
    int previous;
public:
    TOperationCommandLogScope(TTotalForm *owner, TAutoInspectionCommand command);
    ~TOperationCommandLogScope();
};
#endif
