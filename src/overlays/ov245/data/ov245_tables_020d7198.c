/* ov245 .rodata tables, 0x020d7198-0x020d71c4.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

const u8 data_ov245_020d7198[12] = {
    15, 228, 0, 0, 202, 2, 0, 0, 0, 128, 254, 255,
};

/* read by func_ov245_020cfa14 (not yet decompiled) */
const u8 data_ov245_020d71a4[8] = {
    2, 3, 0, 1, 0, 4, 0, 0,
};

/* read by func_ov245_020d2884 (not yet decompiled) */
const u8 data_ov245_020d71ac[4] = {
    28, 27, 37, 0,
};

/* read by constructor of the ov245 rider: installs the handlers (+8 tick, +0xc (020d5538): const struct PoolIds data_ov245_020d71b0; */
const int data_ov245_020d71b0[5] = {
    0, 0, 51, 52, 53,
};
