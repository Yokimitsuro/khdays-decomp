/* ov025 .data tables, 0x020b4a64-0x020b4a78.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4a64: func_ov025_02083e84
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b4a64[20] = {
    85, 73, 47, 99, 109, 47, 99, 109, 111, 95, 38, 46, 112, 50, 0, 0,
    255, 255, 255, 255,
};
