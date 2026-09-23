/* ov253 .rodata tables, 0x020d4894-0x020d4940.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov253_020ccd00 (not yet decompiled) */
const int data_ov253_020d4894[13] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13,
};

/* read by func_ov253_020ccd00 (not yet decompiled) */
const int data_ov253_020d48c8[13] = {
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24, 25, 26, 27,
};

/* read by recover entry: sends message data_ov253_020d48fc (kind 4) to the (020cd9e8): const struct hpair data_ov253_020d48fc; */
const u8 data_ov253_020d48fc[4] = {
    0, 0, 5, 1,
};

/* read by func_ov253_020cda5c (not yet decompiled) */
const u8 data_ov253_020d4900[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by facing tick: the +0x30 delay runs down while non-negative; the +0xc (020cd484): const struct Ov253Axes data_ov253_020d4910; */
const u8 data_ov253_020d4910[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0, 0, 16, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 240, 255, 255, 0, 240, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};
