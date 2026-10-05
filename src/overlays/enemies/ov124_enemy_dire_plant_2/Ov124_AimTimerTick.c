/* Ov124_AimTimerTick: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "game/enemy_common.h"

struct hw60 { unsigned short lo : 8, hi : 8; };
extern int Ov124_FindTarget(void *obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov124_AiQueue2OnFlagClear(void);

void Ov124_AimTimerTick(int *node) {
    int a = node[0];
    int *state = (int *)node[1];
    int buf[3];
    int v = state[0xa] + *(int *)(a + 0x2c);
    state[0xa] = v;
    if (v < 0x6ee) return;
    {
        int r = Ov124_FindTarget(*state, 0);
        state[9] = r;
        if (r != 0) {
            VEC_Subtract((void *)(r + 0x74), (void *)state[5], buf);
            state[6] = FX_Atan2(buf[0], buf[2]);
        }
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)(*state), 0, 0);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov124_AiQueue2OnFlagClear);
}
