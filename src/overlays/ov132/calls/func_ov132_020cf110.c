extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov132_020cf154();

void func_ov132_020cf110(int this_) {
    int n = *(int *)(this_ + 4);
    if (*(unsigned char *)*(int *)(n + 0x48)) return;
    func_ov107_020c9264(*(int *)n, 2, 1);
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov132_020cf154);
}
