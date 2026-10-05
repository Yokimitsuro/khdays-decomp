/* Ov218_DistanceToTarget: ported from a matched sibling family (same shape, constants and offsets adjusted). */

#include "nitro/fx_types.h"
#include "game/actor.h"

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
    Actor base;                  /* 0x000 */
    u8 pad38c[0x4];
    P3bc *p3bc;
} Obj;

typedef struct {
    Obj *obj;
    char pad4[0xc];
    int v44;
} Wrap;

typedef struct {
    char pad0[4];
    Wrap *wrap;
} Param;

int Ov218_DistanceToTarget(Param *param)
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
            obj->base.nextState = 2;
            return -1;
        }
    }

    VEC_Subtract(&p3bc->v190, &obj->base.srt.translation, &local);
    diff = VEC_Normalize(&local, &local);
    obj = wrap->obj;
    diff = diff - (obj->p3bc->v80 + obj->base.sphere.radius);
    if (diff < 0) {
        diff = 0;
    }
    wrap->v44 = FX_Atan2(local.x, local.z);
    return diff;
}
