/* ov140 .rodata tables, 0x020d283c-0x020d28a8.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov139 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cfc04): const struct PoolIds data_ov140_020d283c; */
const int data_ov140_020d283c[3] = {
    2, 3, 4,
};

/* read by Constructor of the ov139 enemy (and its byte-identical twin): installs the handlers (+8 ti (020cfc04): const Vec3 data_ov140_020d2848; */
const u8 data_ov140_020d2848[12] = {
    0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0,
};

/* read by Approach decision of the ov139 enemy (and its byte-identical twin). Acquires the +4 target (020d0948): const Vec3 data_ov140_020d2854; */
const u8 data_ov140_020d2854[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 96, 0, 0,
};

/* read by Slam tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the +0x3 (020d182c): const PosMsg data_ov140_020d2860; */
const u16 data_ov140_020d2860[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Slam tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the +0x3 (020d182c): const PosMsg data_ov140_020d286e; */
const u16 data_ov140_020d286e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Sweep tick of the ov139 enemy (and its byte-identical twin): the +0x14 velocity is the (020d145c): const PosMsg data_ov140_020d287c; */
const u16 data_ov140_020d287c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Rush tick of the ov139 enemy (and its byte-identical twin). The +0x3c timer accumulates th (020d1f18): const PosMsg data_ov140_020d288a; */
const u16 data_ov140_020d288a[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Rush tick of the ov139 enemy (and its byte-identical twin). The +0x3c timer accumulates th (020d1f18): const PosMsg data_ov140_020d2898; */
const u8 data_ov140_020d2898[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
