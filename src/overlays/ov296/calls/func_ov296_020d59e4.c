extern void func_0203c634();
extern void func_ov296_020d5b94(void);
extern void func_ov296_020d5a84(void);
extern void func_ov296_020d5b90(void);

void func_ov296_020d59e4(int this_) {
    int holder = *(int *)(this_ + 4);
    *(signed char *)(*(int *)holder + 0x1c6) = 0;
    *(signed char *)(*(int *)holder + 0x1c7) = -1;
    *(int *)(holder + 4) = *(int *)holder + 0xb0;
    *(int *)(holder + 8) = *(int *)(*(int *)holder + 0x384) + 0xad;
    {
        unsigned short *p = (unsigned short *)(*(int *)holder + 0x60);
        unsigned int u = *p;
        *p = (unsigned short)((u & ~0xff00) | ((((u << 0x10) >> 0x18 | 0x1e) << 0x18) >> 0x10));
    }
    func_0203c634(this_, 1, (int)&func_ov296_020d5b94);
    func_0203c634(this_, 0, (int)&func_ov296_020d5a84);
    func_0203c634(this_, 2, (int)&func_ov296_020d5b90);
}
