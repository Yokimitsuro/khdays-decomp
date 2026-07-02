extern int func_ov107_020cab14();
extern void func_01ff8bc4();
extern int func_020050b4();
extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov269_020d40fc(void);
void func_ov269_020d404c(int *node) {
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
            func_01ff8bc4(t + 0x190, *state + 0xb0, buf);
            state[4] = func_020050b4(buf[0], buf[2]);
        }
    }
    func_ov107_020c9264(*state, 0xb, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x3d0), 3, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov269_020d40fc);
}
