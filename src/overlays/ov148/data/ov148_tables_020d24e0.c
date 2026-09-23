/* ov148 .rodata tables, 0x020d24e0-0x020d24f0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov148_020d0440 (020d0440): const struct ReactionModes data_ov148_020d24e0; */
const u8 data_ov148_020d24e0[8] = {
    2, 3, 0, 1, 96, 8, 0, 0,
};

/* read by func_ov148_020d1974 (020d1974): const struct ChildIds data_ov148_020d24e8; */
const int data_ov148_020d24e8[2] = {
    3, 5,
};
