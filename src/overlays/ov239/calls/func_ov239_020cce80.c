/* Recover entry of the ov239 enemy: plays animation 0, raises bit 0 of the actor's +0x1ae,
 * spawns effect 0 at the +8 point, fires reaction 0x138 mode 9 at the actor's position and
 * hands off to ccf0c. */
typedef struct { int x, y, z; } VecFx32;

extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, VecFx32 v, int d);
extern void func_ov107_020c5af8(int actor, int a, int b, void *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov239_020ccf0c(int *node);

void func_ov239_020cce80(int *node)
{
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 0, 0);
    *(unsigned short *)(*state + 0x1ae) |= 1;
    func_ov107_020c0b90(*state, 0, *(VecFx32 *)state[2], 0);
    func_ov107_020c5af8(*state, 0x138, 9, (void *)(*state + 0x74));
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov239_020ccf0c);
}
