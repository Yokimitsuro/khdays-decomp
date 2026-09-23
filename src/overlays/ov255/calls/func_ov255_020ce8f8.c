/* Second bite tick of an ov255 state: at 1.0 on the +0x50 timer reaction +0x3f8 mode 0x11 fires
 * once at the owner's +0x3b0 body point (+0x65), and a three-phase trigger on the rig's channel-0
 * frame (+0x66) fires mode 1 at 20.0 and mode 0 at 22.0 at the +8 point, restarting below 22.0.
 * Without a nearest target (020cab14, kept in +0x5c) sub-state 2 is requested; otherwise the +0x10
 * step heads for it (func_ov255_020ccdac, never past the gap). The +0x44 timer accumulates the
 * frame rate; the +0x40 rate is the frame rate x 15 up to 0.37, then x 3, and between 0.3 and 0.93
 * the owner's +0x3a0 segment (+0x78, radius 0.75) is swept over the actor list: every entity whose
 * +2 id bit is clear in the +0x63 mask is pushed 1.25 along the +0x1c heading (kind 1); on
 * acceptance the 14-byte message of data_ov255_020d2b44 carries its +0x74 point to the owner's
 * +0x24 hook, its bit is set and reaction +0x3f8 mode 9 fires there. From 2.1 on the hook receives
 * note 0 of data_ov255_020d2b20 once (+0x62). Once the +0xc idle byte clears, animation 0xf plays,
 * the +0x3a4 part plays motion 0xe, +0x44, +0x63, +0x65 and +0x62 clear and the tick hands over
 * to func_ov255_020cedd0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int value; } Fx32;
typedef struct { int x, y, z; } Vec3;
typedef struct { u16 lo; u16 hi; } Cmd4;
typedef struct { u16 id; u8 kind; u8 cmd; u8 flag; u8 pos[9]; } Cmd14;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

#define PACK(cmd, dead, src, at)                                              \
    (dead) = (src);                                                           \
    ((u8 *)&(cmd))[at] = (u8)(((unsigned int)(dead).value >> 0x10 & 0x7f)     \
                              | ((unsigned int)(dead).value >> 0x18 & 0x80)); \
    ((u8 *)&(cmd))[(at) + 1] = (u8)((unsigned int)(dead).value >> 8);         \
    ((u8 *)&(cmd))[(at) + 2] = (u8)(dead).value

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern int func_ov107_020cab14(int obj, int kind);
extern int func_ov255_020ccdac(int *state, int point, Vec3 *dir, int *speed);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern void func_0202f384(Vec3 *out, void *q, const Vec3 *in);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Cmd14 data_ov255_020d2b44;
extern const Cmd4 data_ov255_020d2b20[];
extern int func_0203bec0(int rig, int channel);
extern const Vec3 data_02042258;
extern void func_ov255_020cedd0(int *node);

void func_ov255_020ce8f8(int *node)
{
    int obj;
    int *state = (int *)node[1];
    Vec3 dir;
    int hits[4];
    Segment seg;
    int speed;
    Cmd4 note;
    Fx32 scratchZ;
    Fx32 scratchY;
    Fx32 scratchX;
    int n;
    int i;

    state[0x14] += *(int *)(node[0] + 0x2c);
    if (*((u8 *)state + 0x65) == 0 && state[0x14] >= 0x1000) {
        func_ov107_020c5af8(*state, (short)*(int *)(*state + 0x3f8), 0x11, (void *)(*(int *)(*state + 0x3b0) + 0x14));
        *((u8 *)state + 0x65) = 1;
    }
    {
        unsigned char phase = *((u8 *)state + 0x66);

        if (phase == 0) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x14000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3f8), 1, (void *)state[2]);
                *((u8 *)state + 0x66) = 1;
            }
        } else if (phase == 1) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) >= 0x16000) {
                func_ov107_020c5af8(state[0], (short)*(int *)(*state + 0x3f8), 0, (void *)state[2]);
                *((u8 *)state + 0x66) = 2;
            }
        } else if (phase == 2) {
            if (func_0203bec0(*(int *)(*state + 0x384), 0) < 0x16000) {
                *((u8 *)state + 0x66) = 0;
            }
        }
    }
    state[0x17] = func_ov107_020cab14(*state, 0);
    if (state[0x17] == 0) {
        *(u8 *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    n = func_ov255_020ccdac(state, state[0x17], &dir, &speed);
    if (n < speed) {
        speed = n;
    }
    func_01ffa724(speed, &dir, (Vec3 *)(state + 4));
    state[0x11] += *(int *)(node[0] + 0x2c);
    if (state[0x11] > 0x5dd) {
        state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 10;
    } else {
        state[0x10] = *(int *)(node[0] + 0x2c) * 30 / 2;
    }
    if (state[0x11] > 0x4cc && state[0x11] < 0xeee) {
        seg = *(Segment *)(*(int *)(*state + 0x3a0) + 0x78);
        seg.nRadius = 0xc00;
        n = func_ov107_020c8f44(*state, &seg, hits);
        for (i = 0; i < n; i++) {
            Vec3 push;
            Cmd14 msg;

            obj = hits[i];
            if ((*((u8 *)state + 0x63) & (1 << *(u16 *)(obj + 2))) != 0) {
                continue;
            }
            func_0202f384(&push, state + 7, &data_02042258);
            func_01ffa724(0x1400, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *state, 1, &push, 0) == 0) {
                continue;
            }
            msg = data_ov255_020d2b44;
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
    if (*((u8 *)state + 0x62) == 0 && state[0x11] >= 0x2199) {
        Cmd4 *p = &note;

        p->hi = data_ov255_020d2b20[0].hi;
        p->lo = data_ov255_020d2b20[0].lo;
        if (*(void (**)(int, Cmd4 *, int))(*state + 0x24) != 0) {
            (*(void (**)(int, Cmd4 *, int))(*state + 0x24))(*state, p, 4);
        }
        *((u8 *)state + 0x62) = 1;
    }
    if (*(unsigned char *)state[3] != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0xf, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3a4), 0xe, 0);
    state[0x11] = 0;
    *((u8 *)state + 0x63) = 0;
    *((u8 *)state + 0x65) = 0;
    *((u8 *)state + 0x62) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov255_020cedd0);
}
