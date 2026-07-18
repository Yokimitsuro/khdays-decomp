struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov130_020ccc1c(void);
extern void func_ov130_020cc988(void);
extern void func_ov130_020ccb10(void);

void func_ov130_020cc8c4(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[0x4] = *state + 0xb0;
    state[0x5] = *state + 0x74;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(node, 1, func_ov130_020ccc1c);
    func_0203c634(node, 0, func_ov130_020cc988);
    func_0203c634(node, 2, func_ov130_020ccb10);
}
