/* Double-claw tick: until the +0x66 flag is set the +0x60 timer accumulates the frame rate and at
 * 0.6 the flag is set and the actor spawns effect 8. The +0x2c timer accumulates the frame rate;
 * between 1.4 and 1.67 a 0.6 sphere at each of the owner's +0x3cc and +0x3c8 part points (+0x14)
 * sweeps the actor list: every entity in it is pushed 1.0 away horizontally (the +z axis when
 * directly above, kind 0); on acceptance the message data_ov282_020d472c / data_ov282_020d4764,
 * flags 3, carries the part point to the +0x24 hook and reaction 0 mode 0x4e fires there. Once the
 * +0xc idle byte clears, the +0x6c delay is drawn from the owner's [+0x224, +0x228] range and
 * sub-state 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flagLo : 4; u8 flagHi : 4; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern const Vec3 data_02041dc8;
extern const Vec3 data_02042258;
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov282_020d472c;
extern const Cmd14 data_ov282_020d4764;

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov282_020d3378(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratch1Z;
    Fx32 scratch1Y;
    Fx32 scratch1X;
    Fx32 scratch2Z;
    Fx32 scratch2Y;
    Fx32 scratch2X;
    int hits[4];
    Sphere sphere;
    Vec3 push1;
    Cmd14 msg1;
    Vec3 push2;
    Cmd14 msg2;
    int n;
    int i;

    if (*((u8 *)state + 0x66) == 0) {
        state[0x18] += *(int *)(node[0] + 0x2c);
        if (state[0x18] >= 0x999) {
            *((u8 *)state + 0x66) = 1;
            func_ov107_020c0b90(*state, 8, data_02041dc8, 0);
        }
    }
    state[0xb] += *(int *)(node[0] + 0x2c);
    if (state[0xb] >= 0x1666 && state[0xb] <= 0x1aaa) {
        sphere.center = *(Vec3 *)(*(int *)(*state + 0x3cc) + 0x14);
        sphere.nRadius = 0x999;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Vec3 *at;

            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push1);
            push1.y = 0;
            if (func_01ff8d18(&push1, &push1) == 0) {
                push1 = data_02042258;
            }
            func_01ffa724(0x1000, &push1, &push1);
            if (func_ov107_020ca918(hits[i], *state, *state, 0, &push1, 0) == 0) {
                continue;
            }
            msg1 = data_ov282_020d472c;
            at = (Vec3 *)(*(int *)(*state + 0x3cc) + 0x14);
            PACK(msg1, scratch1X, *(Fx32 *)&at->x, 5);
            PACK(msg1, scratch1Y, *(Fx32 *)&at->y, 8);
            PACK(msg1, scratch1Z, *(Fx32 *)&at->z, 11);
            msg1.flagLo = 3;
            msg1.flagHi = 0;
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg1, 0xe);
            }
            func_ov107_020c5af8(*state, 0, 0x4e, (void *)(*(int *)(*state + 0x3cc) + 0x14));
        }
        sphere.center = *(Vec3 *)(*(int *)(*state + 0x3c8) + 0x14);
        sphere.nRadius = 0x999;
        n = func_ov107_020c8eb8(*state, &sphere, hits);
        for (i = 0; i < n; i++) {
            Vec3 *at;

            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push2);
            push2.y = 0;
            if (func_01ff8d18(&push2, &push2) == 0) {
                push2 = data_02042258;
            }
            func_01ffa724(0x1000, &push2, &push2);
            if (func_ov107_020ca918(hits[i], *state, *state, 0, &push2, 0) == 0) {
                continue;
            }
            msg2 = data_ov282_020d4764;
            at = (Vec3 *)(*(int *)(*state + 0x3c8) + 0x14);
            PACK(msg2, scratch2X, *(Fx32 *)&at->x, 5);
            PACK(msg2, scratch2Y, *(Fx32 *)&at->y, 8);
            PACK(msg2, scratch2Z, *(Fx32 *)&at->z, 11);
            msg2.flagLo = 3;
            msg2.flagHi = 0;
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg2, 0xe);
            }
            func_ov107_020c5af8(*state, 0, 0x4e, (void *)(*(int *)(*state + 0x3c8) + 0x14));
        }
    }
    if (*(u8 *)state[3] != 0) {
        return;
    }
    state[0x1b] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
