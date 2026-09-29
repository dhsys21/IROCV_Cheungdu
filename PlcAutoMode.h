#ifndef PlcAutoModeH
#define PlcAutoModeH

// Only a complete, successful PLC interface response can permit automatic inspection.
// Remember manual/disconnect transitions even if AUTO arrives before the UI status tick.
class TPlcAutoModeState
{
    bool valid;
    bool automatic;
    unsigned long resetVersion;
public:
    TPlcAutoModeState() : valid(false), automatic(false), resetVersion(0) {}
    void Observe(bool isAutomatic)
    {
        if(!isAutomatic && (!valid || automatic)) ++resetVersion;
        valid = true;
        automatic = isAutomatic;
    }
    void Invalidate()
    {
        if(valid) ++resetVersion;
        valid = false;
        automatic = false;
    }
    bool IsAutomatic() const { return valid && automatic; }
    unsigned long GetResetVersion() const { return resetVersion; }
};

#endif
