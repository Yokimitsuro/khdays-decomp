extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov203_020d4b38(void);
void func_ov203_020d4ad8(int *node) {
    int v = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    state[4] = v / 30;
    func_ov107_020c9264(*state, 8, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov203_020d4b38);
}
