/* ov230 .rodata tables, 0x020d63b8-0x020d6468.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov230_020d1b18 (not yet decompiled) */
const int data_ov230_020d63b8[10] = {
    0, 29, 30, 31, 32, 33, 34, 37,
    38, 39,
};

/* read by Rebuild the +0x384 work list for the actor at *(+0x3a8): copy the const pose table to (020d243c): const struct Buf_020ce7fc data_ov230_020d63e0; */
const int data_ov230_020d63e0[27] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27,
};

/* read by Ov230_OnHit (020d2550): const struct ModeTable data_ov230_020d644c; */
const u8 data_ov230_020d644c[24] = {
    0, 1, 2, 3, 0, 96, 0, 0, 184, 3, 0, 0, 248, 7, 0, 0,
    1, 0, 0, 0, 1, 0, 0, 0,
};

/* read by func_ov230_020d5cdc (not yet decompiled) */
const int data_ov230_020d6464[1] = {
    36,
};
