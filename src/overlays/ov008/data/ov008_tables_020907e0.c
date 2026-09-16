/* ov008 .data tables, 0x020907e0-0x020907f0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_020907e0: func_ov008_0206c36c, func_ov008_0206d21c
 *   data_ov008_020907e8: func_ov008_0206c36c, func_ov008_0206d14c
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_020907e0[8] = {
    37, 0, 43, 0, 100, 0, 0, 0,
};

u8 data_ov008_020907e8[8] = {
    37, 0, 100, 0, 0, 0, 0, 0,
};
