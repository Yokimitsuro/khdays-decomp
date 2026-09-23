/* Whirl finish tick of an ov257 state: the +0x54 timer accumulates the frame rate; with the +0x76
 * stage byte at 0, reaching 0.13 fires reaction +0x408 mode 0x18 at the +4 point (stage 1), and at
 * stage 1 reaching 0.87 fires mode 0x1a (stage 2). The +0x40 rate is the frame rate x 3 and the
 * +0x10 step heads for the +0x60 target (func_ov257_020ccf98). The +0x44 timer accumulates the frame
 * rate; between 1.27 and 1.83 the segment of each of the owner's four parts (+0x3c0..+0x3cc,
 * +0x78), moved by the step and with its radius x 3, is swept over the actor list: every entity
 * whose +2 id bit is clear in the +0x73 mask is pushed 5.0 away from the segment start (kind 4); on
 * acceptance the 14-byte message data_ov257_020d32da carries its +0x74 point to the owner's +0x24
 * hook, its bit is set and reaction +0x408 mode 9 fires there. Once the +0xc idle byte clears,
 * animation 0x14 plays, the +0x3d0 part plays motion 0x11 and the tick hands over to
 * func_ov257_020cff88. */
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

extern int func_ov257_020ccf98(int *state, int target, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void VEC_Add(const void *a, const void *b, void *out);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov257_020d32da;
extern void func_ov257_020cff88(int *node);

static inline int FX_Mul(int a, int b)
{
    return (int)(((long long)a * b + 0x800) >> 12);
}

void func_ov257_020cfbac(int *node)
{
    int obj;
    int *pHits;
    int *state = (int *)node[1];
    Vec3 dir;
    int speed;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int part;
    int n;
    int i;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x76) == 0) {
        if (state[0x15] >= 0x222) {
            func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x18, (void *)state[1]);
            *((u8 *)state + 0x76) = 1;
        }
    } else if (*((u8 *)state + 0x76) == 1) {
        if (state[0x15] >= 0xddd) {
            func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x408), 0x1a, (void *)state[1]);
            *((u8 *)state + 0x76) = 2;
        }
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    func_ov257_020ccf98(state, state[0x18], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    n = state[0x11];
    if (n > 0x1444 && n < 0x1d55) {
        for (part = 0; part < 4; part++) {
            int hits[4];
            Segment seg;

            seg = *(Segment *)(((int *)*state)[0xf0 + part] + 0x78);
            VEC_Add(&seg.p0, state + 4, &seg.p0);
            seg.nRadius = FX_Mul(seg.nRadius, 0x3000);
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
                        func_01ffa724(0x5000, &push, &push);
                        if (func_ov107_020ca918(pHits[i], *state, *state, 4, &push, 0) != 0) {
                            msg = data_ov257_020d32da;
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
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x14, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 0x11, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov257_020cff88);
}
