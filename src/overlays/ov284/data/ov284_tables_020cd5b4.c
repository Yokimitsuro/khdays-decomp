/* ov284 .rodata tables, 0x020cd5b4-0x020cd5c8.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Death entry of the ov284 enemy: sends the overlay's 4-byte message to the actor's +0x24 ho (020cd080): const ShortMsg data_ov284_020cd5b4; */
const u8 data_ov284_020cd5b4[4] = {
    0, 0, 5, 3,
};

/* read by Swing tick of the ov284 enemy: re-acquires the target into +0xc and aims the +0x14 yaw at  (020ccd08): const PosMsg data_ov284_020cd5b8; */
const u8 data_ov284_020cd5b8[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
