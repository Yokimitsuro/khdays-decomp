/* Push the +0x28 vector into 020d43a4; unless busy kick anim 3, run 020d4234 and dispatch. */
#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int Ov107_PostTagUpdate(int, int, int);
extern int SetIndexedSlot(int, int, void *);
extern int Ov199_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern int Ov199_SeedDefaultPoseAndAdvance(int, int);
extern int Ov199_StepChargeUntilSettled(int);
void Ov199_ApplyTransformThenReseedIfFree(int param_1) {
    int owner = *(int *)(param_1 + 4);
    Ov199_BuildHeadingRotation((int *)owner, *(VecFx32 *)(owner + 0x28), 1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    Ov107_PostTagUpdate(*(int *)owner, 3, 0);
    Ov199_SeedDefaultPoseAndAdvance(*(int *)owner, 1);
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), (void *)&Ov199_StepChargeUntilSettled);
}
