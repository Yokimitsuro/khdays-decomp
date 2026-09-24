/* Swing callback of the ov244 enemy's arm (ov277 cf13c with a per-swing hit mask): between frames
 * 4.55 and 5.72 of the event
 * the +0x88 animation's bone matrix at the event frame (02016320) gives the arm tip; the sweep box
 * is centred on the arm's +0x14 root at height 0.5, axis-aligned, with the root-to-tip distance as
 * its extent. Every entity it holds is pushed by 1.0 along the flattened direction away from the
 * centre (kind 0) and, on acceptance, the point that far from the centre towards the entity is
 * packed into the overlay's 14-byte template for the owner's +0x24 message hook and effect 0x53
 * plays there. Entity kinds already in the event's +0x11 mask are skipped; the mask keeps only the
 * kinds still inside the box. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Vec3 { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;   /* sign + 23-bit magnitude, big-endian */
typedef struct { int value; } Fx32;
typedef struct { Fx32 x, y, z; } FxVec;
typedef struct { int m[9]; Vec3 trans; } Mtx43;

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

struct Owner {
    char pad000[0x24];
    void (*pfnMessage)(struct Owner *self, PosMsg *msg, int size);
};

struct SwingEvent {
    int pad00;
    struct Owner *pOwner;   /* +0x04 */
    int nFrame;             /* +0x08 */
    int nKey;               /* +0x0c */
    u8 pad10;
    u8 mask11;              /* +0x11: kinds already hit by this swing */
};

extern int func_02016320(void *anim, Mtx43 *out, int a, int key);
extern void VEC_Subtract(void *a, void *b, Vec3 *d);
extern int func_01ff8d18(Vec3 *a, Vec3 *d);
extern int func_ov107_020c8fd0(struct Owner *owner, struct BoxQuery *query, int *out);
extern void func_01ffa724(int scale, Vec3 *v, Vec3 *d);
extern int func_ov107_020ca918(int hit, struct Owner *a, struct Owner *b, int kind, Vec3 *push, int z);
extern void VEC_Add(void *a, void *b, Vec3 *d);
extern void func_02033d0c(int id, int kind, Vec3 *pos, int flag);
extern const Vec3 data_02042270;
extern const Vec3 data_02042258;
extern const Vec3 data_02042264;
extern const PosMsg data_ov244_020d3716;

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

static inline void SendPos(struct SwingEvent *ev, PosMsg *msg, const Vec3 *src)
{
    FxVec vDead;
    vDead.x = *(Fx32 *)&src->x;
    PackFx24(&msg->pos[0], vDead.x.value);
    vDead.y = *(Fx32 *)&src->y;
    PackFx24(&msg->pos[1], vDead.y.value);
    vDead.z = *(Fx32 *)&src->z;
    PackFx24(&msg->pos[2], vDead.z.value);
    if (ev->pOwner->pfnMessage != 0) {
        ev->pOwner->pfnMessage(ev->pOwner, msg, 0xe);
    }
}

void func_ov244_020cf16c(char *self, struct SwingEvent *ev)
{
    Mtx43 mtx;
    int hits[4];
    Vec3 tip;
    struct BoxQuery query;
    Vec3 dir;
    Vec3 push;
    Vec3 pos;
    PosMsg msg;
    PosMsg tmpl;
    long i;
    u8 seen;
    long n;
    u8 bit;

    if (ev->nFrame < 0x48c8 || ev->nFrame > 0x5b83) {
        return;
    }
    seen = 0;
    if (func_02016320((void *)(*(int *)(self + 0x88) + 0x20), &mtx, 0, ev->nKey) == 0) {
        return;
    }
    tip = mtx.trans;
    VEC_Subtract(self + 0x14, &tip, &dir);
    query.vCenter = *(Vec3 *)(self + 0x14);
    query.vCenter.y = 0x800;
    query.vAxisX = data_02042270;
    query.vAxisZ = data_02042258;
    query.vAxisY = data_02042264;
    query.nExtent = func_01ff8d18(&dir, &dir);
    query.bFlag = 0;
    n = func_ov107_020c8fd0(ev->pOwner, &query, hits);
    i = 0;
    if (n > 0) {
        tmpl = data_ov244_020d3716;
        do {
            bit = 1 << *(u16 *)(hits[i] + 2);
            seen |= bit;
            if ((ev->mask11 & bit) != 0) {
                continue;
            }
            VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1000, &push, &push);
            if (func_ov107_020ca918(hits[i], ev->pOwner, ev->pOwner, 0, &push, 0) != 0) {
                msg = tmpl;
                VEC_Subtract((void *)(hits[i] + 0x74), &query.vCenter, &pos);
                func_01ff8d18(&pos, &pos);
                func_01ffa724(query.nExtent, &pos, &pos);
                VEC_Add(&query.vCenter, &pos, &pos);
                SendPos(ev, &msg, &pos);
                func_02033d0c(0, 0x53, &pos, 0);
                ev->mask11 |= bit;
            }
        } while (++i < n);
    }
    ev->mask11 &= seen;
}
