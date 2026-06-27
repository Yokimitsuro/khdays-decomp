void func_02006b90(unsigned int *r0, unsigned int r1, unsigned int r2, unsigned int r3, unsigned int a5)
{
    *r0 = ((r1 | 0x40) | (r2 << 8)) | ((r3 | (a5 << 8)) << 16);
}
