extern void func_ov107_020c9ee8();
extern void func_ov107_020c9264();
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov139_020cd5a4(void);
void func_ov139_020cd4f8(int *node) {
    int *state = (int *)node[1];
    {
        int v = *(int *)(*node + 0x2c) * 0x1e;
        state[4] = v / 5;
    }
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    func_ov107_020c9ee8(*(int *)(*state + 0x390), 1, 0);
    func_ov107_020c9264(*state, 6, 0);
    func_ov107_020c5af8(*state, 0x11f, 7, state[0x13]);
    func_0203c634(node, *(signed char *)(node + 8), func_ov139_020cd5a4);
}
