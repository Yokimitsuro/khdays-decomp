extern void MI_CpuCopy8(const void *src, void *dst, unsigned size);
extern void DC_StoreRange(void *addr, unsigned size);

int func_0200fe88(void *a) {
    unsigned short buf[4];
    unsigned char *p = (unsigned char *)a;

    if (p == 0) return 0;
    if (*(unsigned short *)(p + 0x3c) == 0) return 0;

    MI_CpuCopy8(p + 0x50, buf, 8);
    DC_StoreRange(buf, 8);

    if (*(unsigned int *)(p + 0x44) == 0) {
        if (*(volatile unsigned short *)&buf[0] == 0x2348 || *(volatile unsigned short *)&buf[0] == 0xbd8a) {
            if (buf[3] == 4) return 1;
        }
    }
    return 0;
}
