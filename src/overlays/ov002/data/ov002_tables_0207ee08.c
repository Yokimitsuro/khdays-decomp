/* ov002 .data tables, 0x0207ee08-0x0207ee38.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_QueuePanelGraphics (0x0207ee08, 0x0207ee20).
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov002_0207ee08[24] = {
    0, 0, 1, 0, 2, 0, 3, 0, 4, 0, 5, 0, 255, 255, 255, 255,
    6, 0, 7, 0, 255, 255, 255, 255,
};

u8 data_ov002_0207ee20[24] = {
    166, 0, 167, 0, 168, 0, 169, 0, 170, 0, 171, 0, 255, 255, 255, 255,
    172, 0, 173, 0, 255, 255, 255, 255,
};
