/* Target distance of the ov240 enemy: acquires the actor's +0x394 target when missing (none
 * requests sub-state 2 and returns -1), aims the +0x10 yaw from the +8 position at the
 * target's +0x190 point and returns the flat distance. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);

int Ov240_DistanceToTarget(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int len;

    if (*(int *)(*state + 0x394) == 0) {
        *(int *)(*state + 0x394) = Ov107_FindNearestObject(*state, 0);
        if (*(int *)(*state + 0x394) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 2;
            return -1;
        }
    }
    VEC_Subtract((void *)(*(int *)(*state + 0x394) + 0x190), (void *)state[2], &d);
    d.y = 0;
    len = VEC_Normalize(&d, &d);
    state[4] = FX_Atan2(d.x, d.z);
    return len;
}
