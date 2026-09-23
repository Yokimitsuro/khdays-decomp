/* ov231 .rodata tables, 0x020cfa34-0x020cfa58.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov231_ChaseTick (020cd510): const Vec3 data_ov231_020cfa34; */
const u8 data_ov231_020cfa34[12] = {
    0, 0, 0, 0, 0, 144, 255, 255, 0, 0, 0, 0,
};

/* read by decide which way to sidestep, then hand off to func_ov231_020cdc90. (020cdaa8): VecFx32 data_ov231_020cfa40; */
const u8 data_ov231_020cfa40[12] = {
    0, 176, 255, 255, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by AI hover-dive step (byte-identical in ov232 / (020cdd3c): const Vec3 data_ov231_020cfa4c; */
const int data_ov231_020cfa4c[3] = {
    0, 0, 2048,
};
