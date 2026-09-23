/* ov175 .rodata tables, 0x020cea78-0x020cea88.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov175 enemy (twins by byte identity). Installs the handlers (+8 release (020cc020): IdTable data_ov175_020cea78; */
const int data_ov175_020cea78[3] = {
    1, 2, 4,
};

/* read by Hit handler of the ov175 enemy (x3: ov175/176/177), ported from the matched ov166 sibling. (020cc7b8): const u8 data_ov175_020cea84[]; */
const u8 data_ov175_020cea84[4] = {
    2, 3, 0, 1,
};
