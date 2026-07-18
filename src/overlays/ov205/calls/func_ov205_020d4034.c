struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov205_020d43d0(void);
extern void func_ov205_020d4108(void);
extern void func_ov205_020d42dc(void);

void func_ov205_020d4034(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[0x8] = *state + 0xb0;
    state[0x9] = *state + 0x74;
    state[0xa] = *(int *)(*state + 0x384) + 0xad;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(node, 1, func_ov205_020d43d0);
    func_0203c634(node, 0, func_ov205_020d4108);
    func_0203c634(node, 2, func_ov205_020d42dc);
}
