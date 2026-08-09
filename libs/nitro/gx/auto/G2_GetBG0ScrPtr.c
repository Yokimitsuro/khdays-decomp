/* BG screen base = the display-wide 64K block from DISPCNT plus the per-BG 2K slot in BG0CNT. */
void *G2_GetBG0ScrPtr(void) {
    int scrBase = (*(volatile unsigned short *)0x04000008 & 0x1f00) >> 8;
    unsigned dispBase = (*(volatile unsigned *)0x04000000 & 0x38000000) >> 27;
    return (void *)(0x06000000 + (dispBase << 16) + (scrBase << 11));
}
