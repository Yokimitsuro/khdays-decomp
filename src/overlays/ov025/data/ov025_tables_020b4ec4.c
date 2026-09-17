/* ov025 .data tables, 0x020b4ec4-0x020b4f20.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4ec4: func_ov025_0209b950
 *   data_ov025_020b4ed0: func_ov025_0209bf5c, func_ov025_0209bf74
 *   data_ov025_020b4ee8: func_ov025_0209bf40, func_ov025_0209c62c
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b4ec4[12] = {
    37, 0, 48, 0, 50, 0, 100, 0, 0, 0, 0, 0,
};

u8 data_ov025_020b4ed0[24] = {
    0, 0, 3, 0, 3, 0, 4, 0, 7, 0, 3, 0, 10, 0, 5, 0,
    15, 0, 5, 0, 20, 0, 5, 0,
};

u8 data_ov025_020b4ee8[56] = {
    0, 0, 3, 0, 1, 2, 0, 0, 1, 2, 3, 0, 0, 4, 5, 6,
    0, 0, 11, 0, 5, 0, 1, 3, 4, 5, 1, 14, 15, 16, 17, 4,
    20, 21, 22, 23, 10, 0, 2, 0, 1, 0, 0, 0, 1, 12, 0, 0,
    0, 4, 18, 0, 0, 0, 0, 0,
};
