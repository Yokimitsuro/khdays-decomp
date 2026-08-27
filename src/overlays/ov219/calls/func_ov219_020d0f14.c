extern int func_ov219_020d05f0(void *node);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov219_020d0f88(void);

void func_ov219_020d0f14(int *node) {
    int *state = (int *)node[1];
    if (func_ov219_020d05f0(node) < 0) {
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c5af8(*state, 0x136, 4, state[2]);
    state[5] = 0;
    *((char *)state + 0x3c) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov219_020d0f88);
}
