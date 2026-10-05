/* Advance the fade from the CONTEXT timer at +0x4ae4; once 0x4cb51 ticks have passed, restamp the
 * timer and copy next_state (+0x4ad8) into active_state (+0x4ad0). Fades OUT: the brightness
 * argument is -(elapsed / 0x4cb5), clamped at -16. Fade ramp: 16 steps over 0x4cb51 ticks (0x4cb51
 * / 0x4cb5 = 15.97), driven through SetMasterBrightnessSub with a NEGATIVE brightness. 16 is the DS
 * master brightness range -- the same 0x10 Game_RunSceneLoop writes. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    u8 pad_0000[0x4ad0];
    int active_state;
    int unknown_4ad4;
    int next_state;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac24;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);

void Ov000_TickFadeOutFromCtxTimer(void) {
    u64 elapsed =
        OS_GetTick() - *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4);

    SetMasterBrightnessSub(-(int)func_02020368(elapsed, 0x4cb5));
    if (elapsed <= 0x4cb51) {
        return;
    }

    *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4) = OS_GetTick();
    SetMasterBrightnessSub(-16);
    {
        OverlayContext *context = data_ov000_0205ac24;
        context->active_state = context->next_state;
    }
}
