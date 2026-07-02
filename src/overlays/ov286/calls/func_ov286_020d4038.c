extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov286_020d409c(void);
void func_ov286_020d4038(int *node) {
    int result = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    result = result / 5;
    state[5] = result;
    func_ov107_020c9264(*state, 0, 1, result);
    state[10] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov286_020d409c);
}
