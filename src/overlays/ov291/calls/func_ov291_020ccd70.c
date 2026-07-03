extern int func_ov107_020c9f48();
extern void func_0202f384();
extern void func_01ffa724();
extern void func_ov107_020c9264();
extern void func_ov107_020c9ee8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov291_020cce3c(void);
void func_ov291_020ccd70(int *node, int p2, int p3, int param_4) {
    int *state = (int *)node[1];
    int buf[3];
    int uStack_14 = param_4;
    int scale = func_ov107_020c9f48(*(int *)(*state + 0x394), buf);
    func_0202f384(buf, *state + 0xa0, buf);
    func_01ffa724(scale, buf, state + 4);
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[7] = v / 25;
    }
    if (*(unsigned char *)state[8] == 0) {
        func_ov107_020c9264(*state, 2, 1);
        func_ov107_020c9ee8(*(int *)(*state + 0x394), 1, 1);
        *(signed char *)((char *)state + 0x28) = 0;
        func_0203c634(node, *(signed char *)(node + 8), func_ov291_020cce3c);
    }
}
