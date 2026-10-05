/*
 * Ov275_FireAttackCOnIdle -- x4 (ov206/207/274/275). AI-state tick: acquire the target, wind up, then
 * fire attack 0xc once the sub-node at state[3] goes idle.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/10;
 * state[0x11] = atan2(dir.x, dir.z). While the sub-node byte *(char*)state[3] is still set, return.
 * Once idle: fire attack 0xc (020c9264, flag 0) and hand off to the 020cde58 continuation.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern void Ov275_DecisionTick(void);

void Ov275_FireAttackCOnIdle(int *self) {
    int *state = (int *)self[1];
    VecFx32 v;
    int target;

    target = Ov107_FindNearestObject(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    VEC_Normalize(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 0x1e / 10;
    state[0x11] = FX_Atan2(v.x, v.z);
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0xc, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov275_DecisionTick);
}
