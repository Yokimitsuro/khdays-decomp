/* ov183 .rodata tables, 0x020d2638-0x020d2660.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov181 enemy (x4: ov181/182/183/184): installs the handlers (+8 tick, +0 (020cfc04): struct Ov181Vec3 data_ov183_020d2638; */
const int data_ov183_020d2638[3] = {
    2, 3, 4,
};

/* read by * Swing sweep of the ov181 enemy (x4: ov181/182/183/184): from the +0x14 heading builds th (020d0344): const struct Msg data_ov183_020d2644; */
const u16 data_ov183_020d2644[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by * Dive tick of the ov181 enemy (x4: ov181/182/183/184): copies the +0x78 velocity into +0x (020d1e8c): const struct Msg data_ov183_020d2652; */
const u16 data_ov183_020d2652[7] = {
    0, 261, 0, 0, 0, 0, 0,
};
