/* ov042 .rodata tables, 0x020b46f4-0x020b473c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by * Attack step: the per-frame body of the ov042 enemy's attack state. (020b38d4): PermTable data_ov042_020b46f4; */
const int data_ov042_020b46f4[18] = {
    0, 1, 2, 0, 2, 1, 1, 0,
    2, 1, 2, 0, 2, 0, 1, 2,
    1, 0,
};
