/* Ov245_ApproachTick -- approach tick: refreshes the state's +8 target (020cab14, mode 0) and
 * stops without one; measures the flat distance from the actor's +0xb0 pose to the target's
 * +0x190 minus both +0x80 radii and gives up beyond the actor's +0x2d8 reach; otherwise aims
 * +0x14 at the target (atan2), requests sub-state 4 beyond 3.0, or counts the +0x40 timer down
 * and then requests 6 (within 0.5) or 7, releasing the node's slot either way. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov245_ApproachTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    int gap;
    int target;
    int actor;

    state[2] = Ov107_FindNearestObject(*state, 0);
    if (state[2] == 0) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    target = state[2];
    actor = *state;
    gap = VEC_Normalize(&d, &d) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (gap > *(int *)(*state + 0x2d8)) {
        return;
    }
    state[5] = FX_Atan2(d.x, d.z);
    if (gap > 0x3000) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0x10] -= *(int *)(*node + 0x2c);
    if (state[0x10] > 0) {
        return;
    }
    if (gap <= 0x800) {
        *(unsigned char *)(*state + 0x1c7) = 6;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 7;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
