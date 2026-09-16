/* ov008 .data tables, 0x0209092c-0x02090990.
 *
 * 7 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0209092c: func_ov008_02074c40
 *   data_ov008_02090930: func_ov008_02074c40
 *   data_ov008_02090954: func_ov008_02074c40
 *   data_ov008_02090960: func_ov008_02074c40
 *   data_ov008_02090978: func_ov008_020759c4
 *   data_ov008_0209097c: func_ov008_020759c4
 *   data_ov008_02090980: func_ov008_02076780
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov008_0209092c[1] = {
    10,
};

u8 data_ov008_02090930[36] = {
    37, 0, 115, 0, 32, 0, 37, 0, 48, 0, 50, 0, 100, 0, 58, 0,
    37, 0, 48, 0, 50, 0, 100, 0, 58, 0, 37, 0, 48, 0, 50, 0,
    100, 0, 0, 0,
};

u8 data_ov008_02090954[12] = {
    37, 0, 115, 0, 32, 0, 37, 0, 100, 0, 0, 0,
};

u8 data_ov008_02090960[24] = {
    37, 0, 115, 0, 32, 0, 45, 0, 45, 0, 45, 0, 45, 0, 45, 0,
    45, 0, 45, 0, 45, 0, 0, 0,
};

int data_ov008_02090978[1] = {
    32,
};

int data_ov008_0209097c[1] = {
    47,
};

u8 data_ov008_02090980[16] = {
    37, 0, 48, 0, 50, 0, 100, 0, 37, 0, 99, 0, 0, 0, 0, 0,
};
