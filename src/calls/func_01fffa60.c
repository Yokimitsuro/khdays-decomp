extern void MIi_CpuCopy16(const void *src, void *dst, unsigned int size);

extern void *data_0204c22c;

void func_01fffa60(const void *src, unsigned int size, int channel, int reset_flag) {
    char *st = (char *)data_0204c22c;
    char *slot = *(char **)(st + 4) + channel * 12;
    char *dst;
    unsigned int off;
    if (*(int *)(slot + 8) == 1) return;
    if (reset_flag != 0) *(unsigned short *)(slot + 4) = 0;
    dst = *(char **)slot;
    off = *(unsigned short *)(slot + 4);
    *(unsigned short *)(slot + 4) = (unsigned short)(off + size);
    MIi_CpuCopy16(src, dst + off, size);
    *(int *)(st + 0x68) = 1;
    *(int *)(st + 0x6c) = 1;
}
