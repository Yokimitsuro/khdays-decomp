/* Charge advance of the ov204 enemy (and its byte-identical twin): the +8 velocity is the
 * +0x390 part's motion step rotated by the actor's +0xa0 orientation, the charge helper runs,
 * the target is re-acquired (the +0x38 yaw aimed at it from the +0x24 position), the +0x3c turn
 * rate is the step over 0x3000 capped at 0x200 and the +0x2c travel grows by the step. Once the
 * +0x28 busy byte clears the actor plays animation 0x12 and the tick hands off to d30e0. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern int Ov107_ActionResource_GetOffsetAndScale(void *part, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, void *v, void *d);
extern void Ov205_ChargeSweep(int *state);
extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *d);
extern fx16 FX_Atan2(int x, int z);
extern int FX_Div(int a, int b);
extern void Ov107_PostTagUpdate(int actor, int anim, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov205_AiStep_QueueAction2OnFlag28Clear_5(int *node);

void Ov205_ChargeAdvance(int *node)
{
    int *state = (int *)node[1];
    VecFx32 step;
    VecFx32 dir;
    int speed;
    int rate;

    speed = Ov107_ActionResource_GetOffsetAndScale(*(void **)(*state + 0x390), &step);
    Vec3TransformViaTempMtx(state + 2, (void *)(*state + 0xa0), &step);
    ScaleVec3Fx12(speed, state + 2, state + 2);
    Ov205_ChargeSweep(state);
    state[1] = Ov107_FindNearestObject(*state, 0);
    if (state[1] != 0) {
        VEC_Subtract((void *)(state[1] + 0x74), (void *)state[9], &dir);
        state[0xe] = FX_Atan2(dir.x, dir.z);
    }
    rate = FX_Div(speed, 0x3000);
    if (rate > 0x200) {
        rate = 0x200;
    }
    state[0xf] = rate;
    state[0xb] += speed;
    if (*(u8 *)state[10] != 0) {
        return;
    }
    Ov107_PostTagUpdate(*state, 0x12, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov205_AiStep_QueueAction2OnFlag28Clear_5);
}
