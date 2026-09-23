/* ov176 .rodata tables, 0x020d26b8-0x020d26c8.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov175 enemy (twins by byte identity). Installs the handlers (+8 release (020cfc60): IdTable data_ov176_020d26b8; */
const int data_ov176_020d26b8[3] = {
    1, 2, 4,
};

/* read by Hit handler of the ov175 enemy (x3: ov175/176/177), ported from the matched ov166 sibling. (020d03f8): const u8 data_ov176_020d26c4[]; */
const u8 data_ov176_020d26c4[4] = {
    2, 3, 0, 1,
};
