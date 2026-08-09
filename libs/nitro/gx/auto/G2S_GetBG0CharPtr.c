/* Sub-engine BG base: 0x06200000 plus the per-BG slot in BG0CNT (no display-wide block). */
void *G2S_GetBG0CharPtr(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x3c) >> 2;
    return (void *)(0x06200000 + (slot << 14));
}
