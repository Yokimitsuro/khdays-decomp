/* func_ov253_020cf5f4 -- release entry: restores pose 1, clears bit 0 of the +0x3b4 item's +8
 * low byte, fires reaction 0x16c/8 at the +4 anchor, clears the +0x1c timer and the +0x30 flag
 * and moves the node to 020cf66c. */
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_ov107_020c5af8(int actor, int id, int kind, void *anchor);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020cf66c(void);

void func_ov253_020cf5f4(int *node) {
    int *state = (int *)node[1];

    func_ov107_020c9264(*state, 1, 0);
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    func_ov107_020c5af8(*state, 0x16c, 8, (void *)state[1]);
    state[7] = 0;
    *((unsigned char *)state + 0x30) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020cf66c);
}
