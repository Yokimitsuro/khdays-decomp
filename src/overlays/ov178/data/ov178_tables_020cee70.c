/* ov178 .rodata tables, 0x020cee70-0x020cee8c.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov178 enemy (twins by byte identity). Installs the handlers (+8 release (020cc020): IdTable data_ov178_020cee70; */
const int data_ov178_020cee70[6] = {
    1, 2, 4, 5, 7, 6,
};

/* read by * Hit handler of the ov178 enemy (and its byte-identical twins): copies the hit point into (020cc8a4): const u8 data_ov178_020cee88[]; */
const u8 data_ov178_020cee88[4] = {
    2, 3, 0, 1,
};
