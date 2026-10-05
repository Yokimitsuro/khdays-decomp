/* Dive tick of the ov259 enemy: the +0x68 clock runs up at the frame rate and the +0x14 velocity is
 * rebuilt from the facing towards the +0x10 target (+0x78 / +0x7c yaw from the +0x2c position, the
 * unit direction's height kept), or the latched +0x38 velocity once +0x60 is set; 020cddbc steps
 * along it and returns the remaining distance, and the climb rate eases down by half the clock from
 * 0.4. Within 28 floors (+0x80 of the owner) the dive pose 0x1a starts once (+0x54) with the body
 * glow (020d1700) and +0x420 = 7; within two floors the velocity is latched (+0x60); within seven the
 * owner's +0x60 bit 14 drops. A latched dive that is five floors away again pulls up: bit 10 drops,
 * message 9 at the target, sub-state 12. Otherwise the dive ends on landing (+0x17a bit 0): pose
 * 0x19, messages 2 and 0xf at the target, wing flap 3, effect 0x14, and 020d13cc runs next. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

struct b1 { unsigned char b0 : 1; };

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int y, int x);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern int Ov259_ComputeNormalizedDir(int *node, VecFx32 pos);
extern void Ov259_MirrorPartnerPose(int *node, int pose, int loop);
extern void Ov259_ForwardSweep(int body, int a, int b, VecFx32 v);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov259_MapHeldItemKindToAnim(int actor, int flag);
extern void Ov259_ArmPartnerCue(int *node, int effect, int loop);
extern void Ov259_SlamSweepTick(void);
extern const VecFx32 data_02041dc8;
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov259_TickDive(int *node)
{
    int *state = (int *)node[1];
    VecFx32 zero;
    VecFx32 d;
    VecFx32 n;
    int dist;
    int owner;

    state[0x1a] += *(int *)(node[0] + 0x2c);
    zero = data_02041dc8;
    *(VecFx32 *)(state + 5) = data_02041dc8;
    VEC_Subtract((VecFx32 *)(state + 0xb), (VecFx32 *)state[4], &d);
    state[0x1e] = state[0x1f] = FX_Atan2(d.x, d.z);
    VEC_Normalize(&d, &n);
    {
        int idx = ANG2IDX(state[0x1e]) * 2;
        int y = n.y;

        state[5] = data_0203d210[idx];
        state[6] = y;
        state[7] = data_0203d210[idx + 1];
    }
    if (state[0x18] != 0) {
        *(VecFx32 *)(state + 5) = *(VecFx32 *)(state + 0xe);
    }
    dist = Ov259_ComputeNormalizedDir(node, *(VecFx32 *)(state + 0xb));
    state[6] += 0x660 - state[0x1a] / 2;
    if (dist < *(int *)(*state + 0x80) * 0x1c && state[0x15] == 0) {
        Ov107_PostTagUpdate((Actor *)(*state), 0x1a, 0);
        Ov259_MirrorPartnerPose(node, 0x1a, 0);
        Ov259_ForwardSweep(*(int *)(*state + 0x384), 0x330, 0xee0, zero);
        *(int *)(*state + 0x420) = 7;
        state[0x15] = 1;
    }
    if (state[0x18] == 0 && dist < *(int *)(*state + 0x80) * 2) {
        *(VecFx32 *)(state + 0xe) = *(VecFx32 *)(state + 5);
        state[0x18] = 1;
    }
    owner = *state;
    if (dist < *(int *)(owner + 0x80) * 7) {
        u16 hw60 = *(u16 *)(owner + 0x60);
        *(u16 *)(owner + 0x60) =
            (hw60 & ~0xff00) |
            (((unsigned int)(u16)((((unsigned int)hw60 << 0x10) >> 0x18) & ~0x40) << 0x18) >> 0x10);
    }
    if (state[0x18] != 0 && dist > *(int *)(*state + 0x80) * 5) {
        owner = *state;
        {
            u16 hw60 = *(u16 *)(owner + 0x60);
            *(u16 *)(owner + 0x60) =
                (hw60 & ~0xff00) |
                (((unsigned int)(u16)((((unsigned int)hw60 << 0x10) >> 0x18) & ~4) << 0x18) >> 0x10);
        }
        func_ov107_020c0b90(*state, 9, *(VecFx32 *)state[4], 0);
        state[0x15] = 0;
        *(u8 *)(*state + 0x1c7) = 0xc;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (((struct b1 *)(*state + 0x17a))->b0 != 0) {
        Ov107_PostTagUpdate((Actor *)(*state), 0x19, 0);
        Ov259_MirrorPartnerPose(node, 0x19, 0);
        func_ov107_020c0b90(*state, 2, *(VecFx32 *)state[4], 0);
        func_ov107_020c0b90(*state, 0xf, *(VecFx32 *)state[4], 0);
        Ov259_MapHeldItemKindToAnim(*state, 3);
        Ov259_ArmPartnerCue(node, 0x14, 0);
        state[0x1a] = 0;
        state[0x22] = 0;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov259_SlamSweepTick);
        return;
    }
}
