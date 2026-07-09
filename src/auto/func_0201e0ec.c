int func_0201e0ec(int arg0, unsigned int arg1) {
    if ((int)arg1 < 0) return 0;
    if (arg1 >= *(unsigned int *)(arg0 + 0x1c)) return 0;
    int e = arg0 + 0x20 + arg1 * 0xc;
    if (*(int *)(arg0 + 0x20 + arg1 * 0xc) == -1) e = 0;
    return e;
}
