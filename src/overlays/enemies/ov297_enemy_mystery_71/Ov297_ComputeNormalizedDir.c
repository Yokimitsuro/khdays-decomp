/* Returns the distance from the actor to the point (normalising the direction vector). */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Normalize(void *dst, void *src);

int Ov297_ComputeNormalizedDir(int node, VecFx32 pos) {
    int diff[3];

    VEC_Subtract(&pos, (void *)(**(int **)(node + 4) + 0xb0), diff);
    return VEC_Normalize(diff, diff);
}
