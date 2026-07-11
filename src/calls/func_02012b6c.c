extern int data_02041a04;

/* Look up the BGnCNT register offset for BG `arg0`; if that BG's ext-palette
 * bit (0x2000) is set, the caller uses two palette slots (arg0 += 2). */
int func_02012b6c(int arg0) {
    unsigned int regOff = *(unsigned short *)((char *)&data_02041a04 + arg0 * 2);
    if (regOff == 0) return arg0;
    {
        volatile unsigned short *reg = (volatile unsigned short *)(regOff + 0x04000000);
        if ((*reg & 0x2000) != 0) arg0 += 2;
    }
    return arg0;
}
