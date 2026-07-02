extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov204_020d13b0(void);
void func_ov204_020d1340(int *node) {
    int v = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    int result = v / 5;
    state[0xf] = result;
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 1, 0, result);
    func_ov107_020c9264(*state, 6, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov204_020d13b0);
}
