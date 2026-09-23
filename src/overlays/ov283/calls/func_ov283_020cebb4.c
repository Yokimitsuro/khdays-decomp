/* Decision tick of the ov283 actor: the +0x10 velocity takes the +0x1c push (then damped to 0.6875),
 * the shared step (020ccb48) gives the target distance and a +0x17a bit-1 hit arms +0x74. Past the
 * +0x50 limit (0x7f80) the next move is 9; otherwise, once the +4 rig is idle, +0x34 rerolls 1.57
 * to 3.14 and the next move is picked: far (over 6.0) by a d100 roll (10 / 9 / 2 / 6), armed with the
 * +0x60 timer spent 5, else 4 (+0x7c = the roll passed 2.36, +0x3c cleared). */
typedef unsigned char u8;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 b0 : 1; u8 b1 : 1; } Bits;

extern void func_01ffa724(int scale, const Vec3 *v, Vec3 *out);
extern int func_ov283_020ccb48(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern int func_02023e80(int bound);
extern int func_02023eb4(int bound);

void func_ov283_020cebb4(int *node)
{
    int *state = (int *)node[1];
    int dist;

    {
        Vec3 *push = (Vec3 *)(state + 7);

        *(Vec3 *)(state + 4) = *push;
        func_01ffa724(0xb00, push, push);
    }
    dist = func_ov283_020ccb48(node);
    if (((Bits *)(*state + 0x17a))->b1) {
        state[0x1d] = 1;
    }
    if (state[0x14] > 0x7f80) {
        *(signed char *)(*state + 0x1c7) = 9;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    state[0xd] = func_02023e80(0x1922) + 0x1922;
    if (dist > 0x6000) {
        int lo = 0;
        int roll = func_02023eb4(0x65) + lo;

        if (roll < 10) {
            *(signed char *)(*state + 0x1c7) = 10;
        } else if (roll < 0x1e) {
            *(signed char *)(*state + 0x1c7) = 9;
        } else if (roll < 0x3c) {
            *(signed char *)(*state + 0x1c7) = 2;
        } else {
            *(signed char *)(*state + 0x1c7) = 6;
        }
    } else if (state[0x1d] != 0 && state[0x18] <= 0) {
        *(signed char *)(*state + 0x1c7) = 5;
    } else {
        state[0x1f] = state[0xd] > 0x25b3;
        state[0xf] = 0;
        *(signed char *)(*state + 0x1c7) = 4;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
