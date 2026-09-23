/* ov069 .rodata tables, 0x020ba7d0-0x020ba7ec.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

const u8 data_ov069_020ba7d0[8] = {
    93, 2, 252, 0, 200, 1, 255, 255,
};

const u16 data_ov069_020ba7d8[5] = {
    405, 1351, 455, 1006, 65535,
};

const u16 data_ov069_020ba7e2[5] = {
    402, 157, 451, 452, 65535,
};
