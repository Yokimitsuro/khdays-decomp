/* Idle tick of the ov284 enemy: re-acquires the target into +0xc and aims the +0x14 yaw at its
 * +0x190 point from the +4 position; the surface distance (root minus both +0x80 radii) is
 * measured and, once the +0x20 timer is spent, sub-state 7 is requested and the state ends. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int FX_Sqrt(int x);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov284_IdleTick(int *node)
{
    int *state = (int *)node[1];
    int dist;
    VecFx32 d;
    int target;
    int actor;

    state[3] = Ov107_FindNearestObject(*state, &dist);
    if (state[3] != 0) {
        VEC_Subtract((void *)(state[3] + 0x190), (void *)state[1], &d);
        state[5] = FX_Atan2(d.x, d.z);
    }
    target = state[3];
    actor = *state;
    dist = FX_Sqrt(dist) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (state[8] > 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 7;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
