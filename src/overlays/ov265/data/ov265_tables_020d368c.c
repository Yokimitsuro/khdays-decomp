/* ov265 .rodata tables, 0x020d368c-0x020d36b0.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov265_ChaseTick (020d1164): const Vec3 data_ov265_020d368c; */
const u8 data_ov265_020d368c[12] = {
    0, 0, 0, 0, 0, 144, 255, 255, 0, 0, 0, 0,
};

/* read by decide which way to sidestep, then hand off to func_ov265_020d18e4. (020d16fc): VecFx32 data_ov265_020d3698; */
const u8 data_ov265_020d3698[12] = {
    0, 176, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by AI hover-dive step (byte-identical in ov232 / (020d1990): const Vec3 data_ov265_020d36a4; */
const int data_ov265_020d36a4[3] = {
    0, 0, 2048,
};
