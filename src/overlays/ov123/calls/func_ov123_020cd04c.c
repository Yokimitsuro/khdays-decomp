extern void func_0203c634(void *obj, int idx, void *value);
void func_ov123_020cd04c(int *node) {
    int v = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    state[8] = v / 5;
    if (*(unsigned char *)state[0xc] != 0) return;
    *(signed char *)(*state + 0x1c7) = 2;
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
