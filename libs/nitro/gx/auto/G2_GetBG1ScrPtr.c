/* Main-engine BG base: the display-wide 64K block from DISPCNT plus the per-BG slot in BG1CNT. */
void *G2_GetBG1ScrPtr(void) {
    int slot = (*(volatile unsigned short *)0x0400000a & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (slot << 11));
}
