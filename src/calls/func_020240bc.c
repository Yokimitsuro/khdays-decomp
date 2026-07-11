/* Set BG0CNT engine B (0x04001008), preserving priority + mosaic (0x43). */
void func_020240bc(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg0cnt_b = (volatile unsigned short *)0x04001008;
    *reg_bg0cnt_b = *reg_bg0cnt_b & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
