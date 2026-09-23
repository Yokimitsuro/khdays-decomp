/* ov158 .rodata tables, 0x020cf520-0x020cf574.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov158_Construct (020cbfc4): struct Ov158Kinds data_ov158_020cf520; */
const int data_ov158_020cf520[8] = {
    1, 2, 3, 4, 5, 6, 7, 8,
};

/* read by c634 handler: arm the second phase of the move. (020cd7cc): unsigned short data_ov158_020cf540[];
 *   Ov158_AttackWaitTick (020cd898): unsigned short data_ov158_020cf540[];
 *   Ov158_CommitMove (020cdad0): unsigned short data_ov158_020cf540[];
 *   Ov158_AimedAttackWaitTick (020cdb88): unsigned short data_ov158_020cf540[]; */
const u8 data_ov158_020cf540[20] = {
    0, 0, 5, 1, 0, 0, 5, 4, 0, 0, 5, 2, 0, 0, 5, 0,
    0, 0, 5, 3,
};

/* read by Ov158_EnterGroundDrop (020ce6dc): Vec3 data_ov158_020cf554; */
const u8 data_ov158_020cf554[12] = {
    0, 0, 0, 0, 0, 248, 255, 255, 0, 0, 0, 0,
};

/* read by Ov158_ConstructItem (020ce9d4): const struct Ov158Pose data_ov158_020cf560; */
const int data_ov158_020cf560[1] = {
    6,
};

/* read by Ov158_SendPositionMessage (020cf418): const PosMsg data_ov158_020cf564; */
const u8 data_ov158_020cf564[16] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
