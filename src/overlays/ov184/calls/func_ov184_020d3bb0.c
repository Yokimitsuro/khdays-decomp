extern void func_ov107_020c9264();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov184_020d3c1c(void);
void func_ov184_020d3bb0(int *node) {
    int *state = (int *)node[1];
    func_ov107_020c9264(*state, 0xd, 0);
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x40) << 0x18) >> 0x10));
    }
    state[0x1b] = 0;
    *(unsigned char *)((char *)state + 0x51) &= ~2;
    func_0203c634(node, *(signed char *)(node + 8), func_ov184_020d3c1c);
}
