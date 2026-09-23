/* ov278 .rodata tables, 0x020d6230-0x020d6450.
 *
 * 21 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov278_HandleMessage (020cc86c): const struct Ov278SlotMap data_ov278_020d6230; */
const u8 data_ov278_020d6230[4] = {
    1, 2, 3, 4,
};

/* read by Model pose setup: composes the +0x39c clip's pose (+4) with the constant data_ov278_020d62 (020cbfc4): const struct m4 data_ov278_020d6234; */
const int data_ov278_020d6234[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov278_Construct (020cc154): IdTable data_ov278_020d6244; */
const int data_ov278_020d6244[10] = {
    67, 65, 65, 65, 65, 68, 70, 73,
    78, 79,
};

/* read by Rebuild the two rider work lists (+0x38c for the +0x384 rider, +0x390 for the +0x388 one)  (020cca44): const struct Buf23 data_ov278_020d626c; */
const int data_ov278_020d626c[23] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23,
};

/* read by Constructor of the front rider controller (created by 020cce20). Installs its handlers (+8 (020cce54): IdTable5 data_ov278_020d62c8; */
const int data_ov278_020d62c8[5] = {
    64, 71, 72, 74, 75,
};

/* read by Rebuild the two rider work lists (+0x388 for the +0x384 rider, +0x390 for the +0x38c one) (020cd918): const struct Buf17 data_ov278_020d62dc; */
const int data_ov278_020d62dc[17] = {
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41,
};

/* read by Constructor of the rear rider controller (created by 020cdc84). Installs its handlers (+8, (020cdcb8): IdTable4 data_ov278_020d6320; */
const int data_ov278_020d6320[4] = {
    66, 69, 76, 77,
};

/* read by Rebuild the two rider work lists (+0x38c for the +0x388 rider, +0x394 for the +0x390 one) (020ce820): const struct Buf17 data_ov278_020d6330; */
const int data_ov278_020d6330[17] = {
    43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58,
    59,
};

/* read by Ov278_JumpTick (020cfef8): unsigned short data_ov278_020d6374[];
 *   Ov278_EnterCharge (020d039c): Ov278CueTable data_ov278_020d6374;
 *   func_ov278_020d0ad4 (020d0ad4): Ov236CueTable data_ov278_020d6374; */
const u8 data_ov278_020d6374[12] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 5,
};

/* read by Ov278_TailSweepTick (020d000c): const struct Msg14 data_ov278_020d6380; */
const u16 data_ov278_020d6380[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Rolling-charge tick: the nearest target (020cab14) becomes the +8 mark (none: pose 0xa). W (020d0bac): const Cmd14 data_ov278_020d638e; */
const u16 data_ov278_020d638e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov278_020d1848 (not yet decompiled)
 *   Charge-in tick: refreshes the +4 target (none: pose request 9), measures the surface gap (020d27fc): unsigned short data_ov278_020d639c[];
 *   Publish the pounce landing: send the canned 4-byte block from the config table to the owne (020d296c): struct Blk data_ov278_020d639c;
 *   Recovery wait (first rider): runs the +0x14 timer; once the +0x24 child's byte clears pose (020d30a8): unsigned short data_ov278_020d639c[];
 *   Rider watch tick (first rider): runs the +0x14 timer; once the +0x24 child's byte clears a (020d3194): unsigned short data_ov278_020d639c[];
 *   reaction step: while the gate byte at *node[9] is clear, notify the owner (020d337c): char data_ov278_020d639c[]; */
const u8 data_ov278_020d639c[28] = {
    0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 1, 0, 0, 5, 5,
    0, 0, 5, 0, 0, 0, 5, 6, 0, 0, 5, 0,
};

/* read by Ov278_StompLandingTick (020d29dc): const struct Msg14 data_ov278_020d63b8; */
const u16 data_ov278_020d63b8[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov278_020d1848 (not yet decompiled) */
const u16 data_ov278_020d63c6[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov278_ClawSwipeTick (020d33f4): const Cmd14 data_ov278_020d63d4; */
const u8 data_ov278_020d63d4[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov278_020d374c (not yet decompiled)
 *   Ov278_StalkTick (020d4570): const Cmd4 data_ov278_020d63e4[];
 *   Ov278_StompTick (020d4d38): const Cmd4 data_ov278_020d63e4[];
 *   Ov278_DismountLandingTick (020d5494): u16 data_ov278_020d63e4[];
 *   Rider watch tick (second rider): runs the +0x14 timer; once the +0x20 child's byte clears  (020d5758): unsigned short data_ov278_020d63e4[];
 *   Ov278_StampWalkTick (020d598c): const Cmd4 data_ov278_020d63e4[]; */
const u8 data_ov278_020d63e4[36] = {
    0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 0, 0, 0, 5, 1,
    0, 0, 5, 5, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
    0, 0, 5, 1,
};

/* read by Ov278_StompTick (020d4d38): const Cmd14 data_ov278_020d6408; */
const u16 data_ov278_020d6408[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov278_020d374c (not yet decompiled) */
const u16 data_ov278_020d6416[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov278_StampWalkTick (020d598c): const Cmd14 data_ov278_020d6424; */
const u16 data_ov278_020d6424[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov278_StalkTick (020d4570): const Cmd14 data_ov278_020d6432; */
const u16 data_ov278_020d6432[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov278_StalkTick (020d4570): const Cmd14 data_ov278_020d6440; */
const u8 data_ov278_020d6440[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
