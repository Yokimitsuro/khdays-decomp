/* ov277 .rodata tables, 0x020d35c0-0x020d3750.
 *
 * 20 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Per-frame update of the ov244 enemy. Outside move 6 bit 4 of +0x420 is set; the move effec (020cccec): const Quat data_ov277_020d35c0; */
const int data_ov277_020d35c0[4] = {
    0, 2896, 2896, 0,
};

/* read by Ov277_Construct (020cbfc8): IdTable8 data_ov277_020d35d0; */
const int data_ov277_020d35d0[8] = {
    39, 40, 41, 42, 43, 44, 45, 48,
};

/* read by Rebind the three collision items (+0x384 / +0x388 / +0x38c) to the resources of pose slot (020cc7b0): const struct Tbl10 data_ov277_020d35f0; */
const int data_ov277_020d35f0[10] = {
    15, 16, 17, 18, 19, 20, 21, 22,
    23, 24,
};

/* read by Rebind the three collision items (+0x384 / +0x388 / +0x38c) to the resources of pose slot (020cc7b0): const struct Tbl10 data_ov277_020d3618; */
const int data_ov277_020d3618[10] = {
    2, 3, 4, 5, 6, 7, 8, 9,
    10, 11,
};

/* read by Rebind the three collision items (+0x384 / +0x388 / +0x38c) to the resources of pose slot (020cc7b0): const struct Tbl10 data_ov277_020d3640; */
const int data_ov277_020d3640[10] = {
    28, 29, 30, 31, 32, 33, 34, 35,
    36, 37,
};

/* read by Construction of the ov244 enemy's item (x2 with ov277): installs the handlers (+8 020cd64c (020cd46c): const struct PoseIds data_ov277_020d3668; */
const int data_ov277_020d3668[3] = {
    48, 49, 50,
};

/* read by Ov277_DiveTick (020cdb54): const Cmd14 data_ov277_020d3674; */
const u16 data_ov277_020d3674[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov277_DiveTick (020cdb54): const Cmd14 data_ov277_020d3682; */
const u16 data_ov277_020d3682[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov277_LeapToCoreTick (020ce09c): const struct Msg14 data_ov277_020d3690; */
const u8 data_ov277_020d3690[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov277_020ce8c4 (not yet decompiled) */
const u16 data_ov277_020d36a0[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by func_ov277_020cf13c (not yet decompiled) */
const u16 data_ov277_020d36ae[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by Enemy hurt hook: cancel the current action (mode 1), send the second pair of (020cfdb8): unsigned short data_ov277_020d36bc[];
 *   Kick anim 4, send sprite request 4 (data_ov277_020d36bc entry 10 with the actor's +2 id), (020d02c4): unsigned short data_ov277_020d36bc[];
 *   Play anim 7, send the cue at data_ov277_020d36bc entry 9 through the actor's +0x24 hook, (020d03c8): unsigned short data_ov277_020d36bc[];
 *   Summon wind-up tick: until the +9 one-shot fires, the +0x1c timer accumulates the frame ra (020d044c): const u16 data_ov277_020d36bc[];
 *   func_ov277_020d05b4 (not yet decompiled)
 *   Once the low nibble of the actor's +0x420 word reaches 4, the cue at data_ov277_020d36bc (020d08a4): unsigned short data_ov277_020d36bc[];
 *   Post a 4-byte sprite request (template halfword-pair with the live tile id), kick anim 5, (020d0944): int data_ov277_020d36bc; */
const u8 data_ov277_020d36bc[48] = {
    0, 0, 5, 7, 0, 0, 5, 0, 0, 0, 5, 4, 0, 0, 5, 4,
    0, 0, 5, 5, 2, 2, 2, 4, 0, 0, 5, 5, 0, 0, 5, 4,
    0, 0, 5, 6, 0, 0, 5, 3, 0, 0, 5, 1, 0, 0, 5, 4,
};

/* read by Lunge-bite tick: the +0x1c timer accumulates the frame rate; between 2.67 and 3.0 the step (020cfe28): const Cmd14 data_ov277_020d36ec; */
const u8 data_ov277_020d36ec[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by func_ov277_020d05b4 (not yet decompiled) */
const u8 data_ov277_020d36fc[16] = {
    80, 11, 0, 0, 0, 0, 0, 0, 176, 244, 255, 255, 0, 0, 0, 0,
};

/* read by Constructor of the ov244 enemy's summoned part controller. Installs its handlers (+8, +0xc (020d0c70): IdTable3 data_ov277_020d370c; */
const int data_ov277_020d370c[3] = {
    48, 49, 50,
};

/* read by Ov277_DiveImpactTick (020d11a4): const Cmd14 data_ov277_020d3718; */
const u16 data_ov277_020d3718[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov277_DiveImpactTick (020d11a4): const Cmd14 data_ov277_020d3726; */
const u16 data_ov277_020d3726[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Constructor of the ov114 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c/+0x20 (020d15d0): struct Ov114Kinds data_ov277_020d3734; */
const int data_ov277_020d3734[2] = {
    1, 2,
};

/* read by Face the target and start the wind-up: if there is no target, drop straight to action 2. (020d3120): Ov277Pair data_ov277_020d373c; */
const u8 data_ov277_020d373c[4] = {
    0, 0, 5, 2,
};

/* read by Swing sweep for ov114: probe the forward volume, notify each accepted hit, (020d1d00): const struct Msg data_ov277_020d3740; */
const u8 data_ov277_020d3740[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
