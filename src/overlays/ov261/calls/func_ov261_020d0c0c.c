extern void func_ov261_020d0348();
extern void func_0202f384();
extern void func_01ff8bc4();
extern void func_01ff8d18();
extern int func_01ff8bf8();
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern int data_02042258[];
extern void func_ov261_020d0cd8(void);
void func_ov261_020d0c0c(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[0xf] = v / 15;
    }
    {
        int sub = *(int *)(*state + 0x3a8);
        unsigned int b28[3], b1c[3];
        func_ov261_020d0348(state + 7, sub + 0x74, state[1]);
        func_0202f384(b1c, state + 3, data_02042258);
        func_01ff8bc4(sub + 0x74, state[1], b28);
        func_01ff8d18(b28, b28);
        if ((int)func_01ff8bf8(b1c, b28) > 0xf00) {
            state[0x10] = 0;
            func_ov107_020c5af8(*state, 0x179, 4, state[1]);
            func_0203c634(node, *(signed char *)(node + 8), func_ov261_020d0cd8);
        }
    }
}
