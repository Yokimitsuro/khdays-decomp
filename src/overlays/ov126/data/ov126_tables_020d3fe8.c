/* ov126 .rodata tables, 0x020d3fe8-0x020d4064.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov125 enemy. Installs the handlers (+8 release, +0xc draw veneer, +0x1c (020cfc04): IdTable data_ov126_020d3fe8; */
const int data_ov126_020d3fe8[9] = {
    1, 2, 3, 3, 4, 6, 7, 7,
    8,
};

/* read by Enter the ov125 enemy's recover state: seed the +0x3c counter with twice the owner's +0x2c (020d197c): unsigned short data_ov126_020d400c[];
 *   Recover tick of the ov125 enemy: the +0x2c timer accumulates the owner's +0x2c rate; once  (020d1a44): unsigned short data_ov126_020d400c[];
 *   func_ov126_020d1de8 (not yet decompiled) */
const u8 data_ov126_020d400c[16] = {
    0, 0, 5, 2, 0, 0, 5, 5, 0, 0, 5, 1, 0, 0, 5, 3,
};

/* read by Beam tick of the ov125 enemy (aimed at the player). The aim point is the midpoint of the t (020d27b4): Cmd14 data_ov126_020d401c; */
const u16 data_ov126_020d401c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Beam tick of the ov125 enemy (wind-down). The aim point is the midpoint of the two anchors (020d2e0c): Cmd14 data_ov126_020d402a; */
const u16 data_ov126_020d402a[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Spin strike tick of the ov125 enemy (the Ov143_StepSlamStrike shape). The query the two (020d3a28): struct Ov125Cmd data_ov126_020d4038; */
const u16 data_ov126_020d4038[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Spin strike tick of the ov125 enemy (the Ov143_StepSlamStrike shape). The query the two (020d3a28): struct Ov125Cmd data_ov126_020d4046; */
const u16 data_ov126_020d4046[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Spin strike tick of the ov125 enemy (the Ov143_StepSlamStrike shape). The query the two (020d3a28): struct Ov125Cmd data_ov126_020d4054; */
const u8 data_ov126_020d4054[16] = {
    0, 0, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
