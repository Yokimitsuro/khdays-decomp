/* Set BG0CNT (0x04000008), preserving priority + mosaic bits (0x43). */
void func_0202417c(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg0cnt = (volatile unsigned short *)0x04000008;
    *reg_bg0cnt = *reg_bg0cnt & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
