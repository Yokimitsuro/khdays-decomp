/* Fades the sub screen in over time and, when done, enters state 2. */

#include "nitro/types.h"
#include "game/engine.h"

typedef struct {
    u8 pad_0000[0x4ad0];
    int active_state;
    u8 pad_4ad4[0x2c0];
    int transition_flag;
} OverlayContext;

extern OverlayContext *volatile data_ov000_0205ac24;
extern u64 OS_GetTick(void);
extern unsigned long long func_02020368(unsigned long long dividend, unsigned long long divisor);

void Ov000_TickFadeThenEnterState2(void) {
    u64 elapsed =
        OS_GetTick() - *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4);

    SetMasterBrightnessSub((int)func_02020368(elapsed, 0x4cb5) - 16);
    if (elapsed <= 0x4cb51) {
        return;
    }

    *(u64 *)((u8 *)data_ov000_0205ac24 + 0x4ae4) = OS_GetTick();
    SetMasterBrightnessSub(0);
    data_ov000_0205ac24->active_state = 2;
    data_ov000_0205ac24->transition_flag = 0;
}
