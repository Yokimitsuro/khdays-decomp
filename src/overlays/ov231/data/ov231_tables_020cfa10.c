/* ov231 .rodata tables, 0x020cfa10-0x020cfa30.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov231_Construct (020cbfc8): KindTable data_ov231_020cfa10; */
const int data_ov231_020cfa10[8] = {
    18, 19, 20, 21, 22, 23, 24, 25,
};
