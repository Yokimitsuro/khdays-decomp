/* ov025 .data tables, 0x020b5410-0x020b5474.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b5410: func_ov025_020aa298
 *   data_ov025_020b5414: func_ov025_020aa298
 *   data_ov025_020b5438: func_ov025_020aa298
 *   data_ov025_020b5444: func_ov025_020aa298
 *   data_ov025_020b545c: func_ov025_020ab01c
 *   data_ov025_020b5460: func_ov025_020ab01c
 *   data_ov025_020b5464: func_ov025_020abdd8
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov025_020b5410[1] = {
    10,
};

u8 data_ov025_020b5414[36] = {
    37, 0, 115, 0, 32, 0, 37, 0, 48, 0, 50, 0, 100, 0, 58, 0,
    37, 0, 48, 0, 50, 0, 100, 0, 58, 0, 37, 0, 48, 0, 50, 0,
    100, 0, 0, 0,
};

u8 data_ov025_020b5438[12] = {
    37, 0, 115, 0, 32, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov025_020b5444[24] = {
    37, 0, 115, 0, 32, 0, 45, 0, 45, 0, 45, 0, 45, 0, 45, 0,
    45, 0, 45, 0, 45, 0, 0, 0,
};

int data_ov025_020b545c[1] = {
    32,
};

int data_ov025_020b5460[1] = {
    47,
};

u8 data_ov025_020b5464[16] = {
    37, 0, 48, 0, 50, 0, 100, 0, 37, 0, 99, 0, 0, 0, 0, 0,
};
