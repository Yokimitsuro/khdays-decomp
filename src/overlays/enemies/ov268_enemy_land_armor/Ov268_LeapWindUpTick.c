/* Leap wind-up tick of the ov268 enemy (x3 with ov208/ov209). The +0x2c timer accumulates the
 * owner's rate; once past 0xeee reaction 0x15f mode 0xa fires at the +0xc point (once, flag
 * +0x49). When the +0x50 idle byte is clear, effect 4 spawns at the +8 point, bit 0 of +0x1ae is
 * raised, animation 0xc plays (mode 1) and the target is re-acquired into +0x10 with the +0x54
 * direction zeroed: with a target the flattened unit direction from the +8 point towards its
 * +0x190 is taken, or, when that is degenerate, the sine/cosine of the +0x30 heading, and the
 * direction is scaled by a twenty-fifth of the length; y then becomes 1.0, +0x34 takes the heading
 * of the direction and the tick hands over to Ov268_AdvanceAimGiveUp. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

extern void Ov107_BuildAndSendUpdate(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int b);
extern int Ov107_FindNearestObject(int owner, int flag);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const VecFx32 data_02041dc8;
extern const short data_0203d210[];
extern void Ov268_AdvanceAimGiveUp(int *node);

void Ov268_LeapWindUpTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    int len;
    unsigned short idx;

    state[0xb] += *(int *)(node[0] + 0x2c);
    if (*(u8 *)((char *)state + 0x49) == 0 && state[0xb] >= 0xeee) {
        Ov107_BuildAndSendUpdate(*state, 0x15f, 0xa, (void *)state[3]);
        *(u8 *)((char *)state + 0x49) = 1;
    }
    if (*(u8 *)state[0x14] != 0) {
        return;
    }
    func_ov107_020c0b90(*state, 4, *(VecFx32 *)state[2], 0);
    *(u16 *)(*state + 0x100 + 0xae) |= 1;
    Ov107_PostTagUpdate((Actor *)(*state), 0xc, 1);
    *(VecFx32 *)(state + 0x15) = data_02041dc8;
    state[4] = Ov107_FindNearestObject(*state, 0);
    if (state[4] != 0) {
        VEC_Subtract((VecFx32 *)(state[4] + 0x190), (VecFx32 *)state[2], &d);
        d.y = 0;
        len = VEC_Normalize(&d, (VecFx32 *)(state + 0x15));
        if (len == 0) {
            idx = FX_RadToIdx(state[0xc]);
            state[0x15] = data_0203d210[(idx >> 4) * 2];
            state[0x16] = 0;
            state[0x17] = data_0203d210[(idx >> 4) * 2 + 1];
        }
        ScaleVec3Fx12(len / 25, (VecFx32 *)(state + 0x15), (VecFx32 *)(state + 0x15));
    }
    state[0x16] = 0x1000;
    state[0xd] = FX_Atan2(state[0x15], state[0x17]);
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), (void *)Ov268_AdvanceAimGiveUp);
}
