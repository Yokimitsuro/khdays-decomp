/* Ov205_BeginPose5Aim: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov205_CopyScaleVec3GuardedThenAdvance(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void Ov205_BeginPose5Aim(int *node) {
    int *state = (int *)node[1];
    int local[3];
    Ov107_PostTagUpdate((Actor *)(*state), 5, 0);
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x40;
    if (state[0x10] != 0) {
        VEC_Subtract((void *)(state[0x10] + 400), (void *)state[8], local);
        int r = FX_Atan2(local[0], local[2]);
        state[0xe] = r;
        state[0xd] = r;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov205_CopyScaleVec3GuardedThenAdvance);
}
