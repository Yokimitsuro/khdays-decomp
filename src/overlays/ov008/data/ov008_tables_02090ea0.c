/* ov008 .data tables, 0x02090ea0-0x02090ed4.
 *
 * 6 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090ea0: func_ov008_02082d98
 *   data_ov008_02090ea8: func_ov008_02082df0
 *   data_ov008_02090eb0: func_ov008_02084b10
 *   data_ov008_02090eb8: func_ov008_02084b10
 *   data_ov008_02090ecc: (no C reader yet)
 *   data_ov008_02090ed0: (no C reader yet)
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090ea0[8] = {
    37, 0, 100, 0, 0, 0, 0, 0,
};

u8 data_ov008_02090ea8[8] = {
    37, 0, 51, 0, 100, 0, 0, 0,
};

u8 data_ov008_02090eb0[8] = {
    63, 0, 63, 0, 0, 0, 0, 0,
};

u8 data_ov008_02090eb8[20] = {
    63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0,
    0, 0, 0, 0,
};

int data_ov008_02090ecc[1] = {
    91,
};

int data_ov008_02090ed0[1] = {
    93,
};
