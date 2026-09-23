/* ov260 .rodata tables, 0x020d2a3c-0x020d2a90.
 *
 * 4 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

/* read by func_ov260_020cc0b4 (not yet decompiled) */
const int data_ov260_020d2a3c[12] = {
    36, 37, 41, 45, 46, 47, 48, 50,
    51, 52, 53, 54,
};

/* read by func_ov260_020ccbec (not yet decompiled) */
const u8 data_ov260_020d2a6c[20] = {
    2, 3, 0, 1, 0, 48, 0, 0, 80, 5, 0, 0, 80, 5, 0, 0,
    0, 64, 0, 0,
};

/* read by Ov260_SubPartAConstruct (020d0a58): IdTable2 data_ov260_020d2a80; */
const int data_ov260_020d2a80[2] = {
    43, 44,
};

/* read by Ov260_SubPartBConstruct (020d1858): IdTable2 data_ov260_020d2a88; */
const int data_ov260_020d2a88[2] = {
    39, 40,
};
