/* ov043 .rodata tables, 0x020b576c-0x020b57d4.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov043_SeedRequestRows (020b4bd8): const IntTable4 data_ov043_020b576c; */
const u8 data_ov043_020b576c[16] = {
    68, 1, 0, 0, 188, 254, 255, 255, 68, 1, 0, 0, 188, 254, 255, 255,
};

/* read by Ov043_SeedRequestRows (020b4bd8): const IntTable4 data_ov043_020b577c; */
const u8 data_ov043_020b577c[16] = {
    170, 42, 0, 0, 170, 42, 0, 0, 170, 10, 0, 0, 170, 10, 0, 0,
};

/* read by Ov043_ComputeSlotPosition (020b4ef0): const OffsetPair data_ov043_020b578c; */
const u8 data_ov043_020b578c[24] = {
    236, 17, 0, 0, 143, 34, 0, 0, 143, 254, 255, 255, 20, 238, 255, 255,
    143, 34, 0, 0, 143, 254, 255, 255,
};

/* read by Ov043_SeedRequestRows (020b4bd8): const VecTable4 data_ov043_020b57a4; */
const u8 data_ov043_020b57a4[48] = {
    102, 6, 0, 0, 205, 252, 255, 255, 154, 9, 0, 0, 154, 249, 255, 255,
    205, 252, 255, 255, 154, 9, 0, 0, 205, 4, 0, 0, 0, 0, 0, 0,
    0, 8, 0, 0, 51, 251, 255, 255, 0, 0, 0, 0, 0, 8, 0, 0,
};
