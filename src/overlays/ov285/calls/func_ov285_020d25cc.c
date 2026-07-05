struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634();

void func_ov285_020d25cc(int this_) {
    int holder = *(int *)(this_ + 4);
    ((struct hw60 *)(*(int *)holder + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*(int *)holder + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x86) << 0x18) >> 0x10));
    }
    *(unsigned short *)(*(int *)holder + 0x1ae) |= 3;
    ((struct bf *)(*(int *)(*(int *)holder + 0x38c) + 8))->b &= ~1;
    func_ov107_020c5af8(*(int *)holder, 0, 0x4a, *(int *)(holder + 0x10));
    *(signed char *)(*(int *)holder + 0x1c7) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
