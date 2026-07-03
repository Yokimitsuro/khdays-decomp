struct bf { unsigned b : 8; };
extern int func_ov107_020cab14();
extern void func_01ff8bc4();
extern int func_020050b4();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov250_020d08fc(void);
void func_ov250_020d0834(int *node) {
    int *state = (int *)node[1];
    int t = func_ov107_020cab14(*state, 0);
    state[4] = t;
    if (t != 0) {
        int buf[3];
        int a;
        func_01ff8bc4(t + 0x190, state[1], buf);
        a = func_020050b4(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    func_ov107_020c9264(*state, 0, 0);
    *(int *)(*state + 0x394) = 1;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[7] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov250_020d08fc);
}
