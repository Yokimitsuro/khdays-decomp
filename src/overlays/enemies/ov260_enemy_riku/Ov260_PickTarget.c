/* Pick the target of the ov260 actor: the nearest live entity (020cab14) goes to +0x420; with one,
 * +0x68 takes the flat heading from the +0x10 point to its +0x190 point and the flat distance is
 * returned (0 without a target). */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);

int Ov260_PickTarget(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int len;

    *(int *)(*state + 0x420) = Ov107_FindNearestObject(*state, 0);
    if (*(int *)(*state + 0x420) == 0) {
        return 0;
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x420) + 0x190), (VecFx32 *)state[4], &d);
    d.y = 0;
    len = VEC_Normalize(&d, &d);
    state[0x1a] = FX_Atan2(d.x, d.z);
    return len;
}
