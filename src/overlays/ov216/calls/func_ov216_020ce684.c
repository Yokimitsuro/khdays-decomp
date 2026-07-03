struct hw60 { unsigned short lo : 8, hi : 8; };
struct bf { unsigned b : 8; };
extern void func_ov107_020c5af8();
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov216_020ce748(void);

void func_ov216_020ce684(int *node) {
    int *state = (int *)node[1];
    ((struct hw60 *)(*state + 0x60))->hi &= ~1;
    *(unsigned short *)(*state + 0x1ae) |= 3;
    {
        unsigned short *p = (unsigned short *)(*state + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    ((struct bf *)(*(int *)(*state + 0x3ac) + 8))->b &= ~1;
    func_ov107_020c5af8(*state, 0, 0x4d, *state + 0x74);
    func_0203c634(node, *(signed char *)(node + 8), func_ov216_020ce748);
}
