/* ov163 .rodata tables, 0x020d0e54-0x020d0ec8.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cdde4): struct v5 data_ov163_020d0e54; */
const int data_ov163_020d0e54[5] = {
    2, 3, 5, 6, 10,
};

/* read by func_ov163_020cf73c (020cf73c): unsigned short data_ov163_020d0e68[];
 *   Enter the recoil state, unless the gate byte at state[0x16] says otherwise: play the (020cfd84): unsigned short data_ov163_020d0e68[]; */
const u8 data_ov163_020d0e68[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d01b4): const struct Msg data_ov163_020d0e70; */
const u16 data_ov163_020d0e70[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cf808): const struct Msg data_ov163_020d0e7e; */
const u16 data_ov163_020d0e7e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d01b4): const struct Msg data_ov163_020d0e8c; */
const u16 data_ov163_020d0e8c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cffe8): const struct Msg data_ov163_020d0e9a; */
const u16 data_ov163_020d0e9a[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov163_020ce49c (020ce49c): const struct tbl8 data_ov163_020d0ea8; */
const u8 data_ov163_020d0ea8[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
