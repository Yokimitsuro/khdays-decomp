/* Push the current page's scroll value (field 0x168, shifted into bits 16-24) into engine B's
 * BG3 H/V scroll registers, and reload the BG3 tilemap once when the page's dirty flag (0x16c) is
 * set. Always returns 1. */
extern int func_ov025_02084b14(void);
extern int func_ov025_02084aa4(int entry);
extern void GXS_LoadBG3Scr(int src, int offset, int size);

int func_ov025_020a9b60(void) {
    int page = func_ov025_02084b14();
    volatile int *pScroll = (volatile int *)0x04001018;
    pScroll[0] = 0x01ff0000 & (*(int *)(page + 0x168) << 16);
    pScroll[1] = 0x01ff0000 & (*(int *)(page + 0x168) << 16);
    if (*(int *)(page + 0x16c) != 0) {
        int scr = func_ov025_02084aa4(0x1b);
        GXS_LoadBG3Scr(scr, 0, 0x800);
        *(int *)(page + 0x16c) = 0;
    }
    return 1;
}
