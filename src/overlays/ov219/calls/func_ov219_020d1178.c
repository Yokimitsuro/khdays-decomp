extern void func_ov107_020c9264(int a, int b, int c);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int y);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov219_020d120c(void);

void func_ov219_020d1178(int *node) {
    int *state = (int *)node[1];
    int v[3];
    func_ov107_020c9264(*state, 2, 0);
    if (state[0x14] != 0) {
        func_ov107_020c5af8(*state, 0x136, 6, state[2]);
    }
    if (state[0x10] != 0) {
        int r;
        VEC_Subtract((void *)(state[0x10] + 0x190), (void *)(*state + 0xb0), v);
        r = func_020050b4(v[0], v[2]);
        state[4] = r;
        state[3] = r;
    }
    func_0203c634(node, *(signed char *)(node + 8), func_ov219_020d120c);
}
