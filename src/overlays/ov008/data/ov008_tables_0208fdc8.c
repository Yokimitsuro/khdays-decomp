/* ov008 .rodata tables, 0x0208fdc8-0x0208fec8.
 *
 * 12 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208fdc8: func_ov008_0207dfec, func_ov008_02080d28
 *   data_ov008_0208fe60: func_ov008_020846c0
 *   data_ov008_0208fe64: func_ov008_02088d44
 *   data_ov008_0208fe6c: func_ov008_02088410
 *   data_ov008_0208fe74: func_ov008_02086e7c, func_ov008_02089428
 *   data_ov008_0208fe78: func_ov008_02089428
 *   data_ov008_0208fe7c: func_ov008_02088410
 *   data_ov008_0208fe84: func_ov008_02088d44
 *   data_ov008_0208fe88: func_ov008_02088d44
 *   data_ov008_0208fe98: func_ov008_02087e14
 *   data_ov008_0208fea7: func_ov008_02088d44
 *   data_ov008_0208feb8: func_ov008_020846c0
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov008_0208fdc8[38] = {
    32, 64, 56, 64, 80, 64, 104, 64,
    128, 64, 152, 64, 176, 64, 200, 64,
    224, 64, 20, 128, 44, 128, 68, 128,
    92, 128, 116, 128, 140, 128, 164, 128,
    188, 128, 212, 128, 236, 128,
};

const u8 data_ov008_0208fe60[4] = {
    0, 0, 1, 0,
};

const u8 data_ov008_0208fe64[8] = {
    32, 0, 64, 0, 16, 0, 128, 0,
};

const u8 data_ov008_0208fe6c[8] = {
    40, 24, 160, 16, 24, 24, 192, 16,
};

const u8 data_ov008_0208fe74[4] = {
    32, 104, 96, 16,
};

const u8 data_ov008_0208fe78[4] = {
    128, 104, 96, 16,
};

const u8 data_ov008_0208fe7c[8] = {
    200, 24, 16, 128, 216, 24, 16, 128,
};

const u8 data_ov008_0208fe84[4] = {
    32, 117, 96, 16,
};

const u8 data_ov008_0208fe88[16] = {
    128, 117, 96, 16, 255, 255, 0, 0, 1, 0, 5, 0, 4, 0, 6, 0,
};

const u8 data_ov008_0208fe98[15] = {
    0, 0, 1, 4, 4, 0, 0, 1, 2, 4, 0, 1, 2, 3, 4,
};

const u8 data_ov008_0208fea7[17] = {
    80, 88, 16, 16, 104, 76, 16, 16, 120, 88, 16, 16, 101, 100, 16, 16,
    0,
};

const u8 data_ov008_0208feb8[16] = {
    255, 255, 0, 0, 3, 0, 1, 0, 5, 0, 4, 0, 6, 0, 2, 0,
};
