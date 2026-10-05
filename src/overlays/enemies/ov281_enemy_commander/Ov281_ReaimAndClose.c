/* Re-aim at the target and decide whether to keep closing: measure the delta, latch the heading
 * with FX_Atan2, rebuild the desired direction from the sin/cos table at the current turn angle,
 * and normalise it. If the distance left is still 0x2000 or more, keep going; otherwise switch
 * to action 2 and drop the think callback.
 *
 * The angle index is computed TWICE, once per table entry, exactly as the ROM does -- caching it
 * in a local makes mwcc share the 64-bit multiply and the function comes out different. And the
 * `gap` subtraction has to be written BEFORE the first table store: that is what lets mwcc hoist
 * its load into the multiply sequence, where the ROM has it.
 *
 * Matched byte-exact 2026-07-23. One of four byte-identical siblings. */

#include "nitro/fx_types.h"

extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(void *a, void *b);
extern void ScaleVec3Fx12(int a, void *b, void *c);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern short data_0203d210[];

void Ov281_ReaimAndClose(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    int *obj;
    int mag;
    int gap;

    VEC_Subtract((void *)(state[0] + 0x190), (void *)state[3], &d);
    state[5] = FX_Atan2(d.x, d.z);
    obj = (int *)state[0];
    mag = VEC_Normalize(&d, &d);
    gap = mag - obj[0x20];
    state[8] = data_0203d210[((int)(unsigned short)((unsigned int)(((long long)state[4] * 0x28be60db9391LL + 0x80000000000LL) >> 32) >> 12) >> 4) * 2];
    state[9] = 0;
    state[0xa] = data_0203d210[((int)(unsigned short)((unsigned int)(((long long)state[4] * 0x28be60db9391LL + 0x80000000000LL) >> 32) >> 12) >> 4) * 2 + 1];
    ScaleVec3Fx12(0x200, state + 8, state + 8);
    if (gap >= 0x2000) {
        return;
    }
    *(char *)(state[0] + 0x1c7) = 2;
    SetIndexedSlot(node, *(signed char *)((int)node + 0x20), 0);
}
