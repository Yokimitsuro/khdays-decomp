/* ov115 .rodata tables, 0x020ceb38-0x020ceb7c.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov115_020cc020 (020cc020): void data_ov115_020ceb38(void); */
const int data_ov115_020ceb38[7] = {
    1, 2, 4, 5, 6, 7, 3,
};

/* read by func_ov115_020cc9bc (020cc9bc): void data_ov115_020ceb54(void); */
const u16 data_ov115_020ceb54[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov115_020cc9bc (020cc9bc): void data_ov115_020ceb62(void); */
const u16 data_ov115_020ceb62[7] = {
    0, 517, 0, 0, 0, 0, 0,
};

/* read by * Hit handler of the ov115 enemy (and its byte-identical twins): copies the hit point into (020cce38): const u8 data_ov115_020ceb70[];
 *   func_ov115_020ce5dc (020ce5dc): void data_ov115_020ceb70(void); */
const u8 data_ov115_020ceb70[12] = {
    0, 1, 2, 3, 0, 0, 5, 0, 0, 0, 0, 0,
};
