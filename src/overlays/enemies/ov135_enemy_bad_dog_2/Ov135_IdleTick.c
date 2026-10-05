/* Idle tick of the ov134 enemy (x3: ov134/135/136). Acquires the nearest target (+8) together with
 * its squared distance; none keeps waiting. The distance (square root minus both +0x80 radii)
 * beyond the +0x2d8 range keeps waiting too; otherwise the facing (+0x10) is re-aimed at the
 * target and: while the +0x42 bit-0 flag is set, sub-state 4 is requested at once; under 0x3000
 * the +0x30 timer counts down and, when it runs out, is re-armed at random inside the
 * [+0x224, +0x228] range and sub-state 6 is requested; above 0x6000 but still inside the +0x2d8
 * range sub-state 4 is requested. */

#include "nitro/fx_types.h"
#include "game/engine.h"

struct Flags42 { unsigned char bCharge : 1; };

extern int Ov107_FindNearestObject(int actor, int *distSq);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov135_IdleTick(int *node)
{
    int *state = (int *)node[1];
    int dist;
    VecFx32 d;
    int actor;
    int target;
    int lo;
    int span;

    state[2] = Ov107_FindNearestObject(*state, &dist);
    target = state[2];
    if (target == 0) {
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    if (dist > *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    state[4] = FX_Atan2(d.x, d.z);
    if (((struct Flags42 *)((char *)state + 0x42))->bCharge) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (dist < 0x3000) {
        state[0xc] -= *(int *)(*node + 0x2c);
        if (state[0xc] < 0) {
            lo = *(int *)(*state + 0x224);
            span = *(int *)(*state + 0x228) - lo;
            if (span < 0) {
                span = -span;
            }
            state[0xc] = lo + RandNextScaled(span + 1);
            *(unsigned char *)(*state + 0x1c7) = 6;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        }
        return;
    }
    if (dist > 0x6000 && dist < *(int *)(*state + 0x2d8)) {
        *(unsigned char *)(*state + 0x1c7) = 4;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
