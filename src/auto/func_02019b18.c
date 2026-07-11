/* Init dst from src: copy src[6]/src[7], zero slots, and precompute
 * dst[0xc]=((0x1000-src[6])*src[0x2c])<<3, dst[0xd]=((0x1000-src[7])*src[0x2e])<<3. */
void func_02019b18(int *dst, int *src) {
    dst[0] = src[6];
    dst[5] = src[7];
    dst[1] = 0;
    dst[0xc] = ((0x1000 - src[6]) * *(unsigned short *)((char *)src + 0x2c)) << 3;
    dst[0xd] = ((0x1000 - src[7]) * *(unsigned short *)((char *)src + 0x2e)) << 3;
    dst[4] = 0;
}
