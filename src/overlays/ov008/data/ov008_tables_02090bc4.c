/* ov008 .data tables, 0x02090bc4-0x02090bd4.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090bc4: func_ov008_02079d60, func_ov008_0207b70c
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090bc4[16] = {
    45, 0, 45, 0, 45, 0, 45, 0, 45, 0, 45, 0, 0, 0, 0, 0,
};
