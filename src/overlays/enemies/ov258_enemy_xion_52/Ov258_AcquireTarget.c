/* Target acquisition of the ov258 actor: the nearest target (020cab14) becomes the actor's +0x454;
 * without one the next move is 2 and 0 is returned. Otherwise the flat direction from the +0xc point
 * to the target's +0x190 point is normalised into +0x10, +0x40 is the gap left between both +0x80
 * radii (at least 0) and, when `face` is set, +0x2c turns toward it. Returns 1. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int kind);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);

int Ov258_AcquireTarget(int *node, int face)
{
    int *state = (int *)node[1];
    VecFx32 to;
    VecFx32 from;

    from = *(VecFx32 *)state[3];
    *(int *)(*state + 0x454) = Ov107_FindNearestObject(*state, 0);
    if (*(int *)(*state + 0x454) == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        return 0;
    }
    to = *(VecFx32 *)(*(int *)(*state + 0x454) + 0x190);
    from.y = 0;
    to.y = 0;
    VEC_Subtract(&to, &from, (VecFx32 *)(state + 4));
    state[0x10] = VEC_Normalize((VecFx32 *)(state + 4), (VecFx32 *)(state + 4));
    state[0x10] -= *(int *)(*(int *)(*state + 0x454) + 0x80) + *(int *)(*state + 0x80);
    if (state[0x10] < 0) {
        state[0x10] = 0;
    }
    if (face != 0) {
        state[0xb] = FX_Atan2(state[4], state[6]);
    }
    return 1;
}
