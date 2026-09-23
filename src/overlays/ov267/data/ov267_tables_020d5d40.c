/* ov267 .rodata tables, 0x020d5d40-0x020d5d68.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov267_Construct (020d025c): IdTable data_ov267_020d5d40; */
const int data_ov267_020d5d40[10] = {
    0, 0, 3, 4, 5, 6, 9, 10,
    11, 12,
};
