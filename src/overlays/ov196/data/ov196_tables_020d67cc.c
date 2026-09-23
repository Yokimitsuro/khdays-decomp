/* ov196 .rodata tables, 0x020d67cc-0x020d6848.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov194 enemy (x3: ov194/195/196): installs the handlers (+8 tick, +0xc (020d3844): struct Ov194Vec3 data_ov196_020d67cc; */
const int data_ov196_020d67cc[3] = {
    2, 3, 4,
};

/* read by func_ov196_020d5a48 (020d5a48): unsigned short data_ov196_020d67d8[]; */
const u8 data_ov196_020d67d8[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020d6280): const Vec3 data_ov196_020d67e8; */
const u8 data_ov196_020d67e8[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0,
};

/* read by Swing tick of the ov194 enemy (and its byte-identical twin): the +0x14 turn step is zeroed (020d56d4): const PosMsg data_ov196_020d67f4; */
const u16 data_ov196_020d67f4[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020d6280): const struct Msg14 data_ov196_020d6802; */
const u16 data_ov196_020d6802[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020d50a4): const struct Msg14 data_ov196_020d6810; */
const u8 data_ov196_020d6810[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020d50a4): const struct Msg20 data_ov196_020d6820; */
const u8 data_ov196_020d6820[20] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020d6280): const struct Msg20 data_ov196_020d6834; */
const u8 data_ov196_020d6834[20] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
