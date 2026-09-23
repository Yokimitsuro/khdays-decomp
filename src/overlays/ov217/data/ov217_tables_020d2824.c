/* ov217 .rodata tables, 0x020d2824-0x020d2868.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cfe50): KindTable data_ov217_020d2824; */
const int data_ov217_020d2824[5] = {
    0, 11, 12, 13, 15,
};

/* read by func_ov217_020d0634 (020d0634): int data_ov217_020d2838[]; */
const int data_ov217_020d2838[9] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d0708): u8 data_ov217_020d285c[]; */
const u8 data_ov217_020d285c[12] = {
    2, 3, 0, 1, 248, 7, 0, 0, 205, 76, 0, 0,
};
