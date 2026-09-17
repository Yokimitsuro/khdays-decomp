/* ov025 .rodata tables, 0x020b3808-0x020b3870.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b3808: func_ov025_020858d0
 *   data_ov025_020b3858: func_ov025_02088b7c
 *   data_ov025_020b385c: func_ov025_02088b7c
 *   data_ov025_020b3860: (no C reader yet)
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b3808[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

const u8 data_ov025_020b3858[4] = {
    8, 9, 10, 11,
};

const u8 data_ov025_020b385c[4] = {
    24, 25, 26, 27,
};

const int data_ov025_020b3860[4] = {
    12, 13, 10, 11,
};
