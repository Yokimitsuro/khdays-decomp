/* Lunge tick of an ov235 state (the ceafc shape): at 2.07 on the +0x54 timer reaction +0x3c8
 * mode 7 fires once at the owner's +0x3b4 body point (+0x65). The +0x40 rate follows the frame
 * rate and the +0x10 step heads for the +0x5c target (func_ov235_020cccc0). The +0x44 timer
 * accumulates the frame rate; between 0.2 and 0.5 the segment from the owner's +0x74 centre along
 * the step (radius 2.25) is swept over the actor list: every entity whose +2 id bit is clear in
 * the +0x63 mask is pushed away from the centre (never downwards, unit length, kind 3); on
 * acceptance the 14-byte message of data_ov235_020d250a carries its +0x74 point to the owner's
 * +0x24 hook, its bit is set and reaction +0x3c8 mode 9 fires there. Once the +0xc idle byte
 * clears, the +0x4c cooldown is re-rolled in [+0x224, +0x228] and sub-state 2 is requested. */
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
extern int func_ov235_020cccc0(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov235_020d250a;
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

void func_ov235_020cf7b8(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Vec3 dir;
    int hits[4];
    Segment seg;
    int speed;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    state[0x15] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x65) == 0 && state[0x15] >= 0x2111) {
        func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3c8), 7, (void *)(*(int *)(*state + 0x3b4) + 0x14));
        *((u8 *)state + 0x65) = 1;
    }
    state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 30;
    func_ov235_020cccc0(state, state[0x17], &dir, &speed);
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] > 0x333 && state[0x11] < 0x800) {
        seg.p0 = *(Vec3 *)(*state + 0x74);
        n = func_01ff8d18((Vec3 *)(state + 4), &seg.dir);
        seg.nLength = n;
        seg.nRadius = 0x2400;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x63) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            VEC_Subtract((void *)(obj + 0x74), &seg.p0, &push);
            if (push.y < 0) {
                push.y = 0;
            }
            func_01ff8d18(&push, &push);
            func_01ffa724(0x1000, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 3, &push, 0) == 0) {
                continue;
            }
            msg = data_ov235_020d250a;
            PACK(msg, scratchX, *(Fx32 *)(obj + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(obj + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(obj + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0x63) |= 1 << *(u16 *)(hits[i] + 2);
            func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3c8), 9, (void *)(obj + 0x74));
        }
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    state[0x13] = RandRange(*(int *)(*state + 0x224), *(int *)(*state + 0x228));
    *(u8 *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
