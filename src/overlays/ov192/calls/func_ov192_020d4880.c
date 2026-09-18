/* Begin the ov191 enemy's shockwave (x3: ov191/192/193): copies the canned {id 0, kind 5,
 * sub 1} 14-byte message, packs the state's origin (+4) into its three 24-bit coordinates and
 * hands it to the notify hook; then sets bits 1..4 and 7 of the actor's +0x60 high byte, the hit
 * box (+0x28..+0x3c = origin +- 0x1800), zeroes the +8 step and the +0x24 timer, and advances
 * to the shockwave handler (020d2c08).
 * The message is a 7-halfword template copy (three-pair loop + one) and the coordinates are
 * mirrored into a volatile Vec3 while they are packed (the stores survive and sink under the
 * next load, the first coordinate lands in ip); the state is typed throughout so the
 * zero-vector ldm can hoist over the box stores (cf. func_ov141_020cde94). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 hi, mid, lo; } Fx24;
typedef struct { u16 w[7]; } PosMsg;     /* id, kind/sub, arg + Fx24 pos[3] */
typedef struct Actor { char pad[0x24]; void (*notify)(struct Actor *, PosMsg *, int); char pad28[0x60 - 0x28]; u16 hw60; } Actor;
typedef struct { Actor *actor; Vec3 *origin; Vec3 step; char pad14[0x10]; int timer; Vec3 min; Vec3 max; } State;

extern void func_0203c634(int node, int slot, void *cb);
extern PosMsg data_ov192_020d4bd6;
extern const Vec3 data_02041dc8;
extern void func_ov192_020d4a28(void);

static inline void PackFx24(Fx24 *dst, int v) {
    dst->hi = ((u32)v >> 16 & 0x7f) | ((u32)v >> 24 & 0x80);
    dst->mid = (u32)v >> 8;
    dst->lo = v;
}

void func_ov192_020d4880(int node)
{
    State *st = *(State **)(node + 4);
    PosMsg msg;
    volatile Vec3 pos;
    Vec3 *origin;
    int v;

    msg = data_ov192_020d4bd6;
    origin = st->origin;
    v = origin->x;
    PackFx24((Fx24 *)((u8 *)&msg + 5), v);
    pos.x = v;
    v = origin->y;
    PackFx24((Fx24 *)((u8 *)&msg + 8), v);
    pos.y = v;
    v = origin->z;
    PackFx24((Fx24 *)((u8 *)&msg + 11), v);
    pos.z = v;
    if (st->actor->notify != 0) {
        st->actor->notify(st->actor, &msg, 0xe);
    }
    {
        u16 hw = st->actor->hw60;
        st->actor->hw60 = (hw & ~0xff00) |
            ((((((u32)hw << 0x10) >> 0x18) | 0x9e) << 0x18) >> 0x10);
    }
    st->min.x = st->origin->x - 0x1800;
    st->min.y = st->origin->y - 0x1800;
    st->min.z = st->origin->z - 0x1800;
    st->max.x = st->origin->x + 0x1800;
    st->max.y = st->origin->y + 0x1800;
    st->max.z = st->origin->z + 0x1800;
    st->step = data_02041dc8;
    st->timer = 0;
    func_0203c634(node, *(signed char *)(node + 0x20), func_ov192_020d4a28);
}
