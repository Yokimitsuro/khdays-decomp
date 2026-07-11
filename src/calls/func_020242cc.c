extern unsigned short data_02041dd4[];

/* If the BGnCNT register for BG `param_1` has its ext-palette bit (0x2000) set,
 * the caller consumes two palette slots (param_1 + 2). */
int func_020242cc(int param_1) {
    unsigned short regOff = data_02041dd4[param_1];
    if (regOff == 0) return param_1;
    {
        volatile unsigned short *reg = (volatile unsigned short *)(regOff + 0x04000000);
        if (*reg & 0x2000) return param_1 + 2;
    }
    return param_1;
}
