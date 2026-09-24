/* func_ov253_020ce310 -- revive decision: once the +4 item's animation is free (byte 0 clear)
 * the +0x30 counter is cleared, each of the four +0x458 parts gets its +0x21a stock refilled
 * from +0x218 (clamped) and sub-state 1, the actor's +0x454 is cleared, sub-state 2 requested
 * and the node slot released. */
extern void func_0203c634(int *node, int slot, void *cb);

void func_ov253_020ce310(int *node) {
    int *state = (int *)node[1];
    long i;

    if (*(unsigned char *)state[1] != 0) {
        return;
    }
    state[0xc] = 0;
    for (i = 0; i < 4; i++) {
        int part = (*(int **)(*state + 0x458))[i];
        short stock = *(short *)(part + 0x200 + 0x18);
        *(short *)(part + 0x200 + 0x1a) = stock < 0 ? 0 : (stock > ((short *)(part + 0x200))[0xc] ? ((short *)(part + 0x200))[0xc] : stock);
        *(unsigned char *)((*(int **)(*state + 0x458))[i] + 0x1c7) = 1;
    }
    *(int *)(*state + 0x454) = 0;
    *(unsigned char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
