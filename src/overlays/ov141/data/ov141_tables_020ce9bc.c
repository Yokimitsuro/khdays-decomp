/* ov141 .rodata tables, 0x020ce9bc-0x020cea28.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov141 actor initializer: install the callback table, seed the camera pose, (020cbfc4): struct Ov141KindTable data_ov141_020ce9bc; */
const int data_ov141_020ce9bc[5] = {
    9, 2, 3, 4, 5,
};

/* read by Projectile action enter step (Ghidra: Ov149_ProjectileAction_Enter). (020cd2b0): u16 data_ov141_020ce9d0[4];
 *   func_ov141_020cd364 (020cd364): unsigned short data_ov141_020ce9d0[];
 *   func_ov141_020cd6ec (020cd6ec): unsigned short data_ov141_020ce9d0[]; */
const u8 data_ov141_020ce9d0[12] = {
    0, 0, 5, 0, 0, 0, 5, 1, 0, 0, 5, 2,
};

/* read by Constructor for the actor's sub-object: install the five entry points, set the (020cd9e0): const struct Ov141ChildIds data_ov141_020ce9dc; */
const int data_ov141_020ce9dc[2] = {
    7, 8,
};

/* read by One frame of the ground slam (Ghidra: Ov141_StepSlamProbe). (020cdf7c): struct Vec3 data_ov141_020ce9e4; */
const u8 data_ov141_020ce9e4[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov141_StepSlamStrike). (020ce230): struct Ov141Cmd data_ov141_020ce9f0; */
const u16 data_ov141_020ce9f0[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by One frame of the ground slam (Ghidra: Ov141_StepSlamProbe). (020cdf7c): struct Ov141Cmd data_ov141_020ce9fe; */
const u16 data_ov141_020ce9fe[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov141_StepSlamStrike). (020ce230): struct Ov141Cmd data_ov141_020cea0c; */
const u16 data_ov141_020cea0c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov141_StepSlamStrike). (020ce230): struct Ov141Cmd data_ov141_020cea1a; */
const u16 data_ov141_020cea1a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
