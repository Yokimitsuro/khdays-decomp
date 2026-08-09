typedef unsigned char u8;
typedef unsigned short u16;

typedef struct VecFx32 {
    int x;
    int y;
    int z;
} VecFx32;

struct Actor {
    char pad000[0x60];
    u16 flags60;
    char pad062[0x12];
    VecFx32 position74;
};

struct Ov189ActionState {
    struct Actor *actor;
    char pad004[4];
    struct Actor *target;
    int reactionContext0c;
    int angle10;
    int angle14;
    int timer18;
};

struct Ov189Scene {
    char pad000[0x2c];
    int frameStep2c;
};

struct Ov189ActionNode {
    struct Ov189Scene *scene;
    struct Ov189ActionState *state;
    char pad008[0x18];
    signed char slot20;
};

struct ActorFlags60 {
    u16 low : 8;
    u16 high : 8;
};

extern struct Actor *func_ov107_020cab14(struct Actor *actor, int mode);
extern void VEC_Subtract(VecFx32 *a, VecFx32 *b, VecFx32 *out);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264(struct Actor *actor, int arg1, int arg2);
extern void func_ov107_020c5af8(struct Actor *actor, int reactionId,
                                int reactionMode, int context);
extern void func_0203c634(struct Ov189ActionNode *node, int slot, void *next);
extern void func_ov189_020d0f10(void);

void func_ov189_020d0e2c(struct Ov189ActionNode *node)
{
    struct Ov189ActionState *state = node->state;
    VecFx32 direction;

    state->timer18 += node->scene->frameStep2c;
    if (state->timer18 < 0x6ee) {
        return;
    }

    state->target = func_ov107_020cab14(state->actor, 0);
    if (state->target != 0) {
        VEC_Subtract(&state->target->position74,
                     &state->actor->position74, &direction);
        state->angle10 = state->angle14 = func_020050b4(direction.x,
                                                        direction.z);
    }

    ((struct ActorFlags60 *)&state->actor->flags60)->high &= ~0x82;
    func_ov107_020c9264(state->actor, 0, 0);
    func_ov107_020c5af8(state->actor, 0x12f, 6,
                        state->reactionContext0c);
    func_0203c634(node, node->slot20, func_ov189_020d0f10);
}
