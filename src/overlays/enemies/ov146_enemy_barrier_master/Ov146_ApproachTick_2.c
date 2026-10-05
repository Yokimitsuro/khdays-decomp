/* Approach tick: the +0x2c heading turns towards the actor's +0x190 point from the +0xc anchor,
 * the +0x10 velocity is the +0x28 yaw's direction at speed 0.125, and once the anchor is within 2.0
 * (beyond the actor's +0x80 radius) the next move is 2. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(const void *a, const void *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov146_ApproachTick_2(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int dist;
    int owner;
    unsigned int idx;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[3], &d);
    state[0xb] = FX_Atan2(d.x, d.z);
    owner = *state;
    dist = VEC_Normalize(&d, &d) - *(int *)(owner + 0x80);
    idx = ANG2IDX(state[0xa]);
    state[4] = data_0203d210[idx * 2];
    state[5] = 0;
    state[6] = data_0203d210[idx * 2 + 1];
    ScaleVec3Fx12(0x200, (VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    if (dist < 0x2000) {
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
