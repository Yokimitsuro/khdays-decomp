extern void func_ov035_020b3c18(char *a, char *b);

void func_ov035_020b3b24(char *a, char *b) {
    if ((a[0x694] & 1) == 0) return;
    func_ov035_020b3c18(a, b + 0x10);
}
