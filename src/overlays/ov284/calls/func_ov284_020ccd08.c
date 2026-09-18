/* Swing tick of the ov284 enemy: re-acquires the target into +0xc and aims the +0x14 yaw at its
 * +0x190 point from the +4 position; the +0x1c timer accumulates the frame-time, its fraction
 * over 0xa22 (clamped to 1.0) drives the swing, and past 0x888 reaction 0x16c mode 4 fires
 * once (+0x25) at the position. From the half-way point the +0x3a8 item's +0x68 sphere with a
 * doubled radius offers a kind-0 hit pushed away from the position at 0x1000 to every entity
 * whose +0x1b4 kind bit is clear in the +0x24 mask: on acceptance the overlay's 14-byte
 * template with the +0x3a4 item's +0x14 point goes to the actor's +0x24 message hook, the kind
 * bit is set and reaction 0x16c mode 5 fires there. Once the +8 busy byte clears animation 7
 * plays and the tick hands off to cd020. */
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

struct Ov284Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov284Owner *self, PosMsg *msg, int size);
};

typedef long long s64;

struct Ov284SwingState {
    struct Ov284Owner *pOwner;  /* +0x00 */
    Vec3 *pPos;                 /* +0x04 */
    u8 *pBusy;                  /* +0x08 */
    int pTarget;                /* +0x0c */
    char pad010[4];
    int nYaw;                   /* +0x14 */
    char pad018[4];
    int nTimer;                 /* +0x1c */
    char pad020[4];
    u8 bHitMask24;              /* +0x24 */
    u8 bWarned25;               /* +0x25 */
};

extern int func_ov107_020cab14(struct Ov284Owner *owner, int mode);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int x, int z);
extern s64 func_01ff8a14(int num, int den);
extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c8eb8(struct Ov284Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov284Owner *a, struct Ov284Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov284Owner *owner, int a, int id, void *at);
extern void func_ov107_020c9264(struct Ov284Owner *actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov284_020cd020(void);
extern const PosMsg data_ov284_020cd5b8;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov284SwingState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov284_020ccd08(int *node)
{
    struct Ov284SwingState *state = (struct Ov284SwingState *)node[1];
    Vec3 d;
    int hits[4];
    Sphere sphere;
    Vec3 push;
    PosMsg msg;
    PosMsg tmpl;
    s64 t;
    long i;
    long n;

    state->pTarget = func_ov107_020cab14(state->pOwner, 0);
    if (state->pTarget != 0) {
        VEC_Subtract((void *)(state->pTarget + 0x190), state->pPos, &d);
        state->nYaw = func_020050b4(d.x, d.z);
    }
    state->nTimer += *(int *)(*node + 0x2c);
    t = func_01ff8a14(state->nTimer, 0xa22);
    if (t > 0x100000000LL) {
        t = 0x100000000LL;
    }
    if (state->bWarned25 == 0 && state->nTimer >= 0x888) {
        func_ov107_020c5af8(state->pOwner, 0x16c, 4, state->pPos);
        state->bWarned25 = 1;
    }
    if (t >= 0x80000000LL) {
        sphere = *(Sphere *)(*(int *)(*(int *)((char *)state->pOwner + 0x3a8)) + 0x68);
        sphere.radius <<= 1;
        n = func_ov107_020c8eb8(state->pOwner, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov284_020cd5b8;
            do {
                if (((state->bHitMask24 >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                    VEC_Subtract((void *)(hits[i] + 0x190), state->pPos, &push);
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x1000, &push, &push);
                    if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 0, &push, 0) != 0) {
                        msg = tmpl;
                        SendPos(state, &msg, (Vec3 *)(*(int *)((char *)state->pOwner + 0x3a4) + 0x14));
                        state->bHitMask24 |= 1 << *(u8 *)(hits[i] + 0x1b4);
                        func_ov107_020c5af8(state->pOwner, 0x16c, 5, (void *)(*(int *)((char *)state->pOwner + 0x3a4) + 0x14));
                    }
                }
            } while (++i < n);
        }
    }
    if (*state->pBusy != 0) {
        return;
    }
    func_ov107_020c9264(state->pOwner, 7, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov284_020cd020);
}
