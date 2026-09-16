/* ov008 .rodata tables, 0x0208e8a4-0x0208e8fc.
 *
 * 3 tables before the layout templates 02058df0.c owns (0x0208e8fc-0x0208e958),
 * each written in the width its contents are in: words where the values are
 * small integers, bytes where the words are packed bytes.
 *
 * Readers:
 *   data_ov008_0208e8a4: func_ov008_02051b20
 *   data_ov008_0208e8f4: func_ov008_02054ed4
 *   data_ov008_0208e8f8: func_ov008_02054ed4
 */

typedef unsigned char u8;

const int data_ov008_0208e8a4[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

const u8 data_ov008_0208e8f4[4] = {
    8, 9, 10, 11,
};

const u8 data_ov008_0208e8f8[4] = {
    24, 25, 26, 27,
};
