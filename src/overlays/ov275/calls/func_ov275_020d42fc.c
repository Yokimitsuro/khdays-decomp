/* Landing tick of the ov274 enemy. Each foot has its own window on the +0x24 timer (fed by
 * the owner's rate): the +0x3bc placement between 0x1b28 and 0x1ee6, the +0x3c0 one between
 * 0xded and 0x1199. Inside its window a foot first fires reaction 0x163 mode 9 at its sphere
 * (+0x68, radius x 1.5) once (bits 0 / 1 of +0x52), then the entities in the sphere are each
 * pushed by 0.5 along the unit direction from the sphere's centre (kind 1) and, on
 * acceptance, the overlay's 14-byte template (data_ov275_020d6068 / data_ov275_020d604c)
 * carries the entity's +0x74 position added to the centre and scaled 0.5 to the owner's
 * +0x24 hook, where reaction 0x163 mode 0xa fires. Once the +0xc idle byte clears sub-state 2
 * is requested and the state ends. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;
typedef struct { int value; } Fx32;
typedef struct { Vec3 pos; int nRadius; } Sphere;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct Ov274State {
    int pOwner;                  /* 0x00 */
    Vec3 *pPoint;                /* 0x04 */
    Vec3 *pPos;                  /* 0x08 */
    u8 *pBusy;                   /* 0x0c */
    char pad10[0x14];
    int nTimer;                  /* 0x24 */
    char pad28[0x2a];
    u8 nFlags52;                 /* 0x52 */
};

#define FX_MUL(a, b) ((int)(((long long)(a) * (b) + 0x800) >> 12))

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov274State *state, PosMsg *msg, const Vec3 *src)
{
    Fx32 px;
    Fx32 py;
    Fx32 pz;
    px = *(Fx32 *)&src->x;
    PackFx24(&msg->pos[0], px.value);
    py = *(Fx32 *)&src->y;
    PackFx24(&msg->pos[1], py.value);
    pz = *(Fx32 *)&src->z;
    PackFx24(&msg->pos[2], pz.value);
    if (*(void (**)(int, PosMsg *, int))(state->pOwner + 0x24) != 0) {
        (*(void (**)(int, PosMsg *, int))(state->pOwner + 0x24))(state->pOwner, msg, 0xe);
    }
}

extern int func_ov107_020c8eb8(int owner, Sphere *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const PosMsg data_ov275_020d6068;
extern const PosMsg data_ov275_020d604c;

static inline void SweepFoot(struct Ov274State *state, int nFoot, PosMsg tmpl, int *hits, Sphere *psphere, int nBit)
{
    Vec3 at;
    PosMsg msg;
    Vec3 push;
    long i;
    long n;

    *psphere = *(Sphere *)(*(int *)(state->pOwner + nFoot) + 0x68);
    psphere->nRadius = FX_MUL(psphere->nRadius, 0x1800);
    if ((state->nFlags52 & nBit) == 0) {
        func_ov107_020c5af8(state->pOwner, 0x163, 9, psphere);
        state->nFlags52 |= nBit;
    }
    n = func_ov107_020c8eb8(state->pOwner, psphere, hits);
    i = 0;
    if (n > 0) {
        do {
            VEC_Subtract((void *)(hits[i] + 0x74), &psphere->pos, &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 1, &push, 0) != 0) {
                msg = tmpl;
                VEC_Add((void *)(hits[i] + 0x74), &psphere->pos, &at);
                func_01ffa724(0x800, &at, &at);
                SendPos(state, &msg, &at);
                func_ov107_020c5af8(state->pOwner, 0x163, 0xa, &at);
            }
        } while (++i < n);
    }
}

void func_ov275_020d42fc(int *node)
{
    struct Ov274State *state = (struct Ov274State *)node[1];
    int hits[4];
    Sphere sphere;

    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer >= 0x1b28 && state->nTimer <= 0x1ee6) {
        SweepFoot(state, 0x3bc, data_ov275_020d6068, hits, &sphere, 1);
    }
    if (state->nTimer >= 0xded && state->nTimer <= 0x1199) {
        SweepFoot(state, 0x3c0, data_ov275_020d604c, hits, &sphere, 2);
    }
    if (*state->pBusy != 0) {
        return;
    }
    *(u8 *)(state->pOwner + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
