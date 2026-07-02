extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov136_020d2b4c(void);
void func_ov136_020d2ad4(int *node) {
    int v = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    state[5] = v / 15;
    func_ov107_020c9264(*state, 2, 1, v);
    state[12] = 0;
    func_ov107_020c9ee8(*(int *)(*state + 0x3a0), 0, 1);
    func_0203c634(node, *(signed char *)(node + 8), func_ov136_020d2b4c);
}
