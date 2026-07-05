struct v3 { int x, y, z; };
extern void func_ov107_020c9264(int a, int b, int c);
extern void VEC_Subtract(const void *a, const void *b, void *c);
extern int func_020050b4(int a, int b);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov202_020cd7b0(void);

void func_ov202_020cd740(int *node) {
    int *state = (int *)node[1];
    struct v3 buf;
    func_ov107_020c9264(*state, 3, 0);
    int obj = state[0xd];
    if (obj != 0) {
        VEC_Subtract((const void *)(obj + 0x190), (const void *)(*state + 0xb0), &buf);
        state[2] = state[3] = func_020050b4(buf.x, buf.z);
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov202_020cd7b0);
}
