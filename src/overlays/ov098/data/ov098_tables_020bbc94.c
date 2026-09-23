/* ov098 .rodata tables, 0x020bbc94-0x020bbcdc.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * Attack step: the per-frame body of the ov042 enemy's attack state. (020bae74): PermTable data_ov098_020bbc94; */
const int data_ov098_020bbc94[18] = {
    0, 1, 2, 0, 2, 1, 1, 0,
    2, 1, 2, 0, 2, 0, 1, 2,
    1, 0,
};
