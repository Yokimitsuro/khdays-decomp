/* ov253 .rodata tables, 0x020d482c-0x020d4844.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov253_020cc358 (not yet decompiled) */
const int data_ov253_020d482c[2] = {
    32, 43,
};

/* read by carried item update: after the base update (0203bc78) the +0x84 (020cc248): const struct vec4 data_ov253_020d4834; */
const int data_ov253_020d4834[4] = {
    0, 2896, 2896, 0,
};
