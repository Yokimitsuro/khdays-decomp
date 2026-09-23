/* Stalk tick: the +0x24 rate is the frame rate x 1.5; the +0x18 step timer loops every 2.0,
 * clearing the +0x74 step stage. At 0.4 (stage 0 -> 1) and 1.4 (stage 1 -> 2) a foot stamps while
 * its +0x3d0 / +0x3d2 slot is alive: the actor's +0x24 hook receives note 5 / 8 of
 * data_ov278_020d63e4, reaction 0x166 mode 0xb / 0xc fires at the foot (+0x3c0 / +0x3c4 part, +4)
 * and a sphere there, twice the foot's +0x90 radius, sweeps the actor list: every entity in it is
 * pushed 0.375 away horizontally (kind 1, on behalf of the +0x384 rider); on acceptance the message
 * data_ov278_020d6432 / data_ov278_020d6440 carries its +0x74 point raised by 0.5 and its +0x1b4 byte
 * to the rider's +0x24 hook and reaction 0x166 mode 0xd fires there. The nearest target (020cab14)
 * becomes +4 (none: pose 9). The heading (+0x2c) circles it: the gap to it (centres less both +0x80
 * radii) maps to t in [-1, 1] over 10.0, and the actor heads away (t > 0) or towards it, 45 degrees
 * off, jittered by up to +-(1 - |t|) x 45 degrees. The +0x3c8 part's motion step, turned by the
 * +0xa0 orientation, becomes the +8 velocity. Once the +0x14 countdown runs out past 1.67 on the
 * step timer, the +0x388 part's +0xa8 flag clears and the tick hands over to func_ov278_020d4ce8. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 center; int nRadius; } Sphere;
typedef struct { u16 lo; u16 hi; } Cmd4;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

typedef struct { int w[4]; } Quat;

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020c8eb8(int owner, Sphere *sphere, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_ov107_020cab14(int obj, int kind);
extern int FX_Inv(int a, int b);
extern int func_02023eb4(int n);
extern int func_020050b4(int y, int x);
extern int func_ov107_020c9f48(int part, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern const Cmd4 data_ov278_020d63e4[];
extern const Cmd14 data_ov278_020d6432;
extern const Cmd14 data_ov278_020d6440;
extern void func_ov278_020d4ce8(int *node);

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

void func_ov278_020d4570(int *node)
{
    Cmd4 note1;
    Cmd4 note2;
    int *state = (int *)node[1];
    Fx32 scratch1Z;
    Fx32 scratch1Y;
    Fx32 scratch1X;
    Fx32 scratch2Z;
    Fx32 scratch2Y;
    Fx32 scratch2X;
    Vec3 d;
    Vec3 step;
    int hits[4];
    Sphere sphere;
    int t;
    int a;
    int speed;
    int target;
    int owner;
    int n;
    int i;

    state[9] = *(int *)(node[0] + 0x2c) * 30 / 20;
    state[6] += *(int *)(node[0] + 0x2c);
    if (state[6] >= 0x2000) {
        state[6] -= 0x2000;
        *((u8 *)state + 0x74) = 0;
    }
    if (*((u8 *)state + 0x74) == 0) {
        if (state[6] > 0x666) {
            *((u8 *)state + 0x74) = 1;
            if (*(short *)(*state + 0x3d0) > 0) {
                Vec3 push;
                Vec3 raw;
                Cmd14 msg;

                {
                    Cmd4 *p = &note1;

                    p->hi = data_ov278_020d63e4[5].hi;
                    p->lo = data_ov278_020d63e4[5].lo;
                    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
                    }
                }
                func_ov107_020c5af8(*state, 0x166, 0xb, (void *)(**(int **)(*state + 0x3c0) + 4));
                sphere.center = *(Vec3 *)(**(int **)(*state + 0x3c0) + 4);
                sphere.nRadius = *(int *)(**(int **)(*state + 0x3c0) + 0x90) << 1;
                n = func_ov107_020c8eb8(*state, &sphere, hits);
                for (i = 0; i < n; i++) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
                    push.y = 0;
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x600, &push, &push);
                    if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 1, &push, 0) == 0) {
                        continue;
                    }
                    msg = data_ov278_020d6432;
                    raw = *(Vec3 *)(hits[i] + 0x74);
                    raw.y += 0x800;
                    PACK(msg, scratch1X, *(Fx32 *)&raw.x, 5);
                    PACK(msg, scratch1Y, *(Fx32 *)&raw.y, 8);
                    PACK(msg, scratch1Z, *(Fx32 *)&raw.z, 11);
                    msg.flag = *(u8 *)(hits[i] + 0x1b4);
                    if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24))(*(int *)(*state + 0x384), &msg, 0xe);
                    }
                    func_ov107_020c5af8(*state, 0x166, 0xd, &raw);
                }
            }
        }
    } else if (*((u8 *)state + 0x74) == 1) {
        if (state[6] > 0x1666) {
            *((u8 *)state + 0x74) = 2;
            if (*(short *)(*state + 0x3d2) > 0) {
                Vec3 push;
                Vec3 raw;
                Cmd14 msg;

                {
                    Cmd4 *p = &note2;

                    p->hi = data_ov278_020d63e4[8].hi;
                    p->lo = data_ov278_020d63e4[8].lo;
                    if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
                        (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
                    }
                }
                func_ov107_020c5af8(*state, 0x166, 0xc, (void *)(**(int **)(*state + 0x3c4) + 4));
                sphere.center = *(Vec3 *)(**(int **)(*state + 0x3c4) + 4);
                sphere.nRadius = *(int *)(**(int **)(*state + 0x3c4) + 0x90) << 1;
                n = func_ov107_020c8eb8(*state, &sphere, hits);
                for (i = 0; i < n; i++) {
                    VEC_Subtract((void *)(hits[i] + 0x74), &sphere.center, &push);
                    push.y = 0;
                    func_01ff8d18(&push, &push);
                    func_01ffa724(0x600, &push, &push);
                    if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 1, &push, 0) == 0) {
                        continue;
                    }
                    msg = data_ov278_020d6440;
                    raw = *(Vec3 *)(hits[i] + 0x74);
                    raw.y += 0x800;
                    PACK(msg, scratch2X, *(Fx32 *)&raw.x, 5);
                    PACK(msg, scratch2Y, *(Fx32 *)&raw.y, 8);
                    PACK(msg, scratch2Z, *(Fx32 *)&raw.z, 11);
                    msg.flag = *(u8 *)(hits[i] + 0x1b4);
                    if (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24) != 0) {
                        (*(void (**)(int, Cmd14 *, int))(*(int *)(*state + 0x384) + 0x24))(*(int *)(*state + 0x384), &msg, 0xe);
                    }
                    func_ov107_020c5af8(*state, 0x166, 0xd, &raw);
                }
            }
        }
    }
    state[1] = func_ov107_020cab14(*state, 0);
    if (state[1] == 0) {
        *(u8 *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    VEC_Subtract((void *)(state[1] + 0x190), (void *)state[7], &d);
    target = state[1];
    owner = *state;
    t = FX_Inv(func_01ff8d18(&d, &d) - *(int *)(target + 0x80) - *(int *)(owner + 0x80), 0x5000) * 2 - 0x1000;
    if (t < -0x1000) {
        t = -0x1000;
    }
    if (t > 0x1000) {
        t = 0x1000;
    }
    a = 0x1000 - (t < 0 ? -t : t);
    a = FX_Mul(RandRange(0, a * 2) - a, 0x3244);
    if (t > 0) {
        state[0xb] = func_020050b4(-d.x, -d.z) + 0x3244 - a;
    } else {
        state[0xb] = a + (func_020050b4(d.x, d.z) + 0x3244);
    }
    speed = func_ov107_020c9f48(*(int *)(*state + 0x3c8), &step);
    func_0202f384((Vec3 *)(state + 2), (void *)(*state + 0xa0), &step);
    func_01ffa724(speed, (Vec3 *)(state + 2), state + 2);
    state[5] -= *(int *)(node[0] + 0x2c);
    if (state[5] > 0) {
        return;
    }
    if (state[6] <= 0x1aaa) {
        return;
    }
    *(u8 *)(*(int *)(*state + 0x388) + 0xa8) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov278_020d4ce8);
}
