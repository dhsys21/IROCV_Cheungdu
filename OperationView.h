#ifndef OperationViewH
#define OperationViewH

#include <Classes.hpp>
#include <StdCtrls.hpp>
#include <ExtCtrls.hpp>
#include "OperationViewState.h"

class TTotalForm;

// 폼의 표시 제어기를 참조하며 새로고침 타이머만 소유한다.
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
    void SetCurrent(UnicodeString title, UnicodeString detail, bool error);
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

// 시퀀스가 다음 단계여도 명령 내부 로그는 현재 명령 단계로 남긴다.
// 예외 발생 시에도 이전 단계를 복원한다.
class TOperationCommandLogScope
{
    TOperationView *view;
    int previous;
public:
    TOperationCommandLogScope(TTotalForm *owner, TAutoInspectionCommand command);
    ~TOperationCommandLogScope();
};
#endif
