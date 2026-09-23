/* ov120 .rodata tables, 0x020cdee4-0x020cdf10.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ov120 actor initializer: install the callback table, seed the camera pose, (020cbfc4): struct Ov120Vec3 data_ov120_020cdee4; */
const int data_ov120_020cdee4[3] = {
    2, 3, 4,
};

/* read by * func_ov120_020cd2fc -- Ov120_AreaAttack_Broadcast. (020cd2fc): struct Ov120AreaOpener data_ov120_020cdef0; */
const u8 data_ov120_020cdef0[4] = {
    0, 0, 5, 1,
};

/* read by * func_ov120_020cd2fc -- Ov120_AreaAttack_Broadcast. (020cd2fc): struct Ov120AreaMsg data_ov120_020cdef4; */
const u16 data_ov120_020cdef4[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by func_ov120_020cd6b4 (020cd6b4): struct Ov120AreaMsg data_ov120_020cdf02; */
const u16 data_ov120_020cdf02[7] = {
    0, 5, 0, 0, 0, 0, 0,
};
