/* ov002 .data tables, 0x0207ef68-0x0207efb0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov002_0207ef68[24] = {
    12, 7, 1, 6, 2, 15, 8, 11, 4, 9, 10, 16, 3, 0, 13, 5,
    14, 17, 18, 20, 20, 19, 0, 0,
};

u8 data_ov002_0207ef80[48] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0,
    0, 0, 0, 0, 0, 248, 255, 255, 0, 232, 255, 255, 0, 0, 0, 0,
    0, 248, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0, 0, 232, 255, 255,
};
