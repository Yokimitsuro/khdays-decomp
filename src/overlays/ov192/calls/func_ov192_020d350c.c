extern void func_ov107_020c9264();
extern void func_0203c634();
extern void func_ov192_020d3558();

void func_ov192_020d350c(int this_) {
    int n = *(int *)(this_ + 4);
    func_ov107_020c9264(*(int *)n, 4, 0);
    *(int *)(n + 0x2c) = 0;
    *(char *)(n + 0x38) = 0;
    *(unsigned char *)(n + 0x39) &= ~2;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), (int)&func_ov192_020d3558);
}
