/* ov011 .rodata tables, 0x0205dc7c-0x0205dc90.
 *
 * 2 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov011_0205bb58 (0205bb58): void data_ov011_0205dc7c(void); */
const u16 data_ov011_0205dc7c[3] = {
    255, 65289, 0,
};

/* read by func_ov011_0205cda0 (0205cda0): void data_ov011_0205dc82(void); */
const u16 data_ov011_0205dc82[7] = {
    10, 22, 10, 255, 65280, 6144, 0,
};
