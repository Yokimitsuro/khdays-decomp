/* ov035 .rodata tables, 0x020b4b60-0x020b4b78.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov035_020b3ef0 (020b3ef0): Vec3 data_ov035_020b4b60; */
const u8 data_ov035_020b4b60[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by func_ov035_020b3d44 (020b3d44): Vec3 data_ov035_020b4b6c; */
const u8 data_ov035_020b4b6c[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};
