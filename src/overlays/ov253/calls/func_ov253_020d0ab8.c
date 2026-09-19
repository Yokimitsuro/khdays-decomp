/* func_ov253_020d0ab8 -- taunt wait: the +0x18 speed follows six times the frame step (30 / 5)
 * and the +0x1c timer runs down; once it expires or the actor's +0x21a stock is empty the
 * +0x38c item's +0xa8 flag clears, and when the +8 item's animation is free bit 0 of the +0x3b4
 * item's +8 low byte clears, pose 6 plays and the node moves to 020d0b88. */
struct w8 { unsigned int lo : 8, rest : 24; };

extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020d0b88(void);

void func_ov253_020d0ab8(int *node) {
    int *state = (int *)node[1];

    state[6] = *(int *)(node[0] + 0x2c) * 0x1e / 5;
    state[7] -= *(int *)(node[0] + 0x2c);
    if (state[7] > 0 && *(short *)(*state + 0x200 + 0x1a) != 0) {
        return;
    }
    *(unsigned char *)(*(int *)(*state + 0x38c) + 0xa8) = 0;
    if (*(unsigned char *)state[2] != 0) {
        return;
    }
    ((struct w8 *)(*(int *)(*state + 0x3b4) + 8))->lo &= ~1;
    func_ov107_020c9264(*state, 6, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020d0b88);
}
