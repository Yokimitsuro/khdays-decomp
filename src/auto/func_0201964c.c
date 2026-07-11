/* Init dst from src: copy src[6]->dst[0], src[7]->dst[5], zero dst[1]/[4]/[0xc],
 * and precompute dst[0xd] = (src[0x2e] * (0x2000 - 2*src[7])) << 3. */
void func_0201964c(int *dst, int *src) {
    dst[0] = src[6];
    dst[5] = src[7];
    dst[1] = 0;
    dst[0xc] = 0;
    dst[0xd] = (*(unsigned short *)((char *)src + 0x2e) * (0x2000 - src[7] - src[7])) << 3;
    dst[4] = 0;
}
