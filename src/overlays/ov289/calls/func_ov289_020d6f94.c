struct bf { unsigned b : 8; };
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0203c634();
extern void func_ov289_020d7038(void);

void func_ov289_020d6f94(int this_) {
    int holder = *(int *)(this_ + 4);
    {
        unsigned short *p = (unsigned short *)(*(int *)holder + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x80) << 0x18) >> 0x10));
    }
    ((struct hw60 *)(*(int *)holder + 0x60))->hi &= ~1;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    *(int *)(*(int *)holder + 0x394) = 0;
    *(int *)(holder + 0x34) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov289_020d7038);
}
