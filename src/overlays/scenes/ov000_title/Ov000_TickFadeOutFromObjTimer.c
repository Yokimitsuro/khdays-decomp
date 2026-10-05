/* Same fade-out ramp as Ov000_TickFadeOutFromCtxTimer, but driven from a small object's timestamp
 * at +0x14 rather than the big context's +0x4ae4. Pairs with Ov000_TickFadeInFromObjTimer on that
 * same object. Fade ramp: 16 steps over 0x4cb51 ticks (0x4cb51 / 0x4cb5 = 15.97), driven through
 * SetMasterBrightnessSub with a NEGATIVE brightness. 16 is the DS master brightness range -- the
 * same 0x10 Game_RunSceneLoop writes. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    u8 pad_0000[0x4bc4];
    int active_state;
    int next_state;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac28;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);

void Ov000_TickFadeOutFromObjTimer(void) {
    u64 elapsed =
        OS_GetTick() - *(u64 *)((u8 *)data_ov000_0205ac28 + 0x14);

    SetMasterBrightnessSub(-(int)func_02020368(elapsed, 0x4cb5));
    if (elapsed <= 0x4cb51) {
        return;
    }

    *(u64 *)((u8 *)data_ov000_0205ac28 + 0x14) = OS_GetTick();
    SetMasterBrightnessSub(-16);
    {
        OverlayContext *context = data_ov000_0205ac28;
        context->active_state = context->next_state;
    }
}
