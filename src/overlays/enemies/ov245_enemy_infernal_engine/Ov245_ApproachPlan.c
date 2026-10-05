/* Ov245_ApproachPlan -- approach planner: refreshes the +8 target (020cab14); with none the
 * actor goes to sub-state 2 and the node's slot is released. Otherwise the flattened gap from
 * the actor's +0xb0 to the target's +0x190 (normalised, minus both +0x80 radii) and its heading
 * (+0x14) are taken, the +0x10 angle turned into a forward vector (sine table) which, scaled by
 * 0.1875, becomes the +0x1c step; inside 0.5 the actor goes to sub-state 2 and the slot is released. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int a);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_DotProduct(const VecFx32 *a, const VecFx32 *b);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern const short data_0203d210[];

void Ov245_ApproachPlan(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 fwd;
    int gap;
    int idx;
    int target;
    int actor;

    state[2] = Ov107_FindNearestObject(*state, 0);
    if (state[2] == 0) {
        *(unsigned char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    d.y = 0;
    target = state[2];
    actor = *state;
    gap = VEC_Normalize(&d, &d) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    state[5] = FX_Atan2(d.x, d.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[4] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.x = data_0203d210[(idx >> 4) << 1];                                           /* FX_SinIdx */
    fwd.y = 0;
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                     /* FX_CosIdx */
    VEC_DotProduct(&fwd, &d);
    ScaleVec3Fx12(0x300, &fwd, (VecFx32 *)(state + 7));
    if (gap >= 0x800) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
