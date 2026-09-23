/* ov297 .rodata tables, 0x020d5690-0x020d56b4.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov297 enemy: installs the handlers (+8 tick, +0xc draw, +0x1c message, (020d3844): const int data_ov297_020d5690[2]; */
const int data_ov297_020d5690[2] = {
    2, 3,
};

/* read by Hit handler of the ov297 enemy: the damage is 1; the hit is ignored while the +0x21a stami (020d3dec): const struct ModeTable data_ov297_020d5698; */
const u8 data_ov297_020d5698[4] = {
    0, 1, 2, 3,
};

/* read by Hide entry of the ov297 enemy: spawns effect 0 and fires reaction 0x176 mode 4 at the +8 (020d5540): const struct HideTable data_ov297_020d569c; */
const u8 data_ov297_020d569c[24] = {
    102, 234, 1, 0, 35, 211, 255, 255, 4, 102, 1, 0, 92, 51, 255, 255,
    129, 175, 255, 255, 0, 224, 1, 0,
};
