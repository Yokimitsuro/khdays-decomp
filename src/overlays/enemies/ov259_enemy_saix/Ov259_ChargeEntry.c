/* Charge entry of the ov259 actor: it turns to the +8 target (+0x78 / +0x7c heading), pose 0x11
 * plays on the actor and its partner (020cd524), the body sweeps 0x908-0xb28 flat (020d1700,
 * +0x420 = 4), +0x88 = 0.875 and +0x94 = 100, the timers, step and cue flags, +0xa8 and +0x70 clear,
 * +0xae becomes 0x10 and the node moves on to 020cff54. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void Ov259_MirrorPartnerPose(int *node, int pose, int mode);
extern void Ov259_ForwardSweep(int body, int a, int b, VecFx32 lift);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_SweepSequenceTick(void);
extern const VecFx32 data_02041dc8;

void Ov259_ChargeEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0x74), &d);
    VEC_Normalize(&d, &d);
    state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    Ov107_PostTagUpdate((Actor *)(*state), 0x11, 0);
    Ov259_MirrorPartnerPose(node, 0x11, 0);
    Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x908, 0xb28, data_02041dc8);
    *(int *)(*state + 0x420) = 4;
    state[0x22] = 0xe00;
    state[0x25] = 100;
    state[0x1a] = 0;
    state[0x26] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x2a] = 0;
    *((u8 *)state + 0xae) = 0x10;
    state[0x1c] = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_SweepSequenceTick);
}
