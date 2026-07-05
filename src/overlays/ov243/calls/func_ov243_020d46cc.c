extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov243_020d4720(void);

void func_ov243_020d46cc(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 4, 0);
    func_ov107_020c5af8(*state, 0x13b, 6, state[3]);
    *(unsigned char *)((char *)state + 0x40) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov243_020d4720);
}
