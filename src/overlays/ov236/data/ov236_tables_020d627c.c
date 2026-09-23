/* ov236 .rodata tables, 0x020d627c-0x020d649c.
 *
 * 21 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov236_HandleMessage (020cc86c): const struct Ov236SlotMap data_ov236_020d627c; */
const u8 data_ov236_020d627c[4] = {
    1, 2, 3, 4,
};

/* read by Ov236_SetupModelPoses (020cbfc4): const struct m4 data_ov236_020d6280; */
const int data_ov236_020d6280[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov236_Construct (020cc154): IdTable data_ov236_020d6290; */
const int data_ov236_020d6290[10] = {
    67, 65, 65, 65, 65, 68, 70, 73,
    78, 79,
};

/* read by Ov236_PlayRiderMove (020cca44): const struct Buf23 data_ov236_020d62b8; */
const int data_ov236_020d62b8[23] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23,
};

/* read by Ov236_FrontRidersConstruct (020cce54): IdTable5 data_ov236_020d6314; */
const int data_ov236_020d6314[5] = {
    64, 71, 72, 74, 75,
};

/* read by Ov236_RebuildRiderListsA (020cd918): const struct Buf17 data_ov236_020d6328; */
const int data_ov236_020d6328[17] = {
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39, 40,
    41,
};

/* read by Ov236_RearRidersConstruct (020cdcb8): IdTable4 data_ov236_020d636c; */
const int data_ov236_020d636c[4] = {
    66, 69, 76, 77,
};

/* read by Ov236_RebuildRiderListsB (020ce820): const struct Buf17 data_ov236_020d637c; */
const int data_ov236_020d637c[17] = {
    43, 44, 45, 46, 47, 48, 49, 50,
    51, 52, 53, 54, 55, 56, 57, 58,
    59,
};

/* read by Ov236_JumpTick (020cff4c): unsigned short data_ov236_020d63c0[];
 *   Ov236_EnterCharge (020d03ec): Ov236CueTable data_ov236_020d63c0;
 *   func_ov236_020d0b20 (020d0b20): Ov236CueTable data_ov236_020d63c0; */
const u8 data_ov236_020d63c0[12] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 5,
};

/* read by Ov236_TailSweepTick (020d0060): const struct Msg14 data_ov236_020d63cc; */
const u16 data_ov236_020d63cc[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov236_RollingChargeTick (020d0bf8): const Cmd14 data_ov236_020d63da; */
const u16 data_ov236_020d63da[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov236_020d1894 (not yet decompiled)
 *   Ov236_ChargeInTick (020d2848): unsigned short data_ov236_020d63e8[];
 *   Publish the pounce landing: send the canned 4-byte block from the config table to the owne (020d29b8): struct Blk data_ov236_020d63e8;
 *   Ov236_RecoveryWaitA (020d30f4): unsigned short data_ov236_020d63e8[];
 *   Ov236_RiderWatchTickA (020d31e0): unsigned short data_ov236_020d63e8[];
 *   reaction step: while the gate byte at *node[9] is clear, notify the owner (020d33c8): char data_ov236_020d63e8[]; */
const u8 data_ov236_020d63e8[28] = {
    0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 1, 0, 0, 5, 5,
    0, 0, 5, 0, 0, 0, 5, 6, 0, 0, 5, 0,
};

/* read by Ov236_StompLandingTick (020d2a28): const struct Msg14 data_ov236_020d6404; */
const u16 data_ov236_020d6404[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov236_020d1894 (not yet decompiled) */
const u16 data_ov236_020d6412[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov236_ClawSwipeTick (020d3440): const Cmd14 data_ov236_020d6420; */
const u8 data_ov236_020d6420[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov236_020d3798 (not yet decompiled)
 *   Ov236_StalkTick (020d45bc): const Cmd4 data_ov236_020d6430[];
 *   Ov236_StompTick (020d4d84): const Cmd4 data_ov236_020d6430[];
 *   Ov236_DismountLandingTick (020d54e0): u16 data_ov236_020d6430[];
 *   Ov236_RiderWatchTickB (020d57a4): unsigned short data_ov236_020d6430[];
 *   Ov236_StampWalkTick (020d59d8): const Cmd4 data_ov236_020d6430[]; */
const u8 data_ov236_020d6430[36] = {
    0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 0, 0, 0, 5, 1,
    0, 0, 5, 5, 0, 0, 5, 0, 0, 0, 5, 0, 0, 0, 5, 0,
    0, 0, 5, 1,
};

/* read by Ov236_StompTick (020d4d84): const Cmd14 data_ov236_020d6454; */
const u16 data_ov236_020d6454[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov236_020d3798 (not yet decompiled) */
const u16 data_ov236_020d6462[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov236_StampWalkTick (020d59d8): const Cmd14 data_ov236_020d6470; */
const u16 data_ov236_020d6470[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov236_StalkTick (020d45bc): const Cmd14 data_ov236_020d647e; */
const u16 data_ov236_020d647e[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov236_StalkTick (020d45bc): const Cmd14 data_ov236_020d648c; */
const u8 data_ov236_020d648c[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
