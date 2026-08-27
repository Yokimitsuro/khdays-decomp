extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);

void func_ov264_020ce5cc(int *node) {
    int *state = (int *)node[1];
    state[0x14] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)((char *)state + 0x70) == 0 && state[0x14] >= 0x7f8) {
        func_ov107_020c5af8(*state, 0x15d, 8, state[4]);
        *(unsigned char *)((char *)state + 0x70) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    *(signed char *)(*state + 0x1c7) = 2;
    state[0x15] = *(int *)(*node + 0x2c);
    func_0203c634(node, *(signed char *)(node + 8), 0);
}
