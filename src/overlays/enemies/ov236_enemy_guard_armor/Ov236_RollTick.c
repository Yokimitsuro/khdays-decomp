/* Roll tick: refreshes the +8 target (none: stop); on the first tick (+0x14 latch) the +0xc
 * base heading and +0x10 heading are set to atan2 of the offset to the target, afterwards only
 * the +0x10 heading follows the flattened, normalised offset. The +0x28 timer counts the frame
 * step down; when the +4 child's +0xa8 flag is set and the timer is spent, bit 2 of +0x52 and
 * that flag clear. Once the child's +0xad byte clears, pose request 0xa (actor's +0x3bd latch),
 * 4 (bit 0 of +0x52) or 6 is queued and the node dispatches null. */

#include "nitro/fx_types.h"

struct Bits52 { unsigned char b0 : 1; };

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern int VEC_Normalize(const VecFx32 *v, VecFx32 *out);
extern void SetIndexedSlot(int *node, int slot, void *cb);

void Ov236_RollTick(int *node) {
    int *state = (int *)node[1];
    VecFx32 d;
    int target;
    int child;

    target = state[2] = Ov107_FindNearestObject(*state, 0);
    if (target == 0) {
        return;
    }
    if (state[5] != 0) {
        VEC_Subtract((VecFx32 *)(target + 0x74), (VecFx32 *)(*state + 0x74), &d);
        state[3] = state[4] = FX_Atan2(d.x, d.z);
        state[5] = 0;
    }
    VEC_Subtract((VecFx32 *)(state[2] + 0x74), (VecFx32 *)(*state + 0x74), &d);
    d.y = 0;
    VEC_Normalize(&d, &d);
    state[4] = FX_Atan2(d.x, d.z);
    state[0xa] -= *(int *)(*node + 0x2c);
    child = state[1];
    if (*(unsigned char *)(child + 0xa8) != 0 && state[0xa] <= 0) {
        *((unsigned char *)state + 0x52) &= ~4;
        *(unsigned char *)(state[1] + 0xa8) = 0;
        return;
    }
    if (*(unsigned char *)(child + 0xad) != 0) {
        return;
    }
    if (*(unsigned char *)(*state + 0x3bd) != 0) {
        *(unsigned char *)(*state + 0x1c7) = 0xa;
    } else if (((struct Bits52 *)((char *)state + 0x52))->b0 != 0) {
        *(unsigned char *)(*state + 0x1c7) = 4;
    } else {
        *(unsigned char *)(*state + 0x1c7) = 6;
    }
    SetIndexedSlot(node, *(signed char *)((char *)node + 0x20), 0);
}
