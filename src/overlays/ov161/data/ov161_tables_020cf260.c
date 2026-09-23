/* ov161 .rodata tables, 0x020cf260-0x020cf2d8.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cbfc4): struct v5 data_ov161_020cf260; */
const int data_ov161_020cf260[6] = {
    2, 3, 4, 5, 6, 10,
};

/* read by func_ov161_020cde78 (020cde78): unsigned short data_ov161_020cf278[];
 *   Enter the recoil state of the ov161 enemy (x2: ov161/162), variant of the matched ov163 (020ce4c4): unsigned short data_ov161_020cf278[]; */
const u8 data_ov161_020cf278[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by throw-release tick of the ov161 enemy (x2), ported from the matched ov202 sibling (radius  (020ce9a4): const struct Msg data_ov161_020cf280; */
const u16 data_ov161_020cf280[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cdf44): const struct Msg data_ov161_020cf28e; */
const u16 data_ov161_020cf28e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by throw-release tick of the ov161 enemy (x2), ported from the matched ov202 sibling (radius  (020ce9a4): const struct Msg data_ov161_020cf29c; */
const u16 data_ov161_020cf29c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020ce7d8): const struct Msg data_ov161_020cf2aa; */
const u16 data_ov161_020cf2aa[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov161_020ccc30 (020ccc30): const struct tbl8 data_ov161_020cf2b8; */
const u8 data_ov161_020cf2b8[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
