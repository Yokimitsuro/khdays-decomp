/* AI step: steers toward the target's centre and advances the timer by the owner's frame step; when
 * it passes 0x1188 fires the three-way spread and installs the wait-for-animation step. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(void *a, int b, void *out);
extern void VEC_Normalize(void *a, void *b);
extern fx16 FX_Atan2(int a, int b);
extern void Ov197_FireThreeWaySpread(int *s, int b, int c);
extern void SetIndexedSlot(int *self, int idx, void *cb);
extern void Ov197_AiStep_QueueAction2OnAnimEnd(void);

extern VecFx32 data_02041dc8;

void Ov197_SteerTrailThenAdvance(int *self) {
    VecFx32 v;
    int *s = (int *)self[1];
    int p;
    v = data_02041dc8;
    p = *(int *)(*s + 0x394);
    if (p != 0) {
        v = *(VecFx32 *)(p + 0x74);
        v.y += *(int *)(*(int *)(*s + 0x398) + 0x80);
        VEC_Subtract(&v, *s + 0x3d8, &v);
        VEC_Normalize(&v, &v);
        s[0xe] = FX_Atan2(v.x, v.z);
    }
    s[0x10] += *(int *)(*self + 0x2c);
    if (s[0x10] < 0x1188) return;
    Ov197_FireThreeWaySpread(s, v.y, *s + 0x3d8);
    SetIndexedSlot(self, *(signed char *)((char *)self + 0x20), (void *)&Ov197_AiStep_QueueAction2OnAnimEnd);
}
