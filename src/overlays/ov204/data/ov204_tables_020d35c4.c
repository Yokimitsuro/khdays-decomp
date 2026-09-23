/* ov204 .rodata tables, 0x020d35c4-0x020d368c.
 *
 * 14 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov204 enemy (and its byte-identical twin ov205; variant of the ov139/14 (020cfc04): const Vec3 data_ov204_020d35c4; */
const int data_ov204_020d35c4[3] = {
    0, 2048, 0,
};

/* read by func_ov204_020cfef0 (020cfef0): void data_ov204_020d35d0(void); */
const int data_ov204_020d35d0[4] = {
    0, 1, 2, 3,
};

/* read by Constructor of the ov204 enemy (and its byte-identical twin ov205; variant of the ov139/14 (020cfc04): const struct PoolIds data_ov204_020d35e0; */
const int data_ov204_020d35e0[7] = {
    2, 2, 2, 2, 3, 4, 5,
};

/* read by Slam tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d1930): const ShortMsg data_ov204_020d35fc; */
const u8 data_ov204_020d35fc[4] = {
    0, 0, 5, 1,
};

/* read by Approach decision of the ov204 enemy (and its byte-identical twin). Acquires the +4 target (020d0a84): const Vec3 data_ov204_020d3600; */
const u8 data_ov204_020d3600[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 144, 0, 0,
};

/* read by Charge tick (variant 3) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d2da4): const PosMsg data_ov204_020d360c; */
const u16 data_ov204_020d360c[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Charge tick (variant 1) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d2904): const PosMsg data_ov204_020d361a; */
const u16 data_ov204_020d361a[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Bounce tick of the ov204 enemy's ball (and its byte-identical twin). A wall contact (bit 1 (020d1f14): const PosMsg data_ov204_020d3628; */
const u16 data_ov204_020d3628[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Bounce tick of the ov204 enemy's ball (and its byte-identical twin). A wall contact (bit 1 (020d1f14): const PosMsg data_ov204_020d3636; */
const u16 data_ov204_020d3636[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Slam tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d1930): const PosMsg data_ov204_020d3644; */
const u16 data_ov204_020d3644[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Charge tick (variant 2) of the ov204 enemy (and its byte-identical twin): the +8 velocity  (020d2b54): const PosMsg data_ov204_020d3652; */
const u16 data_ov204_020d3652[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Sweep tick of the ov204 enemy (and its byte-identical twin): the +8 velocity is the +0x390 (020d15a4): const PosMsg data_ov204_020d3660; */
const u16 data_ov204_020d3660[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Charge sweep of the ov204 enemy (and its byte-identical twin): sweeps a 0xa00 sphere at th (020d3114): const PosMsg data_ov204_020d366e; */
const u16 data_ov204_020d366e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ground sweep of the ov204 enemy's charge (and its byte-identical twin): a box centred 0x20 (020d330c): const PosMsg data_ov204_020d367c; */
const u8 data_ov204_020d367c[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
