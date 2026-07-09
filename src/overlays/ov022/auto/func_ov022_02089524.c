int func_ov022_02089524(int arg0, int arg1) {
    int b = *(int *)(arg0 + 0x20);
    if (arg1 < 0) return arg0;
    *(char *)(*(int *)(b + 0xc) + arg1 * 0x114) = 0;
    return 1;
}
