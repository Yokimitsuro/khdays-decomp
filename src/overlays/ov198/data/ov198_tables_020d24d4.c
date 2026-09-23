/* ov198 .rodata tables, 0x020d24d4-0x020d24e4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov198_020d0438 (020d0438): const struct ReactionModes data_ov198_020d24d4; */
const u8 data_ov198_020d24d4[8] = {
    2, 3, 0, 1, 96, 8, 0, 0,
};

/* read by func_ov198_020d1968 (020d1968): const struct ChildIds data_ov198_020d24dc; */
const int data_ov198_020d24dc[2] = {
    3, 5,
};
