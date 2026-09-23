/* ov169 .rodata tables, 0x020cee44-0x020cee58.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov169 enemy (twins by byte identity). Installs the handlers (+8 release (020cc020): IdTable data_ov169_020cee44; */
const int data_ov169_020cee44[4] = {
    1, 2, 4, 5,
};

/* read by * Hit handler of the ov169 enemy (and its byte-identical twins): copies the hit point into (020cc7e4): const u8 data_ov169_020cee54[]; */
const u8 data_ov169_020cee54[4] = {
    2, 3, 0, 1,
};
