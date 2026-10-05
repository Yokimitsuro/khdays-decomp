/* Approach tick of the ov204 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the +0x3c turn rate is the frame-time * 3, the +0x38 target yaw is
 * the direction from the +0x24 position to the target's +0x74, the +8 velocity is the +0x390
 * part's motion step rotated by the actor's +0xa0 orientation and, unless the target distance is
 * within the actor's +0x2d8 reach yet beyond 0x5000, the +0x384 item's +0xa8 byte is cleared and
 * the tick hands off to the next approach state. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_FindNearestObject(int actor, int *dist);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern fx16 FX_Atan2(int x, int z);
extern int Ov107_ActionResource_GetOffsetAndScale(void *part, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, void *v, void *d);
extern void Ov205_stateAcquireTransform(int *node);

void Ov205_ApproachTick(int *node)
{
    int *state = (int *)node[1];
    int dist;
    VecFx32 dir;
    VecFx32 step;
    int speed;

    state[1] = Ov107_FindNearestObject(*state, &dist);
    if (state[1] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    state[0xf] = *(int *)(*node + 0x2c) * 30 / 10;
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
    state[0xe] = FX_Atan2(dir.x, dir.z);
    speed = Ov107_ActionResource_GetOffsetAndScale(*(void **)(*state + 0x390), &step);
    Vec3TransformViaTempMtx(state + 2, (void *)(*state + 0xa0), &step);
    ScaleVec3Fx12(speed, state + 2, state + 2);
    if (dist < *(int *)(*state + 0x2d8) && dist > 0x5000) {
        return;
    }
    *(u8 *)(*(int *)(*state + 0x384) + 0xa8) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov205_stateAcquireTransform);
}
