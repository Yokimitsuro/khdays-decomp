/* Enables or disables the V-blank interrupt in DISPSTAT; returns the previous state. */
int GX_VBlankIntr(int enable) {
    volatile unsigned short *dispstat = (volatile unsigned short *)0x04000004;
    int prev = *dispstat & 8;
    if (enable != 0) {
        *dispstat |= 8;
        return prev;
    }
    *dispstat &= ~8;
    return prev;
}
