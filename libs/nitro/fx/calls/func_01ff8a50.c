extern void FX_InvAsync(int x);

/* Kick an async reciprocal, spin on DIVCNT busy, return the 64-bit DIV_RESULT. */
long long func_01ff8a50(int x) {
    volatile unsigned short *reg_divcnt = (volatile unsigned short *)0x04000280;
    FX_InvAsync(x);
    while (*reg_divcnt & 0x8000) ;
    return *(long long *)0x040002a0;
}
