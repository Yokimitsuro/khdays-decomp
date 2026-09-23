/* ov213 .rodata tables, 0x020d2d74-0x020d2f84.
 *
 * 21 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov213_Construct (020cc054): IdTable8 data_ov213_020d2d74; */
const int data_ov213_020d2d74[8] = {
    57, 58, 59, 61, 62, 65, 65, 68,
};

/* read by Ov213_RebindCollisionSlot (020ccd28): const struct Tbl27 data_ov213_020d2d94; */
const int data_ov213_020d2d94[27] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27,
};

/* read by Ov213_RebindCollisionSlot (020ccd28): const struct Tbl27 data_ov213_020d2e00; */
const int data_ov213_020d2e00[27] = {
    30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43, 44, 45,
    46, 47, 48, 49, 50, 51, 52, 53,
    54, 55, 56,
};

/* read by Ov213_HoverTick (020cfcd0): unsigned short data_ov213_020d2e6c[];
 *   Ov213_EnterPose19State (020cffa4): const struct hpair data_ov213_020d2e6c; */
const u8 data_ov213_020d2e6c[8] = {
    0, 0, 5, 5, 0, 0, 5, 3,
};

/* read by Ov213_EnterStagger (020d03dc): struct Msg data_ov213_020d2e74; */
const u16 data_ov213_020d2e74[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov213_LungeTick (020cf928): const Cmd14 data_ov213_020d2e82; */
const u16 data_ov213_020d2e82[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov213_ShockwaveTick (020cefa0): const struct Msg14 data_ov213_020d2e90; */
const u16 data_ov213_020d2e90[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Ov213_ShockwaveTick (020cefa0): const struct Msg14 data_ov213_020d2e9e; */
const u16 data_ov213_020d2e9e[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov213_TailSweepTick (020d0020): const Cmd14 data_ov213_020d2eac; */
const u16 data_ov213_020d2eac[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov213_RegroupTick (020ceb7c): struct Msg data_ov213_020d2eba; */
const u16 data_ov213_020d2eba[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov213_LockOnEntry (020ce88c): const struct Msg14 data_ov213_020d2ec8; */
const u16 data_ov213_020d2ec8[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov213_EnterRetreat (020cd774): struct Msg data_ov213_020d2ed6; */
const u16 data_ov213_020d2ed6[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov213_EnterScatter (020cf4ec): const struct SpreadMsg data_ov213_020d2ee4; */
const u8 data_ov213_020d2ee4[68] = {
    0, 0, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

/* read by Ov213_CompanionConstruct (020d05a8): int data_ov213_020d2f28; */
const int data_ov213_020d2f28[1] = {
    59,
};

/* read by Ov213_SweepPassHitTest (020d1364): const Cmd14 data_ov213_020d2f2c; */
const u8 data_ov213_020d2f2c[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Ov213_ConstructThirdForm (020d165c): const int data_ov213_020d2f3c[2]; */
const int data_ov213_020d2f3c[2] = {
    67, 59,
};

/* read by func_ov213_020d1f60 (not yet decompiled) */
const u16 data_ov213_020d2f44[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov213_BroadcastPosition (020d1afc): struct Msg data_ov213_020d2f52; */
const u16 data_ov213_020d2f52[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov213_020d1f60 (not yet decompiled) */
const u8 data_ov213_020d2f60[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Ov213_Construct (020d23c0): const struct Ov213PoolEntry data_ov213_020d2f70; */
const int data_ov213_020d2f70[1] = {
    59,
};

/* read by Ov213_GroundSlamTick (020d2a14): const Cmd14 data_ov213_020d2f74; */
const u8 data_ov213_020d2f74[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
