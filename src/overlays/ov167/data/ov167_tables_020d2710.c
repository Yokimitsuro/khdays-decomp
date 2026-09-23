/* ov167 .rodata tables, 0x020d2710-0x020d2720.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov166 enemy (x3: ov166/167/168). Installs the handlers (+8 release, +0x (020cfc60): IdTable data_ov167_020d2710; */
const int data_ov167_020d2710[3] = {
    1, 2, 4,
};

/* read by * Hit handler of the ov166 enemy (x3: ov166/167/168): copies the hit point into +0x2c and  (020d03f8): const u8 data_ov167_020d271c[]; */
const u8 data_ov167_020d271c[4] = {
    2, 3, 0, 1,
};
