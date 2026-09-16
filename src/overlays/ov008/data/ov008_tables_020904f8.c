/* ov008 .data tables, 0x020904f8-0x02090554.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_020904f8: func_ov008_02069570
 *   data_ov008_02090504: func_ov008_02069b7c, func_ov008_02069b94
 *   data_ov008_0209051c: func_ov008_02069b60
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_020904f8[12] = {
    37, 0, 48, 0, 50, 0, 100, 0, 0, 0, 0, 0,
};

u8 data_ov008_02090504[24] = {
    0, 0, 3, 0, 3, 0, 4, 0, 7, 0, 3, 0, 10, 0, 5, 0,
    15, 0, 5, 0, 20, 0, 5, 0,
};

u8 data_ov008_0209051c[56] = {
    0, 0, 3, 0, 1, 2, 0, 0, 1, 2, 3, 0, 0, 4, 5, 6,
    0, 0, 11, 0, 5, 0, 1, 3, 4, 5, 1, 14, 15, 16, 17, 4,
    20, 21, 22, 23, 10, 0, 2, 0, 1, 0, 0, 0, 1, 12, 0, 0,
    0, 4, 18, 0, 0, 0, 0, 0,
};
