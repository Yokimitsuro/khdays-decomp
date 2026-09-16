/* ov008 .data tables, 0x02090050-0x02090064.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090050: func_ov008_0205005c
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090050[20] = {
    85, 73, 47, 99, 109, 47, 99, 109, 111, 95, 38, 46, 112, 50, 0, 0,
    255, 255, 255, 255,
};
