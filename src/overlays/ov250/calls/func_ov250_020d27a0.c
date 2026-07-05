extern int FX_Inv(int a, int b);
extern void func_0203c634();

void func_ov250_020d27a0(int this_) {
    int field0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    int t = *(int *)(holder + 0x1c) + *(int *)(field0 + 0x2c);
    *(int *)(holder + 0x1c) = t;
    *(int *)(*(int *)holder + 0x394) = 0x1000 - FX_Inv(t, 0x555);
    if (*(int *)(*(int *)holder + 0x394) < 1) {
        *(int *)(*(int *)holder + 0x394) = 1;
    }
    if (*(int *)(holder + 0x1c) < 0x555) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 0xc;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
