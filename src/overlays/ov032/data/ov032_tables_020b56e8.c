/* ov032 .rodata tables, 0x020b56e8-0x020b5724.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Shot step of the ov032 enemy (and its byte-identical twins): on the local player both 64-b (020b51a8): Vec3 data_ov032_020b56e8; */
const u8 data_ov032_020b56e8[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by Shot step of the ov032 enemy (and its byte-identical twins): on the local player both 64-b (020b51a8): Vec3 data_ov032_020b56f4; */
const u8 data_ov032_020b56f4[12] = {
    31, 1, 0, 0, 20, 22, 0, 0, 246, 16, 0, 0,
};

/* read by Spawns the ov032 enemy's two attachment effects (and its byte-identical twins): for each o (020b4034): const struct Masks data_ov032_020b5700; */
const u8 data_ov032_020b5700[16] = {
    0, 0, 0, 0, 0, 64, 0, 0, 0, 0, 0, 0, 0, 128, 0, 0,
};

/* read by Scene setup of the ov032 mission (and its byte-identical twins): opens layers 0 and 1 of (020b3524): Params data_ov032_020b5710; */
const int data_ov032_020b5710[5] = {
    0, 2, 0, 0, 7,
};
