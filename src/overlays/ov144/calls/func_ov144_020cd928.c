extern void func_ov144_020cca50(int *state);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov144_020cd9ac(void);

void func_ov144_020cd928(int *node) {
    int *state = (int *)node[1];
    int s;
    func_ov144_020cca50(state);
    s = *state;
    if (*(signed char *)(s + 0x1c6) == 7) {
        func_ov107_020c9264(s, 0, 1);
        func_0203c634(node, *(signed char *)(node + 8), func_ov144_020cd9ac);
        return;
    }
    func_ov107_020c9264(s, 8, 0);
    func_ov107_020c5af8(*state, 0x123, 4, state[2]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov144_020cd9ac);
}
