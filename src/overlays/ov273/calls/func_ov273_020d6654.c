/* Ground-slam tick: the +8 timer accumulates the frame rate. At stage 0 (+0xc), past 1.5 the stage
 * becomes 1 and animation 1 plays. At stage 1 a 8.0-long, 0.375-thick segment from the actor's +0xb0
 * point along data_02042264 is swept over the actor list: every entity whose +2 id bit is clear in
 * the +0xd mask is pushed 0.25 in a random horizontal direction (angle in [-pi, pi) through the
 * sine table, kind 4, on behalf of the +0x384 rider); on acceptance the 14-byte message
 * data_ov273_020d6bb4 carries its +0x74 point to the actor's +0x24 hook, its bit is set and the
 * rider's reaction 0 mode 0x4f fires there. The tick ends once the +0x388 part's rig is idle or
 * the rider's +0x1c4 flags have bit 1 or 3 set; in the latter case the part's animation 0 is
 * advanced by one frame step. Ending requests pose 0. */
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

#define ANG2IDX(a) ((unsigned short)(((long long)(a) * 0x28be60db9391LL + 0x80000000000LL) >> 44) >> 4)

extern const Vec3 data_02042264;
extern const short data_0203d210[];
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_02023eb4(int n);
extern void func_01ffa724(int scale, const Vec3 *v, void *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_0203be68(int part, int a, int b);
extern void func_0203be9c(int part, int a, int frame);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov273_020d6bb4;

void func_ov273_020d6654(int *node)
{
    int *state = (int *)node[1];
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int hits[4];
    Segment seg;
    Vec3 push;
    int n;
    int i;

    state[2] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0xc) == 0) {
        if (state[2] > 0x1800) {
            *((u8 *)state + 0xc) = 1;
            func_ov107_020c9264(*state, 1, 0);
        }
    } else if (*((u8 *)state + 0xc) == 1) {
        n = *state;
        seg.p0 = *(Vec3 *)(n + 0xb0);
        seg.dir = data_02042264;
        seg.nLength = 0x8000;
        seg.nRadius = 0x600;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Cmd14 msg;
            unsigned int idx;
            int angle;

            if ((*((u8 *)state + 0xd) & (1 << *(u16 *)(hits[i] + 2))) != 0) {
                continue;
            }
            angle = func_02023eb4(0x6489) - 0x3244;
            idx = ANG2IDX(angle);
            push.x = data_0203d210[idx * 2];
            push.y = 0;
            push.z = data_0203d210[idx * 2 + 1];
            func_01ffa724(0x400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 4, &push, 0) == 0) {
                continue;
            }
            msg = data_ov273_020d6bb4;
            PACK(msg, scratchX, *(Fx32 *)(hits[i] + 0x74), 5);
            PACK(msg, scratchY, *(Fx32 *)(hits[i] + 0x78), 8);
            PACK(msg, scratchZ, *(Fx32 *)(hits[i] + 0x7c), 11);
            if (*(void (**)(int, Cmd14 *, int))(*state + 0x24) != 0) {
                (*(void (**)(int, Cmd14 *, int))(*state + 0x24))(*state, &msg, 0xe);
            }
            *((u8 *)state + 0xd) |= 1 << *(u16 *)(hits[i] + 2);
            func_ov107_020c5af8(*(int *)(*state + 0x384), 0, 0x4f, (void *)(hits[i] + 0x74));
        }
    }
    if (*(u8 *)(*(int *)(*state + 0x388) + 0xad) != 0 && (*(u8 *)(*(int *)(*state + 0x384) + 0x1c4) & 0xa) == 0) {
        return;
    }
    if ((*(u8 *)(*(int *)(*state + 0x384) + 0x1c4) & 0xa) != 0) {
        n = func_0203be68(*(int *)(*state + 0x388), 0, 0);
        func_0203be9c(*(int *)(*state + 0x388), 0, n + *(int *)(node[0] + 0x2c));
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
