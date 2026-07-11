/* Init dst from src: dst[0]=dst[5]=0x1000, zero dst[1]/[4], and precompute
 * dst[0xc]=(-src[0x24]*src[0x2c])<<4, dst[0xd]=(src[0x28]*src[0x2e])<<4. */
void func_02019900(int *dst, int *src) {
    dst[0] = 0x1000;
    dst[5] = 0x1000;
    dst[1] = 0;
    dst[0xc] = (-src[9] * *(unsigned short *)((char *)src + 0x2c)) << 4;
    dst[0xd] = (src[0xa] * *(unsigned short *)((char *)src + 0x2e)) << 4;
    dst[4] = 0;
}
