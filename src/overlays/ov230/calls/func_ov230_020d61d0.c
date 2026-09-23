/* Beam tick: the +0xc timer accumulates the frame rate; between 1/6 and 1/2 the actor spawns effect
 * 0 at its +0x74 point once (+0x14) and a 5.0-long segment from the +8 point along data_02042264, as
 * thick as the actor's +0x80 radius, sweeps the actor list on behalf of the +0x388 owner. The first
 * entity that accepts a 0.5 horizontal push away from the actor (kind 3) gets effect 8 at its +0x74
 * point, reaction 0 mode 0x53 fires at the +8 point and pose 0 is requested. Otherwise, once the +4
 * part's rig is idle (+0xad), pose 0 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

extern const Vec3 data_02042264;
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov230_020d61d0(int *node)
{
    int *state = (int *)node[1];
    Segment seg;
    int hits[4];
    Vec3 push;
    int i;
    int n;

    state[3] += *(int *)(node[0] + 0x2c);
    if (state[3] >= 0x2a8 && state[3] <= 0x7f8) {
        if (*((u8 *)state + 0x14) == 0) {
            func_ov107_020c0b90(*state, 0, *(Vec3 *)(*state + 0x74), 0);
            *((u8 *)state + 0x14) = 1;
        }
        seg.p0 = *(Vec3 *)state[2];
        seg.dir = data_02042264;
        seg.nLength = 0x5000;
        seg.nRadius = *(int *)(*state + 0x80);
        n = func_ov107_020c8f44(*(int *)(*state + 0x388), &seg, hits);
        for (i = 0; i < n; i++) {
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x388), 3, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c0b90(*(int *)(*state + 0x388), 8, *(Vec3 *)(hits[i] + 0x74), 0);
            func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
            *(u8 *)(*state + 0x1c7) = 0;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
