/* Fade out the sub-screen and advance to the finished result phase. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov005ResultContext { char unknown00[0x4b5c]; long long startTick; char unknown4b64[16]; int resultPhase; } Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
void Ov005_FadeOutResultScreen(void) {
    u64 elapsed = OS_GetTick() - data_ov005_0205b810->startTick;
    SetMasterBrightnessSub(-(int)func_02020368(elapsed, 0x7fd8));
    if (elapsed > 0x7fd88) {
        SetMasterBrightnessSub(-16);
        data_ov005_0205b810->resultPhase = 4;
    }
}
