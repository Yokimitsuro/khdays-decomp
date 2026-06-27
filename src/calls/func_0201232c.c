extern void MIi_CpuClear16(unsigned short data, void *destp, unsigned size);

void func_0201232c(int *p) {
    MIi_CpuClear16(0, p + 1, 0x18);
    p[1] = 0x1000;
    p[2] = 0x1000;
}
