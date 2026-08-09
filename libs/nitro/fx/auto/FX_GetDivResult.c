/* Spins on DIVCNT, then rounds the 64-bit quotient down to fx32 (0x80000 = half of 1<<20). */
int FX_GetDivResult(void) {
    while (*(volatile unsigned short *)0x04000280 & 0x8000) {
    }
    return (int)((*(volatile long long *)0x040002a0 + 0x80000) >> 20);
}
