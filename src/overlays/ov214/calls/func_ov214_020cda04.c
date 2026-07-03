extern void func_0203c634(void *obj, int idx, void *value);
extern void VEC_Subtract(void *a, void *b, void *out);
extern int func_01ff8d18(void *v, void *v2);
extern int func_020050b4(int x, int z);
extern void func_ov107_020c9264();
extern void func_ov107_020c5af8();
extern void func_ov214_020cdac0(void);

void func_ov214_020cda04(int *node) {
    int *state = (int *)node[1];
    int buf[3];
    int target = state[2];
    if (target == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
        return;
    }
    VEC_Subtract((void *)(target + 0x190), (void *)(*state + 0xb0), buf);
    buf[1] = 0;
    state[0x12] = func_01ff8d18(buf, buf);
    {
        int angle = func_020050b4(buf[0], buf[2]);
        state[0x13] = angle;
        state[0x11] = angle;
    }
    func_ov107_020c9264(*state, 3, 0);
    func_ov107_020c5af8(*state, 0x129, 6, state[4]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov214_020cdac0);
}
