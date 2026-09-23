/* ov251 .rodata tables, 0x020d64d0-0x020d652c.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov250 enemy (and its byte-identical twin): installs the handlers (+8 ti (020d3844): const struct PoolIds data_ov251_020d64d0; */
const int data_ov251_020d64d0[3] = {
    2, 3, 4,
};

/* read by Constructor of the ov250 enemy (and its byte-identical twin): installs the handlers (+8 ti (020d3844): const struct Box data_ov251_020d64dc; */
const u8 data_ov251_020d64dc[36] = {
    45, 244, 255, 255, 190, 255, 255, 255, 161, 250, 255, 255, 165, 11, 0, 0,
    205, 45, 0, 0, 110, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 8, 0, 0,
};

/* read by Lunge tick of the ov250 enemy (and its byte-identical twin): the +0x54 velocity is the fac (020d58b0): const PosMsg data_ov251_020d6500; */
const u16 data_ov251_020d6500[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Bite sweep tick of the ov250 enemy (and its byte-identical twin): the +0x1c timer accumula (020d5488): const PosMsg data_ov251_020d650e; */
const u16 data_ov251_020d650e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Leap tick of the ov250 enemy (and its byte-identical twin): the +0x54 velocity takes the (020d5d08): const PosMsg data_ov251_020d651c; */
const u8 data_ov251_020d651c[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
