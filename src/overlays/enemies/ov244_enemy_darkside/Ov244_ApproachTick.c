/* Approach tick of the ov114 enemy: the closest target goes to +0x10 (none requests sub-state
 * 2); the offset from the +4 position to its +0x190 gives the +0x18 heading, and the +0x50
 * velocity is the facing (sin, 0, cos) of the +0x14 yaw at 0x180. Once the +0x4c timer has
 * expired the surface distance (root minus both +0x80 radii) decides: sub-state 6, or 2 when it
 * is still inside 1.0. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void SetIndexedSlot(int node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern int FX_Sqrt(int x);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov244_ApproachTick(int node)
{
    int *state = *(int **)(node + 4);
    int dist;
    VecFx32 d;
    int obj;
    int target;
    unsigned int idx;

    state[4] = Ov107_FindNearestObject(*state, &dist);
    if (state[4] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[4] + 0x190), (VecFx32 *)state[1], &d);
    state[6] = FX_Atan2(d.x, d.z);
    idx = ANG2IDX(state[5]);
    state[0x14] = data_0203d210[idx * 2];                                     /* FX_SinIdx */
    state[0x15] = 0;
    state[0x16] = data_0203d210[idx * 2 + 1];                                 /* FX_CosIdx */
    ScaleVec3Fx12(0x180, (VecFx32 *)(state + 0x14), (VecFx32 *)(state + 0x14));
    obj = *state;
    target = state[4];
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(obj + 0x80));
    if (state[0x13] <= 0) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    if (dist > 0x1000) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
}
