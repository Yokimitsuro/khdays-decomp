/* Sub-engine BG base: 0x06200000 plus the per-BG slot in BG0CNT (no display-wide block). */
void *G2S_GetBG0ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x04001008 & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}
