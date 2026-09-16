/* ov008 .rodata tables, 0x0208fedc-0x0208ff6c.
 *
 * 10 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208fedc: func_ov008_02083464, func_ov008_02083588, func_ov008_02087e14
 *   data_ov008_0208fedd: func_ov008_02083588
 *   data_ov008_0208fef0: func_ov008_02082714
 *   data_ov008_0208fef1: func_ov008_02082714
 *   data_ov008_0208fef2: func_ov008_0208247c
 *   data_ov008_0208fef3: func_ov008_02082714
 *   data_ov008_0208ff04: func_ov008_020823ec
 *   data_ov008_0208ff20: func_ov008_02083c44
 *   data_ov008_0208ff3c: func_ov008_02088410
 *   data_ov008_0208ff64: func_ov008_0208b4ac
 */

typedef unsigned char u8;
typedef unsigned short u16;

const u8 data_ov008_0208fedc[1] = {
    80,
};

const u8 data_ov008_0208fedd[19] = {
    24, 96, 16, 80, 48, 96, 16, 80, 72, 96, 16, 80, 96, 96, 16, 80,
    120, 96, 16,
};

const u8 data_ov008_0208fef0[1] = {
    0,
};

const u8 data_ov008_0208fef1[1] = {
    4,
};

const u8 data_ov008_0208fef2[1] = {
    9,
};

const u8 data_ov008_0208fef3[17] = {
    13, 255, 5, 255, 14, 1, 6, 10, 15, 2, 7, 11, 16, 3, 8, 12,
    17,
};

const int data_ov008_0208ff04[7] = {
    9, 10, 11, 24, 25, 26, 27,
};

const int data_ov008_0208ff20[7] = {
    20, 22, 25, 23, 21, 24, 26,
};

const u8 data_ov008_0208ff3c[40] = {
    32, 0, 24, 20, 56, 0, 24, 20, 80, 0, 24, 20, 104, 0, 24, 20,
    128, 0, 24, 20, 152, 0, 24, 20, 176, 0, 24, 20, 200, 0, 24, 20,
    16, 0, 40, 20, 56, 0, 40, 20,
};

const int data_ov008_0208ff64[2] = {
    32, 32,
};
