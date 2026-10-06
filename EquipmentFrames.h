#ifndef EquipmentFramesH
#define EquipmentFramesH
#include <string>
#include <queue>

// TCP may split one frame into any number of reads or coalesce many frames.
// BCC validation remains in ParseEquipmentMessage; no frame is manufactured here.
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
        { pending.erase(0, next); continue; } // Resync a truncated/corrupt frame.
        if(end == std::string::npos)
        {
            if(pending.size() > 4096) pending.clear(); // IR/OCV ASCII frames are much smaller.
            return;
        }
        if(end <= 4096) frames.push(pending.substr(0, end + 1));
        pending.erase(0, end + 1);
    }
}
#endif
