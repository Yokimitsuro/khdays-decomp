/*
 * Point the node at its stored heading, then advance to the default pose if both sub-nodes are
 * idle (x-family).
 *
 * Hand the heading vector cached at state[10..0xc] to BuildHeadingRotation (020d43a4) with the
 * apply flag set, then gate: if either the sub-node at state[1]+0xad or the one reached through
 * *state+0x388 is still busy, wait. Otherwise fire event 4, seed the default pose (020d4234), and
 * advance with a callback.
 *
 * ★ THIS IS THE ORIGINAL `ldm`-args-coalescing example (it was the deferred-ties entry's own
 * citation), and the STRUCT-BY-VALUE crack matched it on the first compile: the vector at
 * state[10..0xc] is passed as `*(VecFx32 *)(state + 10)`, which mwcc loads with one
 * `ldm r1,{r1,r2,r3}` -- exactly the ROM. Three separate `int` args would have been three `ldr`s.
 * The tie is retired.
 */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov197_BuildHeadingRotation(int *self, VecFx32 v, int flag);
extern void Ov197_SeedDefaultPoseAndAdvance(int a, int b);
extern void SetIndexedSlot(int self, int idx, int cb);
extern int Ov197_InvokeWithVec3ThenSetSubState5;

void Ov197_PointHeadingCheckPose(int self) {
    int *state = *(int **)(self + 4);

    Ov197_BuildHeadingRotation(state, *(VecFx32 *)(state + 10), 1);
    if (*(unsigned char *)(state[1] + 0xad) != 0) {
        return;
    }
    if (*(unsigned char *)(*(int *)(*state + 0x388) + 0xad) != 0) {
        return;
    }
    Ov107_PostTagUpdate((Actor *)(*state), 4, 0);
    Ov197_SeedDefaultPoseAndAdvance(*state, 2);
    SetIndexedSlot(self, *(signed char *)(self + 0x20), (int)&Ov197_InvokeWithVec3ThenSetSubState5);
}
