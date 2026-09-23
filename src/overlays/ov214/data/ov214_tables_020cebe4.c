/* ov214 .rodata tables, 0x020cebe4-0x020cec28.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov214_020cc1fc (020cc1fc): KindTable data_ov214_020cebe4; */
const int data_ov214_020cebe4[5] = {
    0, 11, 12, 13, 15,
};

/* read by func_ov214_020cc9e0 (020cc9e0): int data_ov214_020cebf8[]; */
const int data_ov214_020cebf8[9] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9,
};

/* read by func_ov214_020ccab4 (020ccab4): u8 data_ov214_020cec1c[]; */
const u8 data_ov214_020cec1c[12] = {
    2, 3, 0, 1, 248, 7, 0, 0, 102, 62, 0, 0,
};
