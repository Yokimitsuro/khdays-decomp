/* ov008 .data tables, 0x0209088c-0x0209089c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0209088c: func_ov008_0206ff24
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov008_0209088c[16] = {
    37, 0, 49, 0, 100, 0, 47, 0, 37, 0, 49, 0, 100, 0, 0, 0,
};
