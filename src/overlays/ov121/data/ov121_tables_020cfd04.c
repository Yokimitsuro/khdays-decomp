/* ov121 .rodata tables, 0x020cfd04-0x020cfd30.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov121 actor initializer: install the callback table, seed the camera pose, (020cdde4): struct Ov120Vec3 data_ov121_020cfd04; */
const int data_ov121_020cfd04[3] = {
    2, 3, 4,
};

/* read by * func_ov121_020cf11c -- Ov121_AreaAttack_Broadcast. (020cf11c): struct Ov120AreaOpener data_ov121_020cfd10; */
const u8 data_ov121_020cfd10[4] = {
    0, 0, 5, 1,
};

/* read by * func_ov121_020cf11c -- Ov121_AreaAttack_Broadcast. (020cf11c): struct Ov120AreaMsg data_ov121_020cfd14; */
const u16 data_ov121_020cfd14[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov121_020cf4d4 (020cf4d4): struct Ov120AreaMsg data_ov121_020cfd22; */
const u16 data_ov121_020cfd22[7] = {
    0, 5, 0, 0, 0, 0, 0,
};
