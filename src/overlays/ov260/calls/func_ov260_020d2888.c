/* Beam tick: the +0xc timer accumulates the frame rate; between 0.1 and 0.33 a 5.0-long segment
 * from the +8 point along data_02042264, as thick as the actor's +0x80 radius, is swept over the
 * actor list on behalf of the +0x38c owner: every entity whose +2 id bit is clear in the +0x10 mask
 * is pushed 0.5 horizontally away from the actor (kind 4); on acceptance the owner spawns effect 7 at
 * the +8 point and the bit is set. After any hit reaction 0 mode 0x53 fires there. Once the +4
 * part's rig is idle (+0xad), pose 0 is requested. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { Vec3 p0; Vec3 dir; int nLength; int nRadius; } Segment;

extern const Vec3 data_02042264;
extern int func_ov107_020c8f44(int owner, Segment *seg, int *hits);
extern void VEC_Subtract(const void *a, const void *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov107_020ca918(int hit, int owner, int item, int kind, Vec3 *push, int z);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov260_020d2888(int *node)
{
    int *state = (int *)node[1];
    int hit = 0;
    Segment seg;
    int hits[4];
    Vec3 push;
    int i;
    int n;

    state[3] += *(int *)(node[0] + 0x2c);
    if (state[3] >= 0x198 && state[3] <= 0x550) {
        seg.p0 = *(Vec3 *)state[2];
        seg.dir = data_02042264;
        seg.nLength = 0x5000;
        seg.nRadius = *(int *)(*state + 0x80);
        n = func_ov107_020c8f44(*(int *)(*state + 0x38c), &seg, hits);
        for (i = 0; i < n; i++) {
            u8 bit = 1 << *(u16 *)(hits[i] + 2);

            if ((*((u8 *)state + 0x10) & bit) != 0) {
                continue;
            }
            VEC_Subtract((void *)(hits[i] + 0x74), (void *)(*state + 0x74), &push);
            push.y = 0;
            func_01ff8d18(&push, &push);
            func_01ffa724(0x800, &push, &push);
            if (func_ov107_020ca918(hits[i], *state, *(int *)(*state + 0x38c), 4, &push, 0) == 0) {
                continue;
            }
            func_ov107_020c0b90(*(int *)(*state + 0x38c), 7, *(Vec3 *)state[2], 0);
            hit = 1;
            *((u8 *)state + 0x10) |= bit;
        }
        if (hit != 0) {
            func_ov107_020c5af8(*state, 0, 0x53, (void *)state[2]);
        }
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    *(u8 *)(*state + 0x1c7) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
