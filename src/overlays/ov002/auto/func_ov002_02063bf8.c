/*
 * Store a four-bit value into a packed nibble buffer: row nRow, column nColumn.
 *
 * The row stride is four bytes, so eight nibbles per row, and the parity of the column picks
 * the low or the high half of the byte. The column is signed and the ROM halves it with the
 * sign-correct idiom, which is why the index arithmetic looks heavier than a shift.
 *
 * The ROM predicates the ODD arm with ne and lets the even arm fall through, so the source
 * tests the even case and leaves the odd write in the else: writing the test the other way
 * round predicates the even arm instead and swaps all five predicated instructions.
 */

typedef unsigned char u8;

void func_ov002_02063bf8(u8 *buf, int x, int y, int value) {
    u8 *p = &buf[y * 4 + x / 2];
    if (x % 2 == 0) {
        *p = (u8)((*p & 0xf0) | (value & 0xf));
    } else {
        *p = (u8)((*p & 0xf) | ((value & 0xf) << 4));
    }
}
