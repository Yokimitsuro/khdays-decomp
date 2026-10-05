/* Gap to the ov259 actor's +8 target, floored at 0, after facing it (+0x7c heading). Without a
 * target the actor goes to move 2 and the node ends (the result is then left undefined, as in the
 * original). */

#include "nitro/fx_types.h"

extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);

int Ov259_FaceTargetGap(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int gap;

    if (state[2] == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    } else {
        VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
        gap = VEC_Normalize(&d, &d) - (*(int *)(state[2] + 0x80) + *(int *)(*state + 0x80));
        if (gap < 0) {
            gap = 0;
        }
        state[0x1f] = FX_Atan2(d.x, d.z);
        return gap;
    }
}
