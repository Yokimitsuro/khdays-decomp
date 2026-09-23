/* ov142 .rodata tables, 0x020d25fc-0x020d2668.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov141 actor initializer: install the callback table, seed the camera pose, (020cfc04): struct Ov142KindTable data_ov142_020d25fc; */
const int data_ov142_020d25fc[5] = {
    9, 2, 3, 4, 5,
};

/* read by Projectile action enter step (Ghidra: Ov149_ProjectileAction_Enter). (020d0ef0): u16 data_ov142_020d2610[4];
 *   func_ov142_020d0fa4 (020d0fa4): unsigned short data_ov142_020d2610[];
 *   func_ov142_020d132c (020d132c): unsigned short data_ov142_020d2610[]; */
const u8 data_ov142_020d2610[12] = {
    0, 0, 5, 0, 0, 0, 5, 1, 0, 0, 5, 2,
};

/* read by Constructor for the actor's sub-object: install the five entry points, set the (020d1620): const struct Ov142ChildIds data_ov142_020d261c; */
const int data_ov142_020d261c[2] = {
    7, 8,
};

/* read by One frame of the ground slam (Ghidra: Ov142_StepSlamProbe). (020d1bbc): struct Vec3 data_ov142_020d2624; */
const u8 data_ov142_020d2624[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov142_StepSlamStrike). (020d1e70): struct Ov142Cmd data_ov142_020d2630; */
const u16 data_ov142_020d2630[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by One frame of the ground slam (Ghidra: Ov142_StepSlamProbe). (020d1bbc): struct Ov142Cmd data_ov142_020d263e; */
const u16 data_ov142_020d263e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov142_StepSlamStrike). (020d1e70): struct Ov142Cmd data_ov142_020d264c; */
const u16 data_ov142_020d264c[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by The slam's follow-through (Ghidra: Ov142_StepSlamStrike). (020d1e70): struct Ov142Cmd data_ov142_020d265a; */
const u16 data_ov142_020d265a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
