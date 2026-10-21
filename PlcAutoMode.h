#ifndef PlcAutoModeH
#define PlcAutoModeH

// 정상 PLC 응답을 끝까지 받아야 자동 검사를 허용한다.
// 화면 갱신 전에 AUTO로 돌아와도 수동·단절 전환을 기억한다.
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
    bool IsValid() const { return valid; } // 읽기 전용 표시 상태. 인터록 변경 없음.
    unsigned long GetResetVersion() const { return resetVersion; }
};

#endif
