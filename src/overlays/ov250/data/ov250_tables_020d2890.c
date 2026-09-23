/* ov250 .rodata tables, 0x020d2890-0x020d28ec.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov250 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cfc04): const struct PoolIds data_ov250_020d2890; */
const int data_ov250_020d2890[3] = {
    2, 3, 4,
};

/* read by Constructor of the ov250 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cfc04): const struct Box data_ov250_020d289c; */
const u8 data_ov250_020d289c[36] = {
    45, 244, 255, 255, 190, 255, 255, 255, 161, 250, 255, 255, 165, 11, 0, 0,
    205, 45, 0, 0, 110, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 8, 0, 0,
};

/* read by Lunge tick of the ov250 enemy (and its byte-identical twin): the +0x54 velocity is the fac (020d1c70): const PosMsg data_ov250_020d28c0; */
const u16 data_ov250_020d28c0[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Bite sweep tick of the ov250 enemy (and its byte-identical twin): the +0x1c timer accumula (020d1848): const PosMsg data_ov250_020d28ce; */
const u16 data_ov250_020d28ce[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Leap tick of the ov250 enemy (and its byte-identical twin): the +0x54 velocity takes the (020d20c8): const PosMsg data_ov250_020d28dc; */
const u8 data_ov250_020d28dc[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
