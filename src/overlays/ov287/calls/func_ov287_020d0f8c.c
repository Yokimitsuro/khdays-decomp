struct bf { unsigned b : 8; };
extern void func_ov107_020c9264(int node, int a, int b);
extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634();
extern void func_ov287_020d1058(void);

void func_ov287_020d0f8c(int this_) {
    int holder = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)holder, 3, 0);
    *(unsigned short *)(*(int *)holder + 0x1ae) |= 0x10;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    *(unsigned short *)(*(int *)holder + 0x1ae) |= 1;
    func_ov107_020c5af8(*(int *)holder, 0x15b,
                        (unsigned short)(*(int *)(*(int *)holder + 0x38c) == 0 ? 4 : 5),
                        *(int *)(holder + 0xc));
    *(int *)(*(int *)holder + 0x394) = 0;
    *(int *)(holder + 0x34) = 0;
    *(int *)(holder + 0x4c) = 0;
    *(int *)(holder + 0x50) = 0;
    *(signed char *)(holder + 0x54) = 0;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov287_020d1058);
}
