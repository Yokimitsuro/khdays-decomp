/* Target pick of the ov256 actor: the nearest live entity (020cab14) becomes the +0x430 target;
 * without one the next move is the +0x74 mode + 2 and 0 is returned. Otherwise +0x34 is the unit
 * direction from the +0xb0 anchor to the target's +0x190 point, +0x58 the gap (distance minus both
 * +0x80 radii, at least 0), +0x44 the heading, and 1 is returned. */

#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int obj, int kind);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);

int Ov256_PickTarget(int *node)
{
    int *state = (int *)node[1];

    *(int *)(*state + 0x430) = Ov107_FindNearestObject(*state, 0);
    if (*(int *)(*state + 0x430) == 0) {
        *(signed char *)(*state + 0x1c7) = state[0x1d] + 2;
        return 0;
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x430) + 0x190), (VecFx32 *)(*state + 0xb0), (VecFx32 *)(state + 0xd));
    state[0x16] = VEC_Normalize((VecFx32 *)(state + 0xd), (VecFx32 *)(state + 0xd));
    if ((state[0x16] -= *(int *)(*(int *)(*state + 0x430) + 0x80) + *(int *)(*state + 0x80)) < 0) {
        state[0x16] = 0;
    }
    state[0x11] = FX_Atan2(state[0xd], state[0xf]);
    return 1;
}
