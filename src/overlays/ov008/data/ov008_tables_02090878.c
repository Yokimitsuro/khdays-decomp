/* ov008 .data tables, 0x02090878-0x02090888.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_02090878: func_ov008_0206ff24
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_02090878[16] = {
    37, 0, 48, 0, 50, 0, 100, 0, 37, 0, 99, 0, 0, 0, 0, 0,
};
