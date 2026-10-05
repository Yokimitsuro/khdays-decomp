/* Waits for the action-0x48 windup timer, reacquires and faces a target, clears actor flags60
 * high-byte mask 0x82, stops the current action, starts resource 0x169 mode 6, and advances the
 * node. */

#include "nitro/fx_types.h"
#include "game/enemy_common.h"

extern int Ov107_FindNearestObject(int actor, int mode);
extern void VEC_Subtract(void *a, void *b, void *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_BuildAndSendUpdate(int actor, int resource, int mode, int position);
extern void SetIndexedSlot(void *node, int index, void *next);
extern void Ov281_AiStep_QueueAction2OnAnimEnd(void);

struct Ov281ActorFlags60 {
    unsigned short lo : 8;
    unsigned short hi : 8;
};

void Ov281_CompleteAction48Windup(int *node)
{
    int *owner = (int *)node[0];
    int *state = (int *)node[1];
    VecFx32 delta;
    int timer;
    int heading;

    timer = state[6] + owner[11];
    state[6] = timer;
    if (timer < 0x6ee) {
        return;
    }

    state[2] = Ov107_FindNearestObject(state[0], 0);
    if (state[2] != 0) {
        VEC_Subtract((void *)(state[2] + 0x74), (void *)(state[0] + 0x74), &delta);
        heading = FX_Atan2(delta.x, delta.z);
        state[5] = heading;
        state[4] = heading;
    }

    ((struct Ov281ActorFlags60 *)(state[0] + 0x60))->hi &= ~0x82;
    Ov107_PostTagUpdate((Actor *)state[0], 0, 0);
    Ov107_BuildAndSendUpdate(state[0], 0x169, 6, state[3]);
    SetIndexedSlot(node, *(signed char *)((int)node + 0x20), Ov281_AiStep_QueueAction2OnAnimEnd);
}
