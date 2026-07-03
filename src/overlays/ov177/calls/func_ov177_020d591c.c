struct bf { unsigned b : 8; };
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov177_020d59bc(void);
void func_ov177_020d591c(int *node) {
    int *state = (int *)node[1];
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x46) << 0x18) >> 0x10));
    }
    *(unsigned short *)(*state + 0x1ae) |= 1;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    func_ov107_020c5af8(*state, 0, 0x49, state[2]);
    state[0x12] = 0;
    func_0203c634(node, *(signed char *)(node + 8), func_ov177_020d59bc);
}
