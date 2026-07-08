extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov284_020ccb30(void);

void func_ov284_020ccad8(int *node) {
    int *state = (int *)node[1];
    *(unsigned short *)(*state + 0x1ae) |= 1;
    func_ov107_020c9264(*state, 2, 0);
    func_ov107_020c5af8(*state, 0x16c, 7, state[1]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov284_020ccb30);
}
