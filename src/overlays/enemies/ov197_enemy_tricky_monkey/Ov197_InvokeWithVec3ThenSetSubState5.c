/* Push the +0x28 vector into Ov197_BuildHeadingRotation; unless busy mark state 5 and dispatch. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int Ov197_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void SetIndexedSlot();


void Ov197_InvokeWithVec3ThenSetSubState5(int this_) {
    int node = *(int *)(this_ + 4);
    Ov197_BuildHeadingRotation((int *)node, *(VecFx32 *)(node + 0x28), 1);
    if (*(unsigned char *)(*(int *)(node + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)node + 0x1c7) = 5;
    SetIndexedSlot(this_, *(signed char *)(this_ + 0x20), 0);
}
