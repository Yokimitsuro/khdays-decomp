/*
 * Ov274_SteerHeadingGate -- x4 (ov206/207/274/275). AI-state tick: track a target, steer a stored
 * heading toward it, and once a timer lapses fire the transition if past the target.
 * Acquire target (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail (0203c634 cb=0).
 * Else: dir = normalise(target_pos(+0x190) - state[1]); state[0xf] = delta*30/30;
 * state[0x11] = atan2(dir.x, dir.z). Rebuild state[5..7]: a scalar factor + base vector from
 * 020c9f48/0202f384, scale it (01ffa724) and normalise into w. Decrement timer state[0xb] -= delta;
 * while >0, return. Then if dir . w > 0, clear *(*state[0]+0x384)+0xa8 and fire the transition
 * (0203c634 with the 020cdd78 continuation).
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern int  VEC_DotProduct(void *a, void *b);
extern void Ov274_FireAttackCOnIdle(void);

void Ov274_SteerHeadingGate(int *self) {
    int *state = (int *)self[1];
    VecFx32 v;
    VecFx32 w;
    int target;
    int factor;
    int t;

    target = Ov107_FindNearestObject(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], &v);
    VEC_Normalize(&v, &v);
    state[0xf] = *(int *)(*self + 0x2c) * 30 / 30;
    state[0x11] = FX_Atan2(v.x, v.z);
    factor = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3b4), &w);
    Vec3TransformViaTempMtx((void *)(state + 5), (void *)(*state + 0xa0), &w);
    ScaleVec3Fx12(factor, (void *)(state + 5), (void *)(state + 5));
    VEC_Normalize((void *)(state + 5), &w);
    t = state[0xb] - *(int *)(*self + 0x2c);
    state[0xb] = t;
    if (t > 0) {
        return;
    }
    if (VEC_DotProduct(&v, &w) <= 0) {
        return;
    }
    *(char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov274_FireAttackCOnIdle);
}
