/* ov004 .rodata tables, 0x020510b0-0x020510b8.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov004_0204fd60 (0204fd60): char data_ov004_020510b0[]; */
const u8 data_ov004_020510b0[8] = {
    0, 0, 255, 127, 0, 0, 0, 0,
};
