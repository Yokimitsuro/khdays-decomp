extern void INITi_CpuClear32_0x01ff86fc(unsigned data, void *dst, unsigned size);

void *NNSi_AllocFromHeadOfExpHeap(int *hh, unsigned size, unsigned align) {
    int start = hh[0];
    int aligned = (int)(((unsigned)((align - 1) + start)) & ~(align - 1));
    int new_top = (int)size + aligned;
    unsigned bytes;
    unsigned char flag;
    if ((unsigned)new_top > (unsigned)hh[1]) return 0;
    flag = (unsigned char)hh[-1];
    bytes = (unsigned)(new_top - start);
    if (flag & 1) {
        INITi_CpuClear32_0x01ff86fc(0, (void *)start, bytes);
    }
    hh[0] = new_top;
    return (void *)aligned;
}
