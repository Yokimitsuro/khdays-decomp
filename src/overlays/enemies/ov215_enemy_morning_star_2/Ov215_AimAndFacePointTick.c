/*
 * Aim from the owner (*state+0x190) to a cached point (state[4]); store the heading (atan2 of the
 * UNFLATTENED x,z, unlike the ov188 cousin) at state[0x13]; normalise the aim for the distance and
 * subtract the owner radius (owner+0x80). Turn the node's own heading (state[0x11]) into a sin/cos
 * facing, write it as a vector at state+0x20, scale it by 0x200 (the per-frame step), and if the
 * distance is under 0x2000 drop to phase 2.
 *
 * `const short data_0203d210[]` is load-bearing: without const mwcc must assume the vector stores
 * could write the sin/cos table, which reorders one table load; const is the aliasing fact that
 * matches. One of a 5-member family (family, byte-identical).
 */

#include "nitro/fx_types.h"

static inline void VEC_Set(VecFx32 *vec, int x, int y, int z) {
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern void VEC_Subtract(void *a, void *b, void *d);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(void *a, void *d);
extern void ScaleVec3Fx12(int s, void *v, void *d);
extern void SetIndexedSlot(int self, int idx, int cb);
extern const short data_0203d210[];

void Ov215_AimAndFacePointTick(int self) {
    int *state = *(int **)(self + 4);
    VecFx32 aim;
    int dist;
    int idx;
    int owner;

    VEC_Subtract((void *)(*state + 0x190), (void *)state[4], &aim);
    state[0x13] = FX_Atan2(aim.x, aim.z);
    owner = *state;
    dist = VEC_Normalize(&aim, &aim);
    idx = (int)(((unsigned)(((long long)(int)(unsigned)state[0x11] * 0x28be60db9391LL +
                 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    dist = dist - *(int *)(owner + 0x80);
    VEC_Set((VecFx32 *)(state + 8), (int)data_0203d210[idx * 2], 0,
            (int)data_0203d210[idx * 2 + 1]);
    ScaleVec3Fx12(0x200, (void *)(state + 8), (void *)(state + 8));
    if (dist < 0x2000) {
        *(char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(self, *(signed char *)(self + 0x20), 0);
    }
}
