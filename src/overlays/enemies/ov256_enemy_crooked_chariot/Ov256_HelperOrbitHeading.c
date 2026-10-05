/* Heading from an ov256 helper's orbit point (+0xc anchor plus the +0x10 offset) toward its +0x34
 * target, as a flat angle. */

#include "nitro/fx_types.h"

extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);

int Ov256_HelperOrbitHeading(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 p;

    p = *(VecFx32 *)state[3];
    VEC_Add(&p, (VecFx32 *)(state + 4), &p);
    VEC_Subtract(&p, (VecFx32 *)(state + 0xd), &d);
    return FX_Atan2(d.x, d.z);
}
