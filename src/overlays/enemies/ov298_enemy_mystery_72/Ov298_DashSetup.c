/* Dash setup of the ov298 enemy: the +0x10 velocity is (1.0, 0, 1.0) turned by the +0x34 yaw,
 * normalised and scaled by 0x600 in sub-state 7 (0x330 otherwise); the +0x2c/+0x30 yaws follow
 * it. */

#include "nitro/fx_types.h"

typedef struct { int m[9]; } Mtx33;

extern void MTX_RotY33_(Mtx33 *m, int sin, int cos);
extern void MTX_MultVec33(const VecFx32 *v, Mtx33 *m, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov298_DashSetup(int *node)
{
    int *state = (int *)node[1];
    Mtx33 mtx;
    unsigned int idx;

    state[4] = 0x1000;
    state[5] = 0;
    state[6] = 0x1000;
    idx = ANG2IDX(state[0xd]);
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((VecFx32 *)(state + 4), &mtx, (VecFx32 *)(state + 4));
    VEC_Normalize((VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    ScaleVec3Fx12(*(signed char *)(*state + 0x1c6) != 7 ? 0x330 : 0x600, (VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    state[0xb] = state[0xc] = FX_Atan2(state[4], state[6]);
}
