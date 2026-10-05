/*
 * Ov282_AimCloseInRange -- x3. AI-state tick: aim at the target, steer, and close in until in range or
 * a timer expires. Acquire (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail. Else
 * dir = normalise(flatten_y(target(+0x190) - state[1])) (its magnitude is the planar distance);
 * state[0xa] = atan2(dir.x, dir.z). The height gap = distance - *(target+0x80) - *(state[0]+0x80).
 * factor = 020c9f48(*(*state+0x3b8), &w); build state[5..7] from *state+0xa0 (0202f384) scaled by
 * factor (01ffa724). Advance state[0xb] += owner_delta; while it is under 0x3000 AND the height gap is
 * still >= 0x2000, keep waiting. Otherwise clear the *(*state+0x384)+0xa8 flag, set state[0x14] =
 * 0x6000 and hand off to the 020d280c state.
 */

#include "game/engine.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern int  Ov107_ActionResource_GetOffsetAndScale(int obj, void *out);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern void Ov282_AimSteerFireWhenReady(void);

void Ov282_AimCloseInRange(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];
    int factor, height;
    int target = Ov107_FindNearestObject(*state, 0);

    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
    v[1] = 0;
    height = VEC_Normalize(v, v);
    state[0xa] = FX_Atan2(v[0], v[2]);
    height = height - *(int *)(state[4] + 0x80) - *(int *)(*state + 0x80);
    factor = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3b8), w);
    Vec3TransformViaTempMtx((void *)(state + 5), (void *)(*state + 0xa0), w);
    ScaleVec3Fx12(factor, (void *)(state + 5), (void *)(state + 5));
    state[0xb] += *(int *)(*self + 0x2c);
    if (state[0xb] < 0x3000 && height >= 0x2000) {
        return;
    }
    *(char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    state[0x14] = 0x6000;
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov282_AimSteerFireWhenReady);
}
