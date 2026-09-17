/* ov025 .rodata tables, 0x020b4968-0x020b49a0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4968: func_ov025_020afef4
 *   data_ov025_020b4978: func_ov025_020b0090
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b4968[4] = {
    0, 2, 0, 0,
};

const int data_ov025_020b4978[10] = {
    0, 0, 32, 24, 0, 15, 0, 21,
    0, 32,
};
