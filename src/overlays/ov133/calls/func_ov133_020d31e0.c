extern void func_ov107_020c9264();
extern void VEC_Subtract();
extern int func_020050b4();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov133_020d3250(void);
void func_ov133_020d31e0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 3, 0);
    if (state[0xe] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[0xe] + 0x190, *state + 0xb0, buf);
        a = func_020050b4(buf[0], buf[2]);
        state[4] = a;
        state[3] = a;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov133_020d3250);
}
