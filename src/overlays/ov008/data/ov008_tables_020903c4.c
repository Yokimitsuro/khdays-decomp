/* ov008 .data tables, 0x020903c4-0x020903f0.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_020903c4: func_ov008_0205cde8
 *   data_ov008_020903d0: func_ov008_0205cde8
 *   data_ov008_020903dc: func_ov008_0205cde8
 *   data_ov008_020903e0: func_ov008_0205cde8
 *   data_ov008_020903e8: func_ov008_0205cde8
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_020903c4[12] = {
    37, 0, 100, 0, 47, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov008_020903d0[12] = {
    37, 0, 115, 0, 47, 0, 37, 0, 115, 0, 0, 0,
};

int data_ov008_020903dc[1] = {
    45,
};

u8 data_ov008_020903e0[8] = {
    37, 0, 100, 0, 0, 0, 0, 0,
};

u8 data_ov008_020903e8[8] = {
    37, 0, 115, 0, 0, 0, 0, 0,
};
