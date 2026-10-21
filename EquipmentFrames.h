#ifndef EquipmentFramesH
#define EquipmentFramesH
#include <string>
#include <queue>

// TCP 프레임은 나뉘어 오거나 여러 개가 한 번에 올 수 있다.
// BCC는 ParseEquipmentMessage에서 검증하며 여기서 프레임을 만들지 않는다.
inline void AppendEquipmentFrames(std::string &pending, const std::string &bytes,
    std::queue<std::string> &frames)
{
    pending += bytes;
    for(;;)
    {
        std::string::size_type start = pending.find('\x02');
        if(start == std::string::npos) { pending.clear(); return; }
        if(start) pending.erase(0, start);
        std::string::size_type end = pending.find('\x03');
        std::string::size_type next = pending.find('\x02', 1);
        if(next != std::string::npos && (end == std::string::npos || next < end))
        { pending.erase(0, next); continue; } // 잘리거나 손상된 프레임 이후부터 다시 맞춘다.
        if(end == std::string::npos)
        {
            if(pending.size() > 4096) pending.clear(); // IR/OCV ASCII 프레임은 이보다 훨씬 작다.
            return;
        }
        if(end <= 4096) frames.push(pending.substr(0, end + 1));
        pending.erase(0, end + 1);
    }
}
#endif
