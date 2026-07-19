/* Kicks the divider with FX32_ONE in the high word of the numerator: that is 1.0 << 32, so the
 * quotient comes out as the fx32 reciprocal. */
void FX_InvAsync(int x) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    *(volatile long long *)(div + 4) = (long long)0x1000 << 32;
    *(volatile long long *)(div + 6) = (long long)(unsigned)x;
}
