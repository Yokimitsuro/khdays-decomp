/* ov232 .rodata tables, 0x020d3674-0x020d3698.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by chase tick of the ov231 enemy (x5 with ov232/ov263/ov265/ov280). The +0x18 (020d1150): const Vec3 data_ov232_020d3674; */
const u8 data_ov232_020d3674[12] = {
    0, 0, 0, 0, 0, 144, 255, 255, 0, 0, 0, 0,
};

/* read by decide which way to sidestep, then hand off to func_ov232_020d18d0. (020d16e8): VecFx32 data_ov232_020d3680; */
const u8 data_ov232_020d3680[12] = {
    0, 176, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by AI hover-dive step (byte-identical in ov232 / (020d197c): const Vec3 data_ov232_020d368c; */
const int data_ov232_020d368c[3] = {
    0, 0, 2048,
};
