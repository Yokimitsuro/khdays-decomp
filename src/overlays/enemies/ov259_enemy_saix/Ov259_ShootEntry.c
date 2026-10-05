/* Shoot entry of the ov259 actor: the +0x68 timer and +0xac cue flags clear, +0x94 = 180; with a
 * +0xc aim target it faces it (+0x78 / +0x7c heading); +0x58 is set, pose 0xc plays on the actor
 * and its partner (020cd524), the shot is armed (020cd628: pose 0xf after 0x2a8) and the node moves
 * on to 020ce944. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void Ov259_MirrorPartnerPose(int *node, int pose, int mode);
extern void Ov259_ArmPartnerCue(int *node, int pose, int delay);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_AiQueue2OnAnimEnd(void);

void Ov259_ShootEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    state[0x1a] = 0;
    *((u8 *)state + 0xac) = 0;
    state[0x25] = 0xb4;
    if (state[3] != 0) {
        VEC_Subtract((VecFx32 *)(state[3] + 0x190), (VecFx32 *)(*state + 0xb0), &d);
        state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    }
    state[0x16] = 1;
    Ov107_PostTagUpdate((Actor *)(*state), 0xc, 0);
    Ov259_MirrorPartnerPose(node, 0xc, 0);
    Ov259_ArmPartnerCue(node, 0xf, 0x2a8);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_AiQueue2OnAnimEnd);
}
