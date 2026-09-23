/* ov265 .rodata tables, 0x020d3668-0x020d3688.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov265_Construct (020cfc08): KindTable data_ov265_020d3668; */
const int data_ov265_020d3668[8] = {
    18, 19, 20, 21, 22, 23, 24, 25,
};
