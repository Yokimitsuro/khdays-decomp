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
    int m[9];
} MtxFx33;

typedef struct {
    char pad00[0x74];
    VecFx32 position;
    int radius;
    char pad84[0x33c];
    void *auxResource;
} Ov188Actor;

typedef struct {
    char pad00[0xad];
    u8 active;
} Ov188ActionSubState;

typedef struct {
    Ov188Actor *actor;
    Ov188ActionSubState *subState;
    int field08;
    int hitContext;
    int heading;
    int field14;
    int timer;
    int field1c;
    VecFx32 motion;
    char pad2c[0x10];
    u8 effectStarted;
} Ov188ActionState;

typedef struct {
    char pad00[0x2c];
    int frameStep;
} Ov188ActionScene;

typedef struct {
    Ov188ActionScene *scene;
    Ov188ActionState *state;
    char pad08[0x18];
    signed char slot;
} Ov188ActionNode;

extern short data_0203d210[];
extern const VecFx32 data_02041dc8;
extern void MTX_RotY33_(MtxFx33 *mtx, int sinVal, int cosVal);
extern void MTX_MultVec33(const VecFx32 *v, const MtxFx33 *m, VecFx32 *dst);
extern void func_ov107_020c0b90();
extern void func_ov107_020c5af8(Ov188Actor *actor, int effect, int mode, int context);
extern void *func_ov188_020ce8f8(Ov188ActionState *state, unsigned int mask,
                                 Sphere *sphere, VecFx32 *direction, int strength);
extern void func_ov107_020c9264(Ov188Actor *actor, int mode, int arg);
extern void func_0203c634(Ov188ActionNode *node, int slot, void *callback);
extern void func_ov188_020cf9ac(void);

void func_ov188_020cf818(Ov188ActionNode *node)
{
    Ov188ActionState *state;
    MtxFx33 mtx;
    Sphere sphere;
    int idx;

    state = node->state;
    idx = (unsigned short)(((long long)state->heading * 0x28be60db9391LL +
                            0x80000000000LL) >> 44) >> 4;
    MTX_RotY33_(&mtx, data_0203d210[idx * 2], data_0203d210[idx * 2 + 1]);
    MTX_MultVec33((const VecFx32 *)((char *)state->actor->auxResource + 0x2c),
                  &mtx, &state->motion);

    state->timer += node->scene->frameStep;
    if (state->effectStarted == 0) {
        if (state->timer >= 0x2a8) {
            state->effectStarted = 1;
            func_ov107_020c0b90(state->actor, 2, data_02041dc8, 0);
            func_ov107_020c5af8(state->actor, 0x12f, 4, state->hitContext);
        }
    }

    if (state->timer >= 0xff0) {
        sphere = *(Sphere *)&state->actor->position;
        if (func_ov188_020ce8f8(state, 1, &sphere, 0, 0x1000) != 0) {
            state->motion = data_02041dc8;
        }
    }

    if (state->subState->active == 0) {
        func_ov107_020c9264(state->actor, 6, 0);
        func_0203c634(node, node->slot, func_ov188_020cf9ac);
    }
}

