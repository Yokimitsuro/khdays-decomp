typedef unsigned char u8;

typedef struct {
    int x;
    int y;
    int z;
} VecFx32;

typedef struct {
    VecFx32 center;
    int radius;
} Sphere;

typedef struct {
    Sphere sphere;
    VecFx32 toTarget;
    VecFx32 direction;
} Ov189ActionHitScratch;

typedef struct {
    char pad00[0x74];
    VecFx32 position;
    int radius;
    char pad84[0x143];
    u8 requestedState;
} Ov189Actor;

typedef struct {
    Ov189Actor *actor;
    void *subState;
    Ov189Actor *target;
    int hitContext;
    int heading;
    int targetHeading;
    int timer;
    int field1c;
    VecFx32 motion;
    char pad2c[0x10];
    u8 effectStarted;
} Ov189ActionState;

typedef struct {
    char pad00[0x2c];
    int frameStep;
} Ov189ActionScene;

typedef struct {
    Ov189ActionScene *scene;
    Ov189ActionState *state;
    char pad08[0x18];
    signed char slot;
} Ov189ActionNode;

static inline void VecFx32_Set(VecFx32 *vec, int x, int y, int z)
{
    vec->x = x;
    vec->y = y;
    vec->z = z;
}

extern Ov189Actor *func_ov107_020cab14(Ov189Actor *actor, int index);
extern void func_0203c634(Ov189ActionNode *node, int slot, void *callback);
extern void VEC_Subtract(const VecFx32 *a, const VecFx32 *b, VecFx32 *dst);
extern int func_020050b4(int x, int z);
extern void func_01ffa724(int scale, const VecFx32 *src, VecFx32 *dst);
extern void func_ov107_020c0b90();
extern void *func_ov189_020d0718(Ov189ActionState *state, unsigned int mask,
                                 Sphere *sphere, VecFx32 *direction, int strength);
extern void func_ov107_020c9264(Ov189Actor *actor, int mode, int arg);
extern short data_0203d210[];
extern const VecFx32 data_02041dc8;
extern void func_ov189_020d1cf4(void);

void func_ov189_020d1b00(Ov189ActionNode *node)
{
    Ov189ActionState *state;
    Ov189ActionHitScratch scratch;
    int idx;

    state = node->state;
    state->target = func_ov107_020cab14(state->actor, 0);
    if (state->target == 0) {
        state->actor->requestedState = 2;
        func_0203c634(node, node->slot, 0);
        return;
    }

    VEC_Subtract((const VecFx32 *)((char *)state->target + 0x190),
                 (const VecFx32 *)((char *)state->actor + 0xb0), &scratch.toTarget);
    scratch.toTarget.y = 0;
    state->targetHeading = func_020050b4(scratch.toTarget.x, scratch.toTarget.z);

    idx = (int)(((unsigned)(((long long)(int)(unsigned)state->heading *
                            0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4)
                >> 0x10) >> 4;
    VecFx32_Set(&scratch.direction, data_0203d210[idx * 2], 0,
                data_0203d210[idx * 2 + 1]);
    func_01ffa724(0x599, &scratch.direction, &state->motion);

    state->timer += node->scene->frameStep;
    if (state->effectStarted == 0 && state->timer >= 0) {
        func_ov107_020c0b90(state->actor, 3, data_02041dc8, 0);
        state->effectStarted = 1;
    }

    if (state->timer >= 0) {
        scratch.sphere = *(Sphere *)&state->actor->position;
        func_ov189_020d0718(state, 2, &scratch.sphere, 0, 0x800);
    }

    if (state->timer >= 0x1800) {
        func_ov107_020c9264(state->actor, 0xd, 0);
        func_ov107_020c0b90(state->actor, 6, data_02041dc8, 0);
        func_0203c634(node, node->slot, func_ov189_020d1cf4);
    }
}
