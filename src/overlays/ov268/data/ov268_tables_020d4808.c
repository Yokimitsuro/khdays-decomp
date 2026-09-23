/* ov268 .rodata tables, 0x020d4808-0x020d4848.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov268_BounceShotTick (020d2c88): const Cmd14 data_ov268_020d4808; */
const u8 data_ov268_020d4808[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov268_020d096c (020d096c): const struct tbl8 data_ov268_020d4818; */
const u8 data_ov268_020d4818[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};

/* read by Construction of the ov208 enemy's item (x3 with ov209/ov268): installs the handlers (+8 (020d378c): const struct PoseIds data_ov268_020d4838; */
const int data_ov268_020d4838[4] = {
    17, 17, 18, 19,
};
