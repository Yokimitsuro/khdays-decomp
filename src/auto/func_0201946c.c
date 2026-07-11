void func_0201946c(int *dst, int *src) {
    dst[0] = 0x1000;
    dst[5] = 0x1000;
    dst[1] = 0;
    dst[0xc] = -(src[9] * *(unsigned short *)((char *)src + 0x2c)) << 4;
    dst[0xd] = (src[0xa] * *(unsigned short *)((char *)src + 0x2e)) << 4;
    dst[4] = 0;
}
