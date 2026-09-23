/* ov223 .rodata tables, 0x020d50c4-0x020d50f8.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov223_020cfdbc (not yet decompiled) */
const u8 data_ov223_020d50c4[32] = {
    25, 0, 0, 0, 27, 0, 0, 0, 28, 0, 0, 0, 29, 0, 0, 0,
    30, 0, 0, 0, 255, 255, 255, 255, 35, 0, 0, 0, 34, 0, 0, 0,
};

/* read by Ov223_HandleHit (020d0708): const struct Ov223ReactionModes data_ov223_020d50e4; */
const u8 data_ov223_020d50e4[16] = {
    2, 3, 0, 1, 0, 144, 0, 0, 51, 37, 0, 0, 51, 99, 0, 0,
};

/* read by func_ov223_020d3e58 (not yet decompiled) */
const int data_ov223_020d50f4[1] = {
    33,
};
