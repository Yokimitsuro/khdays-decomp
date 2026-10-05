/* Wait out the wind-up, then re-acquire: once the timer passes 0x6ee, ask the target tracker for
 * a fresh target and, if there is one, face it with FX_Atan2 into both the current and the goal
 * heading. Either way, drop 0x82 from the hw60 high byte, stop the animation and continue.
 *
 * Matched byte-exact 2026-07-23, first compile. One of three byte-identical siblings. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern void *Ov107_FindNearestObject(void *obj, int a);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void SetIndexedSlot(void *node, int idx, void *cb);
extern void Ov155_AiStep_QueueAction2OnFlag0cClear(void);

struct hw60 { unsigned short lo : 8, hi : 8; };

void Ov155_AiWaitThenTarget(int *node) {
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    VecFx32 d;
    int t;
    int h;

    t = state[7] + *(int *)((int)owner + 0x2c);
    state[7] = t;
    if (t < 0x6ee) {
        return;
    }
    state[6] = (int)Ov107_FindNearestObject((void *)state[0], 0);
    if (state[6] != 0) {
        VEC_Subtract((void *)(state[6] + 0x74), (void *)(state[0] + 0x74), &d);
        h = FX_Atan2(d.x, d.z);
        state[5] = h;
        state[4] = h;
    }
    ((struct hw60 *)(state[0] + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)state[0], 0, 0);
    SetIndexedSlot(node, *(signed char *)((int)node + 0x20), Ov155_AiStep_QueueAction2OnFlag0cClear);
}
