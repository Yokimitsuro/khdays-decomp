/* Walk tick of the ov260 actor: the +0x20 velocity is its +0x428 part's +0x2c vector turned by the
 * +0x64 heading. With a +0x50 goal it aims at it (+0x68) and walks along the heading at the part's
 * stride (x1.5 in stance, +0x470) scaled by the remaining distance over 3.0 (clamped to 0-1). Landing
 * on the second flag of +0x17a ends the +0x60 walk time. When the walk time is out or the goal is
 * within 1/8 of the range, pose 3 plays, the part takes motion 2 and the node moves on to 020ce198.
 * Otherwise the +0x70 timer runs with step cues at 0 and 0x4c8 (020cd04c 0 / 1), and once the partner
 * holds no queued move pose 2 plays, the part takes motion 1 and the timer and cues restart. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/enemy_common.h"

typedef struct { int m[9]; } Mtx33;
struct Flag17a { u8 b0 : 1; u8 b1 : 1; };

extern void MTX_RotY33_(Mtx33 *pMtx, int nSin, int nCos);
extern void MTX_MultVec33(const VecFx32 *pIn, const Mtx33 *pMtx, VecFx32 *pOut);
extern int VEC_Normalize(VecFx32 *v, VecFx32 *out);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int y);
extern int FX_Div(int num, int den);
extern void ScaleVec3Fx12(int scale, VecFx32 *v, VecFx32 *d);
extern void Ov260_MapHeldItemKindToAnim(int actor, int flag);
extern void SetIndexedSlot(int *node, int slot, void *cb);
extern void Ov260_DriftCheckStep(void);
extern const short data_0203d210[];

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)
#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

void Ov260_WalkTick(int *node)
{
    int *state = (int *)node[1];
    Mtx33 rot;
    VecFx32 d;
    int speed;
    int t = 0x7fffffff;

    {
        int idx = ANG2IDX(state[0x19]) * 2;

        MTX_RotY33_(&rot, data_0203d210[idx], data_0203d210[idx + 1]);
    }
    MTX_MultVec33((VecFx32 *)(*(int *)(*state + 0x428) + 0x2c), &rot, (VecFx32 *)(state + 8));
    if (state[0x14] != 0) {
        {
            int len = VEC_Normalize((VecFx32 *)(*(int *)(*state + 0x428) + 0x2c), &d);

            speed = FX_MUL(len, *(int *)(*state + 0x470) != 0 ? 0x1800 : 0x1000);
        }
        VEC_Subtract((VecFx32 *)state[0x14], (VecFx32 *)state[4], &d);
        state[0x1a] = FX_Atan2(d.x, d.z);
        d.y = 0;
        t = FX_Div(VEC_Normalize(&d, &d), 0x3000);
        if (t > 0x1000) {
            t = 0x1000;
        } else if (t < 0) {
            t = 0;
        }
        {
            int idx = ANG2IDX(state[0x19]) * 2;

            state[8] = data_0203d210[idx];
            state[9] = 0;
            state[10] = data_0203d210[idx + 1];
        }
        ScaleVec3Fx12(FX_MUL(speed, t), (VecFx32 *)(state + 8), (VecFx32 *)(state + 8));
    }
    if (((struct Flag17a *)(*state + 0x17a))->b1) {
        state[0x18] = 0;
    }
    if (state[0x18] <= 0 || t <= 0x200) {
        Ov107_PostTagUpdate((Actor *)(*state), 3, 0);
        Ov107_StartAnim(*(int *)(*state + 0x428), 2, 0);
        SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), Ov260_DriftCheckStep);
        return;
    }
    state[0x1c] += *(int *)(node[0] + 0x2c);
    if ((*((u8 *)state + 0x7b) & 1) == 0 && state[0x1c] >= 0) {
        *((u8 *)state + 0x7b) |= 1;
        Ov260_MapHeldItemKindToAnim(*state, 0);
    }
    if ((*((u8 *)state + 0x7b) & 2) == 0 && state[0x1c] >= 0x4c8) {
        *((u8 *)state + 0x7b) |= 2;
        Ov260_MapHeldItemKindToAnim(*state, 1);
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 2, 0);
    Ov107_StartAnim(*(int *)(*state + 0x428), 1, 0);
    state[0x1c] = 0;
    *((u8 *)state + 0x7b) = 0;
}
