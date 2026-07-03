struct bf { unsigned b : 8; };
struct blk16 { int a, b, c, d; };
extern void func_0202ea34(void *p, int a, int b, int c, int d);
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov178_020cccb8(void);
extern void func_ov178_020cceb8(void);
extern void func_ov178_020ccf58(void);
void func_ov178_020ccbcc(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = 0xff;
    ((struct bf *)(*(int *)(*state + 0x388) + 8))->b &= ~1;
    state[2] = *state + 0x74;
    state[3] = 0;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0202ea34(state + 0x19, 0, 0, 0, 0);
    *(struct blk16 *)(state + 0x1d) = *(struct blk16 *)(state + 0x19);
    func_0203c634(node, 0, func_ov178_020cccb8);
    func_0203c634(node, 1, func_ov178_020ccf58);
    func_0203c634(node, 2, func_ov178_020cceb8);
}
