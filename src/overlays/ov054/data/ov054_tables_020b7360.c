/* ov054 .rodata tables, 0x020b7360-0x020b7378.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov054_020b66f0 (020b66f0): Vec3 data_ov054_020b7360; */
const u8 data_ov054_020b7360[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by func_ov054_020b6544 (020b6544): Vec3 data_ov054_020b736c; */
const u8 data_ov054_020b736c[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};
