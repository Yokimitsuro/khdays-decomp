/* Fades the reward menu out over time, then requests the next scene and moves to state 8. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct Ov005Context { char opaque00[0x4bf0]; int menuState; u64 startTick; } Ov005Context;
extern Ov005Context *data_ov005_0205b80c;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);
void Ov005_UpdateFadeOut(void) {
    u64 elapsed=OS_GetTick()-data_ov005_0205b80c->startTick;
    SetMasterBrightnessMain(-(int)func_02020368(elapsed, 0x7fd8));
    if(elapsed>0x7fd88) {
        RequestQueue_SetOrPushKind3(16);
        SetMasterBrightnessMain(-16);
        data_ov005_0205b80c->menuState=8;
    }
}
