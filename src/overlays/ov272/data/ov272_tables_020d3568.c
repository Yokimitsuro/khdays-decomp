/* ov272 .rodata tables, 0x020d3568-0x020d358c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by refresh sub-node #0's local transform, then publish it. (020cfc04): struct blk4 data_ov272_020d3568; */
const int data_ov272_020d3568[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov272_Construct (020cfc6c): KindTable data_ov272_020d3578; */
const int data_ov272_020d3578[5] = {
    1, 2, 3, 4, 5,
};
