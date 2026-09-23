/* ov168 .rodata tables, 0x020d6350-0x020d6360.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov166 enemy (x3: ov166/167/168). Installs the handlers (+8 release, +0x (020d38a0): IdTable data_ov168_020d6350; */
const int data_ov168_020d6350[3] = {
    1, 2, 4,
};

/* read by * Hit handler of the ov166 enemy (x3: ov166/167/168): copies the hit point into +0x2c and  (020d4038): const u8 data_ov168_020d635c[]; */
const u8 data_ov168_020d635c[4] = {
    2, 3, 0, 1,
};
