extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov121_020cf11c(void);

void func_ov121_020cf0c0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 4, 0);
    state[0x10] = 0;
    *(unsigned char *)((char *)state + 0x4c) = 0;
    *(unsigned char *)((char *)state + 0x4d) = 0;
    func_ov107_020c5af8(*state, 0x11a, 7, state[3]);
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov121_020cf11c);
}
