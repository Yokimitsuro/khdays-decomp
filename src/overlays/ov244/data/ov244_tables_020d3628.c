/* ov244 .rodata tables, 0x020d3628-0x020d37b8.
 *
 * 20 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov244_Update (020cccec): const Quat data_ov244_020d3628; */
const int data_ov244_020d3628[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov244_Construct (020cbfc8): IdTable8 data_ov244_020d3638; */
const int data_ov244_020d3638[8] = {
    39, 40, 41, 42, 43, 44, 45, 48,
};

/* read by Ov244_RebindCollisionSlot (020cc7b0): const struct Tbl10 data_ov244_020d3658; */
const int data_ov244_020d3658[10] = {
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24,
};

/* read by Ov244_RebindCollisionSlot (020cc7b0): const struct Tbl10 data_ov244_020d3680; */
const int data_ov244_020d3680[10] = {
    2, 3, 4, 5, 6, 7, 8, 9,
    10, 11,
};

/* read by Ov244_RebindCollisionSlot (020cc7b0): const struct Tbl10 data_ov244_020d36a8; */
const int data_ov244_020d36a8[10] = {
    28, 29, 30, 31, 32, 33, 34, 35,
    36, 37,
};

/* read by Ov244_ItemConstruct (020cd46c): const struct PoseIds data_ov244_020d36d0; */
const int data_ov244_020d36d0[3] = {
    48, 49, 50,
};

/* read by Ov244_DiveTick (020cdb54): const Cmd14 data_ov244_020d36dc; */
const u16 data_ov244_020d36dc[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov244_DiveTick (020cdb54): const Cmd14 data_ov244_020d36ea; */
const u16 data_ov244_020d36ea[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov244_LeapToCoreTick (020ce09c): const struct Msg14 data_ov244_020d36f8; */
const u8 data_ov244_020d36f8[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov244_020ce8bc (not yet decompiled) */
const u16 data_ov244_020d3708[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by func_ov244_020cf16c (not yet decompiled) */
const u16 data_ov244_020d3716[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Enemy hurt hook: cancel the current action (mode 1), send the second pair of (020cfe20): unsigned short data_ov244_020d3724[];
 *   Ov244_EnterAnim4 (020d032c): unsigned short data_ov244_020d3724[];
 *   Ov244_EnterAnim7 (020d0430): unsigned short data_ov244_020d3724[];
 *   Ov244_SummonWindupTick (020d04b4): const u16 data_ov244_020d3724[];
 *   func_ov244_020d061c (not yet decompiled)
 *   Ov244_WaitNibbleTick (020d090c): unsigned short data_ov244_020d3724[];
 *   Build the sprite request (mirroring facing), kick anim 5, then dispatch. (020d09ac): int data_ov244_020d3724; */
const u8 data_ov244_020d3724[48] = {
    0, 0, 5, 7, 0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 4,
    0, 0, 5, 5, 2, 2, 2, 4, 0, 0, 5, 5, 0, 0, 5, 4,
    0, 0, 5, 6, 0, 0, 5, 3, 0, 0, 5, 1, 0, 0, 5, 4,
};

/* read by Ov244_LungeBiteTick (020cfe90): const Cmd14 data_ov244_020d3754; */
const u8 data_ov244_020d3754[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov244_020d061c (not yet decompiled) */
const u8 data_ov244_020d3764[16] = {
    80, 11, 0, 0, 0, 0, 0, 0, 176, 244, 255, 255, 0, 0, 0, 0,
};

/* read by Ov244_PartControllerConstruct (020d0cd8): IdTable3 data_ov244_020d3774; */
const int data_ov244_020d3774[3] = {
    48, 49, 50,
};

/* read by Ov244_DiveImpactTick (020d120c): const Cmd14 data_ov244_020d3780; */
const u16 data_ov244_020d3780[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov244_DiveImpactTick (020d120c): const Cmd14 data_ov244_020d378e; */
const u16 data_ov244_020d378e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov114 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c/+0x20 (020d1638): struct Ov114Kinds data_ov244_020d379c; */
const int data_ov244_020d379c[2] = {
    1, 2,
};

/* read by Face the target and start the wind-up: if there is no target, drop straight to action 2. (020d3188): Ov244Pair data_ov244_020d37a4; */
const u8 data_ov244_020d37a4[4] = {
    0, 0, 5, 2,
};

/* read by Swing sweep for ov114: probe the forward volume, notify each accepted hit, (020d1d68): const struct Msg data_ov244_020d37a8; */
const u8 data_ov244_020d37a8[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
