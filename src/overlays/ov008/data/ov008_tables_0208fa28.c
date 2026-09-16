/* ov008 .rodata tables, 0x0208fa28-0x0208fd58.
 *
 * 20 contiguous tables, each written in the width its contents are in:
 * words where the values are small integers, bytes where the words are
 * packed bytes.
 *
 * Readers:
 *   data_ov008_0208fa28: func_ov008_02076158
 *   data_ov008_0208fa38: func_ov008_02077d64
 *   data_ov008_0208fa4c: func_ov008_0207733c
 *   data_ov008_0208fa74: func_ov008_0207733c
 *   data_ov008_0208fa9c: func_ov008_0207733c
 *   data_ov008_0208fac4: func_ov008_0207733c
 *   data_ov008_0208faec: func_ov008_0207733c
 *   data_ov008_0208fb14: func_ov008_0207733c
 *   data_ov008_0208fb3c: func_ov008_02076158
 *   data_ov008_0208fb6c: func_ov008_02078c48
 *   data_ov008_0208fc84: func_ov008_0207ab50
 *   data_ov008_0208fc8c: func_ov008_0207bfe8, func_ov008_0207d888
 *   data_ov008_0208fc9c: func_ov008_0207bcdc
 *   data_ov008_0208fc9d: func_ov008_0207bcdc
 *   data_ov008_0208fc9e: func_ov008_0207bcdc
 *   data_ov008_0208fc9f: func_ov008_0207bcdc
 *   data_ov008_0208fca0: func_ov008_0207bcdc
 *   data_ov008_0208fca3: func_ov008_0207bcdc
 *   data_ov008_0208fca4: func_ov008_0207bcdc
 *   data_ov008_0208fd48: func_ov008_0207dfec
 */

typedef unsigned char u8;
typedef unsigned short u16;

const int data_ov008_0208fa28[4] = {
    47, 44, 45, 46,
};

const int data_ov008_0208fa38[5] = {
    1, 2, 11, 12, 13,
};

const int data_ov008_0208fa4c[10] = {
    1, 24, 2, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov008_0208fa74[10] = {
    1, 21, 5, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov008_0208fa9c[10] = {
    0, 2, 25, 30, 1, 0, 0, 22,
    0, 32,
};

const int data_ov008_0208fac4[10] = {
    22, 0, 32, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov008_0208faec[10] = {
    3, 5, 20, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov008_0208fb14[10] = {
    1, 5, 18, 2, 352, 8, 0, 20,
    0, 32,
};

const int data_ov008_0208fb3c[12] = {
    1100, 1105, 1104, 1101, 1103, 1106, 1100, 1100,
    1107, 1102, 1100, 1100,
};

const int data_ov008_0208fb6c[70] = {
    0, 2, 22, 3, 1, 15, 0, 23,
    0, 32, 0, 25, 6, 3, 67, 15,
    0, 23, 0, 32, 3, 2, 28, 4,
    85, 15, 0, 23, 0, 32, 20, 2,
    28, 3, 197, 15, 0, 23, 0, 32,
    8, 18, 13, 4, 197, 15, 0, 23,
    0, 32, 13, 18, 13, 4, 249, 15,
    0, 23, 0, 32, 19, 18, 13, 4,
    301, 15, 0, 23, 0, 32,
};

const u8 data_ov008_0208fc84[8] = {
    255, 255, 255, 255, 255, 255, 0, 0,
};

const u8 data_ov008_0208fc8c[16] = {
    4, 5, 7, 255, 255, 255, 6, 1, 3, 2, 15, 0, 8, 0, 0, 0,
};

const u8 data_ov008_0208fc9c[1] = {
    8,
};

const u8 data_ov008_0208fc9d[1] = {
    8,
};

const u8 data_ov008_0208fc9e[1] = {
    4,
};

const u8 data_ov008_0208fc9f[1] = {
    4,
};

const u8 data_ov008_0208fca0[3] = {
    6, 1, 5,
};

const u8 data_ov008_0208fca3[1] = {
    5,
};

const u8 data_ov008_0208fca4[164] = {
    5, 3, 3, 3, 1, 4, 6, 5, 10, 2, 6, 4, 5, 3, 4, 4,
    5, 5, 4, 3, 8, 4, 6, 4, 5, 5, 3, 2, 10, 1, 10, 2,
    10, 7, 5, 1, 8, 2, 9, 1, 1, 1, 6, 5, 7, 10, 6, 3,
    4, 10, 7, 4, 5, 4, 10, 6, 5, 4, 5, 5, 6, 5, 6, 5,
    4, 7, 3, 4, 4, 7, 5, 5, 3, 4, 6, 5, 4, 4, 5, 5,
    5, 5, 7, 6, 3, 7, 6, 8, 5, 3, 7, 3, 7, 2, 3, 3,
    5, 5, 10, 1, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
    5, 5, 5, 5, 5, 5, 5, 8, 4, 8, 3, 10, 5, 5, 7, 5,
    5, 5, 5, 5, 5, 5, 5, 5, 5, 3, 5, 6, 6, 5, 5, 5,
    8, 1, 10, 1, 4, 1, 5, 5, 4, 3, 5, 1, 8, 4, 6, 5,
    5, 5, 5, 0,
};

const u8 data_ov008_0208fd48[16] = {
    17, 10, 18, 9, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0,
};
