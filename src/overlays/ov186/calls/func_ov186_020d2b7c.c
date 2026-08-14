typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vec4;

typedef struct {
    int x;
    int y;
    int z;
} Vec3;

typedef struct {
    int owner;
    char padding04[0x28];
    Vec3 motion;
    char padding38[0x0c];
    int *related;
    char padding48[0x18];
    int timer;
    Vec3 direction;
    int baseY;
    int landingY;
} Ov185MoveState;

typedef struct {
    unsigned short a;
    unsigned short b;
} Pair;

extern int func_ov107_020c8eb8(int owner, int source, Vec4 *out);
extern void func_0203c634(int *self, int action, void *callback);
extern short data_0203d210[];
extern Pair data_ov186_020d34c0[];
extern void func_ov186_020d2d1c(void);

static inline int FX_Mul(int a, int b) {
    return (int)(((long long)a * b + 0x800) >> 12);
}

static inline void SetVec3(Vec3 *dst, int x, int y, int z) {
    dst->x = x;
    dst->y = y;
    dst->z = z;
}

/*
 * Per-frame step of the hop arc.
 *
 * Advances the action timer by the frame delta and turns it into an angle index
 * through the shared sin/cos table, which gives the vertical offset of the arc
 * above the anchor height.  The horizontal motion keeps the launch direction
 * scaled by the frame delta times thirty.
 *
 * Once the arc turns downward it sweeps for ground: on a hit it publishes the
 * landing message through the actor hook, records the landing height, sets the
 * actor state to 7 and ends the action.  Otherwise the action ends on its own
 * once the timer reaches 0x1000, handing the node to the follow-up.
 */
void func_ov186_020d2b7c(int *self) {
    Ov185MoveState *ctx = (Ov185MoveState *)self[1];
    int angle;
    int index;
    int y;
    Vec4 out;
    Pair event;
    void (*notify)(int owner, Pair *event, int size);

    ctx->timer += *(int *)(self[0] + 0x2c);
    index = (unsigned short)(((long long)FX_Mul(ctx->timer, 0x3244)
                              * 0x28be60db9391LL
                              + 0x80000000000LL) >> 44) >> 4;
    y = ctx->baseY + data_0203d210[index * 2] * 3
        - ctx->related[1];
    ctx->direction.y = y;

    angle = *(int *)(self[0] + 0x2c) * 30;
    SetVec3(&ctx->motion,
            FX_Mul(ctx->direction.x, angle),
            y,
            FX_Mul(ctx->direction.z, angle));

    if (ctx->direction.y < 0
        && func_ov107_020c8eb8(ctx->owner, ctx->owner + 0x74, &out) != 0) {
        Pair *eventPtr = &event;
        eventPtr->b = data_ov186_020d34c0[0].b;
        eventPtr->a = data_ov186_020d34c0[0].a;
        notify = *(void (**)(int, Pair *, int))(ctx->owner + 0x24);
        if (notify != 0) {
            notify(ctx->owner, eventPtr, 4);
        }
        ctx->landingY = out.x;
        *(signed char *)(ctx->owner + 0x1c7) = 7;
        func_0203c634(self, *(signed char *)((char *)self + 0x20), 0);
        return;
    }

    if (ctx->timer >= 0x1000) {
        func_0203c634(self, *(signed char *)((char *)self + 0x20),
                      &func_ov186_020d2d1c);
    }
}
