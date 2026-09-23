/* ov210 .rodata tables, 0x020d4664-0x020d476c.
 *
 * 11 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov210_Construct (020cfc04): const PoseTable data_ov210_020d4664; */
const int data_ov210_020d4664[8] = {
    28, 29, 30, 31, 32, 33, 34, 35,
};

/* read by * func_ov210_020d01cc -- x3. Message handler: map the kind through a 26-entry table, then  (020d01cc): struct t26 data_ov210_020d4684; */
const int data_ov210_020d4684[26] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26,
};

/* read by Ov210_EnterLeap (020d1750): const u16 data_ov210_020d46ec[];
 *   * func_ov210_020d1af4 -- x3. AI-state entry: set the aim direction, notify, arm and dispat (020d1af4): struct h2 data_ov210_020d46ec;
 *   Ov210_EnterRiseStrike (020d203c): const u16 data_ov210_020d46ec[];
 *   Enter the pounce: play animation 0x18, re-acquire the target and face it, reset the counte (020d32a0): struct pt data_ov210_020d46ec[]; */
const u8 data_ov210_020d46ec[16] = {
    0, 0, 5, 5, 0, 0, 5, 2, 0, 0, 5, 7, 0, 0, 5, 4,
};

/* read by Ov210_RiseDecision (020d114c): const Cmd14 data_ov210_020d46fc; */
const u16 data_ov210_020d46fc[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov210_EnterRiseStrike (020d203c): const Cmd14 data_ov210_020d470a; */
const u16 data_ov210_020d470a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov210_DoubleClawTick (020d3364): const Cmd14 data_ov210_020d4718; */
const u16 data_ov210_020d4718[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov210_EnterLeap (020d1750): const Cmd14 data_ov210_020d4726; */
const u16 data_ov210_020d4726[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov210_BurstTick (020d233c): const Cmd14 data_ov210_020d4734; */
const u16 data_ov210_020d4734[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov210_ChargeTick (020d1c04): const Cmd14 data_ov210_020d4742; */
const u16 data_ov210_020d4742[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov210_DoubleClawTick (020d3364): const Cmd14 data_ov210_020d4750; */
const u16 data_ov210_020d4750[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Ov210_EnterRise (020d3980): const Cmd14 data_ov210_020d475e; */
const u16 data_ov210_020d475e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
