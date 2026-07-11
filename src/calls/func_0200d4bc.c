/* Returns 1 if POWCNT1 (0x04000304) bit 0 (both-2D-engines power) is set. */
int func_0200d4bc(void)
{
    volatile unsigned short *reg_powcnt1 = (volatile unsigned short *)0x04000304;
    return (*reg_powcnt1 & 1) ? 1 : 0;
}
