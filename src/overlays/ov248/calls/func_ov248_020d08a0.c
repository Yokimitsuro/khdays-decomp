/* Beam tick: once, while the +4 part's rig is busy, the actor spawns effect 1 (flag 2). The +0x18
 * timer accumulates the frame rate; past 1/3 a 5.0-long segment from the +8 point along
 * data_02042264, as thick as the actor's +0x80 radius, sweeps the actor list on behalf of the +0x384
 * owner. The first entity that accepts a 0.5 horizontal push away from the actor (kind 3) ends the
 * beam: effect 1 (flag 3), the owner's effect 8 and the actor's effect 0 (flag 1) at its +0x74
 * point, reaction 0 mode 0x53 at the +8 point, and the tick hands over to func_ov248_020d0b28. Past
 * 3.0 without a hit the beam ends the same way without the hit effects. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

extern const Vec3 data_02041dc8;
extern const Vec3 data_02042264;
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov248_020d0b28(int *node);

void func_ov248_020d08a0(int *node)
{
    int *state = (int *)node[1];
    Segment seg;
    int hits[4];
    Vec3 push;
    int i;
    int n;

    if (*((u8 *)state + 0x1c) == 0 && *(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c0b90(*state, 1, data_02041dc8, 2);
        *((u8 *)state + 0x1c) = 1;
    }
    state[6] += *(int *)(node[0] + 0x2c);
    if (state[6] >= 0x550) {
        seg.p0 = *(Vec3 *)state[2];
        seg.dir = data_02042264;
        seg.nLength = 0x5000;
        seg.nRadius = *(int *)(*state + 0x80);
        n = func_ov107_020c8f44(*(int *)(*state + 0x384), &seg, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x384), 3, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c0b90(*state, 1, data_02041dc8, 3);
            func_ov107_020c0b90(*(int *)(*state + 0x384), 8, *(Vec3 *)(*state + 0x74), 0);
            func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 1);
            func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
            func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov248_020d0b28);
            return;
        }
    }
    if (state[6] < 0x3000) {
        return;
    }
    func_ov107_020c0b90(*state, 1, data_02041dc8, 3);
    func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 1);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov248_020d0b28);
}
