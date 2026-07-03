struct hw60 { unsigned short lo : 8, hi : 8; };
struct bf { unsigned b : 8; };
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov195_020d09e4(void);

void func_ov195_020d0918(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x82) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*state + 0x60))->hi &= ~0xc;
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x38c) + 8))->b &= ~1;
    func_ov107_020c5af8(*state, 0, 0x48, state[0x10]);
    state[0xc] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov195_020d09e4);
}
