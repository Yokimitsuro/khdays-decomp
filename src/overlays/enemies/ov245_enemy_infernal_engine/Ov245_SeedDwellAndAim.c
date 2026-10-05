/* Ov245_SeedDwellAndAim -- seed a random dwell (RandNextScaled(0x1f79) + 0x88) at +0x34 and aim the
 * node at the caller's XZ pair (+0x18), then put the owner in state 1. */

#include "game/engine.h"

extern fx16 FX_Atan2(int a, int b);

void Ov245_SeedDwellAndAim(int *node, int *arg) {
    node[0xd] = RandNextScaled(0x1f79) + 0x88;
    node[6] = FX_Atan2(arg[0], arg[2]);
    *(unsigned char *)(node[0] + 0x1c7) = 1;
}
