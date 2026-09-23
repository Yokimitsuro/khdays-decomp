/* ov298 .rodata tables, 0x020d54e8-0x020d54f0.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov298 enemy (and its byte-identical twin): installs the handlers (+8 ti (020d3844): const int data_ov298_020d54e8; */
const int data_ov298_020d54e8[1] = {
    2,
};

/* read by Hit handler of the ov298 enemy: resolves the damage and ignores the hit while the +0x21a (020d3d0c): const struct ModeTable data_ov298_020d54ec; */
const u8 data_ov298_020d54ec[4] = {
    2, 3, 0, 1,
};
