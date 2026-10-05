/* Ov240_AimAtTarget: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "game/enemy_common.h"

extern void VEC_Subtract();
extern fx16 FX_Atan2();
extern void SetIndexedSlot(void *obj, int idx, void *value);
extern void Ov240_ConfigSubStateThenAdvanceSlot(void);
void Ov240_AimAtTarget(int *node) {
    int *state = (int *)node[1];
    Ov107_PostTagUpdate((Actor *)(*state), 0x3, 0);
    if (state[0x10] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[0x10] + 0x190, state[2], buf);
        a = FX_Atan2(buf[0], buf[2]);
        state[4] = a;
        state[3] = a;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov240_ConfigSubStateThenAdvanceSlot);
}
