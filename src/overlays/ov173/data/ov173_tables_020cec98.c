/* ov173 .rodata tables, 0x020cec98-0x020cecac.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov173 enemy (twins by byte identity). Installs the handlers (+8 release (020cc020): IdTable data_ov173_020cec98; */
const int data_ov173_020cec98[4] = {
    4, 2, 3, 1,
};

/* read by Hit handler of the ov173 enemy (x2: ov173/174), variant of the matched ov166 sibling. Reco (020cc7c8): const u8 data_ov173_020ceca8[]; */
const u8 data_ov173_020ceca8[4] = {
    2, 3, 0, 1,
};
