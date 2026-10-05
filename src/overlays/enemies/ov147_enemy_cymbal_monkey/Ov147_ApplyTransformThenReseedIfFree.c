
#include "nitro/fx_types.h"

extern int Ov147_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void Ov107_PostTagUpdate(int obj, int a, int b);
extern void Ov147_SeedDefaultPoseAndAdvance(int obj, int arg1);
extern void SetIndexedSlot(int obj, int a, int cb);
extern void Ov147_StepChargeUntilSettled(void);

// Apply the node's pending transform (vector at node+0x28); if the target slot
// is still free (node[1][0xad]==0), switch to mode 3, seed the default pose and
// advance the sub-state with the follow-up callback.
void Ov147_ApplyTransformThenReseedIfFree(int *this)
{
    int node = this[1];
    Ov147_BuildHeadingRotation((int *)node, *(VecFx32 *)(node + 0x28), 1);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate(*(int *)node, 3, 0);
    Ov147_SeedDefaultPoseAndAdvance(*(int *)node, 1);
    SetIndexedSlot((int)this, *(signed char *)((int)this + 0x20), (int)&Ov147_StepChargeUntilSettled);
}
