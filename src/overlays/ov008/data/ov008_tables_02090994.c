/* ov008 .data tables, 0x02090994-0x020909a4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090994: func_ov008_02076780
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090994[16] = {
    37, 0, 49, 0, 100, 0, 47, 0, 37, 0, 49, 0, 100, 0, 0, 0,
};
