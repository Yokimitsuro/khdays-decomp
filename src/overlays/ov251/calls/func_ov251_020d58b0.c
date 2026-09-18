/* Lunge tick of the ov250 enemy (and its byte-identical twin): the +0x54 velocity is the facing
 * of the +0x14 yaw at the +0x70 speed, which drops by 30 x dt / 256 each tick; the +0x1c timer
 * accumulates the frame-time and, between 0xc00 and 0x1280, a 0x1600 sphere at the +0x3a4
 * item's +0x14 point offers a kind-1 hit pushed along the facing at 0x800 to every entity found:
 * on acceptance the sphere centre plus the push is packed into the overlay's 14-byte template
 * for the actor's +0x24 message hook and reaction 0x159 mode 5 fires there. Once the +0xc busy
 * byte clears the +0x74 cooldown is re-armed at random between the actor's +0x224 and +0x228,
 * sub-state 2 is requested and the state ends. */
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

struct Ov250Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov250Owner *self, PosMsg *msg, int size);
};

struct Ov250SweepState {
    struct Ov250Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    char pad008[4];
    u8 *pBusy;                  /* +0x0c */
    char pad010[4];
    int nYaw;                   /* +0x14 */
    char pad018[4];
    int nTimer;                 /* +0x1c */
    char pad020[0x34];
    Vec3 vVelocity;             /* +0x54 */
    char pad060[0x10];
    int nSpeed;                 /* +0x70 */
    int nCooldown;              /* +0x74 */
};

extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_02023eb4(int bound);
extern void VEC_Add(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_ov107_020c8eb8(struct Ov250Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov250Owner *a, struct Ov250Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov250Owner *owner, int a, int id, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const PosMsg data_ov251_020d6500;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov250SweepState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov251_020d58b0(int *node)
{
    struct Ov250SweepState *state = (struct Ov250SweepState *)node[1];
    Vec3 facing;
    Vec3 push;
    Sphere sphere;
    int hits[4];
    Vec3 at;
    PosMsg msg;
    PosMsg tmpl;
    unsigned int idx;
    int i;
    int n;
    int lo;
    int span;

    idx = ANG2IDX(state->nYaw);
    state->vVelocity.x = data_0203d210[idx * 2];
    state->vVelocity.y = 0;
    state->vVelocity.z = data_0203d210[idx * 2 + 1];
    func_01ffa724(state->nSpeed, &state->vVelocity, &state->vVelocity);
    state->nSpeed -= (int)(((long long)(*(int *)(*node + 0x2c) * 30) * 0x10 + 0x800) >> 12);
    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer >= 0xc00 && state->nTimer < 0x1280) {
        idx = ANG2IDX(state->nYaw);
        facing.x = data_0203d210[idx * 2];
        facing.y = 0;
        facing.z = data_0203d210[idx * 2 + 1];
        func_01ffa724(0x800, &facing, &push);
        sphere.pos = *(Vec3 *)(*(int *)((char *)state->pOwner + 0x3a4) + 0x14);
        sphere.radius = 0x1600;
        n = func_ov107_020c8eb8(state->pOwner, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov251_020d6500;
            do {
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 1, &push, 0) != 0) {
                    msg = tmpl;
                    VEC_Add(&sphere.pos, &push, &at);
                    SendPos(state, &msg, &at);
                    func_ov107_020c5af8(state->pOwner, 0x159, 5, &at);
                }
            } while (++i < n);
        }
    }
    if (*state->pBusy == 0) {
        lo = *(int *)((char *)state->pOwner + 0x224);
        span = *(int *)((char *)state->pOwner + 0x228) - lo;
        if (span < 0) {
            span = -span;
        }
        state->nCooldown = lo + func_02023eb4(span + 1);
        *(u8 *)((char *)state->pOwner + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
