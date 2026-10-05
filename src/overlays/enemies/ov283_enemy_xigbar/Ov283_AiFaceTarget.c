/* AI step: turns towards the target, starts the landing effect and continues with the landing. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(int *a, int *b, int *out);
extern int VEC_Normalize(const VecFx32 *source, VecFx32 *destination);
extern fx16 FX_Atan2(int x, int z);
extern void func_ov107_020c0b90(int owner, int a, VecFx32 v, int flag);
extern void SetIndexedSlot(int self, int idx, void *cb);
extern void Ov283_AiLandStart(int);

void Ov283_AiFaceTarget(int *self) {
    int state = self[1];
    int q = *(int *)state;
    VecFx32 *a = (VecFx32 *)(*(int *)(q + 0x390) + 0x190);
    VecFx32 *b = (VecFx32 *)(q + 0x74);
    VecFx32 diff;
    VEC_Subtract((int *)a, (int *)b, (int *)&diff);

    VEC_Normalize(&diff, &diff);

    int angle = FX_Atan2(diff.x, diff.z);
    *(int *)(state + 0x40) = angle;
    *(int *)(state + 0x38) = angle;

    VecFx32 v = *(VecFx32 *)(*(int *)(state + 8));
    q = *(int *)state;
    func_ov107_020c0b90(q, 1, v, 0);

    SetIndexedSlot((int)self, *(signed char *)((int)self + 0x20), (void *)&Ov283_AiLandStart);
}
