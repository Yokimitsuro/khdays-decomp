/* ov254 .rodata tables, 0x020d5914-0x020d597c.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov254_020cbfc8 (not yet decompiled) */
const u8 data_ov254_020d5914[24] = {
    0, 176, 255, 255, 0, 96, 255, 255, 0, 176, 255, 255, 0, 80, 0, 0,
    0, 160, 0, 0, 0, 80, 0, 0,
};

/* read by func_ov254_020cbfc8 (not yet decompiled) */
const int data_ov254_020d592c[8] = {
    63, 64, 72, 73, 76, 78, 79, 80,
};

/* read by Ov254_HitFilter (020cd984): const struct ReactionModes data_ov254_020d594c; */
const u8 data_ov254_020d594c[48] = {
    0, 1, 2, 3, 64, 21, 0, 0, 3, 0, 0, 0, 64, 21, 0, 0,
    207, 100, 1, 0, 80, 22, 0, 0, 128, 42, 0, 0, 96, 6, 0, 0,
    128, 42, 0, 0, 8, 0, 0, 0, 128, 42, 0, 0, 152, 61, 0, 0,
};
