/* ov174 .rodata tables, 0x020d28d8-0x020d28ec.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov174 enemy (twins by byte identity). Installs the handlers (+8 release (020cfc60): IdTable data_ov174_020d28d8; */
const int data_ov174_020d28d8[4] = {
    4, 2, 3, 1,
};

/* read by Hit handler of the ov173 enemy (x2: ov173/174), variant of the matched ov166 sibling. Reco (020d0408): const u8 data_ov174_020d28e8[]; */
const u8 data_ov174_020d28e8[4] = {
    2, 3, 0, 1,
};
