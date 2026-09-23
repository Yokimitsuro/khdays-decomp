/* ov132 .rodata tables, 0x020d0d78-0x020d0dec.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov132_020cdde4 (020cdde4): struct v5 data_ov132_020d0d78; */
const int data_ov132_020d0d78[5] = {
    2, 3, 4, 5, 6,
};

/* read by func_ov132_020cf6f8 (020cf6f8): unsigned short data_ov132_020d0d8c[];
 *   func_ov132_020cfd40 (020cfd40): unsigned short data_ov132_020d0d8c[]; */
const u8 data_ov132_020d0d8c[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by func_ov132_020d00d4 (020d00d4): const struct Msg data_ov132_020d0d94; */
const u16 data_ov132_020d0d94[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov132_020cf7c4 (020cf7c4): const struct Msg data_ov132_020d0da2; */
const u16 data_ov132_020d0da2[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov132_020d00d4 (020d00d4): const struct Msg data_ov132_020d0db0; */
const u16 data_ov132_020d0db0[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov132_020cff08 (020cff08): const struct Msg data_ov132_020d0dbe; */
const u16 data_ov132_020d0dbe[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov132_020ce4ac (020ce4ac): const struct tbl8 data_ov132_020d0dcc; */
const u8 data_ov132_020d0dcc[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
