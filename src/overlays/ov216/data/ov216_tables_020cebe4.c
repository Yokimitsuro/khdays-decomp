/* ov216 .rodata tables, 0x020cebe4-0x020cec28.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cc210): KindTable data_ov216_020cebe4; */
const int data_ov216_020cebe4[5] = {
    0, 11, 12, 13, 15,
};

/* read by func_ov216_020cc9f4 (020cc9f4): int data_ov216_020cebf8[]; */
const int data_ov216_020cebf8[9] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020ccac8): u8 data_ov216_020cec1c[]; */
const u8 data_ov216_020cec1c[12] = {
    2, 3, 0, 1, 248, 7, 0, 0, 205, 76, 0, 0,
};
