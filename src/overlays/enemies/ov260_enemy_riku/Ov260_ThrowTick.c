/* Throw tick of the ov260 actor: the +0x70 timer accumulates the frame rate and the throw steps fire
 * once each (+0x7b bits): at 0xaa0 the actor is knocked back at the origin (mode 1), at 0xbb0 and
 * 0x2530 effects 0xe and 0xf start at the +0x10 point. Until the throw it keeps aiming at the +0x420
 * target (+0x68); at 0x2a80 the +0x42c part is released from the hand point (-0.11, 1.08, 1.43 turned
 * by the +0xa0 pose, from the +0x10 point) along the +0x64 heading (020d17b4) and effect 0x19 starts.
 * After the throw, once the partner holds no queued move, the next move is 2 and the node ends. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov260_PlaySound(int owner, int mode, int arg);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov260_PlacePart(int part, VecFx32 *at, VecFx32 *dir);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const VecFx32 data_02041dc8;

static inline void VecSet(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

void Ov260_ThrowTick(int *node)
{
    int *state = (int *)node[1];
    VecFx32 d;
    VecFx32 hand;
    VecFx32 dir;

    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0xaa0) {
        *((u8 *)state + 0x7b) |= 1;
        func_ov107_020c0b90(*state, 1, data_02041dc8, 0);
    }
    if ((*((u8 *)state + 0x7b) & 2) == 0 && state[0x1c] >= 0xbb0) {
        *((u8 *)state + 0x7b) |= 2;
        Ov260_PlaySound(*state, 0xe, state[4]);
    }
    if ((*((u8 *)state + 0x7b) & 4) == 0 && state[0x1c] >= 0x2530) {
        *((u8 *)state + 0x7b) |= 4;
        Ov260_PlaySound(*state, 0xf, state[4]);
    }
    if ((*((u8 *)state + 0x7b) & 8) == 0) {
        VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x420) + 0x190), (VecFx32 *)state[4], &d);
        state[0x1a] = FX_Atan2(d.x, d.z);
        if (state[0x1c] < 0x2a80) {
            return;
        }
        *((u8 *)state + 0x7b) |= 8;
        {
            int idx = ANG2IDX(state[0x19]) * 2;

            VecSet(&dir, data_0203d210[idx], 0, data_0203d210[idx + 1]);
            VecSet(&hand, -0x1d0, 0x114d, 0x16e6);
        }
        Vec3TransformViaTempMtx(&hand, (void *)(*state + 0xa0), &hand);
        VEC_Add(&hand, (VecFx32 *)state[4], &hand);
        Ov260_PlacePart(*(int *)(*state + 0x42c), &hand, &dir);
        Ov260_PlaySound(*state, 0x19, state[4]);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
