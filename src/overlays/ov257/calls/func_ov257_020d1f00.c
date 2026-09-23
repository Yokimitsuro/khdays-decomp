/* Landing-slam tick of an ov257 state, run after func_ov257_020d1e24: the +0x10 step heads for the
 * +0x60 target (func_ov257_020ccf98) plus the +0x64 velocity. On the ground (+0x17a bit 0) the +0x40
 * rate and the +0x64 velocity clear; in the air the rate is the frame rate x 6 and the velocity
 * height falls by 3/64 per tick. The nearest target (020cab14) becomes +0x60 and the +0x2c
 * orientation faces it. The +0x44 timer accumulates the frame rate; between 0.5 and 1.0 the segment
 * of each of the owner's four parts (+0x3c0..+0x3cc, +0x78), moved by the step and with a doubled
 * radius, is swept over the actor list: every entity whose +2 id bit is clear in the +0x73 mask is
 * pushed 1.0 away from the segment start (kind 7); on acceptance the 14-byte message
 * data_ov257_020d3294 carries its +0x74 point to the owner's +0x24 hook, its bit is set and reaction
 * +0x408 mode 9 fires there. On touching down (+0x72 still clear) the landing offset
 * data_ov257_020d326c, turned by the owner's +0xa0 orientation and placed at the +0x3d8 part point
 * (+0x14), goes to the hook in message data_ov257_020d333c, bit 6 of the owner's +0x61 byte clears,
 * reaction mode 0x1c fires at the +4 point and +0x72 is set. Once the +0xc idle byte clears on the
 * ground, the +0x4c delay is drawn from the owner's [+0x224, +0x228] range and sub-state 2 is
 * requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[4]; } Quat;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { u16 lo : 8; u16 hi : 8; } Hw60;
struct Bits17a { unsigned char b0 : 1; };

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern int func_ov257_020ccf98(int *state, int target, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern int func_ov107_020cab14(int obj, int kind);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_020050b4(int y, int x);
extern void func_0202f188(Quat *out, const Vec3 *axis, int angle);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_02023eb4(int n);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Vec3 data_02042264;
extern const Cmd14 data_ov257_020d3294;
extern const Vec3 data_ov257_020d326c;
extern const Cmd14 data_ov257_020d333c;

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

void func_ov257_020d1f00(int *node)
{
    int obj;
    int *pHits;
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    int target;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    Fx32 scratch2Z;
    Fx32 scratch2Y;
    Fx32 scratch2X;
    int part;
    int n;
    int i;

    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    VEC_Add(state + 4, state + 0x19, state + 4);
    if (((struct Bits17a *)(*state + 0x17a))->b0) {
        state[0x10] = 0;
        state[0x1a] = 0;
        state[0x19] = 0;
        state[0x1b] = 0;
    } else {
        state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 5;
        state[0x1a] -= 0xc0;
    }
    target = state[0x18] = func_ov107_020cab14(*state, 0);
    if (target != 0) {
        Vec3 d;

        VEC_Subtract((void *)(target + 0x74), (void *)(*state + 0x74), &d);
        func_0202f188((Quat *)(state + 0xb), &data_02042264, func_020050b4(d.x, d.z));
    }
    state[0x11] += *(int *)(node[0] + 0x2c);
    n = state[0x11];
    if (n > 0x800 && n < 0xfff) {
        for (part = 0; part < 4; part++) {
            int hits[4];
            Segment seg;

            seg = *(Segment *)(((int *)*state)[0xf0 + part] + 0x78);
            VEC_Add(&seg.p0, state + 4, &seg.p0);
            seg.nRadius = FX_Mul(seg.nRadius, 0x2000);
            n = func_ov107_020c8f44(*state, &seg, hits);
            i = 0;
            if (i < n) {
                pHits = hits;
                do {
                    Vec3 push;
                    Cmd14 msg;

                    obj = pHits[i];
                    if ((*((u8 *)state + 0x73) & (1 << *(u16 *)(obj + 2))) == 0) {
                        VEC_Subtract((void *)(obj + 0x74), &seg.p0, &push);
                        func_01ff8d18(&push, &push);
                        func_01ffa724(0x1000, &push, &push);
                        if (func_ov107_020ca918(pHits[i], *state, *state, 7, &push, 0) != 0) {
                            msg = data_ov257_020d3294;
                            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
                            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
                            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
                            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
                            }
                            *((u8 *)state + 0x73) |= 1 << *(u16 *)(pHits[i] + 2);
                            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x408), 9, (void *)(obj + 0x74));
                        }
                    }
                    i++;
                } while (i < n);
            }
        }
    }
    if (*((u8 *)state + 0x72) == 0 && ((struct Bits17a *)(*state + 0x17a))->b0) {
        Vec3 pos;
        Cmd14 msg;

        pos = data_ov257_020d326c;
        msg = data_ov257_020d333c;
        func_0202f384(&pos, (void *)(*state + 0xa0), &pos);
        VEC_Add((void *)(*(int *)(*state + 0x3d8) + 0x14), &pos, &pos);
        PACK(msg, scratch2X, *(Fx32 *)&pos.x, 5);
        PACK(msg, scratch2Y, *(Fx32 *)&pos.y, 8);
        PACK(msg, scratch2Z, *(Fx32 *)&pos.z, 11);
        if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
        }
        ((Hw60 *)(*state + 0x60))->hi &= ~0x40;
        func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x1c, (void *)state[1]);
        *((u8 *)state + 0x72) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    if (((struct Bits17a *)(*state + 0x17a))->b0 == 0) {
        return;
    }
    state[0x13] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
