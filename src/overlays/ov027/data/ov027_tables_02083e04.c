/* ov027 .rodata tables, 0x02083e04-0x02083ed0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov027_LoadCharacterModels: load the fallen characters shown on the (02083168): VecFx32 data_ov027_02083e04; */
const u8 data_ov027_02083e04[12] = {
    0, 0, 0, 0, 61, 10, 0, 0, 195, 217, 255, 255,
};

/* read by Ov027_LoadCharacterModels: load the fallen characters shown on the (02083168): VecFx32 data_ov027_02083e10[4][4]; */
const u8 data_ov027_02083e10[192] = {
    0, 0, 0, 0, 205, 252, 255, 255, 102, 214, 255, 255, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    82, 244, 255, 255, 205, 252, 255, 255, 102, 214, 255, 255, 174, 11, 0, 0,
    205, 252, 255, 255, 102, 214, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    164, 232, 255, 255, 205, 252, 255, 255, 102, 214, 255, 255, 0, 0, 0, 0,
    205, 252, 255, 255, 102, 214, 255, 255, 92, 23, 0, 0, 205, 252, 255, 255,
    102, 214, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    205, 220, 255, 255, 205, 252, 255, 255, 102, 214, 255, 255, 82, 244, 255, 255,
    205, 252, 255, 255, 102, 214, 255, 255, 174, 11, 0, 0, 205, 252, 255, 255,
    102, 214, 255, 255, 51, 35, 0, 0, 205, 252, 255, 255, 102, 214, 255, 255,
};
