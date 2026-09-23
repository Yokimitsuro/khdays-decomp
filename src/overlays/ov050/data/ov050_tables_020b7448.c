/* ov050 .rodata tables, 0x020b7448-0x020b7460.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov050 actor: fire the attack. Marks the two effect slots busy, asks ov022_0209fe20 (020b6a00): Vec3 data_ov050_020b7448; */
const u8 data_ov050_020b7448[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by ov050 actor: fire the attack. Marks the two effect slots busy, asks ov022_0209fe20 (020b6a00): Vec3 data_ov050_020b7454; */
const u8 data_ov050_020b7454[12] = {
    31, 1, 0, 0, 20, 22, 0, 0, 246, 16, 0, 0,
};
