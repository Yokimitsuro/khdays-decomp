extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_020050b4(int x, int y);
extern void func_ov107_020c9ee8(int a, int b, int c);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov152_020d5f58(void);

void func_ov152_020d5ed8(int *node) {
    int *state = (int *)node[1];
    int local[3];
    func_ov107_020c9264(*state, 3, 0);
    if (state[0xf] != 0) {
        VEC_Subtract((void *)(state[0xf] + 0x190), (void *)state[0x10], local);
        int r = func_020050b4(local[0], local[2]);
        state[3] = r;
        state[2] = r;
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x3cc), 0, 0);
    func_0203c634(node, *(signed char *)(node + 8), func_ov152_020d5f58);
}
