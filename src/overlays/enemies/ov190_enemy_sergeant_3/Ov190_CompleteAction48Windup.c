/* Waits for the action-0x48 windup timer, faces the current target when present, clears actor
 * flags60 high-byte mask 0x82, starts reaction 0x12f mode 6 and advances the action node. */

#include "nitro/types.h"
#include "nitro/fx_types.h"
#include "game/ai_task.h"

struct Actor {
    char pad000[0x60];
    u16 flags60;
    char pad062[0x12];
    VecFx32 position74;
};

struct Ov190ActionState {
    struct Actor *actor;
    char pad004[4];
    struct Actor *target;
    int reactionContext0c;
    int angle10;
    int angle14;
    int timer18;
};

struct Ov190Scene {
    char pad000[0x2c];
    int frameStep2c;
};

struct Ov190ActionNode {
    AI_TASK_FIELDS(struct Ov190ActionState)
};

struct ActorFlags60 {
    u16 low : 8;
    u16 high : 8;
};

extern struct Actor *Ov107_FindNearestObject(struct Actor *actor, int mode);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern fx16 FX_Atan2(int x, int z);
extern void Ov107_PostTagUpdate(struct Actor *actor, int arg1, int arg2);
extern void Ov107_BuildAndSendUpdate(struct Actor *actor, int reactionId,
                                int reactionMode, int context);
extern void SetIndexedSlot(struct Ov190ActionNode *node, int slot, void *next);
extern void Ov190_AiStep_QueueAction2OnAnimEnd(void);

void Ov190_CompleteAction48Windup(struct Ov190ActionNode *node)
{
    struct Ov190ActionState *state = node->pState;
    VecFx32 direction;

    state->timer18 += ((struct Ov190Scene *)node->pList)->frameStep2c;
    if (state->timer18 < 0x6ee) return;

    state->target = Ov107_FindNearestObject(state->actor, 0);
    if (state->target != 0) {
        VEC_Subtract(&state->target->position74,
                     &state->actor->position74, &direction);
        state->angle10 = state->angle14 = FX_Atan2(direction.x,
                                                        direction.z);
    }

    ((struct ActorFlags60 *)&state->actor->flags60)->high &= ~0x82;
    Ov107_PostTagUpdate(state->actor, 0, 0);
    Ov107_BuildAndSendUpdate(state->actor, 0x12f, 6,
                        state->reactionContext0c);
    SetIndexedSlot(node, node->slot, Ov190_AiStep_QueueAction2OnAnimEnd);
}
