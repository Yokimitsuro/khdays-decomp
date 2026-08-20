/* Paints the vertical tile strip that marks a list entry's extent.
 *
 * One tile is written per pair of rows, at column nX and row nY of the tag-0xb
 * map. Each row of the strip uses its own tile bank, 0x20 apart, and every
 * entry carries the 0x9000 attribute bits. Row 2 is special-cased to a fixed
 * pair of tiles chosen by nCount alone.
 *
 * Elsewhere the tile depends on whether two full rows remain: if they do, the
 * row holding the midpoint of nCount picks one of two tiles by the parity of
 * nCount - 1 and every other row gets a third; if only one row is left, the
 * choice is between the tile for landing exactly on nCount - 1 and the plain
 * one.
 *
 * The row and column steps are written as i * 2 and i * 0x20 rather than as
 * running accumulators, and the loop bound is left inline: both are
 * load-bearing, because that is what lets the compiler build the induction
 * variables itself and place them where the ROM does. */
typedef unsigned short u16;

extern int func_ov002_02053bb8(int nTag);
extern void func_ov002_02053cd4(int nTag);

void func_ov002_0205a924(int nCount, int nRows, int nX, int nY) {
    u16 *p;
    int i;
    int v;

    p = (u16 *)(func_ov002_02053bb8(0xb) + (nX + nY * 32) * 2);

    for (i = 0; i < (nRows + 1) / 2; i++) {
        if (i == 2) {
            if (nCount == 5) {
                *p = 0x91ff;
            } else {
                *p = 0x91fe;
            }
        } else {
            if (nRows - i * 2 >= 2) {
                if ((nCount - 1) / 2 == i) {
                    if ((nCount - 1) % 2 == 0) {
                        v = 0x217;
                    } else {
                        v = 0x218;
                    }
                } else {
                    v = 0x219;
                }
            } else {
                if (nCount - 1 - i * 2 == 0) {
                    v = 0x216;
                } else {
                    v = 0x215;
                }
            }
            *p = (u16)((v + i * 0x20) | 0x9000);
        }
        p++;
    }

    func_ov002_02053cd4(0xb);
}
