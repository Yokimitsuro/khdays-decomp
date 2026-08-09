/* Kicks the hardware divider for a fx32 divide: the numerator goes in the HIGH word of the
 * 64-bit DIV_NUMER, which is the same as shifting it left by 32 before dividing. */
void FX_DivAsync(int numer, int denom) {
    volatile unsigned *div = (volatile unsigned *)0x04000280;
    *(volatile unsigned short *)div = 1;
    div[4] = 0;
    div[5] = (unsigned)numer;
    div[6] = (unsigned)denom;
    div[7] = 0;
}
