/* Aim entry: pose 2 plays; with the +0x64 flag reaction 0x135/7 fires at the +8 point; with a
 * +0x44 target the +0xc / +0x10 heading turns towards it. */

#include "game/enemy_common.h"

extern void Ov107_BuildAndSendUpdate(int a, int b, int c, int d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov218_CopyScaleVec3ThenAdvanceSlot(void);

void Ov218_AimEntry(int *node) {
    int *state = (int *)node[1];
    int v[3];
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0x19] != 0) {
        Ov107_BuildAndSendUpdate(*state, 0x135, 0x7, state[2]);
    }
    if (state[0x11] != 0) {
        int r;
        VEC_Subtract((void *)(state[0x11] + 0x190), (void *)(*state + 0xb0), v);
        r = FX_Atan2(v[0], v[2]);
        state[4] = r;
        state[3] = r;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov218_CopyScaleVec3ThenAdvanceSlot);
}
