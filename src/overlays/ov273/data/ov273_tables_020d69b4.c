/* ov273 .rodata tables, 0x020d69b4-0x020d6bc4.
 *
 * 21 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov273_Construct (020cfc94): IdTable8 data_ov273_020d69b4; */
const int data_ov273_020d69b4[8] = {
    57, 58, 59, 61, 62, 65, 65, 68,
};

/* read by Rebind the two collision items (+0x384 / +0x388) to the resources of this slot: the kinds (020d0968): const struct Tbl27 data_ov273_020d69d4; */
const int data_ov273_020d69d4[27] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27,
};

/* read by Rebind the two collision items (+0x384 / +0x388) to the resources of this slot: the kinds (020d0968): const struct Tbl27 data_ov273_020d6a40; */
const int data_ov273_020d6a40[27] = {
    30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53,
    54, 55, 56,
};

/* read by Hover tick: `ready` = the +0x70 timer has started and the actor's +0x10c slot is empty. Wh (020d3910): unsigned short data_ov273_020d6aac[];
 *   State entry: sends message data_ov273_020d6aac (4 bytes) to the actor's +0x24 hook when se (020d3be4): const struct hpair data_ov273_020d6aac; */
const u8 data_ov273_020d6aac[8] = {
    0, 0, 5, 5, 0, 0, 5, 3,
};

/* read by Stagger entry: clears bit 0 and raises flags 0x86 in the actor's +0x60 high byte, clears b (020d401c): struct Msg data_ov273_020d6ab4; */
const u16 data_ov273_020d6ab4[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov273_LungeTick (020d3568): const Cmd14 data_ov273_020d6ac2; */
const u16 data_ov273_020d6ac2[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov273_ShockwaveTick (020d2be0): const struct Msg14 data_ov273_020d6ad0; */
const u16 data_ov273_020d6ad0[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Ov273_ShockwaveTick (020d2be0): const struct Msg14 data_ov273_020d6ade; */
const u16 data_ov273_020d6ade[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov273_TailSweepTick (020d3c60): const Cmd14 data_ov273_020d6aec; */
const u16 data_ov273_020d6aec[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Regroup tick: once the +0x3dc partner raises bit 2 of its +0x394 word, the +4 anchor posit (020d27bc): struct Msg data_ov273_020d6afa; */
const u16 data_ov273_020d6afa[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Lock-on entry of the ov213 enemy: the +0x24 target is picked (020cab14); without one the n (020d24cc): const struct Msg14 data_ov273_020d6b08; */
const u16 data_ov273_020d6b08[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Retreat entry: broadcasts the +4 anchor position as a 14-byte message built from the (020d13b4): struct Msg data_ov273_020d6b16; */
const u16 data_ov273_020d6b16[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Scatter entry: builds the 0x44-byte spread message from the data_ov273_020d6b24 template (020d312c): const struct SpreadMsg data_ov273_020d6b24; */
const u8 data_ov273_020d6b24[68] = {
    0, 0, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

/* read by Constructor of the ov213 enemy's companion (x2 with ov273): installs the handlers (+8, +0x (020d41e8): int data_ov273_020d6b68; */
const int data_ov273_020d6b68[1] = {
    59,
};

/* read by Ov273_SweepPassHitTest (020d4fa4): const Cmd14 data_ov273_020d6b6c; */
const u8 data_ov273_020d6b6c[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov213 actor's third form: installs the handlers (+8 tick, +0xc draw, (020d529c): const int data_ov273_020d6b7c[2]; */
const int data_ov273_020d6b7c[2] = {
    67, 59,
};

/* read by func_ov273_020d5ba0 (not yet decompiled) */
const u16 data_ov273_020d6b84[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by broadcast this node's position. When the caller's flag word has both (020d573c): struct Msg data_ov273_020d6b92; */
const u16 data_ov273_020d6b92[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov273_020d5ba0 (not yet decompiled) */
const u8 data_ov273_020d6ba0[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov213 actor: installs the handlers (+8 tick, +0x20 hook, +0x1c message, (020d6000): const struct Ov213PoolEntry data_ov273_020d6bb0; */
const int data_ov273_020d6bb0[1] = {
    59,
};

/* read by Ground-slam tick: the +8 timer accumulates the frame rate. At stage 0 (+0xc), past 1.5 the (020d6654): const Cmd14 data_ov273_020d6bb4; */
const u8 data_ov273_020d6bb4[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
