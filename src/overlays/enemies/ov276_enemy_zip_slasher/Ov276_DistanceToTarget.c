/* Ov276_DistanceToTarget: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject();
extern int VEC_Subtract();
extern int VEC_Normalize();
extern fx16 FX_Atan2();

typedef struct {
    char pad0[0x80];
    int v80;
    char pad84[0x10c];
    VecFx32 v190;
} P3bc;

typedef struct {
    char pad0[0xb0];
    VecFx32 vb0;
    char padbc[0x10b];
    unsigned char b1c7;
    char pad1c8[0x1f4];
    P3bc *p3bc;
    char pad3c0[0xc0];
    int v480;
} Obj;

typedef struct {
    Obj *obj;
    char pad4[0x40];
    int v44;
} Wrap;

typedef struct {
    char pad0[4];
    Wrap *wrap;
} Param;

int Ov276_DistanceToTarget(Param *param)
{
    Wrap *wrap;
    Obj *obj;
    P3bc *p3bc;
    int diff;
    VecFx32 local;

    wrap = param->wrap;
    obj = wrap->obj;
    p3bc = obj->p3bc;
    if (p3bc == 0) {
        p3bc = (P3bc *)Ov107_FindNearestObject(obj, 0);
        obj = wrap->obj;
        obj->p3bc = p3bc;
        obj = wrap->obj;
        p3bc = obj->p3bc;
        if (p3bc == 0) {
            obj->b1c7 = 2;
            return -1;
        }
    }

    VEC_Subtract(&p3bc->v190, &obj->vb0, &local);
    diff = VEC_Normalize(&local, &local);
    obj = wrap->obj;
    diff = diff - (obj->v480 + obj->p3bc->v80);
    if (diff < 0) {
        diff = 0;
    }
    wrap->v44 = FX_Atan2(local.x, local.z);
    return diff;
}
