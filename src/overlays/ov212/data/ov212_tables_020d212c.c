/* ov212 .rodata tables, 0x020d212c-0x020d2154.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov212_Construct (020cc628): IdTable data_ov212_020d212c; */
const int data_ov212_020d212c[10] = {
    0, 0, 3, 4, 5, 6, 9, 10,
    11, 12,
};
