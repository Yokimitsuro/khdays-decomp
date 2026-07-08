extern void func_ov297_020d4168(void *node);

void func_ov297_020d5228(int *node) {
    int *state = (int *)node[1];

    func_ov297_020d4168(node);

    if (state[0x17] >= 0) {
        state[0x23] = 1;
        state[0x17] -= *(int *)(*node + 0x2c);
        return;
    }

    state[0x23] = 0;
    *(unsigned char *)(*state + 0x1c7) = 2;
}
