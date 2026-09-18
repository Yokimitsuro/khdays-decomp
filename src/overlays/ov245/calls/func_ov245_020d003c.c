/* func_ov245_020d003c -- wait tick: does nothing until the +0x3dc owner's +0x4c4 flag is set,
 * then counts the state's +0x30 timer down by the scene's +0x2c step; once it expires (and is
 * clamped to 0) the first of the actor's three +0x394 slots without a +0x38c handle requests
 * sub-state 4 and releases the node's slot. */
struct Ov245Slots { char pad[0x394]; int slots[3]; };

extern void func_0203c634(int *node, int slot, void *cb);

void func_ov245_020d003c(int *node) {
    int *state = (int *)node[1];
    int i;

    if (*(int *)(*(int *)(*state + 0x3dc) + 0x4c4) == 0) {
        return;
    }
    state[0xc] -= *(int *)(*node + 0x2c);
    if (state[0xc] > 0) {
        return;
    }
    state[0xc] = 0;
    for (i = 0; i < 3; i++) {
        if (*(int *)(((struct Ov245Slots *)*state)->slots[i] + 0x38c) == 0) {
            *(unsigned char *)(*state + 0x1c7) = 4;
            func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
            return;
        }
    }
}
