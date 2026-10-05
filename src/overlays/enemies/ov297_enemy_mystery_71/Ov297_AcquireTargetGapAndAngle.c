/* Stores the nearest target (none: queues action 2, returns -1); returns the edge gap and sets the
 * angle. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int a, int b);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *src, VecFx32 *dst);
extern fx16 FX_Atan2(int x, int z);

int Ov297_AcquireTargetGapAndAngle(int this_) {
    int *state = (int *)(*(int *)(this_ + 4));
    int t = Ov107_FindNearestObject(*state, 0);
    VecFx32 delta;
    int dist, radiusSum;

    *(int *)(*state + 0x394) = t;
    if (*(int *)(*state + 0x394) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        return -1;
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x394) + 0x190),
                 (VecFx32 *)(*state + 0xb0), &delta);
    dist = VEC_Normalize(&delta, &delta);
    radiusSum = *(int *)(*(int *)(*state + 0x394) + 0x80) + *(int *)(*state + 0x80);
    dist -= radiusSum;
    if (dist < 0) dist = 0;
    *(int *)((int)state + 0x30) = FX_Atan2(delta.x, delta.z);
    return dist;
}
