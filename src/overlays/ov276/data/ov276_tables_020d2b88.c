/* ov276 .rodata tables, 0x020d2b88-0x020d2c04.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov276_020cfcf8 (020cfcf8): void data_ov276_020d2b88(void); */
const int data_ov276_020d2b88[6] = {
    0, 24, 25, 26, 27, 28,
};

/* read by Rebuild the +0x384 work list for the actor at *(+0x3a8): copy the const pose table to (020d044c): const struct Buf_020ce7fc data_ov276_020d2ba0; */
const int data_ov276_020d2ba0[22] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22,
};

/* read by Hit handler of the ov276 enemy: ignored while the +0x21a stamina is spent. With a source (020d0560): const struct ModeTable data_ov276_020d2bf8; */
const u8 data_ov276_020d2bf8[12] = {
    2, 3, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0,
};
