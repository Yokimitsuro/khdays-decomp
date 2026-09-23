/* ov052 .rodata tables, 0x020b7ee8-0x020b7f24.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Shot step of the ov032 enemy (and its byte-identical twins): on the local player both 64-b (020b79a8): Vec3 data_ov052_020b7ee8; */
const u8 data_ov052_020b7ee8[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by Shot step of the ov032 enemy (and its byte-identical twins): on the local player both 64-b (020b79a8): Vec3 data_ov052_020b7ef4; */
const u8 data_ov052_020b7ef4[12] = {
    31, 1, 0, 0, 20, 22, 0, 0, 246, 16, 0, 0,
};

/* read by Spawns the ov032 enemy's two attachment effects (and its byte-identical twins): for each o (020b6834): const struct Masks data_ov052_020b7f00; */
const u8 data_ov052_020b7f00[16] = {
    0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0,
};

/* read by Scene setup of the ov032 mission (and its byte-identical twins): opens layers 0 and 1 of (020b5d24): Params data_ov052_020b7f10; */
const int data_ov052_020b7f10[5] = {
    0, 2, 0, 0, 7,
};
