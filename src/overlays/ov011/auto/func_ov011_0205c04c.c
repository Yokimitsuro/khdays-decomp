/* Disable colour special effects: BLDCNT (0x04000050) = 0. */
void func_ov011_0205c04c(void) {
    volatile unsigned short *reg_bldcnt = (volatile unsigned short *)0x04000050;
    *reg_bldcnt = 0;
}
