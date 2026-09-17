/* ov025 .data tables, 0x020b5270-0x020b5284.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b5270: (no C reader yet)
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b5270[20] = {
    63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0, 63, 0,
    0, 0, 0, 0,
};
