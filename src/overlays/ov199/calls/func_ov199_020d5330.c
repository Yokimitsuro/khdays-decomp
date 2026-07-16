struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634();

void func_ov199_020d5330(int this_) {
    int holder = *(int *)(this_ + 4);
    int field0 = *(int *)this_;
    int t = *(int *)(holder + 0x40) + *(int *)(field0 + 0x2c);
    *(int *)(holder + 0x40) = t;
    if (t < 0xd48) return;
    ((struct hw60 *)(*(int *)holder + 0x60))->hi &= ~1;
    {
        unsigned short *p = (unsigned short *)(*(int *)holder + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    }
    *(signed char *)(*(int *)holder + 0x1c7) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
