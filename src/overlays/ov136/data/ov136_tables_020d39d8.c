/* ov136 .rodata tables, 0x020d39d8-0x020d3a20.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov136_020d1a24 (020d1a24): struct v5 data_ov136_020d39d8; */
const int data_ov136_020d39d8[3] = {
    2, 3, 4,
};

/* read by func_ov136_020d37f0 (020d37f0): unsigned short data_ov136_020d39e4[]; */
const u8 data_ov136_020d39e4[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0,
};

/* read by * func_ov136_020d2f8c -- burst attack tick of the ov134 enemy (and its byte-identical twin (020d2f8c): struct Ov134AreaMsg data_ov136_020d39f4; */
const u16 data_ov136_020d39f4[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by * func_ov136_020d2f8c -- burst attack tick of the ov134 enemy (and its byte-identical twin (020d2f8c): struct Ov134AreaMsg data_ov136_020d3a02; */
const u16 data_ov136_020d3a02[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Attack tick of the ov134 enemy (x3: ov134/135/136). Counts the +0x30 timer and fires react (020d34b4): const struct Msg data_ov136_020d3a10; */
const u8 data_ov136_020d3a10[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
