extern void func_ov107_020c5af8(int a, int b, int c, int d);
extern void func_0203c634();

void func_ov217_020d2230(int this_) {
    int field0 = *(int *)this_;
    int holder = *(int *)(this_ + 4);
    *(int *)(holder + 0x50) += *(int *)(field0 + 0x2c);
    if (*(unsigned char *)(holder + 0x70) == 0 && *(int *)(holder + 0x50) >= 0x7f8) {
        func_ov107_020c5af8(*(int *)holder, 0x144, 8, *(int *)(holder + 0x10));
        *(unsigned char *)(holder + 0x70) = 1;
    }
    if (*(unsigned char *)(*(int *)(holder + 4) + 0xad) != 0) return;
    *(signed char *)(*(int *)holder + 0x1c7) = 2;
    *(int *)(holder + 0x54) = *(int *)(*(int *)this_ + 0x2c);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
