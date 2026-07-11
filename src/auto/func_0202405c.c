/* Set BG2CNT engine B (0x0400100c), preserving priority + mosaic (0x43). */
void func_0202405c(int size, int colorMode, int screenBase, int charBase)
{
    volatile unsigned short *reg_bg2cnt_b = (volatile unsigned short *)0x0400100c;
    unsigned short h = *reg_bg2cnt_b;
    *reg_bg2cnt_b = (h & 0x43) | (size << 14) | (colorMode << 7) | (screenBase << 8) | (charBase << 2);
}
