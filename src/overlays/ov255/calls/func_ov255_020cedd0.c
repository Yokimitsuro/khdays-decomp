/* Third bite tick of an ov255 state: at 2.5 on the +0x50 timer reaction +0x3f8 mode 6 fires once
 * at the owner's +0x3b0 body point (+0x65). Without a nearest target (020cab14, kept in +0x5c)
 * sub-state 2 is requested; otherwise the +0x10 step is the +0x3a4 part's motion step (020c9f48)
 * turned by the +0x1c orientation. The +0x44 timer accumulates the frame rate; up to 0.8 the +0x40
 * rate is the frame rate x 15, then 0, and between 0.63 and 1.25 the owner's +0x3a0 segment
 * (+0x78, radius 0.75) is swept over the actor list: every entity whose +2 id bit is clear in the
 * +0x63 mask is pushed 0.25 along the +0x1c heading (kind 2); on acceptance the 14-byte message of
 * data_ov255_020d2b52 carries its +0x74 point to the owner's +0x24 hook, its bit is set and
 * reaction +0x3f8 mode 9 fires there. From 0.7 on the hook receives note 5 of data_ov255_020d2b20
 * once (+0x62). Once the +0xc idle byte clears, the +0x54 cooldown is re-rolled in
 * [+0x224, +0x228] and sub-state 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov107_020c9f48(int part, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov255_020d2b52;
extern const Cmd4 data_ov255_020d2b20[];
extern const Vec3 data_02042258;
extern int func_02023eb4(int n);

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov255_020cedd0(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Vec3 dir;
    int hits[4];
    Segment seg;
    Cmd4 note;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    state[0x14] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x65) == 0 && state[0x14] >= 0x2800) {
        func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 6, (void *)(*(int *)(*state + 0x3b0) + 0x14));
        *((u8 *)state + 0x65) = 1;
    }
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    n = func_ov107_020c9f48(*(int *)(*state + 0x3a4), &dir);
    func_0202f384(&dir, state + 7, &dir);
    func_01ffa724(n, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    state[0x10] = state[0x11] > 0xccc ? 0 : *(int *)(node[0] + 0x2c) * 30 / 2;
    if (state[0x11] > 0xa22 && state[0x11] < 0x1400) {
        seg = *(Segment *)(*(int *)(*state + 0x3a0) + 0x78);
        seg.nRadius = 0xc00;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x63) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            func_0202f384(&push, state + 7, &data_02042258);
            func_01ffa724(0x400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 2, &push, 0) == 0) {
                continue;
            }
            msg = data_ov255_020d2b52;
            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x63) |= 1 << *(u16 *)(hits[i] + 2);
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 9, (void *)(obj + 0x74));
        }
    }
    if (*((u8 *)state + 0x62) == 0 && state[0x11] >= 0xb33) {
        Cmd4 *p = &note;

        p->hi = data_ov255_020d2b20[5].hi;
        p->lo = data_ov255_020d2b20[5].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
        *((u8 *)state + 0x62) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    state[0x15] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
