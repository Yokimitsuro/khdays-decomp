/* ov000 .rodata tables, 0x0205a884-0x0205a95c.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov000_020535b4 (020535b4): const TileSurfaceCfg data_ov000_0205a884; */
const int data_ov000_0205a884[10] = {
    6, 8, 16, 8, 37, 15, 0, 23,
    0, 32,
};

/* read by func_ov000_020535b4 (020535b4): const TileSurfaceCfg data_ov000_0205a8ac; */
const int data_ov000_0205a8ac[10] = {
    18, 1, 30, 6, 165, 15, 0, 23,
    0, 32,
};

/* read by func_ov000_020535b4 (020535b4): const TileSurfaceCfg data_ov000_0205a8d4; */
const int data_ov000_0205a8d4[10] = {
    0, 14, 18, 2, 1, 15, 0, 23,
    0, 32,
};

/* read by For each variable-stride record, build a sprite via 0205657c (kind-mapped priority) and pl (02055ee4): unsigned char data_ov000_0205a8fc; */
const u8 data_ov000_0205a8fc[4] = {
    8, 9, 10, 11,
};

/* read by For each variable-stride record, build a sprite via 0205657c (kind-mapped priority) and pl (02055ee4): unsigned char data_ov000_0205a900; */
const u8 data_ov000_0205a900[4] = {
    24, 25, 26, 27,
};

/* read by Advance 02030788, then map the current 020315c0 slot to a priority table, storing its inde (020569dc): int data_ov000_0205a904; */
const int data_ov000_0205a904[20] = {
    10, 0, 16, 11, 14, 12, 1, 4,
    5, 6, 7, 9, 13, 15, 17, 18,
    8, 2, 3, 10,
};

/* read by func_ov000_0205a19c (0205a19c): const u8 data_ov000_0205a954[4]; */
const u8 data_ov000_0205a954[8] = {
    224, 16, 16, 160, 19, 0, 0, 0,
};
