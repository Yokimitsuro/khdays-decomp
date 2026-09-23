/* ov165 .rodata tables, 0x020d4a94-0x020d4b08.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d1a24): struct v5 data_ov165_020d4a94; */
const int data_ov165_020d4a94[5] = {
    2, 3, 5, 6, 10,
};

/* read by func_ov165_020d337c (020d337c): unsigned short data_ov165_020d4aa8[];
 *   Enter the recoil state, unless the gate byte at state[0x16] says otherwise: play the (020d39c4): unsigned short data_ov165_020d4aa8[]; */
const u8 data_ov165_020d4aa8[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d3df4): const struct Msg data_ov165_020d4ab0; */
const u16 data_ov165_020d4ab0[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d3448): const struct Msg data_ov165_020d4abe; */
const u16 data_ov165_020d4abe[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d3df4): const struct Msg data_ov165_020d4acc; */
const u16 data_ov165_020d4acc[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d3c28): const struct Msg data_ov165_020d4ada; */
const u16 data_ov165_020d4ada[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov165_020d20dc (020d20dc): const struct tbl8 data_ov165_020d4ae8; */
const u8 data_ov165_020d4ae8[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
