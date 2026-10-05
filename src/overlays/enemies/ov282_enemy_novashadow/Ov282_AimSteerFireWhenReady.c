/*
 * Ov282_AimSteerFireWhenReady -- x3. AI-state tick: aim at the acquired target, steer, then fire once ready.
 * Acquire (020cab14) -> state[4]; none -> mark *state[0]+0x1c7=2 and bail. Else
 * dir = normalise(flatten_y(target(+0x190) - state[1])); state[0xa] = atan2(dir.x, dir.z).
 * factor = 020c9f48(*(*state+0x3b8), &w); build state[5..7] from *state+0xa0 (0202f384) scaled by factor
 * (01ffa724). While the sub-node byte *(u8)state[3] is set, return. Once idle: fire attack 0xd
 * (020c9264), trigger 020c9ee8(*(*state+0x3b8), 2, 0), and hand off to the 020d2918 state.
 */

#include "game/engine.h"

extern int  Ov107_FindNearestObject(int obj, int flag);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern int  Ov107_ActionResource_GetOffsetAndScale(int obj, void *out);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern void Ov107_PostTagUpdate(int a, int b, int c);
extern void Ov107_StartAnim(int a, int b, int c);
extern void Ov282_RebuildSteerAndGate(void);

void Ov282_AimSteerFireWhenReady(int *self) {
    int *state = (int *)self[1];
    int v[3];
    int w[3];
    int factor;
    int target = Ov107_FindNearestObject(*state, 0);

    state[4] = target;
    if (target == 0) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)state[1], v);
    v[1] = 0;
    VEC_Normalize(v, v);
    state[0xa] = FX_Atan2(v[0], v[2]);
    factor = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3b8), w);
    Vec3TransformViaTempMtx((void *)(state + 5), (void *)(*state + 0xa0), w);
    ScaleVec3Fx12(factor, (void *)(state + 5), (void *)(state + 5));
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    Ov107_PostTagUpdate(*state, 0xd, 0);
    Ov107_StartAnim(*(int *)(*state + 0x3b8), 2, 0);
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov282_RebuildSteerAndGate);
}
