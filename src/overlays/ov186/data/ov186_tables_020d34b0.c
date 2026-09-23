/* ov186 .rodata tables, 0x020d34b0-0x020d34dc.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov186_020cfc08 (020cfc08): const struct CameraWork data_ov186_020d34b0; */
const int data_ov186_020d34b0[4] = {
    0, 0, 0, 3072,
};

/* read by func_ov186_020d2b7c (020d2b7c): Pair data_ov186_020d34c0[];
 *   Publish the landing: copy the pending anchor into the live slot and ask the placement help (020d2d1c): Ev data_ov186_020d34c0[];
 *   func_ov186_020d3014 (020d3014): Pair16 data_ov186_020d34c0[]; */
const u8 data_ov186_020d34c0[12] = {
    0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
};

/* read by func_ov186_020d184c (020d184c): const struct CameraWork data_ov186_020d34cc; */
const int data_ov186_020d34cc[4] = {
    0, 0, 0, 2560,
};
