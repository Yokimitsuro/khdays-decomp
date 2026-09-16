/* ov008 .data tables, 0x02090d0c-0x02090d1c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090d0c: func_ov008_0207c518, func_ov008_0207c7c8
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090d0c[16] = {
    45, 0, 45, 0, 45, 0, 45, 0, 45, 0, 45, 0, 0, 0, 0, 0,
};
