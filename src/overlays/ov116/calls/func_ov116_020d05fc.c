/* Action tick of the ov115 enemy (and its byte-identical twins). Clears bit 1 of the actor's
 * +0x5c flags and advances the +0x18 timer. At 0x2a8f (phase 0) the +0xc point takes the
 * target's +0x190 point (or the owner's +0x74 position), raised by 0x8000 and dropped onto the
 * ground by a 0x10000 ray, and the actor is reset (func_0203c960) and placed there (phase 1).
 * At 0x4111 (phase 1) the 0x14-byte kind message from the overlay's +0x0 template carries the
 * packed point to the owner's +0x24 handler and reaction 0x114 mode 5 fires there (phase 2).
 * Between 0x42aa and 0x4400, while the owner's +0x50 state is 1, a 0x8000-radius / 0x200 query
 * sweeps for actors above the point; the first that takes a kind-1 hit gets the +0xe template
 * message with the point raised by 0x1000, reaction 0x114 mode 6, and the task is released.
 * Otherwise the task is released once the actor's +0xad flag is clear. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct SweepQuery {
    Vec3 vPos;
    Vec3 vDir;
    int nRadius;
    int nHeight;
};

struct CastHit { int f0; int f4; int f8; int nFraction; };

struct Ov115Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov115Owner *self, PosMsg *msg, int size);
};

struct Ov115ActionState {
    char *pActor;              /* +0x0 */
    struct Ov115Owner *pOwner; /* +0x4 */
    int pTarget;               /* +0x8 */
    Vec3 vPoint;               /* +0xc */
    int nTimer;                /* +0x18 */
    u8 nPhase;                 /* +0x1c */
};

extern struct CastHit *func_01fff920(void *world, Vec3 *from, Vec3 *step);
extern void func_0203c960(void *transform);
extern void func_0203ca30(void *transform, Vec3 *pos);
extern void func_ov107_020c5af8(struct Ov115Owner *owner, int a, int id, Vec3 *pos);
extern int func_ov107_020c8f44(struct Ov115Owner *owner, struct SweepQuery *query, int *out);
extern int func_ov107_020ca918(int hit, struct Ov115Owner *a, struct Ov115Owner *b, int kind, const Vec3 *push, int z);
extern void func_0203c640(int *node);
extern const PosMsg data_ov116_020d2794;
extern const PosMsg data_ov116_020d27a2;
extern const Vec3 data_02042264;
extern const Vec3 data_02041dc8;


typedef struct { int value; } Fx32;

/* Packs one fixed-point coordinate into a 24-bit message field (sign + 23-bit magnitude,
 * big-endian). The coordinate passes through a Fx32 scratch copy that is never read back; the
 * scratch values are declared z, y, x per call site, which fixes their stack order. */
#define PACK(dst, scratch, src)                                                    \
    (scratch) = (src);                                                             \
    (dst).hi = ((u32)(scratch).value >> 16 & 0x7f) | ((u32)(scratch).value >> 24 & 0x80); \
    (dst).mid = (u32)(scratch).value >> 8;                                         \
    (dst).lo = (scratch).value

static inline void VEC_Set(Vec3 *vec, int x, int y, int z)
{
    int *components = (int *)vec;
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

static inline void SetPoint(struct Ov115ActionState *state, Vec3 at)
{
    state->vPoint = at;
}

void func_ov116_020d05fc(int *node)
{
    struct Ov115ActionState *state = (struct Ov115ActionState *)node[1];
    Vec3 ray;
    PosMsg msg1;
    int hits[4];
    struct SweepQuery query;
    Vec3 at2;
    PosMsg msg2;
    int scene;
    int i;
    int n;
    struct CastHit *hit;
    Fx32 landScratchZ;
    Fx32 landScratchY;
    Fx32 landScratchX;
    Fx32 hitScratchZ;
    Fx32 hitScratchY;
    Fx32 hitScratchX;

    *(u32 *)(state->pActor + 0x5c) &= ~2;
    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nPhase == 0 && state->nTimer >= 0x2a8f) {
        VEC_Set(&ray, 0, 0, 0);
        scene = *(int *)((char *)state->pOwner + 4);
        ray.y = -0x10000;
        SetPoint(state, state->pTarget != 0 ? *(Vec3 *)(state->pTarget + 0x190) : *(Vec3 *)((char *)state->pOwner + 0x74));
        state->vPoint.y += 0x8000;
        hit = func_01fff920(*(void **)(scene + 0x7c), &state->vPoint, &ray);
        if (hit != 0) {
            state->vPoint.y += (int)(((long long)hit->nFraction * ray.y) >> 27);
        }
        func_0203c960(state->pActor + 4);
        func_0203ca30(state->pActor + 4, &state->vPoint);
        state->nPhase = 1;
    }
    if (state->nPhase == 1 && state->nTimer >= 0x4111) {
        msg1 = data_ov116_020d2794;
        PACK(msg1.pos[0], landScratchX, *(Fx32 *)&state->vPoint.x);
        PACK(msg1.pos[1], landScratchY, *(Fx32 *)&state->vPoint.y);
        PACK(msg1.pos[2], landScratchZ, *(Fx32 *)&state->vPoint.z);
        if (state->pOwner->pfnMessage != 0) {
            state->pOwner->pfnMessage(state->pOwner, &msg1, 0xe);
        }
        func_ov107_020c5af8(state->pOwner, 0x114, 5, &state->vPoint);
        state->nPhase = 2;
    }
    if (state->nTimer >= 0x42aa && state->nTimer <= 0x4400 && *(int *)((char *)state->pOwner + 0x50) == 1) {
        query.vPos = state->vPoint;
        query.vDir = data_02042264;
        query.nRadius = 0x8000;
        query.nHeight = 0x200;
        n = func_ov107_020c8f44(state->pOwner, &query, hits);
        for (i = 0; i < n; i++) {
            if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 1, &data_02041dc8, 0) != 0) {
                msg2 = data_ov116_020d27a2;
                at2 = state->vPoint;
                at2.y += 0x1000;
                PACK(msg2.pos[0], hitScratchX, *(Fx32 *)&at2.x);
                PACK(msg2.pos[1], hitScratchY, *(Fx32 *)&at2.y);
                PACK(msg2.pos[2], hitScratchZ, *(Fx32 *)&at2.z);
                if (state->pOwner->pfnMessage != 0) {
                    state->pOwner->pfnMessage(state->pOwner, &msg2, 0xe);
                }
                func_ov107_020c5af8(state->pOwner, 0x114, 6, &at2);
                func_0203c640(node);
                return;
            }
        }
    }
    if (*(u8 *)(state->pActor + 0xad) != 0) {
        return;
    }
    func_0203c640(node);
}
