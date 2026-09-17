/* ov025 .rodata tables, 0x020b4598-0x020b46c0.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4598: func_ov025_020a62bc
 *   data_ov025_020b45a8: func_ov025_020a8d50
 *   data_ov025_020b45c0: func_ov025_020a7780
 *   data_ov025_020b45e8: func_ov025_020a7780
 *   data_ov025_020b4610: func_ov025_020a7780
 *   data_ov025_020b4638: func_ov025_020a7780
 *   data_ov025_020b4660: func_ov025_020a54c8
 *   data_ov025_020b4690: func_ov025_020a54c8
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov025_020b4598[4] = {
    47, 44, 45, 46,
};

const int data_ov025_020b45a8[6] = {
    1, 2, 11, 6, 7, 8,
};

const int data_ov025_020b45c0[10] = {
    0, 6, 15, 2, 288, 8, 0, 22,
    0, 32,
};

const int data_ov025_020b45e8[10] = {
    0, 25, 2, 2, 288, 8, 0, 22,
    0, 32,
};

const int data_ov025_020b4610[10] = {
    0, 22, 5, 2, 288, 8, 0, 22,
    0, 32,
};

const int data_ov025_020b4638[10] = {
    0, 6, 20, 2, 288, 8, 0, 22,
    0, 32,
};

const int data_ov025_020b4660[12] = {
    100, 105, 104, 101, 103, 106, 100, 100,
    107, 102, 100, 100,
};

const int data_ov025_020b4690[12] = {
    110, 115, 114, 111, 113, 116, 110, 110,
    117, 112, 110, 110,
};
