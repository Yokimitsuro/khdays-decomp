extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov114_020cda68(void);

void func_ov114_020cda14(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0xb, 0);
    func_ov107_020c5af8(*state, 0x112, 4, state[1]);
    state[0x11] = 0;
    *(unsigned char *)((char *)state + 0x49) = 0;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov114_020cda68);
}
