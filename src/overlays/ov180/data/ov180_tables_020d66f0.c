/* ov180 .rodata tables, 0x020d66f0-0x020d670c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov180 enemy (twins by byte identity). Installs the handlers (+8 release (020d38a0): IdTable data_ov180_020d66f0; */
const int data_ov180_020d66f0[6] = {
    1, 2, 4, 5, 7, 6,
};

/* read by * Hit handler of the ov178 enemy (and its byte-identical twins): copies the hit point into (020d4124): const u8 data_ov180_020d6708[]; */
const u8 data_ov180_020d6708[4] = {
    2, 3, 0, 1,
};
