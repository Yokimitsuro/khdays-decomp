extern void func_ov107_020c9264();
extern void func_01ff8bc4();
extern int func_020050b4();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov250_020d160c(void);
void func_ov250_020d15a0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 8, 0);
    if (state[9] != 0) {
        int buf[3];
        int a;
        func_01ff8bc4(state[9] + 0x190, state[1], buf);
        a = func_020050b4(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov250_020d160c);
}
