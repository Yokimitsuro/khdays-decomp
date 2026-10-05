/* Lob tick of the ov260 actor: the +0x20 velocity is its +0x428 part's +0x2c vector turned by the
 * +0x64 heading and the +0x70 timer accumulates the frame rate. The lob steps fire once each (+0x7b
 * bits): at 0xaa0 the actor is knocked back at the origin (mode 1) with effect 0x1e, at 0xbb0 and
 * 0x2970 effects 0xe and 0x13, at 0x550 and 0x990 the cues (020cd04c 2 / 3). Until the lob it aims at
 * the +0x420 target (+0x68); at 0x2a80 the +0x430 part is lobbed from the hand point (-0.16, 1.33,
 * 1.46 turned by the +0xa0 pose, from the +0x10 point) along the heading to a spot 0.5 short of to
 * 3.0 past the target (020d09a4). Afterwards it waits while the part is still in flight (+0x60 bit 0);
 * a landed part (+0x38c) queues move 7, otherwise once the partner holds no queued move, move 2. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;
struct Ov260Parts { char pad[0x430]; int parts[2]; };
struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov260_PlaySound(int owner, int mode, int arg);
extern void Ov260_MapHeldItemKindToAnim(int actor, int flag);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Ov260_PlacePartSpan(int part, VecFx32 *at, VecFx32 *from, VecFx32 *to);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const VecFx32 data_02041dc8;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void VecSet(VecFx32 *v, int x, int y, int z)
{
    v->x = x;
    v->y = y;
    v->z = z;
}

void Ov260_LobTick(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    VecFx32 d;
    VecFx32 hand;
    VecFx32 dir;
    VecFx32 dst;

    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((VecFx32 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (VecFx32 *)(state + 8));
    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0xaa0) {
        *((u8 *)state + 0x7b) |= 1;
        func_ov107_020c0b90(*state, 1, data_02041dc8, 0);
        Ov260_PlaySound(*state, 0x1e, state[4]);
    }
    if ((*((u8 *)state + 0x7b) & 2) == 0 && state[0x1c] >= 0xbb0) {
        *((u8 *)state + 0x7b) |= 2;
        Ov260_PlaySound(*state, 0xe, state[4]);
    }
    if ((*((u8 *)state + 0x7b) & 4) == 0 && state[0x1c] >= 0x2970) {
        *((u8 *)state + 0x7b) |= 4;
        Ov260_PlaySound(*state, 0x13, state[4]);
    }
    if ((*((u8 *)state + 0x7b) & 8) == 0 && state[0x1c] >= 0x550) {
        *((u8 *)state + 0x7b) |= 8;
        Ov260_MapHeldItemKindToAnim(*state, 2);
    }
    if ((*((u8 *)state + 0x7b) & 0x10) == 0 && state[0x1c] >= 0x990) {
        *((u8 *)state + 0x7b) |= 0x10;
        Ov260_MapHeldItemKindToAnim(*state, 3);
    }
    if ((*((u8 *)state + 0x7b) & 0x80) == 0) {
        VEC_Subtract((VecFx32 *)(*(int *)(*state + 0x420) + 0x190), (VecFx32 *)state[4], &d);
        state[0x1a] = FX_Atan2(d.x, d.z);
        if (state[0x1c] < 0x2a80) {
            return;
        }
        *((u8 *)state + 0x7b) |= 0x80;
        {
            int idx = ANG2IDX(state[0x19]) * 2;
            const short *sc;

            dir.x = data_0203d210[idx];
            sc = &data_0203d210[idx];
            dir.y = 0;
            dir.z = sc[1];
        }
        ScaleVec3Fx12(RandNextScaled(0x3801) - 0x800, &dir, &dst);
        VEC_Add(&dst, (VecFx32 *)(*(int *)(*state + 0x420) + 0x190), &dst);
        VecSet(&hand, -0x28a, 0x1545, 0x1545 + 0x214);
        Vec3TransformViaTempMtx(&hand, (void *)(*state + 0xa0), &hand);
        VEC_Add(&hand, (VecFx32 *)state[4], &hand);
        Ov260_PlacePartSpan(*(int *)(*state + 0x430), &hand, &dir, &dst);
        return;
    }
    {
        int i;
        int busy = 0;
        int landed = 0;

        for (i = 0; i < 1; i++) {
            int part = ((struct Ov260Parts *)*state)->parts[i];

            if (((struct flags16 *)(part + 0x60))->lo & 1) {
                busy = 1;
                break;
            }
            if (*(int *)(part + 0x38c) != 0) {
                landed = 1;
            }
        }
        if (busy) {
            return;
        }
        if (landed) {
            *(signed char *)(*state + 0x1c7) = 7;
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        if (*(u8 *)(state[1] + 0xad) != 0) {
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
