/* ov025 .data tables, 0x020b4d90-0x020b4dbc.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov025_020b4d90: (no C reader yet)
 *   data_ov025_020b4d9c: (no C reader yet)
 *   data_ov025_020b4da8: (no C reader yet)
 *   data_ov025_020b4dac: (no C reader yet)
 *   data_ov025_020b4db4: (no C reader yet)
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov025_020b4d90[12] = {
    37, 0, 100, 0, 47, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov025_020b4d9c[12] = {
    37, 0, 115, 0, 47, 0, 37, 0, 115, 0, 0, 0,
};

int data_ov025_020b4da8[1] = {
    45,
};

u8 data_ov025_020b4dac[8] = {
    37, 0, 100, 0, 0, 0, 0, 0,
};

u8 data_ov025_020b4db4[8] = {
    37, 0, 115, 0, 0, 0, 0, 0,
};
