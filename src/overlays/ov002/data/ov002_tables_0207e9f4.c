/* ov002 .data tables, 0x0207e9f4-0x0207ea00.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Read by Ov002_RebuildPanelSlots (0x0207e9f4).
 */

typedef unsigned char u8;
typedef unsigned short u16;

u8 data_ov002_0207e9f4[12] = {
    9, 0, 9, 0, 9, 0, 1, 0, 2, 0, 9, 0,
};
