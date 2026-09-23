/* ov137 .rodata tables, 0x020cf35c-0x020cf3b0.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov137_Construct (020cbfc4): struct Ov137Kinds data_ov137_020cf35c; */
const int data_ov137_020cf35c[8] = {
    2, 3, 4, 5, 6, 7, 8, 9,
};

/* read by c634 handler: arm the second phase of the move. (020cd7e8): unsigned short data_ov137_020cf37c[];
 *   Ov137_AttackWaitTick (020cd8b4): unsigned short data_ov137_020cf37c[];
 *   set the follow-up delay, and if the counter allows, commit the move. (020cdac4): unsigned short data_ov137_020cf37c[];
 *   Ov137_AimedAttackWaitTick (020cdba0): unsigned short data_ov137_020cf37c[]; */
const u8 data_ov137_020cf37c[20] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 2, 0, 0, 5, 0,
    0, 0, 5, 3,
};

/* read by Ov137_EnterGroundDrop (020ce68c): Vec3 data_ov137_020cf390; */
const u8 data_ov137_020cf390[12] = {
    0, 0, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
};

/* read by Construction of the ov137 actor: installs its five handlers, configures the (020ce964): const struct Ov137Pose data_ov137_020cf39c; */
const int data_ov137_020cf39c[1] = {
    7,
};

/* read by Ov137_SendPositionMessage (020cf254): const PosMsg data_ov137_020cf3a0; */
const u8 data_ov137_020cf3a0[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
