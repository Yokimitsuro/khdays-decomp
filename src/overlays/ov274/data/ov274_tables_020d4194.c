/* ov274 .rodata tables, 0x020d4194-0x020d42a0.
 *
 * 14 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov274_Construct (020cfc04): struct Ov274Kinds data_ov274_020d4194; */
const int data_ov274_020d4194[5] = {
    18, 19, 21, 22, 23,
};

/* read by * func_ov274_020d0508 -- x4. Message handler: on kinds 6 and 0xa, (re-)arm the emitter, th (020d0508): struct t17 data_ov274_020d41a8; */
const int data_ov274_020d41a8[17] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17,
};

/* read by reset the tuning, quiesce the owner and queue the effect, then hand on. (020d1f68): unsigned short data_ov274_020d41ec[]; */
const u8 data_ov274_020d41ec[8] = {
    184, 3, 0, 0, 0, 0, 5, 0,
};

/* read by func_ov274_020d3684 (not yet decompiled) */
const u16 data_ov274_020d41f4[7] = {
    0, 1285, 0, 0, 0, 0, 0,
};

/* read by func_ov274_020d3684 (not yet decompiled) */
const u16 data_ov274_020d4202[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_JumpWindupTick (020d32cc): const PosMsg data_ov274_020d4210; */
const u16 data_ov274_020d4210[7] = {
    0, 1029, 0, 0, 0, 0, 0,
};

/* read by Ov274_StompTick (020d2d28): const PosMsg data_ov274_020d421e; */
const u16 data_ov274_020d421e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_LandingTick (020d24dc): const PosMsg data_ov274_020d422c; */
const u16 data_ov274_020d422c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_StompTick (020d2d28): const PosMsg data_ov274_020d423a; */
const u16 data_ov274_020d423a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_LandingTick (020d24dc): const PosMsg data_ov274_020d4248; */
const u16 data_ov274_020d4248[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_ChargeTick (020d20b4): const PosMsg data_ov274_020d4256; */
const u16 data_ov274_020d4256[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov274_020d3684 (not yet decompiled) */
const u16 data_ov274_020d4264[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov274_ShockwaveTick (020d3de8): const PosMsg data_ov274_020d4272; */
const u16 data_ov274_020d4272[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov274_020d0b34 (020d0b34): const struct tbl8 data_ov274_020d4280; */
const u8 data_ov274_020d4280[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
