/* Bounce-shot flight tick: the shot faces its +0x54 velocity (+0x34), the +0x2c timer accumulates
 * the frame rate and gravity pulls the vertical velocity down by 1/16 per frame step, capped at
 * -1.0; the step (+0x14) is the velocity, mirrored horizontally when blocked (+0x17a bit 1). A 1.2
 * sphere one step ahead of the +8 point sweeps the actor list: every entity whose +0x1b4 slot bit is
 * clear in +0x4e is pushed 1.0 away horizontally (kind 1); on acceptance effect 1 and reaction 0x154
 * mode 9 fire and the slot bit is set. The same sphere strikes the stage objects of the owner's +4
 * +0x7c grid (func_ov208_020d0888): each struck object (func_ov002_02076dac, power 0xff) gets the
 * message data_ov208_020d47dc at the sphere surface. The shot ends on a solid wall (01fff920, the
 * bounce point mirrored off its plane), when falling onto open ground, or past 3.0: animation 0xe,
 * effect 5 and reaction 0x154 mode 0xc at the end point unless the owner is flagged (+0x1c4 & 0xa),
 * and the tick hands over to func_ov208_020d3244. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

typedef struct { Vec3 push; u8 nPower; u8 nType; int nSe; int nKind; int nMask; } StrikeInfo;
struct Bits17a { unsigned char b0 : 1, b1 : 1; };

extern const Vec3 data_02042258;
extern int func_020050b4(int y, int x);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov208_020d0888(int grid, Sphere *sphere, int *list);
extern int func_ov002_02076dac(int target, StrikeInfo *info);
extern int func_01fff920(int grid, void *pos, void *step);
extern void func_01ffd144(int plane, Vec3 *in, Vec3 *out);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov208_020d47dc;
extern void func_ov208_020d3244(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov208_020d2c6c(int *node)
{
    int *state = (int *)node[1];
    int falling;
    int done;
    int grid;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Sphere sphere;
    int hits[4];
    Vec3 push;
    Vec3 pt;
    int list[4];
    int hit;
    int n;
    int i;

    falling = state[0x16] < 0 && *(int *)(*state + 0x10c) == 0 ? 1 : 0;
    state[0x18] = *(int *)(node[0] + 0x2c) * 30 / 20;
    done = 0;
    n = func_020050b4(state[0x15], state[0x17]);
    state[0xd] = n;
    state[0xb] += *(int *)(node[0] + 0x2c);
    grid = *(int *)(*state + 4);
    state[0x16] -= FX_Mul(*(int *)(node[0] + 0x2c) * 30, 0x100);
    if (state[0x16] < -0x1000) {
        state[0x16] = -0x1000;
    }
    *(Vec3 *)(state + 5) = *(Vec3 *)(state + 0x15);
    if (((struct Bits17a *)(*state + 0x17a))->b1) {
        int x = state[0x15];
        int z = state[0x17];
        int y = state[0x16];

        state[5] = -x;
        state[6] = y;
        state[7] = -z;
    }
    VEC_Add((void *)state[2], state + 5, &sphere.center);
    sphere.nRadius = 0x1371;
    n = func_ov107_020c8eb8(*state, &sphere, hits);
    for (i = 0; i < n; i++) {
        if (((*((u8 *)state + 0x4e) >> *(u8 *)(hits[i] + 0x1b4)) & 1) != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
        push.y = 0;
        if (func_01ff8d18(&push, &push) == 0) {
            push = data_02042258;
        }
        func_01ffa724(0x1000, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *state, 1, &push, 0) == 0) {
            continue;
        }
        VEC_Add((void *)(hits[i] + 0x74), &sphere.center, &pt);
        func_ov107_020c0b90(*state, 1, pt, 0);
        func_ov107_020c5af8(*state, 0x154, 9, &pt);
        *((u8 *)state + 0x4e) |= 1 << *(u8 *)(hits[i] + 0x1b4);
    }
    n = func_ov208_020d0888(*(int *)(grid + 0x7c), &sphere, list);
    for (i = 0; i < n; i++) {
        StrikeInfo info = {0};
        Vec3 dir;
        Vec3 pt2;
        Cmd14 msg;

        VEC_Subtract((void *)(list[i] + 0x2c), &sphere.center, &dir);
        func_01ff8d18(&dir, &dir);
        func_01ffa724(0x800, &dir, &info.push);
        info.nPower = 0xff;
        info.nType = 2;
        info.nSe = *(u16 *)(*state + 0x296);
        info.nKind = 4;
        info.nMask = 1 << *(u8 *)(*state + 0x294);
        if (*(int *)(list[i] + 0x28) == 0) {
            continue;
        }
        if (func_ov002_02076dac(*(int *)(*(int *)(list[i] + 0x28) + 0x158), &info) == 0) {
            continue;
        }
        msg = data_ov208_020d47dc;
        func_01ffa724(sphere.nRadius, &dir, &pt2);
        VEC_Add(&sphere.center, &pt2, &pt2);
        PACK(msg, scratchX, *(Fx32 *)&pt2.x, 5);
        PACK(msg, scratchY, *(Fx32 *)&pt2.y, 8);
        PACK(msg, scratchZ, *(Fx32 *)&pt2.z, 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
    }
    hit = func_01fff920(*(int *)(grid + 0x7c), (void *)state[2], state + 5);
    if (hit != 0 && *(int *)(hit + 8) == 0) {
        Vec3 refl;

        refl = *(Vec3 *)(state + 5);
        func_01ffd144(*(int *)(hit + 0xc), &refl, &refl);
        VEC_Add(&refl, (void *)state[2], state + 8);
        done = 1;
    } else if (falling != 0) {
        *(Vec3 *)(state + 8) = *(Vec3 *)state[2];
        done = 1;
    }
    if (state[0xb] >= 0x3000) {
        *(Vec3 *)(state + 8) = *(Vec3 *)state[2];
        done = 1;
    }
    if (done == 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xe, 0);
    state[0xb] = 0;
    if ((*(u8 *)(*state + 0x1c4) & 0xa) == 0) {
        func_ov107_020c0b90(*state, 5, *(Vec3 *)(state + 8), 0);
        func_ov107_020c5af8(*state, 0x154, 0xc, state + 8);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov208_020d3244);
}
