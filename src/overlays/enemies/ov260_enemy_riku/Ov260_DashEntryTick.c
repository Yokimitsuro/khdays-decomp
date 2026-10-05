/* Dash entry tick of the ov260 actor: with a +8 target it turns to it (+0x64 / +0x68 heading), pose
 * 0xa plays, its +0x428 part takes motion 4, the actor is knocked back at the origin (mode 0xd, 8)
 * and at the +0x10 point (mode 9), effect 0x1c starts there, +0x70 and the +0x7b flag clear, the dash
 * starts (+0x7c) and the node moves on to 020d04bc. Without one, once the partner holds no queued move,
 * pose 0xb plays, the origin knock-back (mode 0xd, 8) runs and the node moves on the same way. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov260_PlaySound(int owner, int mode, int arg);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov260_DashTick(void);
extern const VecFx32 data_02041dc8;

void Ov260_DashEntryTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if (state[2] != 0) {
        VEC_Subtract((VecFx32 *)(state[2] + 0x190), (VecFx32 *)state[4], &d);
        state[0x19] = state[0x1a] = FX_Atan2(d.x, d.z);
        Ov107_PostTagUpdate((Actor *)(*state), 0xa, 0);
        Ov107_StartAnim(*(int *)(*state + 0x428), 4, 0);
        func_ov107_020c0b90(*state, 0xd, data_02041dc8, 8);
        func_ov107_020c0b90(*state, 9, *(VecFx32 *)state[4], 0);
        Ov260_PlaySound(*state, 0x1c, state[4]);
        state[0x1c] = 0;
        *((u8 *)state + 0x7b) = 0;
        state[0x1f] = 1;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov260_DashTick);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0xb, 0);
    func_ov107_020c0b90(*state, 0xd, data_02041dc8, 8);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov260_DashTick);
}
