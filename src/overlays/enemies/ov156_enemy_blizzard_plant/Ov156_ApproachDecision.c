/* Approach decision of the ov156 enemy (and its byte-identical twin): the +0x30 rate is the
 * frame delta * 30 / 20; the target is re-acquired into +0x18 (none ends the tick) and the gap
 * beyond both +0x80 radii must be within the actor's +0x2d8 range; the +0x14 heading aims at the
 * target's +0x190 point from the +8 position. With the +0x34 cooldown spent: a gap under 0x2000
 * requests sub-state 6 and ends the state; otherwise the first of the two +0x3a4 items whose
 * +0x60 low bit is clear requests sub-state 4 and ends the state. */

#include "nitro/fx_types.h"

struct hw60 { unsigned short lo : 8, hi : 8; };

extern int Ov107_FindNearestObject(int actor, int *distSq);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov156_ApproachDecision(int *node)
{
    int *state = (int *)node[1];
    int dist;
    VecFx32 d;
    int actor;
    int target;
    int i;

    state[0xc] = *(int *)(*node + 0x2c) * 0x1e / 20;
    target = state[6] = Ov107_FindNearestObject(*state, &dist);
    if (target == 0) {
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - *(int *)(target + 0x80) - *(int *)(actor + 0x80);
    if (dist >= *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[2], &d);
    state[5] = FX_Atan2(d.x, d.z);
    if (state[0xd] > 0) {
        return;
    }
    if (dist < 0x2000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    for (i = 0; i < 2; i++) {
        if ((((struct hw60 *)((*(int **)(*state + 0x3a4))[i] + 0x60))->lo & 1) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 4;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
}
