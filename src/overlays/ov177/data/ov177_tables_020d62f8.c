/* ov177 .rodata tables, 0x020d62f8-0x020d6308.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov175 enemy (twins by byte identity). Installs the handlers (+8 release (020d38a0): IdTable data_ov177_020d62f8; */
const int data_ov177_020d62f8[3] = {
    1, 2, 4,
};

/* read by Hit handler of the ov175 enemy (x3: ov175/176/177), ported from the matched ov166 sibling. (020d4038): const u8 data_ov177_020d6304[]; */
const u8 data_ov177_020d6304[4] = {
    2, 3, 0, 1,
};
