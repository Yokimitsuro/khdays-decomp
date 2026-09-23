/* ov162 .rodata tables, 0x020d1080-0x020d10f8.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cdde4): struct v5 data_ov162_020d1080; */
const int data_ov162_020d1080[6] = {
    2, 3, 4, 5, 6, 10,
};

/* read by func_ov162_020cfc98 (020cfc98): unsigned short data_ov162_020d1098[];
 *   Enter the recoil state of the ov161 enemy (x2: ov161/162), variant of the matched ov163 (020d02e4): unsigned short data_ov162_020d1098[]; */
const u8 data_ov162_020d1098[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by throw-release tick of the ov161 enemy (x2), ported from the matched ov202 sibling (radius  (020d07c4): const struct Msg data_ov162_020d10a0; */
const u16 data_ov162_020d10a0[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cfd64): const struct Msg data_ov162_020d10ae; */
const u16 data_ov162_020d10ae[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by throw-release tick of the ov161 enemy (x2), ported from the matched ov202 sibling (radius  (020d07c4): const struct Msg data_ov162_020d10bc; */
const u16 data_ov162_020d10bc[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020d05f8): const struct Msg data_ov162_020d10ca; */
const u16 data_ov162_020d10ca[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov162_020cea50 (020cea50): const struct tbl8 data_ov162_020d10d8; */
const u8 data_ov162_020d10d8[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
