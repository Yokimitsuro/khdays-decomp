struct bf { unsigned b : 8; };
extern void func_0203c634();
extern void func_ov288_020d42f4(void);
extern void func_ov288_020d4188(void);
extern void func_ov288_020d42b0(void);

void func_ov288_020d40ec(int this_) {
    int holder = *(int *)(this_ + 4);
    *(signed char *)(*(int *)holder + 0x1c6) = 0;
    *(signed char *)(*(int *)holder + 0x1c7) = -1;
    *(int *)(holder + 0xc) = *(int *)holder + 0xb0;
    ((struct bf *)(*(int *)(*(int *)holder + 0x388) + 8))->b &= ~1;
    *(int *)(*(int *)holder + 0x394) = 0;
    func_0203c634(this_, 1, (int)&func_ov288_020d42f4);
    func_0203c634(this_, 0, (int)&func_ov288_020d4188);
    func_0203c634(this_, 2, (int)&func_ov288_020d42b0);
}
