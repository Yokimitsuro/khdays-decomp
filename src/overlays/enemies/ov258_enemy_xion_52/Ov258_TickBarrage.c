/* Barrage tick of the ov258 actor: the +0x34 and +0x44 clocks run up at the frame rate with three step
 * cues (020cd6c8). The +0x50 stage counts down from 6: at 0.33 effect 10 under the owner, at 0.4 / 2.66
 * / 2.69 plain steps, at 3.15 effect 11 over the +0x448 hand, and after 25 shots the 0x2a aura at
 * (0, 15.6, 8.0) with effect 0x12 / 0x19 (rage). From 20.6 on, every 1/6 s a shot lands near the +0x454
 * partner: k = count % 10 picks on it (0), in front of it turned by its facing (1, 2; 2 on a random
 * side), or on a spiral of radius 10.5 around it with up to 2.5 jitter (3..9). A shot closer than 6.0
 * to the owner is pulled out to 4.5, raised by k/16 over -1.0 and fired (effect 0xc). Once the rig is
 * idle, 50 shots end in a follow-up (020cd2cc, without a +0x38 delay) or move 2; before that the rig
 * replays pose 0xc (first shot) or 0. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

typedef struct { int m[9]; } Mtx33;

extern int Ov258_AcquireTarget(int *node, int face);
extern void Ov258_StepCue(int *node, int step, int phase, unsigned int variant);
extern void func_ov107_020c0b90(int owner, int mode, VecFx32 at, int flag);
extern void Ov107_BuildAndSendUpdate(int actor, int bank, u16 variant, void *at);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *out);
extern int Ov258_PickMove(int *node);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const VecFx32 data_ov258_020d1838;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

/* Random value in [lo, hi]. */
static inline int RandRange(int lo, int hi)
{
    return RandNextScaled(hi - lo + 1) + lo;
}

void Ov258_TickBarrage(int *node)
{
    int *state = (int *)node[1];
    VecFx32 at;
    VecFx32 at2;
    VecFx32 pos;
    Mtx33 rot;
    VecFx32 off;
    VecFx32 target;
    VecFx32 d;
    u8 k;

    state[0xd] += *(int *)(node[0] + 0x2c);
    state[0x11] += *(int *)(node[0] + 0x2c);
    Ov258_AcquireTarget(node, 1);
    Ov258_StepCue(node, 1, 3, (u16)6);
    Ov258_StepCue(node, 0x36, 2, (u16)(*(int *)(*state + 0x460) != 0 ? 0x1b : 0x15));
    Ov258_StepCue(node, 0x5a, 1, (u16)7);
    if (state[0xd] >= 0x550 && *(u16 *)(state + 0x14) == 6) {
        at = *(VecFx32 *)state[3];
        (*(u16 *)(state + 0x14))--;
        at.y = -0xde00;
        func_ov107_020c0b90(*state, 10, at, 0);
    }
    if (state[0xd] >= 0x660 && *(u16 *)(state + 0x14) == 5) {
        (*(u16 *)(state + 0x14))--;
    }
    if (state[0xd] >= 0x2a80 && *(u16 *)(state + 0x14) == 4) {
        (*(u16 *)(state + 0x14))--;
    }
    if (state[0xd] >= 0x2b08 && *(u16 *)(state + 0x14) == 3) {
        (*(u16 *)(state + 0x14))--;
    }
    if (state[0xd] >= 0x3278 && *(u16 *)(state + 0x14) == 2) {
        at2 = *(VecFx32 *)(*(int *)(*state + 0x448) + 0x14);
        (*(u16 *)(state + 0x14))--;
        at2.y += 0xde00;
        func_ov107_020c0b90(*state, 0xb, at2, 0);
    }
    if (state[0xf] >= 0x19 && *(u16 *)(state + 0x14) == 1) {
        (*(u16 *)(state + 0x14))--;
        *(u8 *)(state + 0x15) |= 8;
        state[7] = 0;
        state[8] = 0xfa00;
        state[9] = 0x8000;
        Ov107_BuildAndSendUpdate(*state, *(short *)(state + 0x16), *(int *)(*state + 0x460) != 0 ? 0x12 : 0x19, state + 7);
        func_ov107_020c0b90(*state, 0x2a, *(VecFx32 *)(state + 7), 0);
        *(int *)(*state + 0x428) = 0x8000;
    }
    if (state[0xd] >= 0x5258 && (state[0xc] += *(int *)(node[0] + 0x2c)) >= 0x2a8) {
        k = state[0xf] % 10;
        switch (k) {
        case 0:
            pos = *(VecFx32 *)(*(int *)(*state + 0x454) + 0x190);
            break;
        case 1:
        case 2: {
            int angle = FX_Atan2(*(int *)(*(int *)(*state + 0x454) + 0x19c), *(int *)(*(int *)(*state + 0x454) + 0x1a4));

            off = data_ov258_020d1838;
            if (k == 2) {
                off.x = (RandNextScaled(2) == 0) * 0x5000 ? 1 : -1;
                off.y = 0;
                off.z = 0;
            }
            pos = *(VecFx32 *)(*(int *)(*state + 0x454) + 0x190);
            if (k == 3) {
                off.x = (signed char)(RandNextScaled(2) == 0 ? -1 : 1) * 0x5000;
                off.y = 0;
                off.z = 0;
            }
            {
                int idx = ANG2IDX(angle) * 2;

                MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
            }
            MTX_MultVec33(&off, &rot, &off);
            VEC_Add(&pos, &off, &pos);
            break;
        }
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9: {
            signed char sx = RandNextScaled(2) == 0 ? -1 : 1;
            signed char sz = RandNextScaled(2) == 0 ? -1 : 1;

            pos = k == 2 ? *(VecFx32 *)(*(int *)(*state + 0x454) + 0x190) : *(VecFx32 *)state[3];
            pos = *(VecFx32 *)(*(int *)(*state + 0x454) + 0x190);
            pos.x += sx * FX_MUL(data_0203d210[ANG2IDX((state[0xf] - 3 + state[0xf] / 10 * 3) * 0x6488 / 10) * 2], 0xa800);
            pos.z += sz * FX_MUL(data_0203d210[ANG2IDX((state[0xf] - 3 + state[0xf] / 10 * 3) * 0x6488 / 10) * 2 + 1], 0xa800);
            pos.x += sx * RandRange(0, 0x2800);
            pos.z += sz * RandRange(0, 0x2800);
            break;
        }
        }
        target = *(VecFx32 *)state[3];
        d = pos;
        d.y = 0;
        target.y = 0;
        VEC_Subtract(&d, &target, &d);
        if (VEC_Normalize(&d, &d) < 0x6000) {
            ScaleVec3Fx12(0x4800, &d, &d);
            pos = d;
        }
        pos.y = k * 0x100 + 0xfc00;
        func_ov107_020c0b90(*state, 0xc, pos, 0);
        state[0xf]++;
        state[0xc] = 0;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    if (state[0xf] >= 0x32) {
        if (state[0xe] == 0 && Ov258_PickMove(node) != 0) {
            SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (state[0xf] == 0) {
        Ov107_PostTagUpdate((Actor *)(*state), 0xc, 0);
    } else {
        Ov107_PostTagUpdate((Actor *)(*state), 0, 0);
    }
}
