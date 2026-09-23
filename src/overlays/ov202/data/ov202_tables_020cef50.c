/* ov202 .rodata tables, 0x020cef50-0x020cefc4.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cbfc8): struct v5 data_ov202_020cef50; */
const int data_ov202_020cef50[5] = {
    2, 3, 4, 5, 6,
};

/* read by func_ov202_020cd898 (020cd898): unsigned short data_ov202_020cef64[];
 *   recoil entry of the ov202 enemy (x2), variant of the matched ov132 sibling (+0x60 bit 6 cl (020cdee0): unsigned short data_ov202_020cef64[]; */
const u8 data_ov202_020cef64[8] = {
    0, 0, 5, 0, 0, 0, 5, 4,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020ce280): const struct Msg data_ov202_020cef6c; */
const u16 data_ov202_020cef6c[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020cd964): const struct Msg data_ov202_020cef7a; */
const u16 data_ov202_020cef7a[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020ce280): const struct Msg data_ov202_020cef88; */
const u16 data_ov202_020cef88[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by ported from a matched sibling family (same shape, constants and offsets adjusted). (020ce0b4): const struct Msg data_ov202_020cef96; */
const u16 data_ov202_020cef96[7] = {
    0, 773, 0, 0, 0, 0, 0,
};

/* read by func_ov202_020cc668 (020cc668): const struct tbl8 data_ov202_020cefa4; */
const u8 data_ov202_020cefa4[32] = {
    255, 255, 255, 255, 255, 255, 255, 255, 1, 0, 0, 0, 255, 255, 255, 255,
    255, 255, 255, 255, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0,
};
