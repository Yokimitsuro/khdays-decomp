extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov293_020d273c(void);
void func_ov293_020d26d8(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 1, 1);
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[5] = v / 5;
    }
    state[0x10] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov293_020d273c);
}
