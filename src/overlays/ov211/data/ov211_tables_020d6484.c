/* ov211 .rodata tables, 0x020d6484-0x020d658c.
 *
 * 11 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov210 enemy (x3 with ov211/ov282). Installs the handlers, clears +0x1f4 (020d1a24): const PoseTable data_ov211_020d6484; */
const int data_ov211_020d6484[8] = {
    28, 29, 30, 31, 32, 33, 34, 35,
};

/* read by * func_ov211_020d1fec -- x3. Message handler: map the kind through a 26-entry table, then  (020d1fec): struct t26 data_ov211_020d64a4; */
const int data_ov211_020d64a4[26] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24,
    25, 26,
};

/* read by Leap entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the owner's +0 (020d3570): const u16 data_ov211_020d650c[];
 *   * func_ov211_020d3914 -- x3. AI-state entry: set the aim direction, notify, arm and dispat (020d3914): struct h2 data_ov211_020d650c;
 *   Rise-and-strike entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the (020d3e5c): const u16 data_ov211_020d650c[];
 *   Enter the pounce: play animation 0x18, re-acquire the target and face it, reset the counte (020d50c0): struct pt data_ov211_020d650c[]; */
const u8 data_ov211_020d650c[16] = {
    0, 0, 5, 5, 0, 0, 5, 2, 0, 0, 5, 7, 0, 0, 5, 4,
};

/* read by Rise decision of the ov210 enemy (x3 with ov211/ov282). With any of bits 0-3 of the owner' (020d2f6c): const Cmd14 data_ov211_020d651c; */
const u16 data_ov211_020d651c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Rise-and-strike entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the (020d3e5c): const Cmd14 data_ov211_020d652a; */
const u16 data_ov211_020d652a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Double-claw tick: until the +0x66 flag is set the +0x60 timer accumulates the frame rate a (020d5184): const Cmd14 data_ov211_020d6538; */
const u16 data_ov211_020d6538[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Leap entry of the ov210 enemy (x3 with ov211/ov282): raises bits 3 and 6 of the owner's +0 (020d3570): const Cmd14 data_ov211_020d6546; */
const u16 data_ov211_020d6546[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Burst tick of the ov210 enemy (x3 with ov211/ov282). The +0x2c timer accumulates the owner (020d415c): const Cmd14 data_ov211_020d6554; */
const u16 data_ov211_020d6554[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov210 enemy (x3 with ov211/ov282). The +0x14 step is the +0x44 directio (020d3a24): const Cmd14 data_ov211_020d6562; */
const u16 data_ov211_020d6562[7] = {
    0, 1541, 0, 0, 0, 0, 0,
};

/* read by Double-claw tick: until the +0x66 flag is set the +0x60 timer accumulates the frame rate a (020d5184): const Cmd14 data_ov211_020d6570; */
const u16 data_ov211_020d6570[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by Rise entry of the ov210 enemy (x3 with ov211/ov282): raises bits 2, 3 and 6 of the owner's (020d57a0): const Cmd14 data_ov211_020d657e; */
const u16 data_ov211_020d657e[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
