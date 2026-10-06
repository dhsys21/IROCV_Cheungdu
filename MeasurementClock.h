#ifndef MeasurementClockH
#define MeasurementClockH

// Display-only clock. Protocol receipts, not timer tick counts, define its bounds.
// Unsigned 32-bit subtraction also handles GetTickCount's wraparound.
class TMeasurementClock
{
    unsigned long started, frozen;
    bool running, received, armed;
public:
    TMeasurementClock() { Reset(); }
    void Reset() { started = frozen = 0; running = received = armed = false; }
    void Prepare() { Reset(); armed = true; } // Only an explicitly requested AMS may start this clock.
    void Start(unsigned long now)
    {
        if(!armed || received) return; // Ignore late/duplicate AMS after stop/reset/AMF.
        started = now; frozen = 0; running = received = true;
    }
    unsigned long Elapsed(unsigned long now) const { return running ? now - started : frozen; }
    void Stop(unsigned long now) { frozen = Elapsed(now); running = armed = false; }
    bool IsRunning() const { return running; }
};
#endif
