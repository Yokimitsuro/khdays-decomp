/* Strafe tick: refreshes the +4 target (none: pose request 9) and measures the surface gap
 * (root of the squared distance minus both +0x80 radii). Every 2.0 of the +0x18 timer the +0x34
 * strafe direction is re-rolled and the +0x38 speed halved; the +0x3c timer counts down to pose
 * request 0xb. The +8 velocity is the offset's side vector (world Y x offset) scaled by the
 * direction x speed (the +0x30 heading = atan2 of the offset), the speed eases a fiftieth
 * towards 0x500 and the velocity drops 0x300 in y. Beyond a 4.0 gap the node moves to
 * 020d24dc; inside 2.0 the velocity is -0x100 along the offset instead. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void VEC_CrossProduct(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern const VecFx32 data_02042264;
extern void Ov236_ApproachTick(void);

void Ov236_StrafeTick(int *node) {
    int *state = (int *)node[1];
    int dist;
    VecFx32 d;
    VecFx32 side;
    int actor;
    int target;
    int v;

    target = state[1] = Ov107_FindNearestObject(*state, &dist);
    if (target == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    state[6] += *(int *)(*node + 0x2c);
    if (state[6] >= 0x2000) {
        state[0xd] = (RandNextScaled(2) + (v - v)) != 0 ? -1 : 1;
        state[6] = 0;
        state[0xe] = state[0xe] / 2;
    }
    state[0xf] -= *(int *)(*node + 0x2c);
    if (state[0xf] < 0) {
        *(unsigned char *)(*state + 0x1c7) = 0xb;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[1] + 0x74), (VecFx32 *)(*state + 0x74), &d);
    {
        int actor = state[0];
        int target = state[1];
        dist = VEC_Normalize(&d, &d) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    VEC_CrossProduct(&data_02042264, &d, &side);
    state[0xc] = FX_Atan2(d.x, d.z);
    ScaleVec3Fx12(state[0xe] * state[0xd], &side, (VecFx32 *)(state + 2));
    state[0xe] += (0x500 - state[0xe]) / 50;
    state[3] -= 0x300;
    if (dist > 0x4000) {
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov236_ApproachTick);
        return;
    }
    if (dist >= 0x2000) {
        return;
    }
    ScaleVec3Fx12(-0x100, &d, (VecFx32 *)(state + 2));
}
