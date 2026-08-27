extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov240_020ce8d4(int a, int b);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov240_020cf334(void);

void func_ov240_020cf294(int *node) {
    int *state = (int *)node[1];
    state[0xe] += *(int *)(*node + 0x2c);
    if (*(unsigned char *)((char *)state + 0x3e) == 0 && state[0xe] >= 0x440) {
        func_ov107_020c5af8(*state, 0x139, 4, state[2]);
        *(unsigned char *)((char *)state + 0x3e) = 1;
    }
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    func_ov107_020c9264(*state, 6, 0);
    func_ov240_020ce8d4(*state, 1);
    state[0xe] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov240_020cf334);
}
