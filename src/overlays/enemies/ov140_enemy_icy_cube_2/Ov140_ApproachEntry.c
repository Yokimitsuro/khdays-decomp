/* Approach entry of the ov139 enemy (and its byte-identical twin): without a target the state
 * ends with sub-state 2; else the +0xc target yaw is the flat direction from the +0x4c position
 * to the target's +0x74, the +0x14 velocity is 0x100 along the +8 yaw's (sin, 0, cos) and, once
 * the +0x50 busy byte clears, the +0x390 part restarts action 0, animation 3 (looped) plays and
 * the tick hands off to the approach tick. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(void *a, void *b, void *d);
extern int VEC_Normalize(void *a, void *d);
extern fx16 FX_Atan2(int x, int z);
extern void ScaleVec3Fx12(int scale, void *v, void *d);
extern void Ov107_StartAnim(void *part, int a, int b);
extern void Ov107_PostTagUpdate(int actor, int anim, int flag);
extern const short data_0203d210[];
extern void Ov140_ApproachTick(int *node);

void Ov140_ApproachEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 dir;
    VecFx32 fwd;
    int idx;

    state[1] = Ov107_FindNearestObject(*state, 0);
    if (state[1] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x74), (void *)state[0x13], &dir);
    dir.y = 0;
    VEC_Normalize(&dir, &dir);
    state[3] = FX_Atan2(dir.x, dir.z);
    idx = (unsigned short)((0x28BE60DB9391LL * state[2] + 0x80000000000LL) >> 44);   /* FX_RAD_TO_IDX */
    fwd.y = 0;
    fwd.x = data_0203d210[(idx >> 4) << 1];                                             /* FX_SinIdx */
    fwd.z = data_0203d210[((idx >> 4) << 1) + 1];                                       /* FX_CosIdx */
    ScaleVec3Fx12(0x100, &fwd, state + 5);
    if (*(u8 *)state[0x14] != 0) {
        return;
    }
    Ov107_StartAnim(*(void **)(*state + 0x390), 0, 1);
    Ov107_PostTagUpdate(*state, 3, 1);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov140_ApproachTick);
}
