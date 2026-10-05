/*
 * Ov268_AimSteerDotGate -- x3. AI-state tick: set the turn rate, aim/steer, transition once the timer
 * expires and the target is in front. state[0x18] = owner_delta * 30 / 10. target = acquire(020d0ea4,
 * *state, 0) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail. Else aim = target(+0x190) - state[2],
 * state[0xd] = atan2(normalise(aim)); steer state[5..7] from *state+0xa0 (020c9f48/0202f384) scaled by
 * factor (01ffa724), then w = normalise(state[5..7]). Advance state[0xf] -= owner_delta; while it stays
 * positive return. Once expired, if dot(aim, w) <= 0 keep waiting; otherwise clear *(state[1])+0xa8 and
 * hand off to the 020d1afc state.
 */

#include "game/engine.h"

extern int  Ov268_PickBestFacingNode(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *in, void *out);
extern fx16  FX_Atan2(int x, int z);
extern int  Ov107_ActionResource_GetOffsetAndScale(int obj, void *out);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern int  VEC_DotProduct(void *a, void *b);
extern void Ov268_FaceTargetFireReadyC(void);

void Ov268_AimSteerDotGate(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];
    int factor;
    int target;

    state[0x18] = *(int *)(*self + 0x2c) * 0x1e / 10;
    target = Ov268_PickBestFacingNode(*state, 0);
    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[2], v);
    VEC_Normalize(v, v);
    state[0xd] = FX_Atan2(v[0], v[2]);
    factor = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3ac), w);
    Vec3TransformViaTempMtx((void *)(state + 5), (void *)(*state + 0xa0), w);
    ScaleVec3Fx12(factor, (void *)(state + 5), (void *)(state + 5));
    VEC_Normalize((void *)(state + 5), w);
    state[0xf] -= *(int *)(*self + 0x2c);
    if (state[0xf] > 0) {
        return;
    }
    if (VEC_DotProduct(v, w) <= 0) {
        return;
    }
    *(char *)(state[1] + 0xa8) = 0;
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov268_FaceTargetFireReadyC);
}
