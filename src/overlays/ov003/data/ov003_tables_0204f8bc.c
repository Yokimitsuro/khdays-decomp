/* ov003 .data tables, 0x0204f8bc-0x0204f8e4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

signed char data_ov003_0204f8bc[20] = {
    32, 24, 12, 22, 14, -1, 26, -1, 18, -1,
    29, 37, 16, 10, 34, 20, -1, -1, -1, 0,
};

signed char data_ov003_0204f8d0[20] = {
    31, 23, 11, 21, 13, 35, 25, 30, 17, 27,
    28, 36, 15, 9, 33, 19, 40, 38, 39, 0,
};
