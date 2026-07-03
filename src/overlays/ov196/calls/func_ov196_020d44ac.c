struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov196_020d451c(void);

void func_ov196_020d44ac(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    state[0x11] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov196_020d451c);
}
