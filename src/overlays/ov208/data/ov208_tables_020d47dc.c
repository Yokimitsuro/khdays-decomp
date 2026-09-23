/* ov208 .rodata tables, 0x020d47dc-0x020d481c.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov208_BounceShotTick (020d2c6c): const Cmd14 data_ov208_020d47dc; */
const u8 data_ov208_020d47dc[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov208_020d0968 (020d0968): const struct tbl8 data_ov208_020d47ec; */
const u8 data_ov208_020d47ec[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};

/* read by Ov208_ItemConstruct (020d3768): const struct PoseIds data_ov208_020d480c; */
const int data_ov208_020d480c[4] = {
    17, 17, 18, 19,
};
