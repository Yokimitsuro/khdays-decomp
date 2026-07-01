extern void func_ov054_020b6418(char *a, char *b);

void func_ov054_020b6324(char *a, char *b) {
    if ((a[0x694] & 1) == 0) return;
    func_ov054_020b6418(a, b + 0x10);
}
