/* ov245 .rodata tables, 0x020d7194-0x020d71a4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by hit filter of the +0x214 sub-state while the +0x21a stock is positive: (020cc974) */
const u8 data_ov245_020d7194[16] = {
    0, 1, 2, 3, 15, 228, 0, 0, 202, 2, 0, 0, 0, 128, 254, 255,
};
