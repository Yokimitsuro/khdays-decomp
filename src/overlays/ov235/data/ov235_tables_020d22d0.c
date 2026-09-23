/* ov235 .rodata tables, 0x020d22d0-0x020d2560.
 *
 * 13 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov235_020cbfc4 (not yet decompiled) */
const int data_ov235_020d22d0[11] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    121, 122, 123,
};

/* read by Ov235_SetMotion (020cc9a0): MotionTable data_ov235_020d22fc; */
const int data_ov235_020d22fc[39] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26, 27, 28, 29, 30, 31, 32,
    33, 34, 35, 36, 37, 38, 39,
};

/* read by Ov235_SetMotion (020cc9a0): MotionTable data_ov235_020d2398; */
const int data_ov235_020d2398[39] = {
    41, 42, 43, 44, 45, 46, 47, 48,
    49, 50, 51, 52, 53, 54, 55, 56,
    57, 58, 59, 60, 61, 62, 63, 64,
    65, 66, 67, 68, 69, 70, 71, 72,
    73, 74, 75, 76, 77, 78, 79,
};

/* read by Ov235_SetMotion (020cc9a0): MotionTable data_ov235_020d2434; */
const int data_ov235_020d2434[39] = {
    81, 82, 83, 84, 85, 86, 87, 88,
    89, 90, 91, 92, 93, 94, 95, 96,
    97, 98, 99, 100, 101, 102, 103, 104,
    105, 106, 107, 108, 109, 110, 111, 112,
    113, 114, 115, 116, 117, 118, 119,
};

/* read by Ov235_EnterState10 (020cf5f0)
 *   Ov235_GlideInTick (020d0130): const Cmd4 data_ov235_020d24d0;
 *   func_ov235_020d020c (not yet decompiled)
 *   Ov235_EnterState18 (020d08d4)
 *   Ov235_CirclingTick (020d0d8c): const Cmd4 data_ov235_020d24d0[];
 *   Ov235_AimTick (020d0f60)
 *   Ov235_DashTick (020d10ec): const Cmd4 data_ov235_020d24d0[];
 *   func_ov235_020d161c (not yet decompiled) */
const u8 data_ov235_020d24d0[32] = {
    0, 0, 5, 1, 0, 0, 5, 8, 0, 0, 5, 0, 0, 0, 5, 9,
    0, 0, 5, 11, 0, 0, 5, 7, 0, 0, 5, 2, 0, 0, 5, 8,
};

/* read by func_ov235_020d161c (not yet decompiled) */
const int data_ov235_020d24f0[3] = {
    34, 35, 38,
};

/* read by Ov235_BiteTick3 (020cf244): const Cmd14 data_ov235_020d24fc; */
const u16 data_ov235_020d24fc[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov235_LungeTick (020cf7b8): const Cmd14 data_ov235_020d250a; */
const u16 data_ov235_020d250a[7] = {
    0, 1285, 0, 0, 0, 0, 0,
};

/* read by Ov235_SweepTick (020cfc2c): const Cmd14 data_ov235_020d2518; */
const u16 data_ov235_020d2518[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov235_020d020c (not yet decompiled) */
const u16 data_ov235_020d2526[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov235_BiteTick2 (020ceea0): const Cmd14 data_ov235_020d2534; */
const u16 data_ov235_020d2534[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov235_BiteTick (020ceafc): const Cmd14 data_ov235_020d2542; */
const u16 data_ov235_020d2542[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov235_DashTick (020d10ec): const Cmd14 data_ov235_020d2550; */
const u8 data_ov235_020d2550[16] = {
    0, 0, 5, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
