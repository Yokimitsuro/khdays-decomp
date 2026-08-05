/*
 * func_ov002_02075c64 - draw or clear a 2x2 tile cursor on the BG3 tilemap (THUMB).
 *
 * Fetches the BG3 screen base and writes a 2x2 block of BG map entries at byte offset 0x57a
 * (halfword cells at +0, +2 on the top row and +0x40, +0x42 on the row below). When param_1 is
 * non-zero it stamps the cursor tiles 0x809e/0x809f/0x80be/0x80bf (base, base+1, base+0x20,
 * base+0x21 - a 2x2 arrangement with the same attribute bits); when zero it clears the four cells.
 */
extern void *G2_GetBG3ScrPtr(void);

void func_ov002_02075c64(int param_1)
{
    char *s = (char *)G2_GetBG3ScrPtr();
    if (param_1 != 0) {
        *(unsigned short *)(s + 0x57a) = 0x809e;
        *(unsigned short *)(s + 0x57a + 2) = 0x809e + 1;
        *(unsigned short *)(s + 0x57a + 0x40) = 0x809e + 0x20;
        *(unsigned short *)(s + 0x57a + 0x42) = 0x809e + 0x21;
    } else {
        *(unsigned short *)(s + 0x57a) = 0;
        *(unsigned short *)(s + 0x57a + 2) = 0;
        *(unsigned short *)(s + 0x57a + 0x40) = 0;
        *(unsigned short *)(s + 0x57a + 0x42) = 0;
    }
}
