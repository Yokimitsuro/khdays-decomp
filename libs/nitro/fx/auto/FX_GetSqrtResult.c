/* Spins on the SQRTCNT busy bit, then rounds SQRT_RESULT to fx32 (0x200 = half a unit). */
unsigned FX_GetSqrtResult(void) {
    while (*(volatile unsigned short *)0x040002b0 & 0x8000) {
    }
    return (*(volatile unsigned *)0x040002b4 + 0x200) >> 10;
}
