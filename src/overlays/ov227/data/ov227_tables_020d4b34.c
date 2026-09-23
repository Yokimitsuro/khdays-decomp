/* ov227 .rodata tables, 0x020d4b34-0x020d4b74.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov227_020cfdbc (not yet decompiled) */
const u8 data_ov227_020d4b34[32] = {
    28, 0, 0, 0, 255, 255, 255, 255, 255, 255, 255, 255, 32, 0, 0, 0,
    33, 0, 0, 0, 255, 255, 255, 255, 36, 0, 0, 0, 35, 0, 0, 0,
};

/* read by Ov227_HandleHit (020d0720): const struct Ov227ReactionModes data_ov227_020d4b54; */
const u8 data_ov227_020d4b54[24] = {
    0, 1, 2, 3, 0, 224, 1, 0, 0, 144, 0, 0, 51, 3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Ov227_PartConstruct (020d3e40): IdPair data_ov227_020d4b6c; */
const int data_ov227_020d4b6c[2] = {
    29, 31,
};
