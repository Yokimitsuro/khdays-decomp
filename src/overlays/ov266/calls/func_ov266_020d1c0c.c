/* Stagger tick of the ov266 enemy: the +0x40 timer accumulates the owner's rate and past 0x1a90
 * spawns effect 4 at the zero vector (data_02041dc8), fires reaction 0x15e mode 0xa at the +8
 * point, queues sub-state 0xa and ends the state. */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern VecFx32 data_02041dc8;

void func_ov266_020d1c0c(int *node)
{
    int *state = (int *)node[1];

    state[0x10] += *(int *)(node[0] + 0x2c);
    if (state[0x10] < 0x1a90) {
        return;
    }
    func_ov107_020c0b90(*state, 4, data_02041dc8, 0);
    func_ov107_020c5af8(*state, 0x15e, 0xa, (void *)state[2]);
    *(unsigned char *)(*state + 0x1c7) = 0xa;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
