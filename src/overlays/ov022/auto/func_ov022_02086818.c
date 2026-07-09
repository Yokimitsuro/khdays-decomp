void func_ov022_02086818(int arg0, int arg1) {
    unsigned int *q = *(unsigned int **)(arg0 + 0x20);
    if (arg1 != 0) *q |= 0x20;
    else *q &= 0xffffffdf;
}
