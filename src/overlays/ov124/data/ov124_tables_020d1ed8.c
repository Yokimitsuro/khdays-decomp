/* ov124 .rodata tables, 0x020d1ed8-0x020d1f30.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov123 enemy (and its byte-identical twin): raises bit 8 of the +0 flags (020cfc04): const int data_ov124_020d1ed8[2]; */
const int data_ov124_020d1ed8[2] = {
    1, 2,
};

/* read by Constructor of the ov123 enemy (and its byte-identical twin): raises bit 8 of the +0 flags (020cfc04): struct Ov153Vec3 data_ov124_020d1ee0; */
const int data_ov124_020d1ee0[3] = {
    0, 1024, 0,
};

/* read by func_ov124_020d0ab4 (020d0ab4): short data_ov124_020d1eec; */
const u8 data_ov124_020d1eec[4] = {
    0, 0, 5, 0,
};

/* read by Constructor of the ov156 enemy's held item (and its byte-identical twin): installs the (020d1140): const int data_ov124_020d1ef0[2]; */
const int data_ov124_020d1ef0[2] = {
    3, 5,
};

/* read by Shot flight tick of the ov123 enemy (and its byte-identical twin). Without a +0x24 target  (020d1838): const PosMsg data_ov124_020d1ef8; */
const u16 data_ov124_020d1ef8[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Shot flight tick of the ov123 enemy (and its byte-identical twin). Without a +0x24 target  (020d1838): const PosMsg data_ov124_020d1f06; */
const u16 data_ov124_020d1f06[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Shot flight tick of the ov123 enemy (and its byte-identical twin). Without a +0x24 target  (020d1838): const PosMsg data_ov124_020d1f14; */
const u16 data_ov124_020d1f14[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Shot flight tick of the ov123 enemy (and its byte-identical twin). Without a +0x24 target  (020d1838): const PosMsg data_ov124_020d1f22; */
const u16 data_ov124_020d1f22[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
