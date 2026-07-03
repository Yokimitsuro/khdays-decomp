extern int func_ov107_020cab14();
extern void VEC_Subtract();
extern int func_020050b4();
extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov195_020d20a0(void);
void func_ov195_020d1ff0(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[5] = v / 3;
    }
    {
        int t = func_ov107_020cab14(*state, 0);
        state[2] = t;
        if (t != 0) {
            VEC_Subtract(t + 0x190, *state + 0xb0, buf);
            state[4] = func_020050b4(buf[0], buf[2]);
        }
    }
    func_ov107_020c9264(*state, 0xa, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 2, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov195_020d20a0);
}
