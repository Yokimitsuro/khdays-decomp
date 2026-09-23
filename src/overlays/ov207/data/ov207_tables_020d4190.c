/* ov207 .rodata tables, 0x020d4190-0x020d429c.
 *
 * 14 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov206 enemy (and its byte-identical twins): installs the handlers (+8 (020cfc04): struct Ov206Kinds data_ov207_020d4190; */
const int data_ov207_020d4190[5] = {
    18, 19, 21, 22, 23,
};

/* read by * func_ov207_020d0508 -- x4. Message handler: on kinds 6 and 0xa, (re-)arm the emitter, th (020d0508): struct t17 data_ov207_020d41a4; */
const int data_ov207_020d41a4[17] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17,
};

/* read by reset the tuning, quiesce the owner and queue the effect, then hand on. (020d1f68): unsigned short data_ov207_020d41e8[]; */
const u8 data_ov207_020d41e8[8] = {
    184, 3, 0, 0, 0, 0, 5, 0,
};

/* read by func_ov207_020d3680 (not yet decompiled) */
const u16 data_ov207_020d41f0[7] = {
    0, 1285, 0, 0, 0, 0, 0,
};

/* read by func_ov207_020d3680 (not yet decompiled) */
const u16 data_ov207_020d41fe[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Jump wind-up tick of the ov206 enemy. Until flagged (+0x52) the +0x24 timer accumulates th (020d32c8): const PosMsg data_ov207_020d420c; */
const u16 data_ov207_020d420c[7] = {
    0, 1029, 0, 0, 0, 0, 0,
};

/* read by Stomp tick of the ov206 enemy. While the +0x24 timer (fed by the owner's rate) is between (020d2d24): const PosMsg data_ov207_020d421a; */
const u16 data_ov207_020d421a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Landing tick of the ov206 enemy. Each foot has its own window on the +0x24 timer (fed by (020d24d8): const PosMsg data_ov207_020d4228; */
const u16 data_ov207_020d4228[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Stomp tick of the ov206 enemy. While the +0x24 timer (fed by the owner's rate) is between (020d2d24): const PosMsg data_ov207_020d4236; */
const u16 data_ov207_020d4236[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Landing tick of the ov206 enemy. Each foot has its own window on the +0x24 timer (fed by (020d24d8): const PosMsg data_ov207_020d4244; */
const u16 data_ov207_020d4244[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov206 enemy. The +0x14 velocity is the sine/cosine of the +0x40 heading (020d20b0): const PosMsg data_ov207_020d4252; */
const u16 data_ov207_020d4252[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov207_020d3680 (not yet decompiled) */
const u16 data_ov207_020d4260[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Shockwave tick of the ov206 enemy. While the +0x24 timer (fed by the owner's rate) is at m (020d3de4): const PosMsg data_ov207_020d426e; */
const u16 data_ov207_020d426e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov207_020d0b34 (020d0b34): const struct tbl8 data_ov207_020d427c; */
const u8 data_ov207_020d427c[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
