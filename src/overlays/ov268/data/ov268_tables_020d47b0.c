/* ov268 .rodata tables, 0x020d47b0-0x020d4800.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov268_020cfc80 (not yet decompiled) */
const int data_ov268_020d47b0[5] = {
    0, 20, 21, 22, 23,
};

/* read by * func_ov268_020d0698 -- x3. Message handler: map the message kind through a 15-entry tabl (020d0698): struct t15 data_ov268_020d47c4; */
const int data_ov268_020d47c4[15] = {
    1, 2, 3, 4, 5, 6, 7, 8,
    9, 10, 11, 12, 13, 14, 15,
};
