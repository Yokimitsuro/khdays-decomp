/* ov025 .data tables, 0x020b5478-0x020b5488.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b5478: func_ov025_020abdd8
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b5478[16] = {
    37, 0, 49, 0, 100, 0, 47, 0, 37, 0, 49, 0, 100, 0, 0, 0,
};
