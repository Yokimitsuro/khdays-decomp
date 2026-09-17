/* ov025 .data tables, 0x020b4b30-0x020b4b70.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4b30: func_ov025_0208ab30
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov025_020b4b30[16] = {
    7, 8, 8, 8, 9, 8, 10, 8,
    11, 8, 12, 8, 13, 8, 14, 8,
};
