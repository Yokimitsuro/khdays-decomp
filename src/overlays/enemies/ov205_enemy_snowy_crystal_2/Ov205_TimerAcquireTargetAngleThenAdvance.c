/* Node sub-state entry: accumulates the frame timer until 0x6ee, acquires a target, subtracts the
 * target position from the stored reference VecFx32, computes and mirrors the horizontal angle, clears
 * actor hw60 high-byte bits, runs pose setup, and advances to the next callback. */

#include "nitro/fx_types.h"

typedef struct ActorFlags60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
} ActorFlags60;

extern int Ov107_FindNearestObject(int actor, int arg);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_PostTagUpdate(int actor, int a, int b);
extern void SetIndexedSlot(void *node, int idx, void *next);
extern void Ov205_AiStep_QueueAction2OnFlag28Clear(void);

void Ov205_TimerAcquireTargetAngleThenAdvance(int *node) {
    VecFx32 delta;
    int *frame = (int *)node[0];
    int *state = (int *)node[1];
    int timer = state[0xb] + frame[0xb];
    int target;
    int angle;

    state[0xb] = timer;
    if (timer < 0x6ee) return;

    target = Ov107_FindNearestObject(*state, 0);
    state[0x1] = target;
    if (target != 0) {
        VEC_Subtract((VecFx32 *)(target + 0x74), (VecFx32 *)state[0x9], &delta);
        angle = FX_Atan2(delta.x, delta.z);
        state[0xd] = state[0xe] = angle;
    }

    ((ActorFlags60 *)(*state + 0x60))->hi &= ~0x80;
    Ov107_PostTagUpdate(*state, 0, 0);
    SetIndexedSlot(node, *(signed char *)(node + 8), Ov205_AiStep_QueueAction2OnFlag28Clear);
}
