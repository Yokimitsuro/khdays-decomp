/* ov076 .rodata tables, 0x020b9be4-0x020b9bf0.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Fires one part of the ov037 enemy (x4: ov037/055/075/092) unless actor flag bit 27 forbids (020b891c): Vec3 data_ov076_020b9be4; */
const u8 data_ov076_020b9be4[12] = {
    0, 0, 0, 0, 143, 18, 0, 0, 20, 10, 0, 0,
};
