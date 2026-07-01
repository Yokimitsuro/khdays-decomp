extern void INITi_CpuClear32_0x01ff86fc(unsigned data, void *dst, unsigned size);

void *NNSi_AllocFromTailOfExpHeap(int *hh, unsigned size, unsigned align) {
    int end = hh[1];
    unsigned new_top = (end - size) & ~(align - 1);
    unsigned bytes;
    if (new_top < (unsigned)hh[0]) return 0;
    bytes = end - new_top;
    if ((unsigned char)hh[-1] & 1) {
        INITi_CpuClear32_0x01ff86fc(0, (void *)new_top, bytes);
    }
    hh[1] = (int)new_top;
    return (void *)new_top;
}
