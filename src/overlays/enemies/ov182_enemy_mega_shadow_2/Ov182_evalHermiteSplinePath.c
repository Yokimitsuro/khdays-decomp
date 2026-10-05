/* AI step: moves the actor along a cubic Hermite curve from its start point to a point beside the
 * target, capping the per-frame step at 0x800 and facing the target; at the end of the curve posts
 * pose 7 and installs the fade-in step. Without a target it queues action 2 instead. */

#include "game/enemy_common.h"

struct hw60 { unsigned short lo:8, hi:8; };

extern void SetIndexedSlot(void *node, int slot, void *cb);
extern void VEC_Add(void *a, void *b, void *out);
extern void ScaleVec3Fx12(int scale, void *src, void *dst);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int VEC_Mag(void *v);
extern void VEC_Normalize(void *src, void *dst);
extern fx16 FX_Atan2(int x, int z);
extern void Ov182_AiFadeInTick(void);
extern short data_0203d210[];

void Ov182_evalHermiteSplinePath(int *param_1) {
    int *state = (int *)param_1[1];
    *(int *)(*state + 0x394) = 1;
    if (state[4] == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        SetIndexedSlot(param_1, *(signed char *)(param_1 + 8), 0);
        return;
    }
    {
        int angle = (int)(((unsigned)(((long long)state[0x13] * 0x28be60db9391LL
                     + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
        int local_28[3];
        int s34[3];
        int l40[3];
        int t, t2, t3, t2x3, mag;
        local_28[1] = state[0x11];
        local_28[0] = data_0203d210[angle * 2] << 1;
        local_28[2] = data_0203d210[angle * 2 + 1] << 1;
        VEC_Add(local_28, (void *)(state[4] + 400), local_28);
        t = state[7] + *(int *)(*param_1 + 0x2c);
        t2 = (int)(((long long)t * t + 0x800) >> 12);
        t3 = (int)(((long long)t2 * t + 0x800) >> 12);
        state[7] = t;
        t2x3 = 3 * t2;
        ScaleVec3Fx12(2 * t3 - t2x3 + 0x1000, state + 0x10, s34);
        {
            int h01 = -2 * t3;
            h01 += t2x3;
            ScaleVec3Fx12(h01, local_28, l40);
        }
        VEC_Add(s34, l40, s34);
        ScaleVec3Fx12(t + (t3 - 2 * t2), state + 10, l40);
        VEC_Add(s34, l40, s34);
        ScaleVec3Fx12(t3 - t2, state + 0xd, l40);
        VEC_Add(s34, l40, s34);
        VEC_Subtract(s34, (void *)state[1], state + 0x15);
        state[0x16] = 0;
        mag = VEC_Mag(state + 0x15);
        if (mag > 0x800) {
            VEC_Normalize(state + 0x15, state + 0x15);
            ScaleVec3Fx12(0x800, state + 0x15, state + 0x15);
        }
        VEC_Subtract((void *)(state[4] + 400), (void *)state[1], l40);
        state[6] = FX_Atan2(l40[0], l40[2]);
        if (state[7] >= 0x1000) {
            Ov107_PostTagUpdate((Actor *)(*state), 7, 0);
            ((struct hw60 *)(*state + 0x60))->hi &= ~2;
            state[7] = 0;
            SetIndexedSlot(param_1, *(signed char *)(param_1 + 8), Ov182_AiFadeInTick);
        }
    }
}
