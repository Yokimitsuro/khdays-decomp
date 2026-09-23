/* ov199 .rodata tables, 0x020d6114-0x020d6124.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov199_020d4078 (020d4078): const struct ReactionModes data_ov199_020d6114; */
const u8 data_ov199_020d6114[8] = {
    2, 3, 0, 1, 96, 8, 0, 0,
};

/* read by func_ov199_020d55a8 (020d55a8): const struct ChildIds data_ov199_020d611c; */
const int data_ov199_020d611c[2] = {
    3, 5,
};
