/* Finds the nearest target (queues action 2 when none), returns the gap minus both radii and stores
 * the heading. */

#include "nitro/fx_types.h"
#include "game/actor.h"

extern int Ov107_FindNearestObject();
extern void VEC_Subtract(int *a, int *b, int *out);
extern int VEC_Normalize(int *source, int *destination);
extern fx16 FX_Atan2();

typedef struct {
    char pad0[0x80];
    int v80;
    char pad84[0x10c];
    VecFx32 v190;
} P3bc_020ccb48;

typedef struct {
    Actor base;                  /* 0x000 */
    u8 pad38c[0x4];
    P3bc_020ccb48 *p3bc;
} Obj_020ccb48;

typedef struct {
    Obj_020ccb48 *obj;
    char pad4[0x3c];
    int v40;
} Wrap_020ccb48;

typedef struct {
    char pad0[4];
    Wrap_020ccb48 *wrap;
} Param_020ccb48;

int Ov283_MeasureTargetGap(Param_020ccb48 *param)
{
    Wrap_020ccb48 *wrap;
    Obj_020ccb48 *obj;
    P3bc_020ccb48 *p3bc;
    int diff;
    VecFx32 local;

    wrap = param->wrap;
    obj = wrap->obj;
    p3bc = (P3bc_020ccb48 *)Ov107_FindNearestObject(obj, 0);
    obj = wrap->obj;
    obj->p3bc = p3bc;
    obj = wrap->obj;
    p3bc = obj->p3bc;
    if (p3bc == 0) {
        obj->base.nextState = 2;
        return -1;
    }

    VEC_Subtract(&p3bc->v190.x, &obj->base.srt.translation.x, &local.x);
    diff = VEC_Normalize(&local.x, &local.x);
    obj = wrap->obj;
    p3bc = obj->p3bc;
    diff = diff - (p3bc->v80 + obj->base.sphere.radius);
    if (diff < 0) {
        diff = 0;
    }
    wrap->v40 = FX_Atan2(local.x, local.z);
    return diff;
}
