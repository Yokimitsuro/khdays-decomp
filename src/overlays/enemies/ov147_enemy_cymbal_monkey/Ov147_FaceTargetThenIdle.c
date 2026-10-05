/* Ov147_BuildHeadingRotation takes the vec BY VALUE (r1/r2/r3 via ldm) plus a stack flag. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void VEC_Subtract();
extern int Ov147_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void Ov147_SeedDefaultPoseAndAdvance(int owner, int a);
extern void SetIndexedSlot(int self, int index, void *cb);
extern void Ov147_FaceTargetCheckReach(void);

void Ov147_FaceTargetThenIdle(int self) {
    int *obj = *(int **)(self + 4);
    VecFx32 v;

    VEC_Subtract(*obj + 400, obj[3], &v);
    Ov147_BuildHeadingRotation(obj, v, 0);
    if (*(unsigned char *)(obj[1] + 0xad) == 0) {
        Ov107_PostTagUpdate((Actor *)(*obj), 3, 1);
        Ov147_SeedDefaultPoseAndAdvance(*obj, 1);
        SetIndexedSlot(self, *(signed char *)(self + 0x20), &Ov147_FaceTargetCheckReach);
    }
}
