/* ov005 .rodata tables, 0x0205b38c-0x0205b39c.
 *
 * 1 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Transfer each dirty result row buffer, then clear the dirty mask. (02056fd0): const int data_ov005_0205b38c[4]; */
const int data_ov005_0205b38c[4] = {
    24, 25, 26, 27,
};
