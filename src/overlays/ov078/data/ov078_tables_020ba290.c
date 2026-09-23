/* ov078 .rodata tables, 0x020ba290-0x020ba2e4.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Compute one of this enemy's attack anchor points into `out`: the plain offset {0, 0x2000, (020b8f30): const Ov039SidePair data_ov078_020ba290; */
const u8 data_ov078_020ba290[24] = {
    0, 244, 255, 255, 0, 32, 0, 0, 174, 15, 0, 0, 0, 12, 0, 0,
    0, 32, 0, 0, 215, 15, 0, 0,
};

/* read by Push this enemy's attack event(s): event 5 at each attack anchor (Ov039_GetAttackAnchor) (020b9590): const Ov039BandRow data_ov078_020ba2a8; */
const int data_ov078_020ba2a8[15] = {
    0, 0, 0, 1, 1, 1, 1, 1,
    1, 0, 0, 0, 1, 1, 1,
};
