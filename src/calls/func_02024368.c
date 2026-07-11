/* Program BG1CNT (0x0400000a) for a BG ext-palette slot. Reads DISPCNT VRAM-mode
 * bits (incl. bit 3) to pick the palette-load path, then writes BG1CNT keeping 0x43. */
extern int GX_GetBankForBGExtPltt(int arg);
extern void func_020056b4(int a, int b, int c);

void func_02024368(int size, int colorMode, int screenBase, int charBase) {
    int bank = GX_GetBankForBGExtPltt(size);
    int extPal;
    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPal = 0;
    } else {
        extPal = 1;
    }
    int t = (*(volatile unsigned int *)0x04000000 & 8) ? 1 : 0;
    func_020056b4(1, *(volatile unsigned int *)0x04000000 & 7, t ? 1 : 0);
    {
        volatile unsigned short *reg_bg1cnt = (volatile unsigned short *)0x0400000a;
        *reg_bg1cnt = (*reg_bg1cnt & 0x43)
            | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 13);
    }
}
