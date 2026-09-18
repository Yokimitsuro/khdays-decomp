/* Shot tick of the ov151 enemy (and its byte-identical twin): the +0x38 clock accumulates the
 * frame-time; the forward axis rotated by the +0x18 orientation, scaled by the +0x28 speed
 * (which eases towards 0x100 by a thirtieth), is the +0xc velocity. A target ahead of the flight
 * (its direction from the +8 position not opposed to the forward vector) slews the orientation
 * towards it by 30 x dt x 0x266 / 4096 (slerp, normalised). Once the +0x2c wall timer is spent a
 * wall contact (bit 1 of +0x17a) reflects the forward vector about the +0x114 normal and
 * re-aims the orientation, re-arming the timer at 0x200; the +0x30 floor timer does the same
 * for a floor contact (bit 0, +0x124 normal). The actors inside the owner's +0x74 sphere are
 * pushed away at 0x1000 through the ov107 hit hook (kind 0); the first that takes it gets the
 * overlay's hit message with the +8 position, reaction 0x14f mode 5, sub-state 0 and the slot
 * released. Past 0xf000 on the clock the end message goes out with reaction 0x14f mode 6,
 * sub-state 0 and the slot released. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov151Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov151Owner *self, PosMsg *msg, int size);
};

struct hw60 { unsigned short lo : 8, hi : 8; };
struct Bits17a { u8 bit0 : 1, bit1 : 1; };
struct Quat { int x, y, z, w; };

struct Ov151ShotState {
    struct Ov151Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 *pPos;                 /* +0x08 */
    Vec3 vVelocity;             /* +0x0c */
    struct Quat qOrient;        /* +0x18 */
    int nSpeed;                 /* +0x28 */
    int nWallTimer;             /* +0x2c */
    int nFloorTimer;            /* +0x30 */
    int nTravel;                /* +0x34 */
    int nClock;                 /* +0x38 */
};

extern void func_0202f384(Vec3 *dst, struct Quat *quat, const Vec3 *src);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020cab14(struct Ov151Owner *owner, int mode);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_0202ed60(struct Quat *out, const Vec3 *forward, Vec3 *direction);
extern int VEC_DotProduct(const Vec3 *a, const Vec3 *b);
extern void func_0202f55c(struct Quat *out, int t, struct Quat *from, struct Quat *to);
extern void func_0202f4a4(struct Quat *out, struct Quat *in);
extern int func_ov107_020c8eb8(void *item, Vec3 *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov151Owner *a, void *item, int kind, const Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov151Owner *owner, int a, int id, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042258;
extern const PosMsg data_ov151_020cebfc;
extern const PosMsg data_ov151_020cec26;

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov151ShotState *state, PosMsg *msg, const Vec3 *src)
{
    FxVec vDead;
    vDead.x = *(Fx32 *)&src->x;
    PackFx24(&msg->pos[0], vDead.x.value);
    vDead.y = *(Fx32 *)&src->y;
    PackFx24(&msg->pos[1], vDead.y.value);
    vDead.z = *(Fx32 *)&src->z;
    PackFx24(&msg->pos[2], vDead.z.value);
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

/* Reflect the forward vector about the unit normal n and re-aim the orientation. */
static inline void Bounce(struct Ov151ShotState *state, Vec3 *fwd, Vec3 *n, Vec3 *back, Vec3 *refl)
{
    func_01ffa724(-0x1000, fwd, back);
    func_01ffa724(VEC_DotProduct(back, n) << 1, n, refl);
    VEC_Subtract(refl, back, refl);
    func_01ff8d18(refl, fwd);
    func_0202ed60(&state->qOrient, &data_02042258, fwd);
}

void func_ov151_020cd3ac(int *node)
{
    struct Ov151Owner *owner;
    struct Ov151ShotState *state = (struct Ov151ShotState *)node[1];
    Vec3 fwd;
    Vec3 back;
    Vec3 refl;
    struct Quat want;
    Vec3 d;
    int hits[4];
    Vec3 push;
    PosMsg msg;
    PosMsg endMsg;
    struct Ov151Owner *actor;
    int i;
    int n;

    state->nClock += *(int *)(*node + 0x2c);
    func_0202f384(&fwd, &state->qOrient, &data_02042258);
    func_01ffa724(state->nSpeed, &fwd, &state->vVelocity);
    state->nSpeed += (0x100 - state->nSpeed) / 30;
    state->pTarget = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget != 0) {
        VEC_Subtract((void *)(state->pTarget + 0x74), state->pPos, &d);
        func_01ff8d18(&d, &d);
        func_0202ed60(&want, &data_02042258, &d);
        if (VEC_DotProduct(&fwd, &d) >= 0) {
            func_0202f55c(&state->qOrient, FX_MUL(*(int *)(*node + 0x2c) * 30, 0x266), &state->qOrient, &want);
            func_0202f4a4(&state->qOrient, &state->qOrient);
        }
    }
    if (state->nWallTimer > 0) {
        state->nWallTimer -= *(int *)(*node + 0x2c);
    }
    if (state->nWallTimer <= 0) {
        actor = state->pOwner;
        if (((struct Bits17a *)((char *)actor + 0x17a))->bit1 != 0) {
            Bounce(state, &fwd, (Vec3 *)((char *)actor + 0x114), &back, &refl);
            state->nWallTimer = 0x200;
        }
    }
    if (state->nFloorTimer > 0) {
        state->nFloorTimer -= *(int *)(*node + 0x2c);
    }
    if (state->nFloorTimer <= 0) {
        actor = state->pOwner;
        if (((struct Bits17a *)((char *)actor + 0x17a))->bit0 != 0) {
            Bounce(state, &fwd, (Vec3 *)((char *)actor + 0x124), &back, &refl);
            state->nFloorTimer = 0x200;
        }
    }
    owner = state->pOwner;
    n = func_ov107_020c8eb8(*(void **)((char *)owner + 0x38c), (Vec3 *)((char *)owner + 0x74), hits);
    for (i = 0; i < n; i++) {
        VEC_Subtract((void *)(hits[i] + 0x74), (char *)owner + 0x74, &push);
        func_01ff8d18(&push, &push);
        func_01ffa724(0x1000, &push, &push);
        if (func_ov107_020ca918(hits[i], state->pOwner, *(void **)((char *)state->pOwner + 0x38c), 0, &push, 0) != 0) {
            msg = data_ov151_020cebfc;
            SendPos(state, &msg, state->pPos);
            func_ov107_020c5af8(state->pOwner, 0x14f, 5, state->pPos);
            *(u8 *)((char *)state->pOwner + 0x1c7) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (state->nClock <= 0xf000) {
        return;
    }
    endMsg = data_ov151_020cec26;
    SendPos(state, &endMsg, state->pPos);
    func_ov107_020c5af8(state->pOwner, 0x14f, 6, state->pPos);
    *(u8 *)((char *)state->pOwner + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
