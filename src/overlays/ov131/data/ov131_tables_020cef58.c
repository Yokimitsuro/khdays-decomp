/* ov131 .rodata tables, 0x020cef58-0x020cefcc.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov131_020cbfc4 (020cbfc4): struct v5 data_ov131_020cef58; */
const int data_ov131_020cef58[5] = {
    2, 3, 4, 5, 6,
};

/* read by func_ov131_020cd8d8 (020cd8d8): unsigned short data_ov131_020cef6c[];
 *   func_ov131_020cdf20 (020cdf20): unsigned short data_ov131_020cef6c[]; */
const u8 data_ov131_020cef6c[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by func_ov131_020ce2b4 (020ce2b4): const struct Msg data_ov131_020cef74; */
const u16 data_ov131_020cef74[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov131_020cd9a4 (020cd9a4): const struct Msg data_ov131_020cef82; */
const u16 data_ov131_020cef82[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov131_020ce2b4 (020ce2b4): const struct Msg data_ov131_020cef90; */
const u16 data_ov131_020cef90[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by func_ov131_020ce0e8 (020ce0e8): const struct Msg data_ov131_020cef9e; */
const u16 data_ov131_020cef9e[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov131_020cc68c (020cc68c): const struct tbl8 data_ov131_020cefac; */
const u8 data_ov131_020cefac[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
