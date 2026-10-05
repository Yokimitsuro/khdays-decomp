/* Ov197_BuildHeadingRotation takes the vec BY VALUE (r1/r2/r3 via ldm) plus a stack flag. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract();
extern int Ov197_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void Ov197_SeedDefaultPoseAndAdvance(int owner, int a);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void Ov197_FaceTargetCheckReach(void);

void Ov197_FaceTargetThenIdle(int self) {
    int *obj = *(int **)(self + 4);
    VecFx32 v;

    VEC_Subtract(*obj + 400, obj[3], &v);
    Ov197_BuildHeadingRotation(obj, v, 0);
    if (*(unsigned char *)(obj[1] + 0xad) == 0) {
        Ov107_PostTagUpdate((Actor *)(*obj), 3, 1);
        Ov197_SeedDefaultPoseAndAdvance(*obj, 1);
        SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov197_FaceTargetCheckReach);
    }
}
