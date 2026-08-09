/* BG3 only has a character base in the tiled modes: below 3 always, 3..5 unless it is running as
 * a bitmap layer, and never from mode 6 up. */
void *G2_GetBG3CharPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000e;
    if (mode < 3 || (mode < 6 && (cnt & 0x80) == 0)) {
        unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
        return (void *)(0x06000000 + (dispBase << 16) + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
