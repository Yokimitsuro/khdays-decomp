/* ov157 .rodata tables, 0x020d0b94-0x020d0bf8.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov156 enemy (and its byte-identical twin): sets bit 8 of the +0 flags, (020cdde4): const Vec3 data_ov157_020d0b94; */
const int data_ov157_020d0b94[3] = {
    0, 1408, 0,
};

/* read by Constructor of the ov156 enemy (and its byte-identical twin): sets bit 8 of the +0 flags, (020cdde4): const struct PoolIds data_ov157_020d0ba0; */
const int data_ov157_020d0ba0[4] = {
    1, 2, 3, 6,
};

/* read by func_ov157_020cf320 (020cf320): unsigned short data_ov157_020d0bb0[]; */
const u8 data_ov157_020d0bb0[4] = {
    0, 0, 5, 0,
};

/* read by Ground sweep of the ov156 enemy's charge (and its byte-identical twin): a box centred on t (020ce8c8): const PosMsg data_ov157_020d0bb4; */
const u8 data_ov157_020d0bb4[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov156 enemy's held item (and its byte-identical twin): installs the (020cfd38): const struct KindPair data_ov157_020d0bc4; */
const int data_ov157_020d0bc4[2] = {
    3, 5,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020d03f4): const PosMsg data_ov157_020d0bcc; */
const u16 data_ov157_020d0bcc[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020d03f4): const PosMsg data_ov157_020d0bda; */
const u16 data_ov157_020d0bda[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020d03f4): const PosMsg data_ov157_020d0be8; */
const u8 data_ov157_020d0be8[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
