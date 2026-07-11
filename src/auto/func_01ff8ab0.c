/* Waits for the hardware divider to finish (DIVCNT busy bit), then reads the
 * 64-bit quotient from DIV_RESULT (0x040002a0). */
long long func_01ff8ab0(void) {
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    while (*reg_divcnt & 0x8000)
        ;
    return *(volatile long long *)0x040002a0;
}
