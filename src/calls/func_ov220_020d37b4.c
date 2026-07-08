extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov220_020d2434(int a, int b);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov220_020d380c(void);

void func_ov220_020d37b4(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0xa, 0);
    func_ov220_020d2434(*state, 1);
    func_ov107_020c5af8(*state, 0x137, 6, state[2]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov220_020d380c);
}
