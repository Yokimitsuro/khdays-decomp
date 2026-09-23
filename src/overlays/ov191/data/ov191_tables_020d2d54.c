/* ov191 .rodata tables, 0x020d2d54-0x020d2dc4.
 *
 * 9 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Big constructor of the ov191 enemy (x3: ov191/192/193): raises bit 8 of the +0 flags, inst (020cfc04): struct Ov191Vec3 data_ov191_020d2d54; */
const int data_ov191_020d2d54[3] = {
    0, 1024, 0,
};

/* read by Big constructor of the ov191 enemy (x3: ov191/192/193): raises bit 8 of the +0 flags, inst (020cfc04): struct Ov191Kinds data_ov191_020d2d60; */
const int data_ov191_020d2d60[4] = {
    1, 2, 3, 6,
};

/* read by Begin the ov191 enemy's "pick target" state (x3: ov191/192/193): plays pose 3, clears the (020d11d4): Pair data_ov191_020d2d70; */
const u8 data_ov191_020d2d70[4] = {
    0, 0, 5, 0,
};

/* read by * Box sweep of the ov191 enemy (x3: ov191/192/193). Builds an ov107 box query at *aim with (020d073c): const PosMsg data_ov191_020d2d74; */
const u8 data_ov191_020d2d74[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov191 enemy (x3: ov191/192/193): installs the handlers (+8 tick, +0xc (020d1e4c): const int data_ov191_020d2d84[2]; */
const int data_ov191_020d2d84[2] = {
    5, 7,
};

/* read by * Flight tick of the ov191 projectile state (x3: ov191/192/193). Each frame it rebuilds th (020d2518): const PosMsg data_ov191_020d2d8c; */
const u16 data_ov191_020d2d8c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by * Flight tick of the ov191 projectile state (x3: ov191/192/193). Each frame it rebuilds th (020d2518): const PosMsg data_ov191_020d2d9a; */
const u16 data_ov191_020d2d9a[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by * Flight tick of the ov191 projectile state (x3: ov191/192/193). Each frame it rebuilds th (020d2518): const PosMsg data_ov191_020d2da8; */
const u16 data_ov191_020d2da8[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Begin the ov191 enemy's shockwave (x3: ov191/192/193): copies the canned {id 0, kind 5, (020d2a60): PosMsg data_ov191_020d2db6; */
const u16 data_ov191_020d2db6[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
