/* Target check of the ov252 actor: the nearest target (020cab14) goes to +0x4e4; without one the next
 * move is 2 and 0 is returned. Otherwise returns the ground-plane gap between the two bodies (distance
 * minus both +0x80 radii, at least 0); with `face` the +0x58 heading turns toward the target, and
 * `delta` (when given) receives the ground-plane offset to it. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int Ov107_FindNearestObject(int actor, int *distOut);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);

int Ov252_CheckTarget(int *node, VecFx32 *delta, int face)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int gap;

    *(int *)(*state + 0x4e4) = Ov107_FindNearestObject(*state, 0);
    if (*(int *)(*state + 0x4e4) == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        return 0;
    }
    VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x4e4) + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    d.y = 0;
    gap = VEC_Normalize(&d, &d);
    gap -= (*(int *)(*(int *)(*state + 0x4e4) + 0x80) + *(int *)(*state + 0x80));
    if (gap < 0) {
        gap = 0;
    }
    if (face != 0) {
        state[0x16] = FX_Atan2(d.x, d.z);
    }
    if (delta != 0) {
        *delta = d;
    }
    return gap;
}
