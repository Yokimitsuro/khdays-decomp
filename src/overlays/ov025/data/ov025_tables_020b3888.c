/* ov025 .rodata tables, 0x020b3888-0x020b3924.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b3888: (no C reader yet)
 *   data_ov025_020b3894: (no C reader yet)
 *   data_ov025_020b38b8: (no C reader yet)
 *   data_ov025_020b38d4: func_ov025_0208bca0
 *   data_ov025_020b38fc: func_ov025_0208bca0
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b3888[3] = {
    7, 2, 2,
};

const int data_ov025_020b3894[9] = {
    0, 1, 0, 0, 1, 2, 3, 4,
    5,
};

const int data_ov025_020b38b8[7] = {
    1, 2, 5, 3, 4, 6, 9,
};

const int data_ov025_020b38d4[10] = {
    0, 0, 32, 2, 0, 15, 0, 5,
    0, 32,
};

const int data_ov025_020b38fc[10] = {
    19, 0, 32, 4, 65, 15, 0, 5,
    0, 32,
};
