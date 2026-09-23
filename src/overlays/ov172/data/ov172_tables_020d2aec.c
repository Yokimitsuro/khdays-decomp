/* ov172 .rodata tables, 0x020d2aec-0x020d2afc.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov171 enemy (twins by byte identity). Installs the handlers (+8 release (020cfc60): IdTable data_ov172_020d2aec; */
const int data_ov172_020d2aec[3] = {
    1, 2, 4,
};

/* read by * Hit handler of the ov171 enemy (and its byte-identical twins): copies the hit point into (020d03fc): const u8 data_ov172_020d2af8[]; */
const u8 data_ov172_020d2af8[4] = {
    2, 3, 0, 1,
};
