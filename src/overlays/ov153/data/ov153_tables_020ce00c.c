/* ov153 .rodata tables, 0x020ce00c-0x020ce064.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Big constructor of the ov153 enemy (x3: ov153/154/155): raises bit 8 of the +0 flags, inst (020cbfc4): const int data_ov153_020ce00c[2]; */
const int data_ov153_020ce00c[2] = {
    1, 2,
};

/* read by Big constructor of the ov153 enemy (x3: ov153/154/155): raises bit 8 of the +0 flags, inst (020cbfc4): struct Ov153Vec3 data_ov153_020ce014; */
const int data_ov153_020ce014[3] = {
    0, 2560, 0,
};

/* read by Constructor of the ov153 enemy (x3: ov153/154/155): installs the handlers (+8 tick, +0xc (020cc588): const int data_ov153_020ce020[2]; */
const int data_ov153_020ce020[2] = {
    3, 5,
};

/* read by * Homing flight tick of the ov153 projectile state (x3: ov153/154/155). The actors inside  (020cccf8): const PosMsg data_ov153_020ce028; */
const u16 data_ov153_020ce028[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by * Homing flight tick of the ov153 projectile state (x3: ov153/154/155). The actors inside  (020cccf8): const PosMsg data_ov153_020ce036; */
const u16 data_ov153_020ce036[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by broadcast this node's position. When the caller's flag word has both (020cc894): struct Msg data_ov153_020ce044; */
const u16 data_ov153_020ce044[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by * Homing flight tick of the ov153 projectile state (x3: ov153/154/155). The actors inside  (020cccf8): const PosMsg data_ov153_020ce052; */
const u16 data_ov153_020ce052[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov153_020cde14 (020cde14): struct pair data_ov153_020ce060; */
const u8 data_ov153_020ce060[4] = {
    0, 0, 5, 0,
};
