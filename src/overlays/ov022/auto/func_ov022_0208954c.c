void func_ov022_0208954c(int arg0, int arg1, int arg2) {
    int b = *(int *)(arg0 + 0x20);
    if (arg1 < 0) return;
    *(int *)(arg1 * 0x114 + *(int *)(b + 0xc) + 0x10c) = arg2;
}
