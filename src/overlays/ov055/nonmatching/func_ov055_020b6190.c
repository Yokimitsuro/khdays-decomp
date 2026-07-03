extern void func_ov055_020b6340(char *a, char *b);

void func_ov055_020b6190(char *a, char *b) {
    if ((a[0x694] & 1) == 0) return;
    func_ov055_020b6340(a, b + 0x14);
}
