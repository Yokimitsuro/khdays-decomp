/* ov246 .rodata tables, 0x020d30c0-0x020d3114.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov246_Construct (020cfc04): struct Ov246Kinds data_ov246_020d30c0; */
const int data_ov246_020d30c0[8] = {
    2, 3, 4, 5, 6, 7, 8, 9,
};

/* read by c634 handler: arm the second phase of the move. (020d13d8): unsigned short data_ov246_020d30e0[];
 *   Ov246_AttackWaitTick (020d14a4): unsigned short data_ov246_020d30e0[];
 *   set the follow-up delay, and if the counter allows, commit the move. (020d16b0): unsigned short data_ov246_020d30e0[];
 *   Ov246_AimedAttackWaitTick (020d178c): unsigned short data_ov246_020d30e0[]; */
const u8 data_ov246_020d30e0[20] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 2, 0, 0, 5, 0,
    0, 0, 5, 3,
};

/* read by Ov246_ConstructItem (020d1b50): const struct Ov246Pose data_ov246_020d30f4; */
const int data_ov246_020d30f4[1] = {
    7,
};

/* read by Ov246_SendPositionMessage (020d2584): const PosMsg data_ov246_020d30f8; */
const u8 data_ov246_020d30f8[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Ov246_EnterGroundDrop (020d2e50): Vec3 data_ov246_020d3108; */
const u8 data_ov246_020d3108[12] = {
    0, 0, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
};
