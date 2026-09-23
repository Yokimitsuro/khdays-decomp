/* ov138 .rodata tables, 0x020d2f9c-0x020d2ff0.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov137 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cfc04): struct Ov137Kinds data_ov138_020d2f9c; */
const int data_ov138_020d2f9c[8] = {
    2, 3, 4, 5, 6, 7, 8, 9,
};

/* read by c634 handler: arm the second phase of the move. (020d1428): unsigned short data_ov138_020d2fbc[];
 *   Attack wait tick of the ov137 enemy: the +0x3c timer accumulates the owner's rate. In phas (020d14f4): unsigned short data_ov138_020d2fbc[];
 *   set the follow-up delay, and if the counter allows, commit the move. (020d1704): unsigned short data_ov138_020d2fbc[];
 *   Aimed attack wait tick of the ov137 enemy: the +0x18 direction takes the owner's +0xa0 bas (020d17e0): unsigned short data_ov138_020d2fbc[]; */
const u8 data_ov138_020d2fbc[20] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 2, 0, 0, 5, 0,
    0, 0, 5, 3,
};

/* read by Entry of the ov137 enemy's ground drop: a ray from the +0x10 anchor straight down (-2.0, (020d22cc): Vec3 data_ov138_020d2fd0; */
const u8 data_ov138_020d2fd0[12] = {
    0, 0, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
};

/* read by Construction of the ov138 actor: installs its five handlers, configures the (020d25a4): const struct Ov138Pose data_ov138_020d2fdc; */
const int data_ov138_020d2fdc[1] = {
    7,
};

/* read by Send the ov137 enemy's position message: the overlay's 14-byte template (data_ov138_020d2f (020d2e94): const PosMsg data_ov138_020d2fe0; */
const u8 data_ov138_020d2fe0[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
