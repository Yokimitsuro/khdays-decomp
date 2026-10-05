/* Down entry of the ov259 actor: it turns to the +8 target (+0x78 / +0x7c heading), the +0x68 timer,
 * cue flags, +0x4c and +0xae clear and the +0xa0 knock-down count grows; the recovery time +0x64
 * lengthens with it (0xff0, 0x2fd0, 0x4fb0, then 0x5fa0). With no health left (+0x21a) bits 0-1 of
 * +0x1ae are set. Sound 0x172/0x1b fires at the +0x10 point, the actor is knocked back there (mode
 * 4), pose 5 plays on the actor and its partner, the +0x384 rig closes (020d1764), bit 6 of the +0x60
 * high byte drops, pose 0x16 is queued (020cd628) and the node moves on to 020cfc40. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void Ov259_PlaySound(int actor, int id, int variant, void *at);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov259_MirrorPartnerPose(int *node, int pose, int mode);
extern void Ov259_SwapShells(int rig, int open);
extern void Ov259_ArmPartnerCue(int *node, int pose, int delay);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_DownTick(void);

void Ov259_DownEntry(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)(*state + 0x74), &d);
    VEC_Normalize(&d, &d);
    state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    state[0x1a] = 0;
    *((unsigned char *)state + 0xac) = 0;
    state[0x13] = 0;
    state[0x28]++;
    *((unsigned char *)state + 0xae) = 0;
    if (state[0x28] == 1) {
        state[0x19] = 0xff0;
    } else if (state[0x28] == 2) {
        state[0x19] = 0x2fd0;
    } else if (state[0x28] == 3) {
        state[0x19] = 0x4fb0;
    } else {
        state[0x19] = 0x5fa0;
    }
    if (*(short *)(*state + 0x21a) <= 0) {
        *(u16 *)(*state + 0x1ae) |= 3;
    }
    Ov259_PlaySound(*state, 0x172, 0x1b, (void *)state[4]);
    func_ov107_020c0b90(*state, 4, *(VecFx32 *)state[4], 0);
    Ov107_PostTagUpdate((Actor *)(*state), 5, 0);
    Ov259_MirrorPartnerPose(node, 5, 0);
    Ov259_SwapShells(*(int *)(*state + 0x384), 0);
    {
        u16 hw = *(u16 *)(*state + 0x60);
        *(u16 *)(*state + 0x60) = (hw & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    Ov259_ArmPartnerCue(node, 0x16, 0);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_DownTick);
}
