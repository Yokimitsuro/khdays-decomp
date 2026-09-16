/* ov008 .data tables, 0x02090108-0x02090148.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090108: func_ov008_02056ec0
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov008_02090108[16] = {
    7, 8, 8, 8, 9, 8, 10, 8,
    11, 8, 12, 8, 13, 8, 14, 8,
};
