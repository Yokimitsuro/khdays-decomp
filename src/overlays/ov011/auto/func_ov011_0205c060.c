/* Disable colour special effects on engine B: BLDCNT (0x04001050) = 0. */
void func_ov011_0205c060(void) {
    volatile unsigned short *reg_bldcnt_b = (volatile unsigned short *)0x04001050;
    *reg_bldcnt_b = 0;
}
