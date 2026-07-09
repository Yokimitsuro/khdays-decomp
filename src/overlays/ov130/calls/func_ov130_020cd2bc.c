extern void func_ov130_020cc468();
extern void func_0203c634();

void func_ov130_020cd2bc(int this_) {
    int n = *(int *)(this_ + 4);
    func_ov130_020cc468(this_);
    if (*(unsigned char *)(*(int *)(n + 4) + 0xad)) return;
    *(char *)(*(int *)n + 0x1c7) = 2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
