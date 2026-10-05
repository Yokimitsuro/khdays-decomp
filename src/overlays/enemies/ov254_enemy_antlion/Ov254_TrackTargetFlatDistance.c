/* Re-acquires the current target (stored at +0x3dc of the owner), takes the vector to it,
 * records its horizontal angle at +0x34 and returns the flattened distance.  0 when there
 * is no target. */

#include "nitro/fx_types.h"

extern char *Ov107_FindNearestObject(char *o, int a);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int a, int b);
extern int VEC_Mag(VecFx32 *v);

int Ov254_TrackTargetFlatDistance(char *self) {
    VecFx32 d;
    char *ctx = *(char **)(self + 4);
    char *t;
    *(char **)(*(char **)ctx + 0x3dc) = Ov107_FindNearestObject(*(char **)ctx, 0);
    t = *(char **)(*(char **)ctx + 0x3dc);
    if (t == 0) {
        return 0;
    }
    VEC_Subtract((VecFx32 *)(t + 0x190), *(VecFx32 **)(ctx + 8), &d);
    *(int *)(ctx + 0x34) = FX_Atan2(d.x, d.z);
    d.y = 0;
    return VEC_Mag(&d);
}
