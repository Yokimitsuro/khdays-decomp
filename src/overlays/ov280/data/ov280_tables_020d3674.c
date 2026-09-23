/* ov280 .rodata tables, 0x020d3674-0x020d3694.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov280_Construct (020cfc08): KindTable data_ov280_020d3674; */
const int data_ov280_020d3674[8] = {
    18, 19, 20, 21, 22, 23, 24, 25,
};
