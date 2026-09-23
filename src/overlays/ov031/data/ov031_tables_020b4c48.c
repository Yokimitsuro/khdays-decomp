/* ov031 .rodata tables, 0x020b4c48-0x020b4c60.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov031 actor: fire the attack. Marks the two effect slots busy, asks ov022_0209fe20 (020b4200): Vec3 data_ov031_020b4c48; */
const u8 data_ov031_020b4c48[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 16, 0, 0,
};

/* read by ov031 actor: fire the attack. Marks the two effect slots busy, asks ov022_0209fe20 (020b4200): Vec3 data_ov031_020b4c54; */
const u8 data_ov031_020b4c54[12] = {
    31, 1, 0, 0, 20, 22, 0, 0, 246, 16, 0, 0,
};
