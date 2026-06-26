extern int MI_CpuCopy8();

int FSi_ReadMemoryCore(int a, int b, int c, int d) {
    MI_CpuCopy8(c, b, d);
    return 0;
}
