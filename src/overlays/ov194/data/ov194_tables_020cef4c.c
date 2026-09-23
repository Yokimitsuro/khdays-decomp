/* ov194 .rodata tables, 0x020cef4c-0x020cefc8.
 *
 * 8 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by Constructor of the ov194 enemy (x3: ov194/195/196): installs the handlers (+8 tick, +0xc (020cbfc4): struct Ov194Vec3 data_ov194_020cef4c; */
const int data_ov194_020cef4c[3] = {
    2, 3, 4,
};

/* read by func_ov194_020ce1c8 (020ce1c8): unsigned short data_ov194_020cef58[]; */
const u8 data_ov194_020cef58[16] = {
    0, 0, 5, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 20, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020cea00): const Vec3 data_ov194_020cef68; */
const u8 data_ov194_020cef68[12] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 40, 0, 0,
};

/* read by Swing tick of the ov194 enemy (and its byte-identical twin): the +0x14 turn step is zeroed (020cde54): const PosMsg data_ov194_020cef74; */
const u16 data_ov194_020cef74[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020cea00): const struct Msg14 data_ov194_020cef82; */
const u16 data_ov194_020cef82[7] = {
    0, 261, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020cd824): const struct Msg14 data_ov194_020cef90; */
const u8 data_ov194_020cef90[16] = {
    0, 0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

/* read by Charge tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020cd824): const struct Msg20 data_ov194_020cefa0; */
const u8 data_ov194_020cefa0[20] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};

/* read by Combo tick of the ov194 enemy (x3: ov194/195/196). Until the +0x53 one-shot fires, (020cea00): const struct Msg20 data_ov194_020cefb4; */
const u8 data_ov194_020cefb4[20] = {
    0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0,
};
