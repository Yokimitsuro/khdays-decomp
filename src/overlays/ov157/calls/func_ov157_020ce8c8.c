/* Ground sweep of the ov156 enemy's charge (and its byte-identical twin): a box centred on the
 * given point, axis-aligned (right/forward/up), with half-extent t * 0x2000 for the 32.32
 * fraction t. Every entity whose +0x1b4 kind bit is clear in the +0x39 hit bit is pushed away on
 * the ground plane by 0x800 (lifted by 0x100) through the ov107 checker (kind 1); on acceptance
 * its +0x74 position, lifted by 0xb00 and halved, is packed into the overlay's 14-byte template
 * for the actor's +0x24 message hook, reaction 0x13d mode 5 fires there and the kind bit is
 * set. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef long long s64;

typedef struct Vec3 { int x, y, z; } Vec3;
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

struct BoxQuery {
    Vec3 vCenter;
    Vec3 vAxisX;
    Vec3 vAxisZ;
    Vec3 vAxisY;
    int nExtent;
    int bFlag;
};

struct Ov156Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Ov156Owner *self, PosMsg *msg, int size);
};

struct Ov156ChargeState {
    struct Ov156Owner *pOwner;  /* +0x00 */
    char pad004[0x35];
    u8 bit0 : 1;                /* +0x39 */
    u8 bHit : 1;
};

extern int func_ov107_020c8fd0(struct Ov156Owner *owner, struct BoxQuery *query, int *out);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, struct Ov156Owner *a, struct Ov156Owner *b, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(struct Ov156Owner *owner, int a, int id, Vec3 *at);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const PosMsg data_ov157_020d0bb4;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct Ov156ChargeState *state, PosMsg *msg, const Vec3 *src)
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

void func_ov157_020ce8c8(struct Ov156ChargeState *state, s64 t, const Vec3 *at)
{
    int hits[4];
    struct BoxQuery query;
    Vec3 push;
    Vec3 pos;
    PosMsg msg;
    PosMsg tmpl;
    long i;
    long n;
    int hit;
    int y;
    int z;
    int x;

    query.vCenter = *at;
    query.vAxisX = data_02042270;
    query.vAxisZ = data_02042258;
    query.vAxisY = data_02042264;
    query.nExtent = (int)((t * 0x2000 + 0x80000000LL) >> 32);
    query.bFlag = 1;
    n = func_ov107_020c8fd0(state->pOwner, &query, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov157_020d0bb4;
        do {
            hit = hits[i];
            if (((state->bHit >> *(u8 *)(hit + 0x1b4)) & 1) == 0) {
                VEC_Subtract((void *)(hit + 0x74), &query.vCenter, &push);
                push.y = 0;
                func_01ff8d18(&push, &push);
                push.y = 0x100;
                func_01ffa724(0x800, &push, &push);
                if (func_ov107_020ca918(hits[i], state->pOwner, state->pOwner, 1, &push, 0) != 0) {
                    msg = tmpl;
                    z = *(int *)(hit + 0x7c);
                    y = (*(int *)(hit + 0x78) + 0xb00) >> 1;
                    x = *(int *)(hit + 0x74);
                    pos.x = x;
                    pos.y = y;
                    pos.z = z;
                    SendPos(state, &msg, &pos);
                    state->bHit |= 1 << *(u8 *)(hits[i] + 0x1b4);
                    func_ov107_020c5af8(state->pOwner, 0x13d, 5, &pos);
                }
            }
        } while (++i < n);
    }
}
