/* func_ov023_020839b8 -- switch the main engine into the ov023 display mode: keep the current BG
 * mode in DISPCNT bits 8..12 but force bit 12 on, then set the blend registers and refresh the
 * scene's sprite objects.
 *
 * Two things the ROM shows and mwcc will not do by itself: DISPCNT is read TWICE (so the pointer
 * has to be `volatile`, or the reads get commoned into one), and the masked-out mode is extracted
 * FIRST -- binding it to a local puts the two reads in the ROM's order. Written as one expression
 * the "clear the field" read comes first and 17 bytes differ. */
extern void G2x_SetBlendAlpha_(void *reg, int a, int b, int c, int d);
extern void func_ov023_020839f4(void);

void func_ov023_020839b8(void) {
    volatile unsigned int *reg = (volatile unsigned int *)0x04000000;
    unsigned int mode = (*reg & 0x1f00) >> 8;
    *reg = (*reg & 0xffffe0ff) | ((mode | 0x10) << 8);
    G2x_SetBlendAlpha_((void *)((char *)reg + 0x50), 8, 0x21, 0xd, 3);
    func_ov023_020839f4();
}
