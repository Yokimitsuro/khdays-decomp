extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov251_020d613c(void);
void func_ov251_020d60e0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0x11, 0);
    state[0x1e] = -state[0x1e];
    state[0x20] = -state[0x20];
    if (state[0x1f] > 0) state[0x1f] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov251_020d613c);
}
