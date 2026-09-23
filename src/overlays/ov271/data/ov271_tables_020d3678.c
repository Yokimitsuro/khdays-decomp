/* ov271 .rodata tables, 0x020d3678-0x020d36c4.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov271_Construct (020cfc04): IdTable data_ov271_020d3678; */
const int data_ov271_020d3678[4] = {
    1, 6, 7, 7,
};

/* read by Ov271_Construct (020cfc04): Box data_ov271_020d3688; */
const u8 data_ov271_020d3688[24] = {
    14, 241, 255, 255, 223, 30, 0, 0, 111, 245, 255, 255, 241, 14, 0, 0,
    67, 76, 0, 0, 197, 12, 0, 0,
};

/* read by Ov271_HandleHit (020d04cc): const u8 data_ov271_020d36a0[];
 *   Publish the swing: send the canned 4-byte block from the config table to the owner's notif (020d1b70): struct blk data_ov271_020d36a0;
 *   * func_ov271_020d1c14 -- x3. AI-state tick: orient toward the target, then transition on a (020d1c14): struct h2 data_ov271_020d36a0[];
 *   Enter the attack state: refresh the owner, convert the owner's per-frame delta into the (020d1dc8): struct blk data_ov271_020d36a0;
 *   * func_ov271_020d1e7c -- x3. AI-state tick: clamp, aim, and transition on a timer. (020d1e7c): struct h2 data_ov271_020d36a0[]; */
const u8 data_ov271_020d36a0[20] = {
    2, 3, 0, 1, 0, 0, 5, 2, 0, 0, 5, 1, 0, 0, 5, 3,
    0, 0, 5, 4,
};

/* read by Beam charge tick of the ov200 enemy (x3: ov200/ov201/ov271). The aim point is the midpoint (020d26ec): const Cmd4 data_ov271_020d36b4; */
const u8 data_ov271_020d36b4[4] = {
    0, 0, 5, 0,
};

/* read by Beam state builder of the ov200 enemy (x3: ov200/ov201/ov271). Spawns the 0x54-byte beam (020d21a0): const KindTable data_ov271_020d36b8; */
const int data_ov271_020d36b8[3] = {
    2, 3, 4,
};
