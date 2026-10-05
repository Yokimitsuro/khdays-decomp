/* Approach tick: refreshes the +4 target (none: pose request 9), counts the +0x3c timer down
 * (expired: request 0xb), heads for the target (+0x30 = atan2 of the offset, +8 velocity =
 * 0.25 along it) and, once the surface gap (root of the squared distance minus both +0x80
 * radii, measured twice) closes under 2.0, rolls a strafe direction into +0x34, clears +0x38
 * and moves the node to 020d2628. */

#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int FX_Sqrt(int x);
extern void Ov278_StrafeTick(void);

void Ov278_ApproachTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    int dist;
    int v;

    state[1] = Ov107_FindNearestObject(*state, &dist);
    if (state[1] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 9;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
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
    state[0xc] = FX_Atan2(d.x, d.z);
    ScaleVec3Fx12(0x400, &d, (VecFx32 *)(state + 2));
    {
        int actor = state[0];
        int target = state[1];
        dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    }
    if (dist >= 0x2000) {
        return;
    }
    state[0xd] = (RandNextScaled(2) + (v - v)) != 0 ? -1 : 1;
    state[0xe] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov278_StrafeTick);
}
