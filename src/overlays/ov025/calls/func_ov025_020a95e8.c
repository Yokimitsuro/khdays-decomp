extern int func_ov025_02084b14();
extern void func_ov025_020a7264();
extern void func_ov025_020a73e0();

void func_ov025_020a95e8(void) {
    unsigned int *x = (unsigned int *)func_ov025_02084b14();
    if (x[0x10] != 0 && x[0x11] == 0) return;
    if (x[0x13e] == 0) return;
    if (x[0x13f] == 0) func_ov025_020a7264((int)x, 1);
    func_ov025_020a73e0(x);
}
