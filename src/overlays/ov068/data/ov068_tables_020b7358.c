/* ov068 .rodata tables, 0x020b7358-0x020b7418.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Spawns the ov049 enemy's next effect (x4: ov049/068/087/104) when the rig's countdown at (020b68c4): OffsetTable data_ov068_020b7358; */
const u8 data_ov068_020b7358[192] = {
    0, 0, 0, 0, 0, 0, 0, 0, 205, 4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 16, 0, 0, 51, 251, 255, 255, 0, 0, 0, 0,
    51, 11, 0, 0, 205, 4, 0, 0, 0, 0, 0, 0, 51, 11, 0, 0,
    205, 244, 255, 255, 0, 0, 0, 0, 0, 8, 0, 0, 51, 11, 0, 0,
    0, 0, 0, 0, 0, 8, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
    102, 254, 255, 255, 0, 8, 0, 0, 0, 0, 0, 0, 102, 254, 255, 255,
    154, 249, 255, 255, 0, 0, 0, 0, 205, 4, 0, 0, 102, 6, 0, 0,
    0, 0, 0, 0, 205, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    154, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 51, 251, 255, 255,
    154, 241, 255, 255, 0, 0, 0, 0, 154, 1, 0, 0, 102, 14, 0, 0,
    0, 0, 0, 0, 154, 1, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
    0, 16, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};
