/* Rebuilds the 0x440-long heading vector from the angle at +0x34 and stores its yaw. */

#include "nitro/fx_types.h"

struct Mtx33_ov297 { int m[9]; };

extern void MTX_RotY33_(void *mtx, int cos, int sin);
extern void MTX_MultVec33(VecFx32 *vec, void *mtx, VecFx32 *dst);
extern int VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern void ScaleVec3Fx12(int factor, VecFx32 *src, VecFx32 *dst);
extern fx16 FX_Atan2(int x, int z);
extern const short data_0203d210[];

void Ov297_UpdateHeadingVector(int this_) {
    int *node = (int *)(*(int *)(this_ + 4));
    VecFx32 *dir = (VecFx32 *)((int)node + 0x10);
    struct Mtx33_ov297 mtx;
    int v, angle;

    dir->x = 0x1000;
    dir->y = 0;
    dir->z = 0x1000;

    v = *(int *)((int)node + 0x34);
    angle = (int)(((unsigned)(((long long)(int)(unsigned)v * 0x28be60db9391LL
                 + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    MTX_RotY33_(&mtx, data_0203d210[angle * 2], data_0203d210[angle * 2 + 1]);
    MTX_MultVec33(dir, &mtx, dir);
    VEC_Normalize(dir, dir);
    ScaleVec3Fx12(0x440, dir, dir);
    *(int *)((int)node + 0x2c) = *(int *)((int)node + 0x30) = FX_Atan2(dir->x, dir->z);
}
