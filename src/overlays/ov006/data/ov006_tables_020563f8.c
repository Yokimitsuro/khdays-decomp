/* ov006 .data tables, 0x020563f8-0x02056508.
 *
 * 3 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 */

typedef unsigned char u8;
typedef unsigned short u16;

int data_ov006_020563f8[6] = {
    13, 16, 15, 14, 17, 18,
};

int data_ov006_02056410[2][12] = {
    { -2, -2, -1, 0, 1, 2, 3, 4, 5, 6, -1, -2 },
    { -2, -1, -1, 7, 8, 9, 10, 11, 12, -1, -1, -2 },
};

int data_ov006_02056470[38] = {
    0, 2,
    0, 3,
    0, 4,
    0, 5,
    0, 6,
    0, 7,
    0, 8,
    0, 9,
    0, 10,
    1, 1,
    1, 2,
    1, 3,
    1, 4,
    1, 5,
    1, 6,
    1, 7,
    1, 8,
    1, 9,
    1, 10,
};
