/* Rolling-charge tick: the nearest target (020cab14) becomes the +8 mark (none: pose 0xa). While
 * the actor is blocked (+0x17a bit 1) the +0x3c velocity is reflected off the actor's +0x114 wall
 * normal at half its speed. The step 1/(+0x53 + 1) (64-bit divide) steers the velocity towards the
 * old mark on x and z by 64 steps and caps its speed at 0.75 steps; y clears and the result is
 * kept in +0x18. The four +0x4c hit cooldowns count down. The +0x3a4 part's segment (+0x78), moved
 * by the step and with its radius x 3, sweeps the actor list: an entity whose +0x1b4 slot is
 * cooled down is pushed 0.375 away horizontally from the part (kind 2); on acceptance the message
 * data_ov278_020d638e carries its +0x74 point raised by 0.5 to the +0x24 hook, its slot cools for
 * 8 ticks, reaction 0 mode 0x4e fires there and the velocity bounces off it at full speed. The +0x28
 * timer accumulates the frame rate; past 5.0 the +4 part's +0xa8 flag clears and the tick hands
 * over to func_ov278_020d10c8. */
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

struct Bits17a { unsigned char b0 : 1, b1 : 1; };

extern int func_ov107_020cab14(int obj, int kind);
extern void func_0203c634(int *node, int slot, void *cb);
extern int VEC_Mag(const void *v);
extern void func_01ffa724(int scale, const void *v, void *out);
extern int VEC_DotProduct(const void *a, const void *b);
extern void VEC_Subtract(const void *a, const void *b, void *out);
extern int func_01ff8d18(const void *v, void *out);
extern long long func_020201b8(long long a, long long b);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern const Cmd14 data_ov278_020d638e;
extern void func_ov278_020d10c8(int *node);

void func_ov278_020d0bac(int *node)
{
    int *state = (int *)node[1];
    int actor;
    int owner = *state;
    int prev = state[2];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Segment seg;
    Vec3 neg;
    Vec3 refl;
    Vec3 push;
    Vec3 raw;
    Cmd14 msg;
    Vec3 neg2;
    Vec3 refl2;
    Vec3 normal;
    long long q;
    int accel;
    int cap;
    int speed;
    int len;
    u8 *cb;
    int k;
    int n;
    int i;

    state[2] = func_ov107_020cab14(owner, 0);
    if (state[2] == 0) {
        *(u8 *)(*state + 0x1c7) = 0xa;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    actor = *state;
    if (((struct Bits17a *)(actor + 0x17a))->b1) {
        len = VEC_Mag(state + 0xf);
        func_01ffa724(-0x1000, state + 0xf, &neg);
        func_01ffa724(VEC_DotProduct(&neg, (void *)(actor + 0x114)) << 1, (void *)(actor + 0x114), &refl);
        VEC_Subtract(&refl, &neg, &refl);
        func_01ff8d18(&refl, state + 0xf);
        func_01ffa724(len / 2, state + 0xf, state + 0xf);
    }
    q = func_020201b8(0x100000000LL, (long long)(*((signed char *)state + 0x53) + 1));
    state[0xa] += *(int *)(node[0] + 0x2c);
    accel = (int)(((q << 6) + 0x80000000LL) >> 32);
    if (*(int *)(owner + 0x74) > *(int *)(prev + 0x74)) {
        state[0xf] -= accel;
    }
    if (*(int *)(owner + 0x74) < *(int *)(prev + 0x74)) {
        state[0xf] += accel;
    }
    if (*(int *)(owner + 0x7c) > *(int *)(prev + 0x7c)) {
        state[0x11] -= accel;
    }
    if (*(int *)(owner + 0x7c) < *(int *)(prev + 0x7c)) {
        state[0x11] += accel;
    }
    cap = (int)((q * 0xc00 + 0x80000000LL) >> 32);
    speed = VEC_Mag(state + 0xf);
    if (speed > cap) {
        speed = cap;
    }
    state[0x10] = 0;
    func_01ff8d18(state + 0xf, state + 0xf);
    func_01ffa724(speed, state + 0xf, state + 0xf);
    *(Vec3 *)(state + 6) = *(Vec3 *)(state + 0xf);
    cb = (u8 *)state;
    for (k = 0; k < 4; k++) {
        if (cb[k + 0x4c] != 0) {
            cb[k + 0x4c]--;
        }
    }
    seg = *(Segment *)(**(int **)(*state + 0x3a4) + 0x78);
    VEC_Add(&seg.p0, state + 6, &seg.p0);
    seg.nRadius *= 3;
    n = func_ov107_020c8f44(*state, &seg, hits);
    for (i = 0; i < n; i++) {
        if (((u8 *)state)[0x4c + *(u8 *)(hits[i] + 0x1b4)] != 0) {
            continue;
        }
        VEC_Subtract((void *)(hits[i] + 0x74), (void *)(**(int **)(*state + 0x3a4) + 4), &push);
        push.y = 0;
        func_01ff8d18(&push, &push);
        func_01ffa724(0x600, &push, &push);
        if (func_ov107_020ca918(hits[i], *state, *state, 2, &push, 0) == 0) {
            continue;
        }
        msg = data_ov278_020d638e;
        raw = *(Vec3 *)(hits[i] + 0x74);
        raw.y += 0x800;
        PACK(msg, scratchX, *(Fx32 *)&raw.x, 5);
        PACK(msg, scratchY, *(Fx32 *)&raw.y, 8);
        PACK(msg, scratchZ, *(Fx32 *)&raw.z, 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        ((u8 *)state)[0x4c + *(u8 *)(hits[i] + 0x1b4)] = 8;
        func_ov107_020c5af8(*state, 0, 0x4e, &raw);
        VEC_Subtract((void *)(**(int **)(*state + 0x3a4) + 4), (void *)(hits[i] + 0x74), &normal);
        normal.y = 0;
        func_01ff8d18(&normal, &normal);
        len = VEC_Mag(state + 0xf);
        func_01ffa724(-0x1000, state + 0xf, &neg2);
        func_01ffa724(VEC_DotProduct(&neg2, &normal) << 1, &normal, &refl2);
        VEC_Subtract(&refl2, &neg2, &refl2);
        func_01ff8d18(&refl2, state + 0xf);
        func_01ffa724(0x1000, state + 0xf, state + 0xf);
    }
    if (state[0xa] < 0x5000) {
        return;
    }
    *(u8 *)(state[1] + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov278_020d10c8);
}
