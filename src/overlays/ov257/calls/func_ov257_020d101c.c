/* Follow-up strike tick of an ov257 state, run after func_ov257_020d0a00: the +0x54 timer
 * accumulates the frame rate; with the +0x76 stage byte at 0, reaching 2.13 fires reaction +0x408
 * mode 0x1e at the +4 point, and at stage 1 reaching 3.2 fires mode 0x1f (the stage stays 1). The
 * +0x40 rate is the frame rate x 1.5; without a nearest target (020cab14, kept in +0x60) sub-state 2
 * is requested, otherwise the +0x10 step heads for it (func_ov257_020ccf98). The +0x44 timer
 * accumulates the frame rate; between 0.83 and 1.33 the segment of the owner's +0x3c0 part (+0x78),
 * moved by the step and with a doubled radius, is swept over the actor list, and between 1.33 and
 * 1.83 the +0x3c4 part's: every entity whose +2 id bit is clear in that sweep's mask (+0x74 /
 * +0x75) is pushed 0.25 away from the segment start (kind 6); on acceptance the sweep's 14-byte
 * message (data_ov257_020d3278 / data_ov257_020d3286) carries its +0x74 point to the owner's +0x24
 * hook, its bit is set and reaction +0x408 mode 0x20 fires there. Once the +0xc idle byte clears,
 * animation 0x21 plays, the +0x3d0 part plays motion 0x1e, +0x73, +0x75 and +0x44 clear and the
 * tick hands over to func_ov257_020d167c. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
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
extern int func_ov257_020ccf98(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov257_020d3278;
extern const Cmd14 data_ov257_020d3286;
extern void func_ov257_020d167c(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov257_020d101c(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 scratch2Z;
    Fx32 scratch2Y;
    Fx32 scratch2X;
    int n;
    int i;
    int sweepObj;
    int j;
    int count;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x76) == 0) {
        if (state[0x15] >= 0x2222) {
            func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x1e, (void *)state[1]);
            *((u8 *)state + 0x76) = 1;
        }
    } else if (*((u8 *)state + 0x76) == 1) {
        if (state[0x15] >= 0x3333) {
            func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x1f, (void *)state[1]);
            *((u8 *)state + 0x76) = 1;
        }
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 20;
    state[0x18] = func_ov107_020cab14(*state, 0);
    if (state[0x18] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    n = state[0x11];
    if (n > 0xd55 && n < 0x1555) {
        int hits[4];
        Segment seg;

        seg = *(Segment *)(*(int *)(*state + 0x3c0) + 0x78);
        VEC_Add(&seg.p0, state + 4, &seg.p0);
        seg.nRadius = FX_Mul(seg.nRadius, 0x2000);
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x74) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(obj + 0x74), &seg.p0, &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 6, &push, 0) == 0) {
                continue;
            }
            msg = data_ov257_020d3278;
            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x74) |= 1 << *(u16 *)(hits[i] + 2);
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x408), 0x20, (void *)(obj + 0x74));
        }
    }
    if (state[0x11] > 0x1555 && state[0x11] < 0x1d55) {
        int hits[4];
        Segment seg;

        seg = *(Segment *)(*(int *)(*state + 0x3c4) + 0x78);
        VEC_Add(&seg.p0, state + 4, &seg.p0);
        seg.nRadius = FX_Mul(seg.nRadius, 0x2000);
        count = func_ov107_020c8f44(*state, &seg, hits);
        for (j = 0; j < count; j++) {
            Vec3 push;
            Cmd14 msg;

            sweepObj = hits[j];
            if ((*((u8 *)state + 0x75) & (1 << *(u16 *)(sweepObj + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(sweepObj + 0x74), &seg.p0, &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x400, &push, &push);
            if (func_ov107_020ca918(hits[j], *state, *state, 6, &push, 0) == 0) {
                continue;
            }
            msg = data_ov257_020d3286;
            PACK(msg, scratch2X, *(Fx32 *)(sweepObj + 0x74), 5);
            PACK(msg, scratch2Y, *(Fx32 *)(sweepObj + 0x78), 8);
            PACK(msg, scratch2Z, *(Fx32 *)(sweepObj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x75) |= 1 << *(u16 *)(hits[j] + 2);
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x408), 0x20, (void *)(sweepObj + 0x74));
        }
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x21, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x1e, 0);
    *((u8 *)state + 0x73) = 0;
    *((u8 *)state + 0x75) = 0;
    state[0x11] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020d167c);
}
