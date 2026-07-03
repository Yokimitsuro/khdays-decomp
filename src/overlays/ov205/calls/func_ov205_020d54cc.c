extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov205_020d5570(void);
void func_ov205_020d54cc(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[0xf] = v / 5;
    }
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 4, 0);
    func_ov107_020c9264(*state, 0xc, 0);
    *(signed char *)((char *)state + 0x45) = 0;
    *(signed char *)((char *)state + 0x44) = 0;
    state[0xb] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov205_020d5570);
}
