/* Hardware square root of a positive fixed-point value; non-positive input gives 0. */
extern int FX_GetSqrtResult(void);

int FX_Sqrt(int x) {
    volatile unsigned short *sqrtcnt = (volatile unsigned short *)0x40002b0;
    if (x <= 0) {
        return 0;
    }
    *sqrtcnt = 1;
    *(volatile int *)(sqrtcnt + 4) = 0;
    *(volatile int *)(sqrtcnt + 6) = x;
    return FX_GetSqrtResult();
}
