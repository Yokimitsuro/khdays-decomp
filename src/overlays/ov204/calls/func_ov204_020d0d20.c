extern int func_ov107_020cab14(int a, int b);
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov204_020d0db4(void);
void func_ov204_020d0d20(int *node) {
    int *state = (int *)node[1];
    int t = func_ov107_020cab14(*state, 0);
    state[1] = t;
    if (t == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[15] = v / 10;
    }
    func_ov107_020c9264(*state, 2, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov204_020d0db4);
}
