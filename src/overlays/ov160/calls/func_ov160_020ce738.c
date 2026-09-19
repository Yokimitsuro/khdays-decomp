/* Entry of the ov160 enemy's ground drop: a ray from the +0x10 anchor straight down (-2.0,
 * data_ov160_020cf7a8) is cast against the collision owner (+4 -> +0x7c); hitting nothing sets
 * the "airborne" flag. The +4 and +8 sub-objects are hidden (+0x5c bit 1) and the +0xc one shown;
 * its channels 0 and 2 take the flag (as a short) with a zero second argument and it is
 * reset (c7ac 0). Reaction 0x151 mode 7 fires at the anchor,
 * the +0x28 distance, the +0x30 hit mask and the +0x34/+0x38 words are cleared and the drop
 * tick func_ov160_020ce834 takes the slot. */
typedef struct { int x, y, z; } Vec3;

extern void *func_01fff920(void *collision, Vec3 *origin, Vec3 *direction);
extern void func_0203b9fc(int item, int channel, short a, int b);
extern void func_0203c7ac(int item, int a);
extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov160_020ce834(int *node);
extern Vec3 data_ov160_020cf7a8;

void func_ov160_020ce738(int *node)
{
    int *state = (int *)node[1];
    Vec3 dir;
    int bAir;
    int coll;

    coll = *(int *)(*state + 4);
    dir = data_ov160_020cf7a8;
    bAir = 0;
    if (func_01fff920(*(void **)(coll + 0x7c), (Vec3 *)(state + 4), &dir) == 0) {
        bAir = 1;
    }
    *(int *)(state[1] + 0x5c) |= 2;
    *(int *)(state[2] + 0x5c) |= 2;
    *(int *)(state[3] + 0x5c) &= ~2;
    func_0203b9fc(state[3], 0, bAir, 0);
    func_0203b9fc(state[3], 2, bAir, 0);
    func_0203c7ac(state[3], 0);
    func_ov107_020c5af8(*state, 0x151, 7, state + 4);
    state[0xa] = 0;
    *(unsigned char *)((char *)state + 0x30) = 0;
    state[0xd] = 0;
    state[0xe] = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), (void *)func_ov160_020ce834);
}
