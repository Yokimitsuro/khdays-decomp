extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);

void func_ov198_020d0f9c(int *node) {
    int *state = (int *)node[1];
    state[0x10] -= *(int *)(*node + 0x2c);
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    if (state[0x10] <= 0) {
        *(signed char *)(*state + 0x1c7) = 4;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    func_ov107_020c9264(*state, 1, 0);
}
