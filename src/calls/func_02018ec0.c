extern void func_02018cec(void *ptr, unsigned short arg1, int arg2, void *arg3);

void func_02018ec0(int *dst, int *src, unsigned int arg) {
    func_02018cec((void *)src[2], arg, src[0] >> 12, dst);
    dst[4] = (dst[4] & ~0xc0000000) | 0x40000000;
    dst[0] |= 8;
}
