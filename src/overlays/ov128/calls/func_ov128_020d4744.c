extern void func_ov128_020d3e38();
extern void func_0203c634();

void func_ov128_020d4744(int this_) {
    int n = *(int *)(this_ + 4);
    func_ov128_020d3e38(this_);
    if (*(unsigned char *)(*(int *)(n + 4) + 0xad)) return;
    *(char *)(*(int *)n + 0x1c7) = 4;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
