/* ov164 .rodata tables, 0x020d2c74-0x020d2ce8.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cfc04): struct v5 data_ov164_020d2c74; */
const int data_ov164_020d2c74[5] = {
    2, 3, 5, 6, 10,
};

/* read by func_ov164_020d155c (020d155c): unsigned short data_ov164_020d2c88[];
 *   Enter the recoil state, unless the gate byte at state[0x16] says otherwise: play the (020d1ba4): unsigned short data_ov164_020d2c88[]; */
const u8 data_ov164_020d2c88[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d1fd4): const struct Msg data_ov164_020d2c90; */
const u16 data_ov164_020d2c90[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d1628): const struct Msg data_ov164_020d2c9e; */
const u16 data_ov164_020d2c9e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from the matched ov202 sibling (same shape: throw-release tick with the 0xc00 guard (020d1fd4): const struct Msg data_ov164_020d2cac; */
const u16 data_ov164_020d2cac[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d1e08): const struct Msg data_ov164_020d2cba; */
const u16 data_ov164_020d2cba[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov164_020d02bc (020d02bc): const struct tbl8 data_ov164_020d2cc8; */
const u8 data_ov164_020d2cc8[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
