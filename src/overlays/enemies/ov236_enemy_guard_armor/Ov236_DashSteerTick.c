/* Dash steer tick: the +0x14 rate is 30/30 of the frame step; the +0x3ac sub-object's steer
 * vector (transformed by the actor's +0xa0 pose) drives the +0x18 step scaled by its factor
 * times the alignment (floored at 0) with the direction to the target (none: pose request
 * 0xa, dispatch null), whose atan2 lands in +0x10. The +0x28 timer counts the frame step down;
 * once spent (or at once when bit 0 of +0x52 is set) the +4 child's +0xa8 flag clears and the
 * node moves to 020d1704. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}
struct Bits52 { unsigned char b0 : 1; };
extern int  Ov107_FindNearestObject(int obj, int flag);
extern void VEC_Subtract(void *a, void *b, void *c);
extern int  VEC_Normalize(void *a, void *b);
extern fx16  FX_Atan2(int x, int z);
extern int  VEC_DotProduct(void *a, void *b);
extern void SetIndexedSlot(int self, int idx, int cb);
extern void ScaleVec3Fx12(int scale, void *in, void *out);
extern void Ov236_SpawnStep(void);

void Ov236_DashSteerTick(int *self) {
    int *state = (int *)self[1];
    VecFx32 d;
    VecFx32 w;
    int factor;
    int target;
    int dot;

    state[5] = *(int *)(*self + 0x2c) * 30 / 30;
    factor = Ov107_ActionResource_GetOffsetAndScale(*(int *)(*state + 0x3ac), &w);
    Vec3TransformViaTempMtx(&w, (void *)(*state + 0xa0), &w);
    target = state[2] = Ov107_FindNearestObject(*state, 0);
    if (target != 0) {
        VEC_Subtract((void *)(target + 0x74), (void *)(*state + 0x74), &d);
        d.y = 0;
        VEC_Normalize(&d, &d);
        state[4] = FX_Atan2(d.x, d.z);
        dot = VEC_DotProduct(&w, &d);
        if (dot < 0) dot = 0;
    } else {
        *(char *)(*state + 0x1c7) = 0xa;
        SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), 0);
        return;
    }
    ScaleVec3Fx12(FX_Mul(factor, dot), &w, (void *)(state + 6));
    state[0xa] -= *(int *)(*self + 0x2c);
    if (state[0xa] > 0) {
        if (((struct Bits52 *)((char *)state + 0x52))->b0 == 0) return;
    }
    *(unsigned char *)(state[1] + 0xa8) = 0;
    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (int)&Ov236_SpawnStep);
}
