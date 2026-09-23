/* ov134 .rodata tables, 0x020cdf78-0x020cdfc0.
 *
 * 5 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov134_020cbfc4 (020cbfc4): struct v5 data_ov134_020cdf78; */
const int data_ov134_020cdf78[3] = {
    2, 3, 4,
};

/* read by func_ov134_020cdd90 (020cdd90): unsigned short data_ov134_020cdf84[]; */
const u8 data_ov134_020cdf84[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0,
};

/* read by * func_ov134_020cd52c -- burst attack tick of the ov134 enemy (and its byte-identical twin (020cd52c): struct Ov134AreaMsg data_ov134_020cdf94; */
const u16 data_ov134_020cdf94[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by * func_ov134_020cd52c -- burst attack tick of the ov134 enemy (and its byte-identical twin (020cd52c): struct Ov134AreaMsg data_ov134_020cdfa2; */
const u16 data_ov134_020cdfa2[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Attack tick of the ov134 enemy (x3: ov134/135/136). Counts the +0x30 timer and fires react (020cda54): const struct Msg data_ov134_020cdfb0; */
const u8 data_ov134_020cdfb0[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
