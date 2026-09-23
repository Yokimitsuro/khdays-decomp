/* ov279 .rodata tables, 0x020d357c-0x020d35a0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by refresh sub-node #0's local transform, then publish it. (020cfc04): struct blk4 data_ov279_020d357c; */
const int data_ov279_020d357c[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov279_Construct (020cfc6c): KindTable data_ov279_020d358c; */
const int data_ov279_020d358c[5] = {
    1, 2, 3, 4, 5,
};
