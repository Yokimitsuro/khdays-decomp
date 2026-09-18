/* Sweep tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390
 * part's motion step rotated by the actor's +0xa0 orientation and scaled by its speed (the step
 * buffer is then overwritten with the facing of the +0x34 yaw); the +0x2c timer accumulates the
 * frame-time and, below 0x1000, a 0x1000 sphere at the +0x24 position offers a kind-0 hit with
 * the velocity as push to every entity whose id bit is clear in the +0x44 mask: on acceptance
 * the entity's +0x74 position raised by 0x800 is packed into the overlay's 14-byte template for
 * the actor's +0x24 message hook, reaction 0x132 mode 4 fires there and the id bit is set
 * (through `1 >> id`, as the original does). Once the +0x28 busy byte clears, sub-state 2 is
 * requested and the tick hands off to a null callback. */
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

struct Ov204Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov204Owner *self, PosMsg *msg, int size);
};

struct Ov204SweepState {
    struct Ov204Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 vVelocity;             /* +0x08 */
    char pad014[0x10];
    Vec3 *pPos;                 /* +0x24 */
    u8 *pBusy;                  /* +0x28 */
    int nTimer;                 /* +0x2c */
    char pad030[4];
    int nYaw;                   /* +0x34 */
    char pad038[0xc];
    u8 bHitMask44;              /* +0x44 */
};

extern int func_ov107_020c9f48(void *part, Vec3 *out);
extern void func_0202f384(Vec3 *dst, void *quat, Vec3 *src);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020c8eb8(struct Ov204Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov204Owner *a, struct Ov204Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov204Owner *owner, int a, int id, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern short data_0203d210[];
extern const PosMsg data_ov205_020d72a0;

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov204SweepState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov205_020d51e4(int *node)
{
    struct Ov204SweepState *state = (struct Ov204SweepState *)node[1];
    int hits[4];
    Sphere sphere;
    Vec3 step;
    Vec3 at;
    PosMsg msg;
    PosMsg tmpl;
    int speed;
    unsigned int idx;
    int i;
    int n;

    speed = func_ov107_020c9f48(*(void **)((char *)state->pOwner + 0x390), &step);
    func_0202f384(&state->vVelocity, (char *)state->pOwner + 0xa0, &step);
    func_01ffa724(speed, &state->vVelocity, &state->vVelocity);
    idx = ANG2IDX(state->nYaw);
    step.y = 0;
    step.x = data_0203d210[idx * 2];
    step.z = data_0203d210[idx * 2 + 1];
    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer < 0x1000) {
        sphere.pos = *state->pPos;
        sphere.radius = 0x1000;
        n = func_ov107_020c8eb8(state->pOwner, &sphere, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov205_020d72a0;
            do {
                if (((state->bHitMask44 >> *(u16 *)(hits[i] + 2)) & 1) == 0) {
                    if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 0, &state->vVelocity, 0) != 0) {
                        msg = tmpl;
                        at = *(Vec3 *)(hits[i] + 0x74);
                        at.y += 0x800;
                        SendPos(state, &msg, &at);
                        func_ov107_020c5af8(state->pOwner, 0x132, 4, &at);
                        state->bHitMask44 |= 1 >> *(u16 *)(hits[i] + 2);
                    }
                }
            } while (++i < n);
        }
    }
    if (*state->pBusy == 0) {
        *(u8 *)((char *)state->pOwner + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
    }
}
