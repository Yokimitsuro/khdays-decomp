/* ov229 .rodata tables, 0x020d686c-0x020d691c.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov229_020d1b18 (not yet decompiled) */
const int data_ov229_020d686c[10] = {
    0, 29, 30, 31, 32, 33, 34, 37,
    38, 39,
};

/* read by Rebuild the +0x384 work list for the actor at *(+0x3a8): copy the const pose table to (020d243c): const struct Buf_020ce7fc data_ov229_020d6894; */
const int data_ov229_020d6894[27] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27,
};

/* read by Hit handler of the ov228 enemy (x2 with ov229): ignored while the +0x21a stamina is spent. (020d2550): const struct ModeTable data_ov229_020d6900; */
const u8 data_ov229_020d6900[24] = {
    0, 1, 2, 3, 0, 96, 0, 0, 184, 3, 0, 0, 248, 7, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
};

/* read by func_ov229_020d5cb8 (not yet decompiled) */
const int data_ov229_020d6918[1] = {
    35,
};
