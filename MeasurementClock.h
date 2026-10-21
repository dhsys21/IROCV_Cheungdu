#ifndef MeasurementClockH
#define MeasurementClockH

// 표시용 시간. 타이머 횟수가 아닌 통신 수신 시각으로 계산한다.
// 부호 없는 32비트 차이로 GetTickCount 순환을 처리한다.
class TMeasurementClock
{
    unsigned long started, frozen;
    bool running, received, armed;
public:
    TMeasurementClock() { Reset(); }
    void Reset() { started = frozen = 0; running = received = armed = false; }
    void Prepare() { Reset(); armed = true; } // 명시적으로 요청한 AMS만 시간을 시작한다.
    void Start(unsigned long now)
    {
        if(!armed || received) return; // 정지·초기화·AMF 이후의 지연·중복 AMS는 무시한다.
        started = now; frozen = 0; running = received = true;
    }
    unsigned long Elapsed(unsigned long now) const { return running ? now - started : frozen; }
    void Stop(unsigned long now) { frozen = Elapsed(now); running = armed = false; }
    bool IsRunning() const { return running; }
};
#endif
