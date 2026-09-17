/* ov025 .rodata tables, 0x020b3c70-0x020b3cac.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b3c70: func_ov025_02090140
 *   data_ov025_020b3c78: (no C reader yet)
 *   data_ov025_020b3c84: func_ov025_02095cbc
 *   data_ov025_020b3c90: func_ov025_0208fae0
 *   data_ov025_020b3c9c: func_ov025_0209522c
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b3c70[2] = {
    62, 63,
};

const int data_ov025_020b3c78[3] = {
    16, 17, 18,
};

const int data_ov025_020b3c84[3] = {
    6, 5, 4,
};

const int data_ov025_020b3c90[3] = {
    4, 3, 0,
};

const int data_ov025_020b3c9c[4] = {
    72, 73, 70, 71,
};
