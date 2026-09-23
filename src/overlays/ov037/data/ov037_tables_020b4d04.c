/* ov037 .rodata tables, 0x020b4d04-0x020b4d10.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Fires one part of the ov037 enemy (x4: ov037/055/075/092) unless actor flag bit 27 forbids (020b3a3c): Vec3 data_ov037_020b4d04; */
const u8 data_ov037_020b4d04[12] = {
    0, 0, 0, 0, 143, 18, 0, 0, 20, 10, 0, 0,
};
