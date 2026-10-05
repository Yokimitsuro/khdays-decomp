/* Grab release of the ov228 enemy: with a +8 held actor and the +0x1c4 flags clear of bit 1,
 * the +0x40/+0x44 yaws face from the +0xc position to the held actor's +0x190 point and the
 * hold is dropped; animation 0xc plays, the overlay's animation 9 starts, effect 2 spawns at the
 * origin, reaction 0x12b mode 4 fires at the position, the +0x4c timer and +0x61 flag reset and
 * the tick hands off to d1d14. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract(void *a, void *b, VecFx32 *d);
extern fx16 FX_Atan2(int x, int z);
extern void Ov229_startAnim(int actor, int anim);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int b);
extern void Ov107_BuildAndSendUpdate(int actor, int a, int id, void *at);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov229_AiSlamWindup(int *node);
extern VecFx32 data_02041dc8;

void Ov229_GrabRelease(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;

    if (state[2] != 0 && (*(unsigned char *)((char *)state + 0x1c4) & 2) == 0) {
        VEC_Subtract((void *)(state[2] + 0x190), (void *)state[3], &d);
        state[0x10] = state[0x11] = FX_Atan2(d.x, d.z);
        state[2] = 0;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 0xc, 0);
    Ov229_startAnim(*state, 9);
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    Ov107_BuildAndSendUpdate(*state, 0x12b, 4, (void *)state[3]);
    state[0x13] = 0;
    *(unsigned char *)((char *)state + 0x61) = 0;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov229_AiSlamWindup);
}
