/* ov009 .rodata tables, 0x02055fb0-0x02056108.
 *
 * 10 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Advance 02030788, then map the current 020315c0 slot to a priority table, storing its inde (0204ee50): int data_ov009_02055fb0; */
const int data_ov009_02055fb0[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

/* read by For each variable-stride record, build a sprite via func_ov009_02052330 (kind-mapped prior (02051c98): unsigned char data_ov009_02056000; */
const u8 data_ov009_02056000[4] = {
    8, 9, 10, 11,
};

/* read by For each variable-stride record, build a sprite via func_ov009_02052330 (kind-mapped prior (02051c98): unsigned char data_ov009_02056004; */
const u8 data_ov009_02056004[4] = {
    24, 25, 26, 27,
};

/* read by func_ov009_02054070 (02054070): const int data_ov009_02056008[2];
 *   func_ov009_020544b4 (020544b4): const int data_ov009_02056008[2]; */
const int data_ov009_02056008[2] = {
    20, 21,
};

/* read by func_ov009_02054070 (02054070): const int data_ov009_02056010[4]; */
const int data_ov009_02056010[4] = {
    14, 16, 15, 61,
};

/* read by func_ov009_020530c4 (020530c4): const Ov009ObjectConfig data_ov009_02056020; */
const int data_ov009_02056020[4] = {
    0, 1, 0, 0,
};

/* read by func_ov009_02053404 (02053404): const TileSurfaceCfg data_ov009_02056030; */
const int data_ov009_02056030[10] = {
    19, 0, 32, 4, 453, 15, 0, 5,
    0, 32,
};

/* read by func_ov009_02053404 (02053404): const TileSurfaceCfg data_ov009_02056058; */
const int data_ov009_02056058[10] = {
    0, 14, 18, 2, 1, 15, 0, 5,
    0, 32,
};

/* read by func_ov009_02053404 (02053404): const TileSurfaceCfg data_ov009_02056080; */
const int data_ov009_02056080[10] = {
    4, 0, 32, 13, 37, 15, 0, 5,
    0, 32,
};

/* read by func_ov009_020530c4 (020530c4): const int data_ov009_020560a8[3][8];
 *   Page-scroll tick for the ov009 menu: eases each of the three pages towards its (02054180): const int data_ov009_020560a8[3][8];
 *   func_ov009_02054558 (02054558): const int data_ov009_020560a8[3][8];
 *   func_ov009_02054b58 (02054b58): const int data_ov009_020560a8[3][8]; */
const int data_ov009_020560a8[24] = {
    1, 31, 34, 37, 40, 50, 51, 52,
    2, 32, 35, 38, 41, 53, 54, 55,
    3, 33, 36, 39, 42, 56, 57, 58,
};
