/* Sub-engine BG base: 0x06200000 plus the per-BG slot in BG1CNT (no display-wide block). */
void *G2S_GetBG1ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400100a & 0x1f00) >> 8;
    return (void *)(0x06200000 + (slot << 11));
}
