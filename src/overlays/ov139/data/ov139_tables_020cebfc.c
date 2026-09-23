/* ov139 .rodata tables, 0x020cebfc-0x020cec68.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov139 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cbfc4): const struct PoolIds data_ov139_020cebfc; */
const int data_ov139_020cebfc[3] = {
    2, 3, 4,
};

/* read by Constructor of the ov139 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cbfc4): const Vec3 data_ov139_020cec08; */
const u8 data_ov139_020cec08[12] = {
    0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0,
};

/* read by Approach decision of the ov139 enemy (and its byte-identical twin). Acquires the +4 target (020ccd08): const Vec3 data_ov139_020cec14; */
const u8 data_ov139_020cec14[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0,
};

/* read by Slam tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the +0x3 (020cdbec): const PosMsg data_ov139_020cec20; */
const u16 data_ov139_020cec20[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Slam tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the +0x3 (020cdbec): const PosMsg data_ov139_020cec2e; */
const u16 data_ov139_020cec2e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Sweep tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the (020cd81c): const PosMsg data_ov139_020cec3c; */
const u16 data_ov139_020cec3c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Rush tick of the ov139 enemy (and its byte-identical twin). The +0x3c timer accumulates th (020ce2d8): const PosMsg data_ov139_020cec4a; */
const u16 data_ov139_020cec4a[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Rush tick of the ov139 enemy (and its byte-identical twin). The +0x3c timer accumulates th (020ce2d8): const PosMsg data_ov139_020cec58; */
const u8 data_ov139_020cec58[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
