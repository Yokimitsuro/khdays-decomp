/* Aimed strike entry: the +0x388 shape gains bit 1, pose 5 plays and reaction 0x135/7 fires at
 * the +8 point; with a +0x44 target the +0xc / +0x10 heading turns towards it. */

#include "game/enemy_common.h"

extern void Ov107_BuildAndSendUpdate(int a, int b, int c, int d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov218_ThrowReleaseEntry(void);

struct ov220b_LowByteFlags { unsigned bits : 8; };

void Ov218_AimedStrikeEntry(int *node) {
    int *state = (int *)node[1];
    int v[3];
    ((struct ov220b_LowByteFlags *)(*(int *)(*state + 0x388) + 8))->bits |= 2;
    Ov107_PostTagUpdate((Actor *)(*state), 0x5, 0);
    Ov107_BuildAndSendUpdate(*state, 0x135, 0x7, state[2]);
    if (state[0x11] != 0) {
        int r;
        VEC_Subtract((void *)(state[0x11] + 0x190), (void *)(*state + 0xb0), v);
        r = FX_Atan2(v[0], v[2]);
        state[4] = r;
        state[3] = r;
    }
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov218_ThrowReleaseEntry);
}
