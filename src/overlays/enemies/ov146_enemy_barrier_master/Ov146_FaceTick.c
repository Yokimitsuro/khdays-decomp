/* Face tick of the ov146 actor: the +0x2c heading turns toward its partner (+8) on the ground plane;
 * once the partner holds no queued move the next move is 4 and the node ends. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov146_FaceTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    VEC_Subtract((VecFx32 *)(state[2] + 0xb0), (VecFx32 *)(*state + 0xb0), &d);
    VEC_Normalize(&d, &d);
    state[0xb] = FX_Atan2(d.x, d.z);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    *(unsigned char *)(*state + 0x1c7) = 4;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
