/* Bounce tick of the ov204 enemy's ball (and its byte-identical twin). A wall contact (bit 1 of
 * the actor's +0x17a) reflects the +0x48 direction about the +0x114 contact normal (flattened),
 * sends the overlay's 14-byte message with the +0x24 position to the actor's +0x24 hook and
 * fires reaction 0x132 mode 9 there. The +8 velocity is the direction times the +0x54 speed,
 * which decays to 995/1000 each tick. Once the +0x2c timer (frame-time) reaches 0x198, the
 * velocity becomes a capsule from the position with the actor's +0x80 radius: every entity in
 * the sphere accepting a kind-3 hit pushed away at the speed gets the reflected direction about
 * the flattened normal from its closest point on the axis, the 14-byte message with its
 * position and reaction 0x132 mode 4; then every other ready actor of the scene's +0x80 list
 * with a clear +0x1ac mode whose +0x22c hit shapes (active ones) cross the capsule receives a
 * 0x2004/8 hit packet (push at the speed along that normal, the actor's +0x2a2/+0x258 ids,
 * strength 100) through the actor's +0x25c source; the first accepted hit reflects the
 * direction and ends the search. Phase +0x45 0 waits for the +0x28 busy byte to clear and
 * plays animation 0xa (looped); phase 1 plays animation 0xb once the speed drops below 0x200
 * and hands off to d2728. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long fx64;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { Vec3 pos; int radius; } Sphere;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
struct hw60 { unsigned short lo : 8, hi : 8; };
struct w8 { unsigned int lo : 8, rest : 24; };
struct Bits17a { u8 bit0 : 1, bit1 : 1; };

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

typedef struct Segment {
    Vec3 p0;
    Vec3 dir;
    int scale;
} Segment;

struct Capsule {
    Segment seg;
    int radius;
};

struct HitPacket {
    u32 flagsLo : 16;
    u32 flagsHi : 16;
    Vec3 normal;
    int field_10 : 16;
    int field_12 : 16;
    int field_14 : 16;
    int field_16 : 16;
    void *field_18;
    signed char field_1c;
    u8 pad01d[3];
    int field_20;
    u32 flags24Lo : 16;
    u32 flags24Hi : 16;
    int field_28;
};

struct Ov204Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov204Owner *self, PosMsg *msg, int size);
};

struct Ov204BallState {
    struct Ov204Owner *pOwner;  /* +0x00 */
    int pTarget;                /* +0x04 */
    Vec3 vVelocity;             /* +0x08 */
    char pad014[0x10];
    Vec3 *pPos;                 /* +0x24 */
    u8 *pBusy;                  /* +0x28 */
    int nTimer;                 /* +0x2c */
    char pad030[0x15];
    u8 nPhase45;                /* +0x45 */
    char pad046[2];
    Vec3 vDir;                  /* +0x48 */
    int nSpeed;                 /* +0x54 */
};

extern int func_01ff8d18(Vec3 *v, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c5af8(struct Ov204Owner *owner, int a, int id, Vec3 *at);
extern int func_ov107_020c8eb8(struct Ov204Owner *owner, Sphere *sphere, int *out);
extern int func_ov107_020ca918(int hit, struct Ov204Owner *a, struct Ov204Owner *b, int kind, Vec3 *push, int z);
extern int func_02036304(void *point, Segment *seg, fx64 *outDist);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern int func_ov107_020c38ac(void *shape, Segment *seg, int flags);
extern int func_ov107_020c5cfc(int other, int source, struct HitPacket *packet);
extern void func_ov107_020c9264(struct Ov204Owner *actor, int anim, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov205_020d6368(int *node);
extern const PosMsg data_ov205_020d7268;
extern const PosMsg data_ov205_020d7276;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov204BallState *state, PosMsg *msg, const Vec3 *src)
{
    volatile int px;
    volatile int py;
    volatile int pz;
    int x;
    x = src->x;
    px = x;
    PackFx24(&msg->pos[0], x);
    x = src->y;
    py = x;
    PackFx24(&msg->pos[1], x);
    x = src->z;
    pz = x;
    PackFx24(&msg->pos[2], x);
    if (state->pOwner->pfnMessage != 0) {
        state->pOwner->pfnMessage(state->pOwner, msg, 0xe);
    }
}

/* Reflect the +0x48 direction about the unit normal n. */
static inline void Reflect(struct Ov204BallState *state, Vec3 *n, Vec3 *back, Vec3 *refl)
{
    func_01ffa724(-0x1000, &state->vDir, back);
    func_01ffa724(VEC_DotProduct(back, n) << 1, n, refl);
    VEC_Subtract(refl, back, refl);
    func_01ff8d18(refl, &state->vDir);
}

/* Closest point of the capsule axis to `point`, into `out`. */
static inline void AxisPoint(void *point, Segment *seg, fx64 *t, Vec3 *out)
{
    func_02036304(point, seg, t);
    out->x = (int)((*t * seg->dir.x + 0x80000000LL) >> 32);
    out->y = (int)((*t * seg->dir.y + 0x80000000LL) >> 32);
    out->z = (int)((*t * seg->dir.z + 0x80000000LL) >> 32);
    VEC_Add(&seg->p0, out, out);
}

void func_ov205_020d5b54(int *node)
{
    struct Ov204BallState *state = (struct Ov204BallState *)node[1];
    Vec3 back;
    Vec3 refl;
    Vec3 n;
    Vec3 closest;
    Vec3 push;
    PosMsg wallMsg;
    int hits[4];
    struct Capsule cap;
    Sphere sphere;
    PosMsg msg;
    fx64 t;
    int nHits;
    int scene;
    int i;
    int hit;
    int other;
    int *entry;
    int *shape;

    if (((struct Bits17a *)((char *)state->pOwner + 0x17a))->bit1 != 0) {
        n = *(Vec3 *)((char *)state->pOwner + 0x114);
        n.y = 0;
        func_01ff8d18(&n, &n);
        Reflect(state, &n, &back, &refl);
        wallMsg = data_ov205_020d7276;
        SendPos(state, &wallMsg, state->pPos);
        func_ov107_020c5af8(state->pOwner, 0x132, 9, state->pPos);
    }
    func_01ffa724(state->nSpeed, &state->vDir, &state->vVelocity);
    state->nSpeed = state->nSpeed * 995 / 1000;
    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer >= 0x198) {
        cap.seg.p0 = *state->pPos;
        cap.seg.scale = func_01ff8d18(&state->vVelocity, &cap.seg.dir);
        cap.radius = *(int *)((char *)state->pOwner + 0x80);
        sphere.pos = cap.seg.p0;
        sphere.radius = cap.radius;
        nHits = func_ov107_020c8eb8(state->pOwner, &sphere, hits);
        i = 0;
        if (nHits > 0) {
            do {
                hit = hits[i];
                VEC_Subtract((void *)(hit + 0x74), &cap.seg.p0, &push);
                func_01ff8d18(&push, &push);
                func_01ffa724(state->nSpeed, &push, &push);
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 3, &push, 8) != 0) {
                    msg = data_ov205_020d7268;
                    AxisPoint((void *)(hit + 0x74), &cap.seg, &t, &closest);
                    VEC_Subtract((void *)(hit + 0x74), &closest, &n);
                    n.y = 0;
                    func_01ff8d18(&n, &n);
                    Reflect(state, &n, &back, &refl);
                    SendPos(state, &msg, (Vec3 *)(hits[i] + 0x74));
                    func_ov107_020c5af8(state->pOwner, 0x132, 4, state->pPos);
                }
            } while (++i < nHits);
        }
        scene = *(int *)((char *)state->pOwner + 4);
        entry = func_01fffd70(scene + 0x80);
        other = entry == 0 ? 0 : *entry;
        while (other != 0) {
            if (other != (int)state->pOwner && (((struct hw60 *)(other + 0x60))->lo & 1) != 0 &&
                (*(u16 *)(other + 0x1ac) & 7) == 0) {
                for (shape = func_01fffd70(other + 0x22c); shape != 0; shape = func_01fffd8c(other + 0x22c)) {
                    if ((((struct w8 *)(shape + 2))->lo & 1) != 0 && func_ov107_020c38ac((void *)shape[0], &cap.seg, 0) != 0) {
                        struct HitPacket packet = {0};
                        AxisPoint((void *)(other + 0x74), &cap.seg, &t, &closest);
                        VEC_Subtract((void *)(other + 0x74), &closest, &n);
                        n.y = 0;
                        func_01ff8d18(&n, &n);
                        func_01ffa724(state->nSpeed, &n, &push);
                        packet.flagsLo = 0x2004;
                        packet.flagsHi = 8;
                        packet.normal = push;
                        packet.field_10 = *(u16 *)((char *)state->pOwner + 0x2a2);
                        packet.field_14 = *(int *)((char *)state->pOwner + 0x258);
                        packet.field_18 = shape;
                        packet.field_1c = 0x64;
                        if (func_ov107_020c5cfc(other, *(int *)((char *)state->pOwner + 0x25c), &packet) != 0) {
                            Reflect(state, &n, &back, &refl);
                            break;
                        }
                    }
                }
            }
            entry = func_01fffd8c(scene + 0x80);
            other = entry == 0 ? 0 : *entry;
        }
    }
    if (state->nPhase45 == 0) {
        if (*state->pBusy != 0) {
            return;
        }
        func_ov107_020c9264(state->pOwner, 0xa, 1);
        state->nPhase45 = 1;
        return;
    }
    if (state->nPhase45 != 1) {
        return;
    }
    if (state->nSpeed >= 0x200) {
        return;
    }
    func_ov107_020c9264(state->pOwner, 0xb, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov205_020d6368);
}
