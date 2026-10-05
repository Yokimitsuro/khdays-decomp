/*
 * Ov209_WindUpFaceReset -- x3 (ov208/209/268). AI-state tick: wind up, then face the target and reset.
 * Timer state[0xb] += owner_delta; while it stays under 0x6ee, return. Once past: acquire the target
 * (020cab14) -> state[4]; if found, state[0xc] = state[0xd] = atan2 of target(+0x74) - state[3].
 * Clear the +0x60 hi-byte bits 0x82, fire attack 0 (020c9264) and hand off to the 020d180c state.
 */

#include "game/enemy_common.h"

struct hw60 { unsigned short lo : 8, hi : 8; };
extern int  Ov107_FindNearestObject(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern fx16  FX_Atan2(int x, int z);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void Ov209_AiStep_QueueAction2OnAnimEnd(void);

void Ov209_WindUpFaceReset(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int target;

    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] < 0x6ee) {
        return;
    }
    target = Ov107_FindNearestObject(*state, 0);
    state[4] = target;
    if (target != 0) {
        int a;
        VEC_Subtract((void *)(target + 0x74), (void *)state[3], v);
        a = FX_Atan2(v[0], v[2]);
        state[0xd] = a;
        state[0xc] = a;
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)(*state), 0, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov209_AiStep_QueueAction2OnAnimEnd);
}
