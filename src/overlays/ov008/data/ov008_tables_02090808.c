/* ov008 .data tables, 0x02090808-0x02090818.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090808: func_ov008_0206d1b0
 *   data_ov008_02090814: func_ov008_0206d46c
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090808[12] = {
    37, 0, 100, 0, 47, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov008_02090814[4] = {
    252, 48, 0, 0,
};
