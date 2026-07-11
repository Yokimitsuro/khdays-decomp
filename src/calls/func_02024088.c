/* Set BG1CNT engine B (0x0400100a), preserving priority + mosaic (0x43). */
void func_02024088(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg1cnt_b = (volatile unsigned short *)0x0400100a;
    *reg_bg1cnt_b = *reg_bg1cnt_b & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
