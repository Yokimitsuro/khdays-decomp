/* ov147 .rodata tables, 0x020ce8a0-0x020ce8b0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov147_020cc800 (020cc800): const struct ReactionModes data_ov147_020ce8a0; */
const u8 data_ov147_020ce8a0[8] = {
    2, 3, 0, 1, 96, 8, 0, 0,
};

/* read by func_ov147_020cdd34 (020cdd34): const struct ChildIds data_ov147_020ce8a8; */
const int data_ov147_020ce8a8[2] = {
    3, 5,
};
