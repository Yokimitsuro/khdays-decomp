extern int func_ov220_020d2448(void *node);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov220_020d2f5c(void);

void func_ov220_020d2ee8(int *node) {
    int *state = (int *)node[1];
    if (func_ov220_020d2448(node) < 0) {
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c5af8(*state, 0x137, 4, state[2]);
    state[5] = 0;
    *((char *)state + 0x3c) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov220_020d2f5c);
}
