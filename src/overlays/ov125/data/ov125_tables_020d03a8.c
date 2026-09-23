/* ov125 .rodata tables, 0x020d03a8-0x020d0424.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Ov125_Construct (020cbfc4): IdTable data_ov125_020d03a8; */
const int data_ov125_020d03a8[9] = {
    1, 2, 3, 3, 4, 6, 7, 7,
    8,
};

/* read by Ov125_EnterRecover (020cdd3c): unsigned short data_ov125_020d03cc[];
 *   Ov125_RecoverTick (020cde04): unsigned short data_ov125_020d03cc[];
 *   func_ov125_020ce1a8 (not yet decompiled) */
const u8 data_ov125_020d03cc[16] = {
    0, 0, 5, 2, 0, 0, 5, 5, 0, 0, 5, 1, 0, 0, 5, 3,
};

/* read by Ov125_BeamTick (020ceb74): Cmd14 data_ov125_020d03dc; */
const u16 data_ov125_020d03dc[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov125_BeamWindDownTick (020cf1cc): Cmd14 data_ov125_020d03ea; */
const u16 data_ov125_020d03ea[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov125_SpinStrikeTick (020cfde8): struct Ov125Cmd data_ov125_020d03f8; */
const u16 data_ov125_020d03f8[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov125_SpinStrikeTick (020cfde8): struct Ov125Cmd data_ov125_020d0406; */
const u16 data_ov125_020d0406[7] = {
    0, 5, 0, 0, 0, 0, 0,
};

/* read by Ov125_SpinStrikeTick (020cfde8): struct Ov125Cmd data_ov125_020d0414; */
const u8 data_ov125_020d0414[16] = {
    0, 0, 5, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
