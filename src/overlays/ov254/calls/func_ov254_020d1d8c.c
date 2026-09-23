/* Slam tick: bit 7 of the actor's +0x61 byte clears; while the +4 part's rig is busy animation 1
 * plays and the actor spawns effect 0 at the +8 point. The +0xc timer accumulates the frame rate;
 * past 1/6 a 4.0-long, 1.5-thick segment from the +8 point along data_02042264 sweeps the actor list
 * on behalf of the +0x38c owner. The first entity that accepts a 2.0 horizontal push away from the
 * actor (the +z axis when directly above), lifted by 1.0 (kind 1), ends the slam: animation 2,
 * effect 0 (flag 1) and the owner's effect 1 at the +8 point, reaction 0 mode 0x50 there, and the
 * tick hands over to func_ov254_020d2020. Past 0.5 without a hit it ends the same way without the
 * hit effects. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;
typedef struct { u16 lo : 8; u16 hi : 8; } Hw60;

extern const Vec3 data_02042264;
extern const Vec3 data_02042258;
extern void func_ov107_020c9264(int owner, int anim, int mode);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov254_020d2020(int *node);

void func_ov254_020d1d8c(int *node)
{
    int *state = (int *)node[1];
    Segment seg;
    int hits[4];
    Vec3 push;
    int n;
    int i;

    ((Hw60 *)(*state + 0x60))->hi &= ~0x80;
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 1, 0);
        func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 0);
    }
    state[3] += *(int *)(node[0] + 0x2c);
    if (state[3] >= 0x2a8) {
        seg.p0 = *(Vec3 *)state[2];
        seg.dir = data_02042264;
        seg.nLength = 0x4000;
        seg.nRadius = 0x1800;
        n = func_ov107_020c8f44(*(int *)(*state + 0x38c), &seg, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
            push.y = 0;
            if (func_01ff8d18(&push, &push) == 0) {
                push = data_02042258;
            }
            func_01ffa724(0x2000, &push, &push);
            push.y = 0x1000;
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 1, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c9264(*state, 2, 0);
            func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 1);
            func_ov107_020c0b90(*(int *)(*state + 0x38c), 1, *(Vec3 *)state[2], 0);
            func_ov107_020c5af8(*state, 0, 0x50, (void *)state[2]);
            func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov254_020d2020);
            return;
        }
    }
    if (state[3] < 0x800) {
        return;
    }
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)state[2], 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov254_020d2020);
}
