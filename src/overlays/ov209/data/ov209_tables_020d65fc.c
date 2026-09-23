/* ov209 .rodata tables, 0x020d65fc-0x020d663c.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Bounce-shot flight tick: the shot faces its +0x54 velocity (+0x34), the +0x2c timer accumu (020d4a8c): const Cmd14 data_ov209_020d65fc; */
const u8 data_ov209_020d65fc[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov209_020d2788 (020d2788): const struct tbl8 data_ov209_020d660c; */
const u8 data_ov209_020d660c[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};

/* read by Construction of the ov208 enemy's item (x3 with ov209/ov268): installs the handlers (+8 (020d5588): const struct PoseIds data_ov209_020d662c; */
const int data_ov209_020d662c[4] = {
    17, 17, 18, 19,
};
