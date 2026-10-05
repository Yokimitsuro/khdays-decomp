/* Ov239_BeginAimAtTarget: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "game/enemy_common.h"

struct v3 { int x, y, z; };
extern void VEC_Subtract(const void *a, const void *b, void *c);
extern fx16 FX_Atan2(int a, int b);
extern void SetIndexedSlot(void *node, int idx, void *value);
extern void Ov239_ConfigSubStateThenAdvanceSlot_2(void);

void Ov239_BeginAimAtTarget(int *node) {
    int *state = (int *)node[1];
    struct v3 buf;
    Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
    int obj = state[0xd];
    if (obj != 0 && (*(unsigned char *)(*state + 0x1c4) & 2) == 0) {
        VEC_Subtract((const void *)(obj + 0x190), (const void *)(*state + 0xb0), &buf);
        state[3] = state[4] = FX_Atan2(buf.x, buf.z);
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov239_ConfigSubStateThenAdvanceSlot_2);
}
