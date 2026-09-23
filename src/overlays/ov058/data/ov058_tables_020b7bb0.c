/* ov058 .rodata tables, 0x020b7bb0-0x020b7c04.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Compute one of this enemy's attack anchor points into `out`: the plain offset {0, 0x2000, (020b6850): const Ov039SidePair data_ov058_020b7bb0; */
const u8 data_ov058_020b7bb0[24] = {
    0, 244, 255, 255, 0, 32, 0, 0, 174, 15, 0, 0, 0, 12, 0, 0,
    0, 32, 0, 0, 215, 15, 0, 0,
};

/* read by Push this enemy's attack event(s): event 5 at each attack anchor (Ov039_GetAttackAnchor) (020b6eb0): const Ov039BandRow data_ov058_020b7bc8; */
const int data_ov058_020b7bc8[15] = {
    0, 0, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1,
};
