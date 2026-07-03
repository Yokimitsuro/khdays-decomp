struct hw60 { unsigned short lo : 8, hi : 8; };
struct bf { unsigned b : 8; };
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov215_020d10fc(void);
extern void func_ov215_020d0e90(void);
extern void func_ov215_020d1018(void);

void func_ov215_020d0dd8(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    ((struct bf *)(*(int *)(*state + 0x3ac) + 8))->b &= ~1;
    state[4] = *state + 0xb0;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    }
    func_0203c634(node, 1, func_ov215_020d10fc);
    func_0203c634(node, 0, func_ov215_020d0e90);
    func_0203c634(node, 2, func_ov215_020d1018);
}
