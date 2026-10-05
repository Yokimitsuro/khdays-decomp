/* Guard entry of the ov146 actor: pose 2 plays; with a partner guard (+0x58) the partner plays it too
 * and, with a pending move (+0x5c), the partner moves to the +0x1c point (020ce2d0) and the +0x3bc
 * effect stops. With a target (+0x54) both headings turn to it; +0x48 clears and the node moves on to
 * 020cdd74. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov146_Rider_LaunchIfReady(int partner, VecFx32 at);
extern int Ov146_Mount_SetStateIfReady(int param_1, int param_2);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov146_HopTick(void);

void Ov146_GuardEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    if (state[0x16] != 0) {
        Ov107_PostTagUpdate((Actor *)state[2], 2, 0);
        if (state[0x17] != 0) {
            Ov146_Rider_LaunchIfReady(state[2], *(VecFx32 *)(state + 7));
            Ov146_Mount_SetStateIfReady(*(int *)(*state + 0x3bc), 0);
        }
    }
    if (state[0x15] != 0) {
        VEC_Subtract((VecFx32 *)(state[0x15] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
        state[0xa] = state[0xb] = FX_Atan2(d.x, d.z);
    }
    state[0x12] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov146_HopTick);
}
