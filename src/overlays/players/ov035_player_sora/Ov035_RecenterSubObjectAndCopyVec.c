/* When the effect node is in its visible state, places it at the character's mark point, turns it
 * with the character and draws it. */

#include "nitro/types.h"
#include "nitro/fx_types.h"

extern VecFx32 Ov035_GetMarkPoint(char *self);
extern void Scene_DrawNode(int p);

void Ov035_RecenterSubObjectAndCopyVec(int this_, int arg1) {
    VecFx32 tmp;
    if (*(int *)arg1 != 2) return;
    tmp = Ov035_GetMarkPoint((char *)this_);
    *(unsigned short *)(arg1 + 0x80) =
        (unsigned short)((unsigned short)(*(unsigned short *)(*(int *)(this_ + 0x20) + 0x80) - 0x8000) + 0x8000);
    *(unsigned short *)(arg1 + 4) |= 0x20;
    *(VecFx32 *)(arg1 + 0xa8) = tmp;
    Scene_DrawNode(arg1 + 4);
}
