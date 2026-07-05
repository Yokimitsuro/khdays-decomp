extern void func_ov297_020d4168(int *node);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov297_020d52c0(void);

void func_ov297_020d527c(int *node) {
    int *state = (int *)node[1];
    func_ov297_020d4168(node);
    state[0x1f]++;
    func_ov107_020c9264(*state, 7, 0);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov297_020d52c0);
}
