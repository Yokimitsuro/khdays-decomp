/* ov159 .rodata tables, 0x020d4f80-0x020d4fd4.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov158 enemy (and its byte-identical twin): installs the handlers (+8 ti (020d1a24): struct Ov158Kinds data_ov159_020d4f80; */
const int data_ov159_020d4f80[8] = {
    1, 2, 3, 4, 5, 6, 7, 8,
};

/* read by c634 handler: arm the second phase of the move. (020d322c): unsigned short data_ov159_020d4fa0[];
 *   Attack wait tick of the ov158 enemy: the +0x3c timer accumulates the owner's rate. In phas (020d32f8): unsigned short data_ov159_020d4fa0[];
 *   commit the move once the counter allows. If the counter at +0x40 has (020d3530): unsigned short data_ov159_020d4fa0[];
 *   Aimed attack wait tick of the ov158 enemy: the +0x18 direction takes the owner's +0xa0 bas (020d35e8): unsigned short data_ov159_020d4fa0[]; */
const u8 data_ov159_020d4fa0[20] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 2, 0, 0, 5, 0,
    0, 0, 5, 3,
};

/* read by Entry of the ov158 enemy's ground drop: a ray from the +0x10 anchor straight down (-2.0, (020d413c): Vec3 data_ov159_020d4fb4; */
const u8 data_ov159_020d4fb4[12] = {
    0, 0, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
};

/* read by Construction of the ov158 enemy's item: installs the handlers (+8 020ceaf0, +0xc 020ceb20, (020d4434): const struct Ov158Pose data_ov159_020d4fc0; */
const int data_ov159_020d4fc0[1] = {
    6,
};

/* read by Send the ov158 enemy's position message: the overlay's 14-byte template (data_ov159_020d4f (020d4e78): const PosMsg data_ov159_020d4fc4; */
const u8 data_ov159_020d4fc4[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
