/* ov171 .rodata tables, 0x020ceeac-0x020ceebc.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov171 enemy (twins by byte identity). Installs the handlers (+8 release (020cc020): IdTable data_ov171_020ceeac; */
const int data_ov171_020ceeac[3] = {
    1, 2, 4,
};

/* read by * Hit handler of the ov171 enemy (and its byte-identical twins): copies the hit point into (020cc7bc): const u8 data_ov171_020ceeb8[]; */
const u8 data_ov171_020ceeb8[4] = {
    2, 3, 0, 1,
};
