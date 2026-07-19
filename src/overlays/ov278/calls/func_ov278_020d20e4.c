struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov278_020d2174(void);

void func_ov278_020d20e4(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    ((struct bf *)(*(int *)(*state + 0x3b0) + 8))->b &= ~1;
    ((struct bf *)(*(int *)(*state + 0x3b4) + 8))->b &= ~1;
    func_0203c634(node, *(signed char *)(node + 8), func_ov278_020d2174);
}
