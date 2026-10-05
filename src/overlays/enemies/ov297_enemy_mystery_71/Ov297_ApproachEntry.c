/* Approach entry of the ov298 enemy: sets the +0x50 speed to 0x900 and, with a +0xc target,
 * aims the +0x2c/+0x30 yaws at it (the facing of the +0x2c yaw is dotted against that direction
 * and discarded); one of animations 5/6 plays at random and the tick hands off to d5034. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern int VEC_DotProduct(VecFx32 *a, VecFx32 *b);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov297_CopyScaleVecSetFlag88ThenAdvance(int *node);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov297_ApproachEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 facing;
    VecFx32 dir;
    unsigned int idx;
    int actor;

    state[0x14] = 0x900;
    if (state[3] != 0) {
        idx = ANG2IDX(state[0xb]);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        VEC_Subtract((void *)(state[3] + 0x74), (void *)(*state + 0x74), &dir);
        VEC_Normalize(&dir, &dir);
        VEC_DotProduct(&facing, &dir);
        state[0xb] = state[0xc] = FX_Atan2(dir.x, dir.z);
    }
    actor = *state;
    Ov107_PostTagUpdate((Actor *)actor, RandNextScaled(2) + 5, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov297_CopyScaleVecSetFlag88ThenAdvance);
}
