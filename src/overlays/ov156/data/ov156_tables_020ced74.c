/* ov156 .rodata tables, 0x020ced74-0x020cedd8.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov156 enemy (and its byte-identical twin): sets bit 8 of the +0 flags, (020cbfc4): const Vec3 data_ov156_020ced74; */
const int data_ov156_020ced74[3] = {
    0, 1408, 0,
};

/* read by Constructor of the ov156 enemy (and its byte-identical twin): sets bit 8 of the +0 flags, (020cbfc4): const struct PoolIds data_ov156_020ced80; */
const int data_ov156_020ced80[4] = {
    1, 2, 3, 6,
};

/* read by func_ov156_020cd500 (020cd500): unsigned short data_ov156_020ced90[]; */
const u8 data_ov156_020ced90[4] = {
    0, 0, 5, 0,
};

/* read by Ground sweep of the ov156 enemy's charge (and its byte-identical twin): a box centred on t (020ccaa8): const PosMsg data_ov156_020ced94; */
const u8 data_ov156_020ced94[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov156 enemy's held item (and its byte-identical twin): installs the (020cdf18): const struct KindPair data_ov156_020ceda4; */
const int data_ov156_020ceda4[2] = {
    3, 5,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020ce5d4): const PosMsg data_ov156_020cedac; */
const u16 data_ov156_020cedac[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020ce5d4): const PosMsg data_ov156_020cedba; */
const u16 data_ov156_020cedba[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Dash tick of the ov156 enemy (and its byte-identical twin). The actors inside the owner's (020ce5d4): const PosMsg data_ov156_020cedc8; */
const u8 data_ov156_020cedc8[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
