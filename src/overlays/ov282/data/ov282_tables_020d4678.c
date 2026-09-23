/* ov282 .rodata tables, 0x020d4678-0x020d4780.
 *
 * 11 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov282_Construct (020cfc04): const PoseTable data_ov282_020d4678; */
const int data_ov282_020d4678[8] = {
    28, 29, 30, 31, 32, 33, 34, 35,
};

/* read by * func_ov282_020d01d4 -- x3. Message handler: map the kind through a 26-entry table, then  (020d01d4): struct t26 data_ov282_020d4698; */
const int data_ov282_020d4698[26] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26,
};

/* read by Leap entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the owner's +0 (020d1760): const u16 data_ov282_020d4700[];
 *   * func_ov282_020d1b04 -- x3. AI-state entry: set the aim direction, notify, arm and dispat (020d1b04): struct h2 data_ov282_020d4700;
 *   Ov282_EnterRiseStrike (020d204c): const u16 data_ov282_020d4700[];
 *   Enter the pounce: play animation 0x18, re-acquire the target and face it, reset the counte (020d32b4): struct pt data_ov282_020d4700[]; */
const u8 data_ov282_020d4700[16] = {
    0, 0, 5, 5, 0, 0, 5, 2, 0, 0, 5, 7, 0, 0, 5, 4,
};

/* read by Ov282_RiseDecision (020d1158): const Cmd14 data_ov282_020d4710; */
const u16 data_ov282_020d4710[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov282_EnterRiseStrike (020d204c): const Cmd14 data_ov282_020d471e; */
const u16 data_ov282_020d471e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov282_DoubleClawTick (020d3378): const Cmd14 data_ov282_020d472c; */
const u16 data_ov282_020d472c[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Leap entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the owner's +0 (020d1760): const Cmd14 data_ov282_020d473a; */
const u16 data_ov282_020d473a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Ov282_BurstTick (020d2350): const Cmd14 data_ov282_020d4748; */
const u16 data_ov282_020d4748[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov210 enemy (x3 with ov211/ov282). The +0x14 step is the +0x44 directio (020d1c14): const Cmd14 data_ov282_020d4756; */
const u16 data_ov282_020d4756[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Ov282_DoubleClawTick (020d3378): const Cmd14 data_ov282_020d4764; */
const u16 data_ov282_020d4764[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Rise entry of the ov210 enemy (x3 with ov211/ov282): raises bits 2, 3 and 6 of the owner's (020d3990): const Cmd14 data_ov282_020d4772; */
const u16 data_ov282_020d4772[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
