/* ov255 .rodata tables, 0x020d29d8-0x020d2bc4.
 *
 * 13 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov255_020cbfc4 (not yet decompiled) */
const int data_ov255_020d29d8[12] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 73, 76, 77,
};

/* read by Ov255_SetMotion (020cca7c): MotionTable data_ov255_020d2a08; */
const int data_ov255_020d2a08[35] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35,
};

/* read by Ov255_SetMotion (020cca7c): MotionTable data_ov255_020d2a94; */
const int data_ov255_020d2a94[35] = {
    37, 38, 39, 40, 41, 42, 43, 44,
    45, 46, 47, 48, 49, 50, 51, 52,
    53, 54, 55, 56, 57, 58, 59, 60,
    61, 62, 63, 64, 65, 66, 67, 68,
    69, 70, 71,
};

/* read by Ov255_BiteTick2 (020ce8f8): const Cmd4 data_ov255_020d2b20[];
 *   Ov255_BiteTick3 (020cedd0): const Cmd4 data_ov255_020d2b20[];
 *   Ov255_GroundStrikeEnterTick (020cf1c0)
 *   Ov255_SlamTick (020cf51c): const Cmd4 data_ov255_020d2b20[];
 *   Ov255_LungeTick (020cfa28): const Cmd4 data_ov255_020d2b20[];
 *   Ov255_HoverInTick (020cff68): const Cmd4 data_ov255_020d2b20[];
 *   func_ov255_020d0044 (not yet decompiled)
 *   Ov255_TakeOffEnterTick (020d0710)
 *   Ov255_HoverInTick2 (020d0908): const Cmd4 data_ov255_020d2b20[]; */
const u8 data_ov255_020d2b20[36] = {
    0, 0, 5, 10, 0, 0, 5, 0, 0, 0, 5, 10, 0, 0, 5, 9,
    0, 0, 5, 2, 0, 0, 5, 10, 0, 0, 5, 7, 0, 0, 5, 8,
    0, 0, 5, 1,
};

/* read by Ov255_BiteTick2 (020ce8f8): const Cmd14 data_ov255_020d2b44; */
const u16 data_ov255_020d2b44[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov255_BiteTick3 (020cedd0): const Cmd14 data_ov255_020d2b52; */
const u16 data_ov255_020d2b52[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov255_LungeTick (020cfa28): const Cmd14 data_ov255_020d2b60; */
const u16 data_ov255_020d2b60[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov255_GroundStrikeEnterTick (020cf1c0): const Cmd14 data_ov255_020d2b6e; */
const u16 data_ov255_020d2b6e[7] = {
    0, 2821, 0, 0, 0, 0, 0,
};

/* read by Ov255_SlamTick (020cf51c): const Cmd14 data_ov255_020d2b7c; */
const u16 data_ov255_020d2b7c[7] = {
    0, 1285, 0, 0, 0, 0, 0,
};

/* read by Ov255_BiteTick (020ce534): const Cmd14 data_ov255_020d2b8a; */
const u16 data_ov255_020d2b8a[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov255_020d0044 (not yet decompiled) */
const u8 data_ov255_020d2b98[16] = {
    0, 0, 5, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Ov255_HomingShotFlightTick (020d1ed8): const Cmd14 data_ov255_020d2ba8; */
const u16 data_ov255_020d2ba8[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov255_HomingShotFlightTick (020d1ed8): const Cmd14 data_ov255_020d2bb6; */
const u16 data_ov255_020d2bb6[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
