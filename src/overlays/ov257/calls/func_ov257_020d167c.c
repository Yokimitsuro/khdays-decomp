/* Finishing strike tick of an ov257 state, run after func_ov257_020d101c: the +0x54 timer
 * accumulates the frame rate and the +0x40 rate is the frame rate x 3; without a nearest target
 * (020cab14, kept in +0x60) sub-state 2 is requested, otherwise the +0x10 step heads for it
 * (func_ov257_020ccf98). The +0x44 timer accumulates the frame rate; below 1.0 a sphere of radius
 * 4.0 around the owner's +0x3d4 part point (+0x14), moved by the step, is swept over the actor list
 * and every entity in it is pushed 0.25 away from the centre (kind 6); on acceptance the 14-byte
 * message data_ov257_020d32b0 carries its +0x74 point to the owner's +0x24 hook and reaction +0x408
 * mode 0x20 fires there. Between 0.67 and 1.17 the segment of the +0x3c4 part (+0x78), moved by the
 * step and with its radius x 2.5, is swept the same way, skipping entities whose +2 id bit is set
 * in the +0x75 mask and setting it on acceptance (message data_ov257_020d332e). Once the +0xc idle
 * byte clears, the +0x4c delay is drawn from the owner's [+0x224, +0x228] range, +0x50 clears and
 * sub-state 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { Vec3 center; int nRadius; } Sphere;

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
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_02023eb4(int n);
extern const Cmd14 data_ov257_020d32b0;
extern const Cmd14 data_ov257_020d332e;

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;
    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov257_020d167c(int *node)
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
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
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
    if (n > 0 && n < 0xfff) {
        int hits[4];
        Sphere sphere;

        sphere.center = *(Vec3 *)(*(int *)(*state + 0x3d4) + 0x14);
        VEC_Add(&sphere.center, state + 4, &sphere.center);
        sphere.nRadius = 0x4000;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            VEC_Subtract((void *)(obj + 0x74), &sphere.center, &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 6, &push, 0) == 0) {
                continue;
            }
            msg = data_ov257_020d32b0;
            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x408), 0x20, (void *)(obj + 0x74));
        }
    }
    if (state[0x11] > 0xaaa && state[0x11] < 0x12aa) {
        int hits[4];
        Segment seg;

        seg = *(Segment *)(*(int *)(*state + 0x3c4) + 0x78);
        VEC_Add(&seg.p0, state + 4, &seg.p0);
        seg.nRadius = FX_Mul(seg.nRadius, 0x2800);
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
            msg = data_ov257_020d332e;
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
    state[0x13] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    state[0x14] = 0;
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
