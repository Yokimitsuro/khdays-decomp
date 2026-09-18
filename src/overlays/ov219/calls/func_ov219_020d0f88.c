/* Chase decision of the ov219 enemy (and its byte-identical twin): a negative distance to the
 * target ends the state; otherwise, once the +4 item is idle, the actor plays animation 4
 * (looped), publishes a zero vector to the item with mode 1 and hands off to the chase tick. */
typedef unsigned char u8;
struct Vecx32 { int x, y, z; };

extern int func_ov219_020d05f0(int *node);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int anim, int flag);
extern void func_ov107_020c0b90(int actor, int a, struct Vecx32 v, int b);
extern const struct Vecx32 data_02041dc8;
extern void func_ov219_020d1028(int *node);

void func_ov219_020d0f88(int *node)
{
    int *state = (int *)node[1];

    if (func_ov219_020d05f0(node) < 0) {
        func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) == 0) {
        func_ov107_020c9264(*state, 4, 1);
        func_ov107_020c0b90(*state, 1, data_02041dc8, 0);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov219_020d1028);
    }
}
