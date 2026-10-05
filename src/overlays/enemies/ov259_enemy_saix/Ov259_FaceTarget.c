/* Face the ov259 actor's +8 target: +0x7c becomes the heading of the flattened offset from the
 * actor's +0xb0 position to the target's +0x190 point. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);

void Ov259_FaceTarget(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if (state[2] == 0) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    VEC_Normalize(&d, &d);
    state[0x1f] = FX_Atan2(d.x, d.z);
}
