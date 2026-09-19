/* Shockwave tick of the ov274 enemy. While the +0x24 timer (fed by the owner's rate) is at most
 * 0x3b8, a box centred 0x800 above the +4 point, axis-aligned, with half-extent
 * timer x 5 / 0x3b8 (fixed point) pushes every entity whose +0x1b4 kind bit is clear in the
 * +0x50 mask away on the ground plane by 0x800 (kind 2); on acceptance the entity's +0x74
 * position is packed into the overlay's 14-byte template (data_ov275_020d6092) for the owner's
 * +0x24 hook, reaction 0x163 mode 0xc fires there and the kind bit is set. Once the +0xc idle
 * byte clears sub-state 2 is requested and the state ends. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;
typedef struct { int value; } Fx32;

typedef struct {
    u16 id;             /* +0x0 */
    u8 kind;            /* +0x2 */
    u8 cmd;             /* +0x3 */
    u8 flag;            /* +0x4 */
    Fx24 pos[3];        /* +0x5 */
} PosMsg;

struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

struct Ov274State {
    int pOwner;                  /* 0x00 */
    Vec3 *pPoint;                /* 0x04 */
    int pPos;                    /* 0x08 */
    u8 *pBusy;                   /* 0x0c */
    char pad10[0x14];
    int nTimer;                  /* 0x24 */
    char pad28[0x28];
    u8 bHitMask50;               /* 0x50 */
};

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

extern int func_ov107_020c8fd0(int owner, struct BoxQuery *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, int a, int b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const PosMsg data_ov275_020d6092;

void func_ov275_020d5c08(int *node)
{
    int hit;
    struct Ov274State *state = (struct Ov274State *)node[1];
    int hits[4];
    struct BoxQuery query;
    Vec3 push;
    PosMsg msg;
    PosMsg tmpl;
    long n;
    long i;

    state->nTimer += *(int *)(*node + 0x2c);
    if (state->nTimer <= 0x3b8) {
        query.vCenter = *state->pPoint;
        query.vCenter.y += 0x800;
        query.vAxisX = data_02042270;
        query.vAxisZ = data_02042258;
        query.vAxisY = data_02042264;
        query.nExtent = (state->nTimer * 5 << 12) / 0x3b8;
        query.bFlag = 1;
        n = func_ov107_020c8fd0(state->pOwner, &query, hits);
        i = 0;
        if (n > 0) {
            tmpl = data_ov275_020d6092;
            do {
                if (((state->bHitMask50 >> *(u8 *)(hits[i] + 0x1b4)) & 1) == 0) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &push);
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x800, &push, &push);
                    if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 2, &push, 0) != 0) {
                        msg = tmpl;
                        hit = hits[i];
                        SendPos(state, &msg, (Vec3 *)(hit + 0x74));
                        func_ov107_020c5af8(state->pOwner, 0x163, 0xc, (void *)(hit + 0x74));
                        state->bHitMask50 |= 1 << *(u8 *)(hits[i] + 0x1b4);
                    }
                }
            } while (++i < n);
        }
    }
    if (*state->pBusy != 0) {
        return;
    }
    *(u8 *)(state->pOwner + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
