/* ov008 .data tables, 0x0209018c-0x020901fc.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0209018c: func_ov008_02056ec0
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov008_0209018c[28] = {
    7, 3, 8, 1, 9, 1, 10, 1,
    11, 3, 13, 1, 14, 3, 16, 1,
    17, 3, 18, 1, 19, 1, 111, 2,
    114, 2, 117, 2,
};
