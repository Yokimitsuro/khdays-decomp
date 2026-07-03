extern void func_ov107_020c9264();
extern void VEC_Subtract();
extern int func_020050b4();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov181_020cdbb8(void);
void func_ov181_020cdb4c(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 8, 0);
    if (state[9] != 0) {
        int buf[3];
        int a;
        VEC_Subtract(state[9] + 0x190, state[1], buf);
        a = func_020050b4(buf[0], buf[2]);
        state[6] = a;
        state[5] = a;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov181_020cdbb8);
}
