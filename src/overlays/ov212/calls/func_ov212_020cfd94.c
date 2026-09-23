/* Stagger entry of the ov212 enemy: plays animation 9, spawns effect 2 at the zero vector
 * (data_02041dc8), fires reaction 0x128 mode 9 at the +8 point, clears the +0x40 timer and the
 * +0x5a byte and hands off to the stagger tick (020d1c0c). */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern VecFx32 data_02041dc8;
extern void func_ov212_020cfe1c(int *node);

void func_ov212_020cfd94(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 9, 0);
    func_ov107_020c0b90(*state, 2, data_02041dc8, 0);
    func_ov107_020c5af8(*state, 0x128, 9, (void *)state[2]);
    state[0x10] = 0;
    *(unsigned char *)((char *)state + 0x5a) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov212_020cfe1c);
}
