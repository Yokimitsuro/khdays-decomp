/* Chase tick of the ov191 enemy (x3: ov191/192/193): sets the turn rate (+0x30) to 30x the
 * node's +0x2c speed over 20, acquires the target through 020d1bdc (which also reports the
 * squared distance) -- none returns -- and, while the surface distance stays inside the actor's
 * +0x2d8 range, faces the target's +0x190 anchor from the +8 position. With no +0x34 hold
 * pending, closer than 0x2000 goes to sub-state 6, and any of the four +0x3a4 parts whose +0x60
 * low byte lacks bit 0 sends it to sub-state 4. */

#include "nitro/fx_types.h"

struct hw60 { unsigned short lo : 8, hi : 8; };

extern int Ov191_FindTarget(int obj, int *out);
extern int FX_Sqrt(int x);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(int node, int slot, void *cb);

void Ov191_ChaseTick(int node)
{
    int *state = *(int **)(node + 4);
    int dist2[4];
    int obj;
    int target;
    int dist;
    int i;

    state[0xc] = *(int *)(*(int *)node + 0x2c) * 30 / 20;
    state[6] = Ov191_FindTarget(*state, dist2);
    target = state[6];
    if (target == 0) {
        return;
    }
    obj = *state;
    dist = FX_Sqrt(dist2[0]) - *(int *)(target + 0x80) - *(int *)(obj + 0x80);
    dist2[0] = dist;
    if (dist >= *(int *)(*state + 0x2d8)) {
        return;
    }
    VEC_Subtract((VecFx32 *)(state[6] + 0x190), (VecFx32 *)state[2], (VecFx32 *)(dist2 + 1));
    state[5] = FX_Atan2(dist2[1], dist2[3]);
    if (state[0xd] > 0) {
        return;
    }
    if (dist2[0] < 0x2000) {
        *(unsigned char *)(*state + 0x1c7) = 6;
        SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
        return;
    }
    for (i = 0; i < 4; i++) {
        if ((((struct hw60 *)((*(int **)(*state + 0x3a4))[i] + 0x60))->lo & 1) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 4;
            SetIndexedSlot(node, *(signed char *)(node + 0x20), 0);
            return;
        }
    }
}
