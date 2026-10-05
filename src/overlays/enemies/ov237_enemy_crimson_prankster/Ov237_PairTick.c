/* Pair tick (brain slot 2) of the ov237 actor: a pending +0x58 reacquires the target (020cd830) and
 * +0x20 keeps the frame rate. A linked, merged pair builds the +0x2c merge timer (to 40.0, then +0x5c);
 * a +0x4bc landing on either side sets bits 1, 2 and 4 of both +0x60 high bytes, and the landed state,
 * the +0x4c4 rejoin point (from the side in move 0xc), a saved +0x4a0 health, the +0x4b8 hold (the
 * weaker side of a split pair) and the +0x4a8 request are kept in sync; a split partner closer than 7.0
 * turns the +0x3c aim away by data_ov237_020d1bc4. In move 2 the +0x28 cooldown runs down (twice as fast
 * unless paired and merged), the +0x494 grab time takes the shorter side, both sides at 0 health start
 * move 3 (+0x4c0). The +0x10 heading turns toward +0x14 at the +0x20 rate and orients the pose, and the
 * +0x3c velocity is handed to the actor (+0xf0) and cleared. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/engine.h"

typedef struct { int x, y, z, w; } Quat;
typedef struct { int m[9]; } Mtx33;

extern int Ov237_TargetGap(int *node);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern void VEC_Add(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern void Srt_SetRotationQuat(void *srt, const Quat *rot);
extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);
extern const short data_0203d210[];
extern const VecFx32 data_ov237_020d1bc4;
extern const VecFx32 data_02042264;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define ACTOR ((char *)*state)
#define PARTNER (*(char **)(ACTOR + 0x4a4))

void Ov237_PairTick(int *node)
{
    int *state = (int *)node[1];
    Quat q;
    VecFx32 d;
    VecFx32 off;
    Mtx33 rot;

    if (state[0x16] != 0) {
        Ov237_TargetGap(node);
    }
    state[8] = *(int *)(node[0] + 0x2c);
    if (*(int *)(ACTOR + 0x4ac) != 0 && state[0x17] == 0 && *(int *)(PARTNER + 0x4b0) == 0) {
        if (state[0xb] < 0x28000) {
            state[0xb] += *(int *)(node[0] + 0x2c);
        }
        if (state[0xb] >= 0x28000) {
            state[0xb] = 0;
            state[0x17] = 1;
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0) {
        if (*(int *)(ACTOR + 0x4bc) != 0) {
            {
                u16 hw = *(u16 *)(ACTOR + 0x60);

                *(u16 *)(ACTOR + 0x60) = (hw & ~0xff00) |
                    ((((((unsigned int)hw << 0x10) >> 0x18) | 0x16) << 0x18) >> 0x10);
            }
            {
                u16 hw = *(u16 *)(PARTNER + 0x60);

                *(u16 *)(PARTNER + 0x60) = (hw & ~0xff00) |
                    ((((((unsigned int)hw << 0x10) >> 0x18) | 0x16) << 0x18) >> 0x10);
            }
            *(int *)(ACTOR + 0x4bc) = 0;
            *(int *)(PARTNER + 0x4bc) = 0;
        }
        if (*(int *)(PARTNER + 0x4bc) != 0) {
            *(int *)(ACTOR + 0x4bc) = 1;
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0) {
        if (*(signed char *)(ACTOR + 0x1c6) == 0xc) {
            *(VecFx32 *)(PARTNER + 0x4c4) = *(VecFx32 *)(ACTOR + 0x4c4);
        } else if (*(signed char *)(PARTNER + 0x1c6) == 0xc) {
            *(VecFx32 *)(ACTOR + 0x4c4) = *(VecFx32 *)(PARTNER + 0x4c4);
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0 && *(short *)(PARTNER + 0x4a0) != 0) {
        *(short *)(ACTOR + 0x21a) = *(short *)(PARTNER + 0x4a0);
        *(short *)(PARTNER + 0x4a0) = 0;
    }
    if (*(int *)(ACTOR + 0x4ac) != 0) {
        *(int *)(ACTOR + 0x4b8) = 0;
        *(int *)(PARTNER + 0x4b8) = 0;
        if (*(int *)(PARTNER + 0x4b0) != 0) {
            if (*(short *)(PARTNER + 0x21a) < *(short *)(ACTOR + 0x21a)) {
                *(int *)(PARTNER + 0x4b8) = 1;
            } else if (*(short *)(PARTNER + 0x21a) > *(short *)(ACTOR + 0x21a)) {
                *(int *)(ACTOR + 0x4b8) = 1;
            }
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0 && *(int *)(PARTNER + 0x4b0) != 0 && *(signed char *)(PARTNER + 0x1c6) != 0xd) {
        int dist;
        int ang;

        VEC_Subtract((VecFx32 *)(PARTNER + 0xb0), (VecFx32 *)state[0xe], &d);
        dist = VEC_Normalize(&d, &d);
        ang = FX_Atan2(d.x, d.z);
        if (dist < 0x7000) {
            off = data_ov237_020d1bc4;
            {
                int idx = ANG2IDX(ang) * 2;

                MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
            }
            MTX_MultVec33(&off, &rot, &off);
            VEC_Add((VecFx32 *)(state + 0xf), &off, (VecFx32 *)(state + 0xf));
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0 && *(int *)(PARTNER + 0x4b0) != 0) {
        if (*(signed char *)(PARTNER + 0x1c6) == 2 && *(signed char *)(ACTOR + 0x1c6) == 2) {
            *(int *)(ACTOR + 0x4a8) = 1;
        }
        if (*(signed char *)(ACTOR + 0x1c6) != 0xc) {
            *(int *)(PARTNER + 0x4a8) = *(int *)(ACTOR + 0x4a8);
        }
        if (*(signed char *)(ACTOR + 0x1c6) == 0xc) {
            *(int *)(PARTNER + 0x4a8) = 1;
        } else if (*(signed char *)(PARTNER + 0x1c6) == 0xc) {
            *(int *)(ACTOR + 0x4a8) = 1;
        }
    }
    if (state[0xa] > 0 && *(signed char *)(ACTOR + 0x1c6) == 2) {
        if ((*(int *)(ACTOR + 0x4ac) != 0 && *(int *)(ACTOR + 0x4b0) != 0) || *(int *)(ACTOR + 0x4ac) == 0) {
            state[0xa] -= *(int *)(node[0] + 0x2c) * 2;
        } else {
            state[0xa] -= *(int *)(node[0] + 0x2c);
        }
        if (state[0xa] < 0) {
            state[0xa] = 0;
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0) {
        if (*(int *)(ACTOR + 0x494) > *(int *)(PARTNER + 0x494)) {
            *(int *)(ACTOR + 0x494) = *(int *)(PARTNER + 0x494);
        } else {
            *(int *)(PARTNER + 0x494) = *(int *)(ACTOR + 0x494);
        }
    }
    if (*(int *)(ACTOR + 0x4ac) != 0 && *(int *)(ACTOR + 0x4c0) == 0 && *(short *)(ACTOR + 0x21a) <= 0 &&
        *(short *)(PARTNER + 0x21a) <= 0) {
        *(int *)(ACTOR + 0x4c0) = 1;
        *(int *)(PARTNER + 0x4c0) = 1;
        *(signed char *)(ACTOR + 0x1c7) = 3;
    }
    state[4] = Angle_TurnToward(state[4], state[5], state[8], 0);
    QuatFromAxisAngle(&q, &data_02042264, state[4]);
    Srt_SetRotationQuat((void *)(*state + 0xa0), &q);
    {
        VecFx32 *vel = (VecFx32 *)(state + 0xf);

        *(VecFx32 *)(*state + 0xf0) = *vel;
        INITi_CpuClear32_0x01ff86fc(0, vel, 0xc);
    }
}
