void G3X_SetClearColor(unsigned color, unsigned alpha, unsigned depth,
                       unsigned polygonID, int fog) {
    unsigned v = color | (alpha << 16) | (polygonID << 24);
    if (fog != 0) {
        v |= 0x8000;
    }
    *(volatile unsigned *)0x04000350 = v;
    *(volatile unsigned short *)0x04000354 = (unsigned short)depth;
}
