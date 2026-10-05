/* Approach tick of the ov139 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the gap to the target beyond both +0x80 radii is measured, the
 * +0xc target yaw is the direction from the +0x4c position to the target's +0x74, the +0x14
 * velocity is the +0x390 part's motion step rotated by the actor's +0xa0 orientation and, unless
 * the gap is within the actor's +0x2d8 range but beyond 0x3000, the +0x384 item's +0xa8 byte
 * clears and the tick hands off to cd224. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *dist);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int FX_Sqrt(int x);
extern fx16 FX_Atan2(int x, int z);
extern int Ov107_ActionResource_GetOffsetAndScale(void *part, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, void *v, void *d);
extern void Ov139_AcquireTargetTransformScaleThenAdvance(int *node);

void Ov139_ApproachTick(int *node)
{
    int *state = (int *)node[1];
    int dist;
    VecFx32 dir;
    VecFx32 step;
    int speed;
    int actor;
    int target;

    target = state[1] = Ov107_FindNearestObject(*state, &dist);
    if (target == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    dist = FX_Sqrt(dist) - (*(int *)(target + 0x80) + *(int *)(actor + 0x80));
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    state[3] = FX_Atan2(dir.x, dir.z);
    speed = Ov107_ActionResource_GetOffsetAndScale(*(void **)(*state + 0x390), &step);
    Vec3TransformViaTempMtx(state + 5, (void *)(*state + 0xa0), &step);
    ScaleVec3Fx12(speed, state + 5, state + 5);
    if (dist < *(int *)(*state + 0x2d8) && dist > 0x3000) {
        return;
    }
    *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov139_AcquireTargetTransformScaleThenAdvance);
}
