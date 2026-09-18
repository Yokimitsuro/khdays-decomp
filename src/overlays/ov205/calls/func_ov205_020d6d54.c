/* Charge sweep of the ov204 enemy (and its byte-identical twin): sweeps a 0xa00 sphere at the
 * +0x24 position and, for every entity whose id bit is clear in the +0x44 mask, offers a kind-2
 * hit with the +8 velocity as push; on acceptance the entity's +0x74 position is packed into the
 * overlay's 14-byte template and delivered to the actor's +0x24 message hook, reaction 0x132
 * mode 4 fires there and the id bit is set (through `1 >> id`, as the original does). */
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

struct Ov204ChargeState {
    struct Ov204Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 vVelocity;             /* +0x08 */
    char pad014[0x10];
    Vec3 *pPos;                 /* +0x24 */
    char pad028[0x1c];
    u8 bHitMask44;              /* +0x44 */
};

extern int func_ov107_020c8eb8(struct Ov204Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov204Owner *a, struct Ov204Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov204Owner *owner, int a, int id, Vec3 *at);
extern const PosMsg data_ov205_020d72ae;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov204ChargeState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov205_020d6d54(struct Ov204ChargeState *state)
{
    Sphere sphere;
    int hits[4];
    Vec3 at;
    PosMsg msg;
    PosMsg tmpl;
    long i;
    long n;

    sphere.pos = *state->pPos;
    sphere.radius = 0xa00;
    n = func_ov107_020c8eb8(state->pOwner, &sphere, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov205_020d72ae;
        do {
            if (((state->bHitMask44 >> *(u16 *)(hits[i] + 2)) & 1) == 0) {
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 2, &state->vVelocity, 0) != 0) {
                    msg = tmpl;
                    at = *(Vec3 *)(hits[i] + 0x74);
                    SendPos(state, &msg, &at);
                    func_ov107_020c5af8(state->pOwner, 0x132, 4, &at);
                    state->bHitMask44 |= 1 >> *(u16 *)(hits[i] + 2);
                }
            }
        } while (++i < n);
    }
}
