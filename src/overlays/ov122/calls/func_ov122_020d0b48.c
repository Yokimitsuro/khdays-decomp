extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov122_020d0bac(void);
void func_ov122_020d0b48(int *node) {
    int result = *(int *)(*node + 0x2c) * 0x1e;
    int *state = (int *)node[1];
    result = result / 10;
    state[6] = result;
    func_ov107_020c9264(*state, 2, 1, result);
    state[16] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov122_020d0bac);
}
