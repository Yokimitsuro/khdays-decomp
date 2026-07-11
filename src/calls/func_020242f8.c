/* Program BG0CNT (0x04000008) for a BG ext-palette slot. Reads DISPCNT VRAM-mode
 * bits to pick the palette-load path, then writes BG0CNT preserving 0x43. */
extern int GX_GetBankForBGExtPltt(int arg);
extern void func_020056b4(int a, int b, int c);

void func_020242f8(int size, int colorMode, int screenBase, int charBase) {
    int bank = GX_GetBankForBGExtPltt(size);
    int extPal;
    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPal = 0;
    } else {
        extPal = 1;
    }
    func_020056b4(1, *(volatile unsigned int *)0x04000000 & 7, 0);
    {
        volatile unsigned short *reg_bg0cnt = (volatile unsigned short *)0x04000008;
        *reg_bg0cnt = (*reg_bg0cnt & 0x43)
            | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 13);
    }
}
