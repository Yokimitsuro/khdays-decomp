/* ov263 .rodata tables, 0x020d3698-0x020d36bc.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov263_ChaseTick (020d1170): const Vec3 data_ov263_020d3698; */
const u8 data_ov263_020d3698[12] = {
    0, 0, 0, 0, 0, 144, 255, 255, 0, 0, 0, 0,
};

/* read by decide which way to sidestep, then hand off to func_ov263_020d18f0. (020d1708): VecFx32 data_ov263_020d36a4; */
const u8 data_ov263_020d36a4[12] = {
    0, 176, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by AI hover-dive step (byte-identical in ov232 / (020d199c): const Vec3 data_ov263_020d36b0; */
const int data_ov263_020d36b0[3] = {
    0, 0, 2048,
};
