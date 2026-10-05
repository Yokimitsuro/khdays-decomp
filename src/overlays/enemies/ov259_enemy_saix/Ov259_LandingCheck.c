/* Landing check of the ov259 actor: the +0x14 velocity stops and, once grounded or against a wall
 * (+0x17a bits 0 / 1), it turns to the +8 target (+0x78 / +0x7c heading) and the next move is 0xa. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02041dc8;

void Ov259_LandingCheck(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    *(VecFx32 *)(state + 5) = data_02041dc8;
    if (!((struct Flag17a *)(*state + 0x17a))->b0 && !((struct Flag17a *)(*state + 0x17a))->b1) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
    state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    *(signed char *)(*state + 0x1c7) = 0xa;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
