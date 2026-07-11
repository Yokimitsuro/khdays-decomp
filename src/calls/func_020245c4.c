/* Program BG0CNT engine B (0x04001008) for a BG ext-palette slot. */
extern int GX_GetBankForBGExtPltt(int arg);

void func_020245c4(int size, int colorMode, int screenBase, int charBase) {
    int bank = GX_GetBankForBGExtPltt(size);
    int extPal;
    if (bank == 0x20 || bank == 0x10 || bank == 0x60) {
        extPal = 0;
    } else {
        extPal = 1;
    }
    {
        volatile unsigned short *reg_bg0cnt_b = (volatile unsigned short *)0x04001008;
        *reg_bg0cnt_b = (*reg_bg0cnt_b & 0x43)
            | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 13);
    }
}
