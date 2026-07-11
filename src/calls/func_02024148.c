/* Set BG1CNT (0x0400000a), preserving priority + mosaic bits (0x43). */
void func_02024148(int size, int colorMode, int screenBase, int charBase, int extPal) {
    volatile unsigned short *reg_bg1cnt = (volatile unsigned short *)0x0400000a;
    *reg_bg1cnt = *reg_bg1cnt & 0x43
        | (size << 0xe) | (colorMode << 7) | (screenBase << 8) | (charBase << 2) | (extPal << 0xd);
}
