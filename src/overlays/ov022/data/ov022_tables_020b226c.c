/* ov022 .rodata tables, 0x020b226c-0x020b2394.
 *
 * 6 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov022_02085f9c (02085f9c): Ov022DefaultValues data_ov022_020b226c; */
const u8 data_ov022_020b226c[16] = {
    0, 0, 0, 0, 255, 63, 0, 0, 255, 127, 0, 0, 255, 191, 0, 0,
};

/* read by Preserve the original unit's predicated-store scheduling in the point loop. (02086264): const Ov022CornerTable data_ov022_020b227c; */
const u8 data_ov022_020b227c[32] = {
    0, 96, 255, 255, 0, 96, 255, 255, 0, 160, 0, 0, 0, 96, 255, 255,
    0, 160, 0, 0, 0, 160, 0, 0, 0, 96, 255, 255, 0, 160, 0, 0,
};

/* read by func_ov022_02086d7c (02086d7c): const Ov022ScaleSourcePair data_ov022_020b229c; */
const u8 data_ov022_020b229c[8] = {
    0, 16, 0, 0, 0, 16, 0, 0,
};

/* read by func_ov022_02086d7c (02086d7c): const Ov022PresetTable data_ov022_020b22a4; */
const u8 data_ov022_020b22a4[200] = {
    0, 0, 6, 0, 0, 176, 5, 0, 0, 192, 7, 0, 0, 176, 6, 0,
    0, 208, 8, 0, 0, 96, 5, 0, 0, 80, 10, 0, 0, 80, 6, 0,
    0, 0, 8, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 176, 5, 0,
    0, 160, 6, 0, 0, 224, 6, 0, 0, 208, 8, 0, 0, 96, 5, 0,
    0, 160, 9, 0, 0, 48, 6, 0, 0, 0, 8, 0, 0, 0, 6, 0,
    0, 0, 6, 0, 0, 0, 5, 0, 0, 32, 7, 0, 0, 240, 6, 0,
    0, 208, 8, 0, 0, 96, 5, 0, 0, 32, 10, 0, 0, 96, 6, 0,
    0, 0, 8, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 176, 5, 0,
    0, 160, 6, 0, 0, 224, 6, 0, 0, 208, 8, 0, 0, 96, 5, 0,
    0, 160, 9, 0, 0, 48, 6, 0, 0, 0, 8, 0, 0, 0, 6, 0,
    0, 0, 6, 0, 0, 176, 5, 0, 0, 160, 6, 0, 0, 224, 6, 0,
    0, 208, 8, 0, 0, 96, 5, 0, 0, 160, 9, 0, 0, 48, 6, 0,
    0, 0, 8, 0, 0, 0, 6, 0,
};

/* read by func_ov022_020892f0 (020892f0): struct Ov022TrackTable5 data_ov022_020b236c; */
const int data_ov022_020b236c[5] = {
    0, 3, 1, 2, 4,
};

/* read by func_ov022_02089384 (02089384): struct tbl5_02089384 data_ov022_020b2380; */
const int data_ov022_020b2380[5] = {
    0, 3, 1, 2, 4,
};
