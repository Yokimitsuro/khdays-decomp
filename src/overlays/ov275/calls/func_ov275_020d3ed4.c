/* Charge tick of the ov274 enemy. The +0x14 velocity is the sine/cosine of the +0x40 heading
 * (y 0) normalised and scaled 0x800 (after a 0x200 scaling of the raw pair); the entities
 * inside 0x1d00 of the +8 point are swept and each one ahead of the velocity (positive dot
 * product of its offset from the +8 point) is tested along the velocity (kind 0): on
 * acceptance the overlay's 14-byte template (data_ov275_020d6076) carries the entity's +0x74
 * position added to the +0x3b0 body's transform and scaled 0x800 to the owner's
 * +0x24 hook and reaction 0x163 mode 6 fires at the +8 point; every accepted or rejected
 * candidate bumps the +0x52 count. Four hits end the charge (animation 5 mode 0, hand-over to
 * func_ov275_020d4284); otherwise the +0x20 step counter fires reaction 0x163 mode 4 at 5 and
 * mode 5 at 10 (wrapping), and the +0x24 timer, fed by the owner's rate, ends the charge the
 * same way past 3.0 or once the owner reports a wall (+0x17a bit 1). */
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
    char pad10[4];
    Vec3 vVelocity;              /* 0x14 */
    int nStep;                   /* 0x20 */
    int nTimer;                  /* 0x24 */
    char pad28[0x18];
    int nHeading;                /* 0x40 */
    char pad44[0xe];
    u8 nHits52;                  /* 0x52 */
};

struct Bit1 { u8 bit0 : 1, bit1 : 1; };

static inline unsigned short FX_RadToIdx(int rad) {
    return (unsigned short)((0x28BE60DB9391LL * rad + 0x80000000000LL) >> 44);
}

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

extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern int func_ov107_020c8eb8(int owner, Sphere *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int VEC_DotProduct(Vec3 *a, Vec3 *b);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void VEC_Add(Vec3 *a, Vec3 *b, Vec3 *d);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const short data_0203d210[];
extern const PosMsg data_ov275_020d6076;
extern void func_ov275_020d4284(int *node);

void func_ov275_020d3ed4(int *node)
{
    struct Ov274State *state = (struct Ov274State *)node[1];
    Sphere query;
    Vec3 dir;
    int hits[4];
    Vec3 d;
    PosMsg msg;
    Vec3 at;
    PosMsg tmpl;
    long n;
    long i;

    dir.x = data_0203d210[(FX_RadToIdx(state->nHeading) >> 4) * 2];
    dir.y = 0;
    dir.z = data_0203d210[(FX_RadToIdx(state->nHeading) >> 4) * 2 + 1];
    func_01ffa724(0x200, &dir, &state->vVelocity);
    func_01ff8d18(&dir, &dir);
    func_01ffa724(0x800, &dir, &dir);
    query.pos = *state->pPos;
    query.nRadius = 0x1d00;
    n = func_ov107_020c8eb8(state->pOwner, &query, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov275_020d6076;
        do {
            VEC_Subtract((void *)(hits[i] + 0x74), state->pPos, &d);
            if (VEC_DotProduct(&d, &dir) > 0) {
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 0, &dir, 0) != 0) {
                    msg = tmpl;
                    VEC_Add((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*(int *)(*(int *)(state->pOwner + 0x3b0)) + 4), &at);
                    func_01ffa724(0x800, &at, &at);
                    SendPos(state, &msg, &at);
                    func_ov107_020c5af8(state->pOwner, 0x163, 6, state->pPos);
                }
                state->nHits52++;
            }
        } while (++i < n);
    }
    if (state->nHits52 >= 4) {
        func_ov107_020c9264(state->pOwner, 5, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov275_020d4284);
        return;
    }
    state->nStep++;
    if (state->nStep == 5) {
        func_ov107_020c5af8(state->pOwner, 0x163, 4, state->pPos);
    } else if (state->nStep == 0xa) {
        func_ov107_020c5af8(state->pOwner, 0x163, 5, state->pPos);
        state->nStep = 0;
    }
    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer < 0x3000 && ((struct Bit1 *)(state->pOwner + 0x17a))->bit1 == 0) {
        return;
    }
    func_ov107_020c9264(state->pOwner, 5, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov275_020d4284);
}
