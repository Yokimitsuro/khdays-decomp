extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov239_020cd224(void);

void func_ov239_020cd190(int *node) {
    int *state = (int *)node[1];
    state[0xb] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)((char *)state + 0x32) == 0 && state[0xb] >= 0x2a8) {
        func_ov107_020c5af8(*state, 0x138, 4, state[2]);
        *(unsigned char *)((char *)state + 0x32) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    func_ov107_020c9264(*state, 4, 0);
    state[0xb] = 0;
    *(unsigned char *)((char *)state + 0x32) = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov239_020cd224);
}
