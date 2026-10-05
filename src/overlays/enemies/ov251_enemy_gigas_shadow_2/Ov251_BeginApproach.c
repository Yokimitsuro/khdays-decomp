/* Begin the approach: with no target, roll a fresh hold time between the bounds at +0x224/+0x228
 * and drop to action 2. With one, play animation 0xc, latch the heading to it with FX_Atan2 into
 * both the current and the goal slots, convert the owner's per-frame delta into the per-second
 * budget at state[8], set 0x40 in the hw60 high byte, clear the travel accumulator and the byte
 * at state+0x50, and start event 0x159 on the sub-object.
 *
 * Matched byte-exact 2026-07-23, first compile. The `* 30 / 30` is genuine: the ROM multiplies
 * by 30 and then divides by 30 through the textbook signed magic (0x88888889, shift 4, with the
 * add correction), which is not a no-op on the negative side.
 *
 * One of four byte-identical siblings. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"
#include "game/engine.h"

extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate(int obj, int a, int b, int c);
extern void Ov251_AiSwingRecover(void);

void Ov251_BeginApproach(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int lo;
    int d;
    int h;

    if (state[4] == 0) {
        lo = *(int *)(state[0] + 0x224);
        d = *(int *)(state[0] + 0x228) - lo;
        if (d < 0) {
            d = -d;
        }
        state[0x1d] = lo + RandNextScaled(d + 1);
        *(char *)(state[0] + 0x1c7) = 2;
        SetIndexedSlot(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    Ov107_PostTagUpdate((Actor *)state[0], 0xc, 0);
    VEC_Subtract((void *)(state[4] + 0x190), (void *)state[1], &v);
    h = FX_Atan2(v.x, v.z);
    state[6] = h;
    state[5] = h;
    state[8] = *(int *)(node[0] + 0x2c) * 0x1e / 0x1e;
    {
        unsigned short hw60 = *(unsigned short *)(state[0] + 0x60);
        *(unsigned short *)(state[0] + 0x60) =
            (hw60 & ~0xff00) | (((((unsigned int)hw60 << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10);
    }
    state[7] = 0;
    *(unsigned char *)((int)state + 0x50) = 0;
    Ov107_BuildAndSendUpdate(state[0], 0x159, 7, state[1]);
    SetIndexedSlot(node, *(signed char *)((int)node + 0x20), Ov251_AiSwingRecover);
}
