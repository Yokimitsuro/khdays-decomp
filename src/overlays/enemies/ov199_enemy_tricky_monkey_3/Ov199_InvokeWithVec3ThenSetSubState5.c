/* Push the +0x28 vector into 020d43a4; unless busy mark state 5 and dispatch. */
#include "nitro/types.h"
#include "nitro/fx_types.h"

extern int SetIndexedSlot(int, int, void *);
extern int Ov199_BuildHeadingRotation(int *self, VecFx32 v, int flag);
void Ov199_InvokeWithVec3ThenSetSubState5(int param_1) {
    int owner = *(int *)(param_1 + 4);
    Ov199_BuildHeadingRotation((int *)owner, *(VecFx32 *)(owner + 0x28), 1);
    if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)owner + 0x1c7) = 5;
    SetIndexedSlot(param_1, *(signed char *)(param_1 + 0x20), 0);
}
