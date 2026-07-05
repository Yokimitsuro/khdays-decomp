extern int func_01ff8a04(int a, int b);
extern void func_0203c634();

void func_ov184_020d4368(int this_) {
    int field0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    int t = *(int *)(holder + 0x1c) + *(int *)(field0 + 0x2c);
    *(int *)(holder + 0x1c) = t;
    *(int *)(*(int *)holder + 0x394) = 0x1000 - func_01ff8a04(t, 0x555);
    if (*(int *)(*(int *)holder + 0x394) < 0xcc) {
        *(int *)(*(int *)holder + 0x394) = 0xcc;
    }
    if (*(int *)(holder + 0x1c) < 0x555) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 0xc;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
