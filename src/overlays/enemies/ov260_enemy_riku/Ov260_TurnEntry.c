/* Turn entry of the ov260 actor: with a +8 target it faces it from the +0x10 point (+0x64 / +0x68
 * heading), pose 8 plays, +0x7c, the target and the +0x79 flag clear and the node moves on to
 * 020d02ac. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov260_TickRecovery(void);

void Ov260_TurnEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if (state[2] != 0) {
        VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)state[4], &d);
        state[0x19] = state[0x1a] = FX_Atan2(d.x, d.z);
    }
    Ov107_PostTagUpdate((Actor *)(*state), 8, 0);
    state[0x1f] = 0;
    state[2] = 0;
    *((u8 *)state + 0x79) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov260_TickRecovery);
}
