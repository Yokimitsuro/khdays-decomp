extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov292_020d3dfc(int *state);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov292_020d45bc(void);

void func_ov292_020d4580(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 1, 1);
    func_ov292_020d3dfc(state);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov292_020d45bc);
}
