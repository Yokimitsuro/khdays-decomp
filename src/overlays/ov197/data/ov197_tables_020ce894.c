/* ov197 .rodata tables, 0x020ce894-0x020ce8a4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov197_020cc7f8 (020cc7f8): const struct ReactionModes data_ov197_020ce894; */
const u8 data_ov197_020ce894[8] = {
    2, 3, 0, 1, 96, 8, 0, 0,
};

/* read by func_ov197_020cdd28 (020cdd28): const struct ChildIds data_ov197_020ce89c; */
const int data_ov197_020ce89c[2] = {
    3, 5,
};
