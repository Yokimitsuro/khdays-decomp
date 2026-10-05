/* Latch the secondary camera target and drop the three view flags that depend on
 * it. A null target leaves everything alone. The three-word copy is a WHOLE-
 * STRUCT assignment, which is what produces the ldm/stm pair. */

#include "nitro/fx_types.h"

typedef struct {
    char pad0000[0xd4];
    unsigned int dwViewFlags;   /* +0xd4 */
} CameraState;

extern VecFx32 data_02047458;
extern CameraState NNS_G3dGlb;

void NNS_G3dGlbSetBaseScale(const VecFx32 *target) {
    if (target == 0) {
        return;
    }

    data_02047458 = *target;
    NNS_G3dGlb.dwViewFlags &= ~0xa4;
}
