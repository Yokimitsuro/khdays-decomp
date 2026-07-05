extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov293_020d34b4(void);

void func_ov293_020d3470(int *node) {
    int *n0 = (int *)node[0];
    int *state = (int *)node[1];
    state[0x10] += n0[0xb];
    if (state[0x10] > 0x4800) {
        *(unsigned char *)(*(int *)(*state + 0x384) + 0xa8) = 0;
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov293_020d34b4);
    }
}
