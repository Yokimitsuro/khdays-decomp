extern int func_ov107_020cab14();
extern void func_0203c634(void *obj, int idx, void *value);
extern int func_ov107_020c9f48();
extern void func_0202f384();
extern void func_01ffa724();
extern void func_ov107_020c9264();
extern void func_ov205_020d4d70(void);
void func_ov205_020d4c84(int *node, int p2, int p3, int param_4) {
    int *state = (int *)node[1];
    int buf[3];
    int uStack_14 = param_4;
    int t = func_ov107_020cab14(*state, 0);
    state[1] = t;
    if (t == 0) {
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), 0);
        return;
    }
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[0xf] = v / 10;
    }
    {
        int scale = func_ov107_020c9f48(*(int *)(*state + 0x390), buf);
        func_0202f384(state + 2, *state + 0xa0, buf);
        func_01ffa724(scale, state + 2, state + 2);
    }
    if (*(unsigned char *)state[10] == 0) {
        func_ov107_020c9264(*state, 4, 0);
        func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d4d70);
    }
}
