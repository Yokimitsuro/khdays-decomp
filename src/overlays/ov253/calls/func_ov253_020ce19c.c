/* func_ov253_020ce19c -- animation wait: the +0x1c timer runs up by the frame step; once the
 * +4 item's animation is free (byte 0 clear) the +0x34 repeat count grows: under 2 pose 0xb
 * plays again, otherwise pose 8 and the node moves to 020ce210. */
extern void func_ov107_020c9264(int actor, int pose, int flag);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov253_020ce210(void);

void func_ov253_020ce19c(int *node) {
    int *state = (int *)node[1];

    state[7] += *(int *)(node[0] + 0x2c);
    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    state[0xd]++;
    if (state[0xd] < 2) {
        func_ov107_020c9264(*state, 0xb, 0);
        return;
    }
    func_ov107_020c9264(*state, 8, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov253_020ce210);
}
