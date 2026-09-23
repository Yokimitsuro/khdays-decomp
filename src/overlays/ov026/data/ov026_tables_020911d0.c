/* ov026 .rodata tables, 0x020911d0-0x020911e0.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov008_IsShopRecordListed: whether shop record pRecord (0208d4f0): const u16 data_ov026_020911d0[]; */
const u8 data_ov026_020911d0[16] = {
    0, 0, 26, 0, 117, 0, 172, 0, 225, 0, 40, 1, 101, 1, 0, 0,
};
