/* ov275 .rodata tables, 0x020d5fb4-0x020d60c0.
 *
 * 14 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov274 enemy (and its byte-identical twins): installs the handlers (+8 (020d1a24): struct Ov274Kinds data_ov275_020d5fb4; */
const int data_ov275_020d5fb4[5] = {
    18, 19, 21, 22, 23,
};

/* read by * func_ov275_020d2328 -- x4. Message handler: on kinds 6 and 0xa, (re-)arm the emitter, th (020d2328): struct t17 data_ov275_020d5fc8; */
const int data_ov275_020d5fc8[17] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17,
};

/* read by reset the tuning, quiesce the owner and queue the effect, then hand on. (020d3d88): unsigned short data_ov275_020d600c[]; */
const u8 data_ov275_020d600c[8] = {
    184, 3, 0, 0, 0, 0, 5, 0,
};

/* read by func_ov275_020d54a4 (not yet decompiled) */
const u16 data_ov275_020d6014[7] = {
    0, 1285, 0, 0, 0, 0, 0,
};

/* read by func_ov275_020d54a4 (not yet decompiled) */
const u16 data_ov275_020d6022[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Jump wind-up tick of the ov274 enemy. Until flagged (+0x52) the +0x24 timer accumulates th (020d50ec): const PosMsg data_ov275_020d6030; */
const u16 data_ov275_020d6030[7] = {
    0, 1029, 0, 0, 0, 0, 0,
};

/* read by Stomp tick of the ov274 enemy. While the +0x24 timer (fed by the owner's rate) is between (020d4b48): const PosMsg data_ov275_020d603e; */
const u16 data_ov275_020d603e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Landing tick of the ov274 enemy. Each foot has its own window on the +0x24 timer (fed by (020d42fc): const PosMsg data_ov275_020d604c; */
const u16 data_ov275_020d604c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Stomp tick of the ov274 enemy. While the +0x24 timer (fed by the owner's rate) is between (020d4b48): const PosMsg data_ov275_020d605a; */
const u16 data_ov275_020d605a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Landing tick of the ov274 enemy. Each foot has its own window on the +0x24 timer (fed by (020d42fc): const PosMsg data_ov275_020d6068; */
const u16 data_ov275_020d6068[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov274 enemy. The +0x14 velocity is the sine/cosine of the +0x40 heading (020d3ed4): const PosMsg data_ov275_020d6076; */
const u16 data_ov275_020d6076[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov275_020d54a4 (not yet decompiled) */
const u16 data_ov275_020d6084[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Shockwave tick of the ov274 enemy. While the +0x24 timer (fed by the owner's rate) is at m (020d5c08): const PosMsg data_ov275_020d6092; */
const u16 data_ov275_020d6092[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov275_020d2954 (020d2954): const struct tbl8 data_ov275_020d60a0; */
const u8 data_ov275_020d60a0[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
