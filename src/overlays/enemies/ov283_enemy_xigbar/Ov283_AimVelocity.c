/* Aim the ov283 actor's +0x10 velocity: a diagonal unit step turned by the +0x44 heading, normalised and
 * scaled to 0.25; both headings (+0x38, +0x40) point along it. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov283_AimVelocity(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;

    state[4] = 0x1000;
    state[5] = 0;
    state[6] = 0x1000;
    {
        int idx = ANG2IDX(state[0x11]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((VecFx32 *)(state + 4), &rot, (VecFx32 *)(state + 4));
    VEC_Normalize((VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    ScaleVec3Fx12(0x400, (VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    state[0xe] = state[0x10] = FX_Atan2(state[4], state[6]);
}
