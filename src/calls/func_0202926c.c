extern void INITi_CpuClear32_0x01ff86fc(unsigned int data, void *dst, unsigned int size);

int func_0202926c(void *p, int field22_short, int field28) {
    INITi_CpuClear32_0x01ff86fc(0, p, 0x38);
    *(unsigned short *)((char *)p + 0x22) = (unsigned short)field22_short;
    *(int *)((char *)p + 0x28) = field28;
    *(int *)((char *)p + 0x24) = -1;
    return 1;
}
