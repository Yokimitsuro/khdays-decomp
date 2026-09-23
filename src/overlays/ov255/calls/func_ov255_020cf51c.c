/* Slam tick of an ov255 state: at 2.07 on the +0x50 timer reaction +0x3f8 mode 7 fires once at
 * the owner's +0x3b0 body point (+0x65). The +0x40 rate clears and the +0x10 step heads for the
 * +0x5c target (func_ov255_020ccdac). The +0x44 timer accumulates the frame rate; between 0.4 and
 * 1.0 a box (half extents 0.375, 0.375, 1.5) oriented by the body's pose and centred 1.5 along its
 * third axis from the body point is swept over the actor list: every entity whose +2 id bit is
 * clear in the +0x63 mask is pushed away from the body point (kind 3); on acceptance the 14-byte
 * message of data_ov255_020d2b7c carries its +0x74 point to the owner's +0x24 hook, its bit is set
 * and reaction +0x3f8 mode 9 fires there. From 0.7 on the hook receives note 2 of
 * data_ov255_020d2b20 once (+0x62). Once the +0xc idle byte clears, the +0x54 cooldown is
 * re-rolled in [+0x224, +0x228] and sub-state 2 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { int w[4]; } Quat;
typedef struct { Vec3 c; Vec3 ax; Vec3 ay; Vec3 az; Vec3 ext; } Box;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8df0(int owner, Box *box, int *hits);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern void VEC_Add(const void *a, const void *b, void *out);
extern const Vec3 data_02042270;
extern const Vec3 data_02042264;
extern const Vec3 data_02042258;
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov255_020d2b7c;
extern const Cmd4 data_ov255_020d2b20[];
extern int func_02023eb4(int n);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);

static inline int RandRange(int lo, int hi)
{
    int d = hi - lo;

    if (d < 0) {
        d = -d;
    }
    return lo + func_02023eb4(d + 1);
}

void func_ov255_020cf51c(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Vec3 dir;
    int hits[4];
    Box box;
    Quat q;
    int speed;
    Cmd4 note;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    state[0x14] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x65) == 0 && state[0x14] >= 0x2111) {
        func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 7, (void *)(*(int *)(*state + 0x3b0) + 0x14));
        *((u8 *)state + 0x65) = 1;
    }
    state[0x10] = 0;
    func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    n = state[0x11];
    if (n > 0x666 && n < 0x1000) {
        q = *(Quat *)(*(int *)(*state + 0x3b0) + 4);
        func_0202f384(&box.ax, &q, &data_02042270);
        func_0202f384(&box.ay, &q, &data_02042264);
        func_0202f384(&box.az, &q, &data_02042258);
        func_01ffa724(0x1800, &box.az, &box.c);
        VEC_Add(&box.c, (void *)(*(int *)(*state + 0x3b0) + 0x14), &box.c);
        box.ext.x = 0x600;
        box.ext.y = 0x600;
        box.ext.z = 0x1800;
        n = func_ov107_020c8df0(*state, &box, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x63) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(obj + 0x74), (void *)(*(int *)(*state + 0x3b0) + 0x14), &push);
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1000, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 3, &push, 0) == 0) {
                continue;
            }
            msg = data_ov255_020d2b7c;
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

        p->hi = data_ov255_020d2b20[2].hi;
        p->lo = data_ov255_020d2b20[2].lo;
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
