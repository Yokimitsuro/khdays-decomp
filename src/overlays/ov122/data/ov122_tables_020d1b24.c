/* ov122 .rodata tables, 0x020d1b24-0x020d1b50.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov122 actor initializer: install the callback table, seed the camera pose, (020cfc04): struct Ov120Vec3 data_ov122_020d1b24; */
const int data_ov122_020d1b24[3] = {
    2, 3, 4,
};

/* read by * func_ov122_020d0f3c -- Ov122_AreaAttack_Broadcast. (020d0f3c): struct Ov120AreaOpener data_ov122_020d1b30; */
const u8 data_ov122_020d1b30[4] = {
    0, 0, 5, 1,
};

/* read by * func_ov122_020d0f3c -- Ov122_AreaAttack_Broadcast. (020d0f3c): struct Ov120AreaMsg data_ov122_020d1b34; */
const u16 data_ov122_020d1b34[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov122_020d12f4 (020d12f4): struct Ov120AreaMsg data_ov122_020d1b42; */
const u16 data_ov122_020d1b42[7] = {
    0, 5, 0, 0, 0, 0, 0,
};
