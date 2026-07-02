extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov194_020ce934(void);
void func_ov194_020ce8c8(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[5] = v / 3;
    }
    func_ov107_020c9264(*state, 0xe, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 6, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov194_020ce934);
}
