extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov141_020cd108();

void func_ov141_020cd0c0(int this_) {
    int n = *(int *)(this_ + 4);
    if (*(int *)(n + 0x14) >= 0x80) return;
    *(int *)(n + 0x30) = 0;
    func_ov107_020c9264(*(int *)n, 2, 1);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov141_020cd108);
}
