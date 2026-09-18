/* Charge tick (variant 3) of the ov204 enemy (and its byte-identical twin): the +8 velocity is
 * the +0x390 part's motion step rotated by the actor's +0xa0 orientation, the charge sweep runs,
 * the target is re-acquired (the +0x38 yaw aimed at it from the +0x24 position), the +0x3c turn
 * rate is the step over 0x3000 capped at 0x200 and the +0x2c travel grows by the step. Once the
 * +0x28 busy byte clears: at the start of the +0x58 phase the +0x20 point is packed into the
 * overlay's 14-byte template for the actor's +0x24 message hook and reaction 0x132 mode 5 fires
 * there; the phase accumulates the frame-time and drives the ground sweep (phase over 0x600 as a
 * 64-bit fraction); past 0x800 the +0x390 part runs action 8, animation 0x11 plays, the +0x44
 * mask and the phase reset and the tick hands off to the charge advance. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long s64;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov204Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov204Owner *self, PosMsg *msg, int size);
};

struct Ov204ChargeState {
    struct Ov204Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 vVelocity;             /* +0x08 */
    char pad014[0xc];
    Vec3 *pPoint;               /* +0x20 */
    Vec3 *pPos;                 /* +0x24 */
    u8 *pBusy;                  /* +0x28 */
    int nTravel;                /* +0x2c */
    char pad030[8];
    int nTargetYaw;             /* +0x38 */
    int nTurnRate;              /* +0x3c */
    char pad040[4];
    u8 bHitMask44;              /* +0x44 */
    char pad045[0x13];
    int nPhase;                 /* +0x58 */
};

extern int func_ov107_020c9f48(void *part, Vec3 *out);
extern void func_0202f384(Vec3 *dst, void *quat, Vec3 *src);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern void func_ov204_020d3114(struct Ov204ChargeState *state);
extern int func_ov107_020cab14(struct Ov204Owner *actor, int mode);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_020050b4(int x, int z);
extern int FX_Inv(int a, int b);
extern void func_ov107_020c5af8(struct Ov204Owner *owner, int a, int id, Vec3 *at);
extern s64 func_01ff8a14(int num, int den);
extern void func_ov204_020d330c(struct Ov204ChargeState *state, s64 t, Vec3 *at);
extern void func_ov107_020c9ee8(void *part, int a, int b);
extern void func_ov107_020c9264(struct Ov204Owner *actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern const PosMsg data_ov204_020d360c;
extern void func_ov204_020d2ff4(int *node);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov204ChargeState *state, PosMsg *msg, const Vec3 *src)
{
    volatile int px;
    volatile int py;
    volatile int pz;
    int x;
    x = src->x;
    PackFx24(&msg->pos[0], x);
    px = x;
    x = src->y;
    PackFx24(&msg->pos[1], x);
    py = x;
    x = src->z;
    PackFx24(&msg->pos[2], x);
    pz = x;
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

void func_ov204_020d2da4(int *node)
{
    struct Ov204ChargeState *state = (struct Ov204ChargeState *)node[1];
    Vec3 step;
    Vec3 dir;
    PosMsg msg;
    int speed;
    int rate;

    speed = func_ov107_020c9f48(*(void **)((char *)state->pOwner + 0x390), &step);
    func_0202f384(&state->vVelocity, (char *)state->pOwner + 0xa0, &step);
    func_01ffa724(speed, &state->vVelocity, &state->vVelocity);
    func_ov204_020d3114(state);
    state->pTarget = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget != 0) {
        VEC_Subtract((void *)(state->pTarget + 0x74), state->pPos, &dir);
        state->nTargetYaw = func_020050b4(dir.x, dir.z);
    }
    rate = FX_Inv(speed, 0x3000);
    if (rate > 0x200) {
        rate = 0x200;
    }
    state->nTurnRate = rate;
    state->nTravel += speed;
    if (*state->pBusy != 0) {
        return;
    }
    if (state->nPhase == 0) {
        msg = data_ov204_020d360c;
        SendPos(state, &msg, state->pPoint);
        func_ov107_020c5af8(state->pOwner, 0x132, 5, state->pPoint);
    }
    state->nPhase += *(int *)(*node + 0x2c);
    func_ov204_020d330c(state, func_01ff8a14(state->nPhase, 0x600), state->pPoint);
    if (state->nPhase < 0x800) {
        return;
    }
    func_ov107_020c9ee8(*(void **)((char *)state->pOwner + 0x390), 8, 0);
    func_ov107_020c9264(state->pOwner, 0x11, 0);
    state->bHitMask44 = 0;
    state->nPhase = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov204_020d2ff4);
}
