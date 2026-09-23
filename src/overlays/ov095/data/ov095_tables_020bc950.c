/* ov095 .rodata tables, 0x020bc950-0x020bc9a4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Compute one of this enemy's attack anchor points into `out`: the plain offset {0, 0x2000, (020bb5f0): const Ov039SidePair data_ov095_020bc950; */
const u8 data_ov095_020bc950[24] = {
    0, 244, 255, 255, 0, 32, 0, 0, 174, 15, 0, 0, 0, 12, 0, 0,
    0, 32, 0, 0, 215, 15, 0, 0,
};

/* read by Push this enemy's attack event(s): event 5 at each attack anchor (Ov039_GetAttackAnchor) (020bbc50): const Ov039BandRow data_ov095_020bc968; */
const int data_ov095_020bc968[15] = {
    0, 0, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1,
};
