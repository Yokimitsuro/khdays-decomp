/* ov205 .rodata tables, 0x020d7204-0x020d72cc.
 *
 * 14 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov204 enemy (and its byte-identical twin ov205; variant of the ov139/14 (020d3844): const Vec3 data_ov205_020d7204; */
const int data_ov205_020d7204[3] = {
    0, 2048, 0,
};

/* read by func_ov205_020d3b30 (020d3b30): void data_ov205_020d7210(void); */
const int data_ov205_020d7210[4] = {
    0, 1, 2, 3,
};

/* read by Constructor of the ov204 enemy (and its byte-identical twin ov205; variant of the ov139/14 (020d3844): const struct PoolIds data_ov205_020d7220; */
const int data_ov205_020d7220[7] = {
    2, 2, 2, 2, 3, 4, 5,
};

/* read by Slam tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d5570): const ShortMsg data_ov205_020d723c; */
const u8 data_ov205_020d723c[4] = {
    0, 0, 5, 1,
};

/* read by Approach decision of the ov204 enemy (and its byte-identical twin). Acquires the +4 target (020d46c4): const Vec3 data_ov205_020d7240; */
const u8 data_ov205_020d7240[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 144, 0, 0,
};

/* read by Charge tick (variant 3) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d69e4): const PosMsg data_ov205_020d724c; */
const u16 data_ov205_020d724c[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Charge tick (variant 1) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d6544): const PosMsg data_ov205_020d725a; */
const u16 data_ov205_020d725a[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Bounce tick of the ov204 enemy's ball (and its byte-identical twin). A wall contact (bit 1 (020d5b54): const PosMsg data_ov205_020d7268; */
const u16 data_ov205_020d7268[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Bounce tick of the ov204 enemy's ball (and its byte-identical twin). A wall contact (bit 1 (020d5b54): const PosMsg data_ov205_020d7276; */
const u16 data_ov205_020d7276[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Slam tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d5570): const PosMsg data_ov205_020d7284; */
const u16 data_ov205_020d7284[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Charge tick (variant 2) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d6794): const PosMsg data_ov205_020d7292; */
const u16 data_ov205_020d7292[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Sweep tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d51e4): const PosMsg data_ov205_020d72a0; */
const u16 data_ov205_020d72a0[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Charge sweep of the ov204 enemy (and its byte-identical twin): sweeps a 0xa00 sphere at th (020d6d54): const PosMsg data_ov205_020d72ae; */
const u16 data_ov205_020d72ae[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ground sweep of the ov204 enemy's charge (and its byte-identical twin): a box centred 0x20 (020d6f4c): const PosMsg data_ov205_020d72bc; */
const u8 data_ov205_020d72bc[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
