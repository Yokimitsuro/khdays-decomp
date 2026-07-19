/* From BG mode 5 up, BG2 can be a bitmap layer: then it has no character base at all. */
void *G2_GetBG2CharPtr(void) {
    int mode = *(volatile unsigned *)0x04000000 & 7;
    unsigned cnt = *(volatile unsigned short *)0x0400000c;
    if (mode < 5 || (cnt & 0x80) == 0) {
        unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x07000000) >> 24;
        return (void *)(0x06000000 + (dispBase << 16) + (((cnt & 0x3c) >> 2) << 14));
    }
    return 0;
}
