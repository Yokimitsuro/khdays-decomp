extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *dst, void *src);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov264_020cdac0(void);

void func_ov264_020cda04(int *node) {
    int *state = (int *)node[1];
    int v[3];
    int r;
    if (state[2] == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    VEC_Subtract((void *)(state[2] + 0x190), (void *)(*state + 0xb0), v);
    v[1] = 0;
    state[0x12] = func_01ff8d18(v, v);
    r = func_020050b4(v[0], v[2]);
    state[0x13] = r;
    state[0x11] = r;
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c5af8(*state, 0x15d, 6, state[4]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov264_020cdac0);
}
